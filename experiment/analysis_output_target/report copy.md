# SunSpec model-definition backend comparison

Backends: `c_define` (native C++ struct/vector literals, compiled in), `json` (jsmn-tokenized JSON text parsed at runtime), `flatbuffers` (pre-compiled FlatBuffers binary blob, zero-copy accessors). All three expose the identical SunspecModelDef/SunspecGroupDef/SunspecPointDef accessor surface (see include/sunspec_adapter.h and CLAUDE.md's adapter pattern), so the same walk code (load_only.cpp / walk_shallow.cpp / walk_deep.cpp) runs unchanged against all three -- only which src/CMakeLists.txt backend switch is on changes. Model 160 (has a repeating "module" subgroup) is used throughout so walk_deep is meaningfully more work than walk_shallow.

This run is on **Pico2 (RP2350) hardware**: each variant was cross-compiled via experiment/target's CMakeLists, flashed and executed with `picotool`, and its result line(s) read back over USB serial with `tio` (see the module docstring's '--target mode' section). `heap_peak_bytes` is always blank here -- there's no valgrind on target, only the in-firmware `mallinfo()` sampling that also produces `heap_net_growth_bytes` / `heap_peak_call_bytes_cheap`. Since target execution has no OS scheduling jitter, repeated `--runs` samples of one flash are expected to be identical (or near enough); it's included mainly for parity with host mode's report shape.

Methodology: every metric is net of the `noop` binary (touches nothing from the sunspec library, so none of it gets linked in), which cancels out harness/process-startup cost. Timing is the mean over 5 runs of a 100000-iteration loop, reported in nanoseconds per call. `heap_peak_bytes` is the true peak live heap measured externally with `valgrind --tool=massif` (blank if valgrind wasn't available, and always in --target mode). `heap_net_growth_bytes` / `heap_peak_call_bytes_cheap` are a cheap in-process cross-check via glibc `mallinfo()` sampled around 2000 repeated calls. `stack_bytes_per_call` is the gcc `-fstack-usage` frame size, max across every function defined in the variant's own .cpp file.

## Per-variant summary

| backend | variant | time_ns_net | flash_bytes | flash_bytes_net | static_ram_bytes | static_ram_bytes_net | heap_peak_bytes | heap_net_growth_bytes | heap_peak_call_bytes_cheap | stack_bytes_per_call |
|---|---|---|---|---|---|---|---|---|---|---|
| json | noop | 0.0 | 707644 | 0 | 4296 | 0 | None | 224808 | 0 | 0 |
| json | load_only | 334500675.0 | 707724 | 80 | 4316 | 20 | None | 224808 | 0 | 8 |
| json | walk_shallow | 339140005.0 | 707864 | 220 | 4316 | 20 | None | 224808 | 0 | 80 |
| json | walk_deep | 356601975.0 | 708032 | 388 | 4316 | 20 | None | 224808 | 0 | 120 |
| c_define | noop | 0.0 | 467456 | 0 | 4296 | 0 | None | 348168 | 0 | 0 |
| c_define | load_only | 1082745.0 | 467536 | 80 | 4316 | 20 | None | 348168 | 0 | 8 |
| c_define | walk_shallow | 1067505.0 | 467644 | 188 | 4316 | 20 | None | 348168 | 0 | 72 |
| c_define | walk_deep | 1095455.0 | 467788 | 332 | 4316 | 20 | None | 348168 | 0 | 112 |
| flatbuffers | noop | 0.0 | 376000 | 0 | 4296 | 0 | None | 456 | 0 | 0 |
| flatbuffers | load_only | 54850.0 | 376088 | 88 | 4316 | 20 | None | 456 | 0 | 8 |
| flatbuffers | walk_shallow | 113920.0 | 376444 | 444 | 4316 | 20 | None | 456 | 0 | 48 |
| flatbuffers | walk_deep | 188635.0 | 376652 | 652 | 4316 | 20 | None | 456 | 0 | 72 |

## Timing decomposition

`model_lookup_ns` is load_only net of noop (getModelDefinition() alone). `shallow_walk_ns` is walk_shallow net of load_only (cost of reading every accessor on the top-level group's own points). `deep_walk_ns` is walk_deep net of load_only (same, recursively over every nested subgroup too). `nested_subgroup_extra_ns` is deep_walk_ns minus shallow_walk_ns -- the added cost of the repeating module subgroup specifically.

| backend | model_lookup_ns | shallow_walk_ns | deep_walk_ns | nested_subgroup_extra_ns |
|---|---|---|---|---|
| json | 334500675.0 | 4639330.0 | 22101300.0 | 17461970.0 |
| c_define | 1082745.0 | -15240.0 | 12710.0 | 27950.0 |
| flatbuffers | 54850.0 | 59070.0 | 133785.0 | 74715.0 |
