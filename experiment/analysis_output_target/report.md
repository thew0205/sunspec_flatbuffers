# SunSpec model-definition backend comparison

Backends: `c_define` (native C++ struct/vector literals, compiled in), `json` (jsmn-tokenized JSON text parsed at runtime), `flatbuffers` (pre-compiled FlatBuffers binary blob, zero-copy accessors). All three expose the identical SunspecModelDef/SunspecGroupDef/SunspecPointDef accessor surface (see include/sunspec_adapter.h and CLAUDE.md's adapter pattern), so the same walk code (load_only.cpp / walk_shallow.cpp / walk_deep.cpp) runs unchanged against all three -- only which src/CMakeLists.txt backend switch is on changes. Model 160 (has a repeating "module" subgroup) is used throughout so walk_deep is meaningfully more work than walk_shallow.

This run is on **Pico2 (RP2350) hardware**: each variant was cross-compiled via experiment/target's CMakeLists, flashed and executed with `picotool`, and its result line(s) read back over USB serial with `tio` (see the module docstring's '--target mode' section). `heap_peak_bytes` is always blank here -- there's no valgrind on target, only the in-firmware `mallinfo()` sampling that also produces `heap_net_growth_bytes` / `heap_peak_call_bytes_cheap`. Since target execution has no OS scheduling jitter, repeated `--runs` samples of one flash are expected to be identical (or near enough); it's included mainly for parity with host mode's report shape.

Methodology: every metric is net of the `noop` binary (touches nothing from the sunspec library, so none of it gets linked in), which cancels out harness/process-startup cost. Timing is the mean over 5 runs of a 100000-iteration loop, reported in nanoseconds per call. `heap_peak_bytes` is the true peak live heap measured externally with `valgrind --tool=massif` (blank if valgrind wasn't available, and always in --target mode). `heap_net_growth_bytes` / `heap_peak_call_bytes_cheap` are a cheap in-process cross-check via glibc `mallinfo()` sampled around 2000 repeated calls. `stack_bytes_per_call` is the gcc `-fstack-usage` frame size, max across every function defined in the variant's own .cpp file.

## Per-variant summary

| backend | variant | time_ns_net | flash_bytes | flash_bytes_net | static_ram_bytes | static_ram_bytes_net | heap_peak_bytes | heap_net_growth_bytes | heap_peak_call_bytes_cheap | stack_bytes_per_call |
|---|---|---|---|---|---|---|---|---|---|---|
| json | noop | 0.0 | 36688 | 0 | 3760 | 0 | None | 0 | 0 | 0 |
| json | load_only | 230.0 | 731596 | 694908 | 4280 | 520 | None | 224808 | 0 | 8 |
| json | walk_shallow | 225250375.0 | 731696 | 695008 | 4280 | 520 | None | 224808 | 0 | 48 |
| json | walk_deep | 238163555.0 | 731832 | 695144 | 4280 | 520 | None | 224808 | 0 | 64 |
| c_define | noop | 0.0 | 36688 | 0 | 3760 | 0 | None | 0 | 0 | 0 |
| c_define | load_only | 225.0 | 603352 | 566664 | 4280 | 520 | None | 348168 | 0 | 8 |
| c_define | walk_shallow | 4280.0 | 603396 | 566708 | 4280 | 520 | None | 348168 | 0 | 24 |
| c_define | walk_deep | 7705.0 | 603572 | 566884 | 4280 | 520 | None | 348168 | 0 | 24 |
| flatbuffers | noop | 0.0 | 36688 | 0 | 3760 | 0 | None | 0 | 0 | 0 |
| flatbuffers | load_only | 100.0 | 375820 | 339132 | 4264 | 504 | None | 456 | 0 | 8 |
| flatbuffers | walk_shallow | 17745.0 | 376112 | 339424 | 4264 | 504 | None | 456 | 0 | 32 |
| flatbuffers | walk_deep | 41125.0 | 376328 | 339640 | 4264 | 504 | None | 456 | 0 | 48 |

## Timing decomposition

`model_lookup_ns` is load_only net of noop (getModelDefinition() alone). `shallow_walk_ns` is walk_shallow net of load_only (cost of reading every accessor on the top-level group's own points). `deep_walk_ns` is walk_deep net of load_only (same, recursively over every nested subgroup too). `nested_subgroup_extra_ns` is deep_walk_ns minus shallow_walk_ns -- the added cost of the repeating module subgroup specifically.

| backend | model_lookup_ns | shallow_walk_ns | deep_walk_ns | nested_subgroup_extra_ns |
|---|---|---|---|---|
| json | 230.0 | 225250145.0 | 238163325.0 | 12913180.0 |
| c_define | 225.0 | 4055.0 | 7480.0 | 3425.0 |
| flatbuffers | 100.0 | 17645.0 | 41025.0 | 23380.0 |
