# SunSpec model-definition backend comparison

Backends: `c_define` (native C++ struct/vector literals, compiled in), `json` (jsmn-tokenized JSON text parsed at runtime), `flatbuffers` (pre-compiled FlatBuffers binary blob, zero-copy accessors). All three expose the identical SunspecModelDef/SunspecGroupDef/SunspecPointDef accessor surface (see include/sunspec_adapter.h and CLAUDE.md's adapter pattern), so the same walk code (load_only.cpp / walk_shallow.cpp / walk_deep.cpp) runs unchanged against all three -- only which src/CMakeLists.txt backend switch is on changes. Model 160 (has a repeating "module" subgroup) is used throughout so walk_deep is meaningfully more work than walk_shallow.


Methodology: every metric is net of the `noop` binary (touches nothing from the sunspec library, so none of it gets linked in), which cancels out harness/process-startup cost. Timing is the mean over 5 runs of a 100000-iteration loop, reported in nanoseconds per call. `heap_peak_bytes` is the true peak live heap measured externally with `valgrind --tool=massif` (blank if valgrind wasn't available, and always in --target mode). `heap_net_growth_bytes` / `heap_peak_call_bytes_cheap` are a cheap in-process cross-check via glibc `mallinfo()` sampled around 2000 repeated calls. `stack_bytes_per_call` is the gcc `-fstack-usage` frame size, max across every function defined in the variant's own .cpp file.

## Per-variant summary

| backend | variant | time_ns_net | flash_bytes | flash_bytes_net | static_ram_bytes | static_ram_bytes_net | heap_peak_bytes | heap_net_growth_bytes | heap_peak_call_bytes_cheap | stack_bytes_per_call |
|---|---|---|---|---|---|---|---|---|---|---|
| json | noop | 0.0 | 749661 | 0 | 1920 | 0 | 393760 | 297536 | 0 | 16 |
| json | load_only | 7804211.4 | 749964 | 303 | 1968 | 48 | 395744 | 267296 | 0 | 32 |
| json | walk_shallow | 7332465.2 | 751120 | 1459 | 1968 | 48 | 393760 | 267296 | 0 | 128 |
| json | walk_deep | 7861385.2 | 751836 | 2175 | 1968 | 48 | 395744 | 267296 | 0 | 144 |
| c_define | noop | 0.0 | 947310 | 0 | 1008 | 0 | 587816 | 518592 | 0 | 16 |
| c_define | load_only | 4099.0 | 947619 | 309 | 1056 | 48 | 587816 | 493536 | 0 | 32 |
| c_define | walk_shallow | 4339.4 | 948736 | 1426 | 1056 | 48 | 587816 | 493536 | 0 | 128 |
| c_define | walk_deep | 4729.6 | 949528 | 2218 | 1056 | 48 | 587816 | 493536 | 0 | 144 |
| flatbuffers | noop | 0.0 | 301594 | 0 | 1288 | 0 | 78720 | 912 | 0 | 16 |
| flatbuffers | load_only | 2204.2 | 301916 | 322 | 1328 | 40 | 78720 | 0 | 0 | 32 |
| flatbuffers | walk_shallow | 5351.6 | 306189 | 4595 | 1336 | 48 | 78720 | 0 | 0 | 128 |
| flatbuffers | walk_deep | 8875.0 | 307999 | 6405 | 1336 | 48 | 78720 | 0 | 0 | 144 |

## Timing decomposition

`model_lookup_ns` is load_only net of noop (getModelDefinition() alone). `shallow_walk_ns` is walk_shallow net of load_only (cost of reading every accessor on the top-level group's own points). `deep_walk_ns` is walk_deep net of load_only (same, recursively over every nested subgroup too). `nested_subgroup_extra_ns` is deep_walk_ns minus shallow_walk_ns -- the added cost of the repeating module subgroup specifically.

| backend | model_lookup_ns | shallow_walk_ns | deep_walk_ns | nested_subgroup_extra_ns |
|---|---|---|---|---|
| json | 7804211.4 | -471746.2 | 57173.8 | 528920.0 |
| c_define | 4099.0 | 240.4 | 630.6 | 390.2 |
| flatbuffers | 2204.2 | 3147.4 | 6670.8 | 3523.4 |
