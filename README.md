# sunspec_flatbuffers

A compact Sunspec library implementation using FlatBuffers for model definitions and a Modbus memory-map buffer for efficient point storage and access.

**Highlights**
- Small, embeddable C++ library for working with SunSpec models.
- Models authored as FlatBuffers schemas and shipped as binary/JSON model artifacts.
- Reader/writer modules that map FlatBuffer model fields to a Modbus-style memory map.
- Tools and scripts for converting model JSON to FlatBuffer bins and running tests.

**Contents**
- `include/`: Public headers and bundled FlatBuffers runtime.
- `src/`: Implementation, including `reader/` and `writer/` modules.
- `models/`: Model conversion scripts and example model data.
- `tests/`: Unit and integration test scaffolding for host and target.
- `tools/`: Utility scripts for building and running tests across host/target.
- `sunspec_model_definition.fbs`: Primary FlatBuffers schema for SunSpec models.

Requirements
- A CMake-capable build system (CMake >= 3.13 recommended).
- A C++17-compatible compiler.
- Ninja or Make (recommended: Ninja).
- FlatBuffers toolchain if you plan to recompile schemas (optional — precompiled headers are included).

Quick build (out-of-tree)

```bash
cmake -S . -B build -G Ninja
cmake --build build
```

Running model conversion

Convert model JSON to binary FlatBuffer format (used by the library) with the provided script:

```bash
./models/json_to_bin.sh
```

Testing

There are helper scripts and tasks for host and target test builds in `tools/` and the workspace tasks. To build host tests using CMake/Ninja:

```bash
cmake -S . -B build -G Ninja
cmake --build build --target all
```

Or use the provided workspace tasks (Host/Target Test Build) in your editor's task runner.

Project layout (quick)

- `include/` — API headers and bundled FlatBuffers runtime.
- `src/reader/` — Code that reads FlatBuffer model data into the Modbus memory-map buffer.
- `src/writer/` — Code that writes from the memory-map into FlatBuffer outputs.
- `models/` — Conversion scripts and example JSON/FlatBuffer data.
- `tests/` — Test sources and CMake test targets.
- `tools/` — Build/run helpers such as `dual_target_test_build.sh` and `dual_target_test_build_run.sh`.

Contributing

- Open an issue or a pull request describing the change.
- Follow existing code style and add tests for functional changes.

License

See the `models/LICENSE` file for model-related licensing; other code in the repo follows the licensing indicated at its source (check individual headers/files).

Questions or help

Open an issue with details about your platform and what you'd like to do.
