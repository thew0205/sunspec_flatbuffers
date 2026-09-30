#!python3
"""
Compares the three SunSpec model-definition backends -- c_define (native
C++ struct/vector literals, compiled in), json (jsmn-tokenized JSON text,
parsed at runtime), and flatbuffers (a pre-compiled FlatBuffers binary blob,
read via zero-copy accessors) -- across:

  - flash usage      (.text size, from `size`, both raw and net of the
                       "noop" baseline, which links none of libsunspec.a)
  - static RAM usage  (.data + .bss, from `size`, raw and net of "noop")
  - dynamic (heap) memory usage:
      * heap_peak_bytes       -- true peak live heap at any point during
                                  the run, measured externally with
                                  `valgrind --tool=massif` (blank if
                                  valgrind isn't installed, or --no-massif
                                  was passed)
      * heap_net_growth_bytes -- heap growth that persists across 2000
                                  repeated calls, sampled in-process via
                                  glibc mallinfo2() around each call (a
                                  leak/caching indicator -- 0 means
                                  everything a call allocates, it frees)
      * heap_peak_call_bytes  -- largest single-call increase in
                                  mallinfo2()'s uordblks seen across those
                                  2000 calls; cheap, no-tool-required
                                  cross-check, but it under-reports true
                                  peak whenever a call allocates and frees
                                  again before returning -- that's what
                                  heap_peak_bytes (massif) is for.
  - stack usage per call (gcc's -fstack-usage frame size, max across every
    function defined in the variant's own .cpp file -- own frame only, not
    non-inlined callees; the flag is already enabled in CMakeLists.txt)
  - model-lookup timing   (net time of the "load_only" variant: just
    getModelDefinition(160), no tree walk)
  - shallow-walk timing   (net time of "walk_shallow" minus "load_only" --
    isolates the cost of reading every accessor on the top-level group's
    own points)
  - deep-walk timing      (net time of "walk_deep" minus "load_only" --
    same, but recursively over every nested subgroup too; model 160 has a
    repeating "module" subgroup, so this is meaningfully more work than
    walk_shallow)

Methodology: every metric is reported net of the "noop" binary (touches
nothing from the sunspec library, so the linker pulls none of it in), which
cancels out the cost of the harness itself (timed loop / mallinfo2 pass /
process startup). This mirrors research_experiment/power_meter/analysis.py.

Each backend is a library-wide compile-time choice (src/CMakeLists.txt's
SUNSPEC_FLATBUFFERS_IMPLEMENTATION / SUNSPEC_JSON_IMPLEMENTATION switches),
so this script drives three separate configure+build cycles -- one per
backend, each into its own build_<backend> directory -- rather than three
targets in one build like power_meter's independent serialization formats.

--target mode runs the identical comparison on real Pico2 (RP2350) hardware
instead of as a native host process: each variant is built as a .uf2 via
experiment/target's CMakeLists (same harness_main.cpp logic, only stdio and
a board-idle loop differ -- see experiment/target/harness_main.cpp), flashed
and executed with `picotool`, and its JSON result line(s) read back over USB
serial with `tio`. flash/RAM/stack numbers come from `size`/-fstack-usage on
the .elf exactly as in host mode; heap numbers come from the same in-firmware
mallinfo() sampling; there is no massif pass (no valgrind on target), so
heap_peak_bytes is always blank in --target mode.

Note on re-flashing: picotool's remote force-reboot-into-BOOTSEL (`load -fx`
/ `reboot -f -u`) relies on the RP2350's USB "reset via vendor interface",
which was found to be unreliable on the hardware this was developed against
-- it would report success without the board actually re-entering BOOTSEL.
flash_target() tries it first (cheap, sometimes works) but falls back to
polling for the board to appear in BOOTSEL mode and prints a prompt asking
for a manual BOOTSEL press if it doesn't show up quickly. Once flashed, a
variant's harness computes its result once and then reprints the same JSON
line once a second forever (see harness_main.cpp) -- both so a capture
attached at an arbitrary time doesn't have to win a race against a single
post-boot print, and so repeated --runs samples for one variant don't each
need a fresh (currently unreliable) reboot: capture_target_json() just keeps
one serial session open long enough to collect that many lines.

Usage:
    ./analyze_backends.py [--runs N] [--no-massif] [--out-dir DIR]
    ./analyze_backends.py --target [--runs N] [--port /dev/ttyACM0] [--out-dir DIR]
"""

import argparse
import csv
import glob
import json
import os
import re
import shutil
import subprocess
import tempfile
import time
import serial

PWD = os.path.dirname(os.path.abspath(__file__))
SUNSPEC_ROOT_DIR = os.path.dirname(PWD)
HOST_SOURCE_DIR = os.path.join(PWD, "host")
TARGET_SOURCE_DIR = os.path.join(PWD, "target")

BACKENDS = ["json", "c_define", "flatbuffers"]
VARIANTS = ["noop", "load_only", "walk_shallow", "walk_deep"]

# RP2040 / RP2350 BOOTSEL-mode USB VID:PID pairs (lsusb output), used to
# detect when the board is sitting in the boot ROM rather than running an
# application.
_BOOTSEL_USB_IDS = ("2e8a:0003", "2e8a:000f")


def _find_picotool():
    """picotool isn't on PATH in this project's setup (see
    tools/dual_target_test_build_run.sh, which hardcodes the same
    ${HOME}/.pico-sdk/picotool/<version>/picotool/picotool layout) -- probe
    the versions the Pico VS Code extension installs, newest first."""
    base = os.path.join(os.path.expanduser("~"), ".pico-sdk", "picotool")
    for version in ("2.3.1", "2.2.0", "2.2.0-a4", "2.1.1"):
        candidate = os.path.join(base, version, "picotool", "picotool")
        if os.path.isfile(candidate):
            return candidate
    found = shutil.which("picotool")
    if found:
        return found
    raise SystemExit("picotool not found (checked ~/.pico-sdk/picotool/* and PATH)")

SUMMARY_COLUMNS = [
    "backend", "variant", "time_ns_net", "flash_bytes", "flash_bytes_net",
    "static_ram_bytes", "static_ram_bytes_net", "heap_peak_bytes",
    "heap_net_growth_bytes", "heap_peak_call_bytes_cheap", "stack_bytes_per_call",
]
DECOMPOSED_COLUMNS = [
    "backend", "model_lookup_ns", "shallow_walk_ns", "deep_walk_ns", "nested_subgroup_extra_ns",
]


def sh(cmd, cwd=None) -> str:
    """Run a command and raise on failure (like set -e)."""
    print(f"+ {' '.join(cmd)}")
    result = subprocess.run(cmd, cwd=cwd, check=True, capture_output=True, text=True)
    return result.stdout


def build_dir_for(backend):
    return os.path.join(PWD, f"build_{backend}")


def configure_and_build(backend):
    bdir = build_dir_for(backend)
    sh(["cmake", "-S", HOST_SOURCE_DIR, "-B", bdir,
        f"-DSUNSPEC_ROOT_DIR={SUNSPEC_ROOT_DIR}", f"-DBACKEND={backend}"])
    sh(["cmake", "--build", bdir, "-j12"])


# --- target (Pico2 hardware) support --------------------------------------

def target_build_dir_for(backend):
    return os.path.join(PWD, f"build_target_{backend}")


def configure_and_build_target(backend):
    bdir = target_build_dir_for(backend)
    sh(["cmake", "-S", TARGET_SOURCE_DIR, "-B", bdir, "-GNinja",
        f"-DSUNSPEC_ROOT_DIR={SUNSPEC_ROOT_DIR}", f"-DBACKEND={backend}"])
    sh(["cmake", "--build", bdir, "-j12"])


def _lsusb_output():
    return subprocess.run(["lsusb"], capture_output=True, text=True).stdout


def device_in_bootsel() -> bool:
    out = _lsusb_output()
    return any(usb_id in out for usb_id in _BOOTSEL_USB_IDS)


def wait_for_bootsel(picotool, timeout=60):
    """Blocks until an RP2040/RP2350 in BOOTSEL mode is visible on the USB
    bus. Tries picotool's own remote force-reboot first (cheap, and works on
    hardware where the RP2350's USB reset-via-vendor-interface responds);
    if that doesn't land the board in BOOTSEL within a couple of seconds,
    prints a prompt and just polls, so a manual BOOTSEL press (hold BOOTSEL,
    tap RESET or replug) picks up automatically instead of the whole run
    hanging silently."""
    if device_in_bootsel():
        return
    subprocess.run([picotool, "reboot", "-f", "-u"], capture_output=True, text=True)
    deadline = time.time() + timeout
    prompted = False
    while time.time() < deadline:
        if device_in_bootsel():
            return
        if not prompted and time.time() > deadline - timeout + 3:
            print("  picotool's remote BOOTSEL reset didn't take -- please "
                  "hold BOOTSEL and tap RESET (or replug while holding "
                  "BOOTSEL) on the Pico2 now...")
            prompted = True
        time.sleep(0.3)
    raise SystemExit("Timed out waiting for the Pico2 to enter BOOTSEL mode.")


def find_serial_port(timeout=15) -> str:
    deadline = time.time() + timeout
    while time.time() < deadline:
        ports = sorted(glob.glob("/dev/ttyACM*"))
        if ports:
            return ports[0]
        time.sleep(0.2)
    raise SystemExit("No /dev/ttyACM* serial device appeared after flashing "
                      "(is stdio_usb enabled and the board plugged in?)")


def flash_target(picotool, uf2_path):
    """Puts the board in BOOTSEL (see wait_for_bootsel) and loads+executes
    uf2_path. Always goes through the explicit wait_for_bootsel() step first
    -- `picotool load -fx` alone was found to sometimes report success
    without the board actually re-entering BOOTSEL, silently leaving the
    previous firmware running."""
    wait_for_bootsel(picotool)
    sh([picotool, "load", "-fx", uf2_path])

def reboot_target(picotool):
    """Puts the board in BOOTSEL (see wait_for_bootsel) and loads+executes
    uf2_path. Always goes through the explicit wait_for_bootsel() step first
    -- `picotool load -fx` alone was found to sometimes report success
    without the board actually re-entering BOOTSEL, silently leaving the
    previous firmware running."""
    sh([picotool, "reboot", "-f"])


def capture_target_json(runs, picotool, settle_s=3, period_s=1.0) -> list:
    """The flashed harness computes its result once, then reprints the same
    JSON line once a second forever (see harness_main.cpp's rationale
    comment) -- so rather than reboot between samples (unreliable, see
    flash_target), this just keeps one `tio` session open long enough to
    collect `runs` lines and returns them all, mirroring run_binary()'s
    list-of-dicts shape for build_summary_rows()/build_decomposed_rows().
    The first `settle_s` seconds of output are discarded: that's the
    firmware's own stdio_init_all()+sleep_ms(2000) settle window plus the
    one-off timed/heap test passes, during which a partial line could be
    caught mid-connect."""
    port = find_serial_port()
    capture_s = settle_s + int(round(period_s)) + 3000
    # result = subprocess.run(
    #     ["timeout", str(capture_s), "tio", "-b", "115200", "--timestamp", port],
    #     capture_output=True, text=True)
    # Configure the serial port with a 1-second read timeout
    samples = []
    for _ in range(runs):
        captured_lines = []
        reboot_target(picotool)
        time.sleep(1)

        with serial.Serial(port, 115200, timeout=1) as ser:
            start_time = time.time()
            i = 0
            # Read data for exactly 10 seconds
            while time.time() - start_time < capture_s and i < 2:
                line = ser.readline().decode('utf-8', errors='ignore')
                if line:
                    # Recreate the timestamp look if needed
                    timestamp = time.strftime("[%Y-%m-%d %H:%M:%S]")
                    captured_lines.append(f"{timestamp} {line}")
                    i += 1


        results = []
        for line in captured_lines:
            # tio prefixes each line with "[HH:MM:SS.mmm] "; strip that and any
            # other leading log-style bracket before trying to parse JSON.
            brace = line.find("{")
            if brace == -1:
                continue
            try:
                results.append(json.loads(line[brace:]))
            except json.JSONDecodeError:
                continue

        if not results:
            raise SystemExit(
                f"No JSON lines captured from {port} within {capture_s}s "
                "(flashed firmware never printed, or tio couldn't read it).")   
        # Drop anything caught during the settle window, then take the last
        # `runs` samples (all identical in practice -- deterministic firmware,
        # no OS scheduling jitter -- but this keeps the shape host mode has).
        samples.append(results[-1]) 
    return samples

# def capture_target_json(runs, settle_s=3, period_s=1.0) -> list:
#     """The flashed harness computes its result once, then reprints the same
#     JSON line once a second forever (see harness_main.cpp's rationale
#     comment) -- so rather than reboot between samples (unreliable, see
#     flash_target), this just keeps one `tio` session open long enough to
#     collect `runs` lines and returns them all, mirroring run_binary()'s
#     list-of-dicts shape for build_summary_rows()/build_decomposed_rows().
#     The first `settle_s` seconds of output are discarded: that's the
#     firmware's own stdio_init_all()+sleep_ms(2000) settle window plus the
#     one-off timed/heap test passes, during which a partial line could be
#     caught mid-connect."""
#     port = find_serial_port()
#     capture_s = settle_s + int(round(runs * period_s)) + 3
#     result = subprocess.run(
#         ["timeout", str(capture_s), "tio", "-b", "115200", "--timestamp", port],
#         capture_output=True, text=True)

#     results = []
#     for line in result.stdout.splitlines():
#         # tio prefixes each line with "[HH:MM:SS.mmm] "; strip that and any
#         # other leading log-style bracket before trying to parse JSON.
#         brace = line.find("{")
#         if brace == -1:
#             continue
#         try:
#             results.append(json.loads(line[brace:]))
#         except json.JSONDecodeError:
#             continue

#     if not results:
#         raise SystemExit(
#             f"No JSON lines captured from {port} within {capture_s}s "
#             "(flashed firmware never printed, or tio couldn't read it).")
#     # Drop anything caught during the settle window, then take the last
#     # `runs` samples (all identical in practice -- deterministic firmware,
#     # no OS scheduling jitter -- but this keeps the shape host mode has).
#     samples = results[-runs:] if len(results) >= runs else results
#     return samples

def collect_target(runs, picotool) -> dict:
    raw = {}
    for backend in BACKENDS:
        print(f"\n=== {backend} (target) ===")
        configure_and_build_target(backend)
        bdir = target_build_dir_for(backend)
        raw[backend] = {}
        for variant in VARIANTS:
            elf_path = os.path.join(bdir, f"experiment_{variant}.elf")
            uf2_path = os.path.join(bdir, f"experiment_{variant}.uf2")
            if not os.path.isfile(uf2_path):
                raise SystemExit(f"missing binary: {uf2_path} (did the build fail?)")

            print(f"  flashing {backend}/{variant}...")
            flash_target(picotool, uf2_path)
            program_results = capture_target_json(runs, picotool)
            size_results = parse_size(elf_path)
            stack_usage = find_stack_usage(backend, variant, bdir=bdir)

            raw[backend][variant] = {
                "program_results": program_results,
                "size_results": size_results,
                "stack_usage": stack_usage,
                "peak_heap_bytes": None,  # no valgrind on target
            }
            print(f"  done: {backend}/{variant}")
    return raw


def parse_size(binary_path) -> dict:
    out = sh(["size", binary_path])
    lines = out.strip().splitlines()
    headers = lines[0].split()
    values = lines[1].split(maxsplit=len(headers) - 1)
    return dict(zip(headers, values))


def find_stack_usage(backend, variant, bdir=None) -> dict:
    """Parses gcc's -fstack-usage .su file for this variant's own .cpp
    (not harness_main.cpp, which is shared and not variant-specific),
    returning the largest reported frame size per function signature.
    Each line is "file:line:col:signature\\tbytes\\tqualifier"; the
    signature itself may contain colons (namespaces, templates), so it's
    isolated with a bounded split rather than rsplit(":", 1).

    Each variant now builds as its own library (experiment_<variant>_lib)
    under experiment/common/CMakeLists.txt, not compiled directly into the
    executable's own CMakeFiles dir, so the .su file lives under the
    build tree's common/ subdirectory. bdir defaults to the host build dir;
    --target mode passes its own build_target_<backend> dir."""
    if bdir is None:
        bdir = build_dir_for(backend)
    su_path = os.path.join(
        bdir, "common", "CMakeFiles",
        f"experiment_{variant}_lib.dir", f"{variant}.cpp.su")
    stack = {}
    if not os.path.isfile(su_path):
        return stack
    with open(su_path) as fh:
        for line in fh:
            line = line.strip()
            if not line:
                continue
            parts = line.split("\t")
            if len(parts) != 3:
                continue
            loc, bytes_str, _qualifier = parts
            loc_parts = loc.split(":", 3)
            signature = loc_parts[3] if len(loc_parts) == 4 else loc
            try:
                n = int(bytes_str)
            except ValueError:
                continue
            stack[signature] = max(stack.get(signature, 0), n)
    return stack


def max_stack_bytes(stack: dict) -> int:
    return max(stack.values(), default=0)


def run_binary(binary_path, runs) -> list:
    results = []
    for _ in range(runs):
        out = sh([binary_path])
        results.append(json.loads(out.strip().splitlines()[-1]))
    return results


def run_massif(binary_path):
    """Peak live heap bytes over the whole run, via valgrind's massif tool.
    Returns None if valgrind isn't available or the run couldn't be parsed."""
    if shutil.which("valgrind") is None:
        return None
    with tempfile.TemporaryDirectory() as td:
        out_file = os.path.join(td, "massif.out")
        cmd = [
            "valgrind", "--tool=massif", "--pages-as-heap=no", "-q",
            f"--massif-out-file={out_file}", binary_path,
        ]
        subprocess.run(cmd, capture_output=True, text=True)
        if not os.path.isfile(out_file):
            return None
        with open(out_file) as fh:
            content = fh.read()
        values = [int(v) for v in re.findall(r"mem_heap_B=(\d+)", content)]
        return max(values) if values else 0


def collect(runs, use_massif) -> dict:
    raw = {}
    for backend in BACKENDS:
        print(f"\n=== {backend} ===")
        configure_and_build(backend)
        bdir = build_dir_for(backend)
        raw[backend] = {}
        for variant in VARIANTS:
            binary_path = os.path.join(bdir, f"experiment_{variant}")
            if not os.path.isfile(binary_path):
                raise SystemExit(f"missing binary: {binary_path} (did the build fail?)")

            program_results = run_binary(binary_path, runs)
            size_results = parse_size(binary_path)
            stack_usage = find_stack_usage(backend, variant)
            peak_heap_bytes = run_massif(binary_path) if use_massif else None

            raw[backend][variant] = {
                "program_results": program_results,
                "size_results": size_results,
                "stack_usage": stack_usage,
                "peak_heap_bytes": peak_heap_bytes,
            }
            print(f"  done: {backend}/{variant}")
    return raw


# --- per-entry accessors -----------------------------------------------

def avg(values):
    return sum(values) / len(values)


def flash_bytes(entry):
    return int(entry["size_results"]["text"])


def static_ram_bytes(entry):
    return int(entry["size_results"]["data"]) + int(entry["size_results"]["bss"])


def avg_time_us(entry):
    return avg([r["time_taken"] for r in entry["program_results"]])


def iterations(entry):
    return entry["program_results"][0]["iteration"]


def ns_per_iter(entry):
    return (avg_time_us(entry) / iterations(entry)) * 1000.0


def heap_net_growth(entry):
    return max(r.get("heap_net_growth_bytes", 0) for r in entry["program_results"])


def heap_peak_call(entry):
    return max(r.get("heap_peak_call_bytes", 0) for r in entry["program_results"])


# --- report building -----------------------------------------------------

def build_summary_rows(raw):
    rows = []
    for backend in BACKENDS:
        baseline = raw[backend]["noop"]
        base_ns = ns_per_iter(baseline)
        base_flash = flash_bytes(baseline)
        base_ram = static_ram_bytes(baseline)

        for variant in VARIANTS:
            entry = raw[backend][variant]
            rows.append({
                "backend": backend,
                "variant": variant,
                "time_ns_net": round(ns_per_iter(entry) - base_ns, 1),
                "flash_bytes": flash_bytes(entry),
                "flash_bytes_net": flash_bytes(entry) - base_flash,
                "static_ram_bytes": static_ram_bytes(entry),
                "static_ram_bytes_net": static_ram_bytes(entry) - base_ram,
                "heap_peak_bytes": entry["peak_heap_bytes"],
                "heap_net_growth_bytes": heap_net_growth(entry),
                "heap_peak_call_bytes_cheap": heap_peak_call(entry),
                "stack_bytes_per_call": max_stack_bytes(entry["stack_usage"]),
            })
    return rows


def build_decomposed_rows(raw):
    rows = []
    for backend in BACKENDS:
        base_ns = ns_per_iter(raw[backend]["noop"])
        load_ns = ns_per_iter(raw[backend]["load_only"]) - base_ns
        shallow_ns = ns_per_iter(raw[backend]["walk_shallow"]) - base_ns
        deep_ns = ns_per_iter(raw[backend]["walk_deep"]) - base_ns

        rows.append({
            "backend": backend,
            "model_lookup_ns": round(load_ns, 1),
            "shallow_walk_ns": round(shallow_ns - load_ns, 1),
            "deep_walk_ns": round(deep_ns - load_ns, 1),
            "nested_subgroup_extra_ns": round((deep_ns - load_ns) - (shallow_ns - load_ns), 1),
        })
    return rows


# --- output formatting -----------------------------------------------------

def print_table(rows, columns):
    widths = {
        c: max(len(c), max((len(str(r.get(c, ""))) for r in rows), default=0))
        for c in columns
    }
    print("  ".join(c.ljust(widths[c]) for c in columns))
    print("  ".join("-" * widths[c] for c in columns))
    for r in rows:
        print("  ".join(str(r.get(c, "")).ljust(widths[c]) for c in columns))


def write_csv(path, rows, columns):
    with open(path, "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=columns)
        w.writeheader()
        for r in rows:
            w.writerow(r)


def to_markdown_table(rows, columns):
    lines = ["| " + " | ".join(columns) + " |", "|" + "|".join(["---"] * len(columns)) + "|"]
    for r in rows:
        lines.append("| " + " | ".join(str(r.get(c, "")) for c in columns) + " |")
    return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--runs", type=int, default=5,
                         help="times to re-run each binary for timing (default: 5)")
    parser.add_argument("--no-massif", action="store_true",
                         help="skip the valgrind massif peak-heap pass (faster; "
                              "heap_peak_bytes will be blank)")
    parser.add_argument("--out-dir", default=None,
                         help="directory (relative to this script) to write "
                              "csv/json/markdown reports into (default: "
                              "analysis_output, or analysis_output_target "
                              "with --target)")
    parser.add_argument("--target", action="store_true",
                         help="run on real Pico2 hardware via picotool+tio "
                              "instead of as a native host process (see the "
                              "module docstring's '--target mode' section)")
    parser.add_argument("--picotool", default=None,
                         help="path to picotool (target mode only; default: "
                              "probe ~/.pico-sdk/picotool/*, then PATH)")
    args = parser.parse_args()

    out_dir_name = args.out_dir or ("analysis_output_target" if args.target else "analysis_output")
    out_dir = os.path.join(PWD, out_dir_name)
    os.makedirs(out_dir, exist_ok=True)

    if args.target:
        picotool = args.picotool or _find_picotool()
        raw = collect_target(args.runs, picotool)
    else:
        use_massif = not args.no_massif
        if use_massif and shutil.which("valgrind") is None:
            print("warning: valgrind not found on PATH -- heap_peak_bytes will be blank "
                  "(pass --no-massif to silence this warning)")
            use_massif = False

        raw = collect(args.runs, use_massif)

    with open(os.path.join(out_dir, "raw_results.json"), "w") as f:
        json.dump(raw, f, indent=2)

    summary_rows = build_summary_rows(raw)
    decomposed_rows = build_decomposed_rows(raw)

    print("\n" + "=" * 100)
    print("PER-VARIANT SUMMARY (time net of 'noop' baseline, ns/call; memory in bytes)")
    print("=" * 100)
    print_table(summary_rows, SUMMARY_COLUMNS)

    print("\n" + "=" * 100)
    print("TIMING DECOMPOSITION (net of 'noop' and of model lookup itself, ns/call)")
    print("=" * 100)
    print_table(decomposed_rows, DECOMPOSED_COLUMNS)

    write_csv(os.path.join(out_dir, "summary.csv"), summary_rows, SUMMARY_COLUMNS)
    write_csv(os.path.join(out_dir, "timing_decomposition.csv"), decomposed_rows, DECOMPOSED_COLUMNS)

    platform_note = (
        "This run is on **Pico2 (RP2350) hardware**: each variant was cross-compiled "
        "via experiment/target's CMakeLists, flashed and executed with `picotool`, "
        "and its result line(s) read back over USB serial with `tio` (see the "
        "module docstring's '--target mode' section). `heap_peak_bytes` is always "
        "blank here -- there's no valgrind on target, only the in-firmware "
        "`mallinfo()` sampling that also produces `heap_net_growth_bytes` / "
        "`heap_peak_call_bytes_cheap`. Since target execution has no OS scheduling "
        "jitter, repeated `--runs` samples of one flash are expected to be "
        "identical (or near enough); it's included mainly for parity with host "
        "mode's report shape.\n"
    ) if args.target else ""
    report = [
        "# SunSpec model-definition backend comparison\n",
        "Backends: `c_define` (native C++ struct/vector literals, compiled in), "
        "`json` (jsmn-tokenized JSON text parsed at runtime), `flatbuffers` "
        "(pre-compiled FlatBuffers binary blob, zero-copy accessors). All three "
        "expose the identical SunspecModelDef/SunspecGroupDef/SunspecPointDef "
        "accessor surface (see include/sunspec_adapter.h and CLAUDE.md's adapter "
        "pattern), so the same walk code (load_only.cpp / walk_shallow.cpp / "
        "walk_deep.cpp) runs unchanged against all three -- only which "
        "src/CMakeLists.txt backend switch is on changes. Model 160 (has a "
        "repeating \"module\" subgroup) is used throughout so walk_deep is "
        "meaningfully more work than walk_shallow.\n",
        platform_note,
        f"Methodology: every metric is net of the `noop` binary (touches nothing "
        f"from the sunspec library, so none of it gets linked in), which cancels "
        f"out harness/process-startup cost. Timing is the mean over {args.runs} "
        f"runs of a 100000-iteration loop, reported in nanoseconds per call. "
        "`heap_peak_bytes` is the true peak live heap measured externally with "
        "`valgrind --tool=massif` (blank if valgrind wasn't available, and always "
        "in --target mode). "
        "`heap_net_growth_bytes` / `heap_peak_call_bytes_cheap` are a cheap "
        "in-process cross-check via glibc `mallinfo()` sampled around 2000 "
        "repeated calls. `stack_bytes_per_call` is the gcc `-fstack-usage` frame "
        "size, max across every function defined in the variant's own .cpp file.\n",
        "## Per-variant summary\n",
        to_markdown_table(summary_rows, SUMMARY_COLUMNS),
        "\n## Timing decomposition\n",
        "`model_lookup_ns` is load_only net of noop (getModelDefinition() alone). "
        "`shallow_walk_ns` is walk_shallow net of load_only (cost of reading every "
        "accessor on the top-level group's own points). `deep_walk_ns` is "
        "walk_deep net of load_only (same, recursively over every nested "
        "subgroup too). `nested_subgroup_extra_ns` is deep_walk_ns minus "
        "shallow_walk_ns -- the added cost of the repeating module subgroup "
        "specifically.\n",
        to_markdown_table(decomposed_rows, DECOMPOSED_COLUMNS),
    ]
    with open(os.path.join(out_dir, "report.md"), "w") as f:
        f.write("\n".join(report) + "\n")

    print(f"\nWrote {out_dir}/raw_results.json, summary.csv, "
          f"timing_decomposition.csv, report.md")


if __name__ == "__main__":
    main()
