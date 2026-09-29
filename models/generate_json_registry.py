#!/usr/bin/env python3
"""Wires every model in models/json/ into the SUNSPEC_JSON_IMPLEMENTATION
adapter (include/adapters/json/sunspec_json_definition.h /
src/adapters/json/sunspec_json_definition.cpp):

  1. Ensures src/models/json/model_json_<id>.cpp exists for every model
     (reuses generate_model_json_cpp.py's per-model generation).
  2. Regenerates the SunspecModelList enum in the header.
  3. Regenerates the `static const SunspecModelDef modelDef<id>;` member
     declarations in the header.
  4. Regenerates the `extern const char *const kModelJsonText<id>;`
     declarations, the out-of-class `modelDef<id>` definitions, and the
     kAllModels[] lookup table in the .cpp.
  5. Regenerates the JSON-mode MODEL_FILES list in src/CMakeLists.txt.

Re-run whenever models/json/*.json changes.
"""
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
JSON_DIR = ROOT / "models" / "json"
MODEL_JSON_CPP_DIR = ROOT / "src" / "models" / "json"
HEADER_PATH = ROOT / "include" / "adapters" / "json" / "sunspec_json_definition.h"
CPP_PATH = ROOT / "src" / "adapters" / "json" / "sunspec_json_definition.cpp"
CMAKE_PATH = ROOT / "src" / "CMakeLists.txt"

sys.path.insert(0, str(Path(__file__).resolve().parent))
import generate_model_json_cpp as jsoncpp  # noqa: E402


def load_model_ids() -> list[int]:
    ids = []
    for path in sorted(JSON_DIR.glob("model_*.json")):
        ids.append(json.loads(path.read_text())["id"])
    return sorted(ids)


def ensure_model_json_cpp_files(ids: list[int]) -> list[int]:
    written = []
    MODEL_JSON_CPP_DIR.mkdir(parents=True, exist_ok=True)
    for mid in ids:
        out_path = MODEL_JSON_CPP_DIR / f"model_json_{mid}.cpp"
        out_path.write_text(jsoncpp.generate(mid))
        written.append(mid)
    return written


def update_header(ids: list[int]) -> None:
    text = HEADER_PATH.read_text()

    enum_start = text.index("enum SunspecModelList : uint16_t\n{")
    enum_open = text.index("{", enum_start)
    enum_close = text.index("};", enum_open)
    body = "\n    SunspecModelList_kModelInvalid = 0,\n"
    for mid in ids:
        body += f"    SunspecModelList_kModel{mid} = {mid},\n"
    body += "    SunspecModelList_kModelEnd = 0xFFFF,\n"
    text = text[: enum_open + 1] + body + text[enum_close:]

    decl_marker = "static const SunspecModelDef modelDef1;"
    decl_start = text.rindex("/**", 0, text.index(decl_marker))
    decl_end = text.index("};", text.index(decl_marker))
    decl_end = text.rindex("\n", 0, decl_end) + 1
    decls = ""
    for mid in ids:
        decls += (
            f"    /**\n"
            f"     * @brief Static definition for Model {mid}.\n"
            f"     */\n"
            f"    static const SunspecModelDef modelDef{mid};\n\n"
        )
    text = text[:decl_start] + decls.rstrip("\n") + "\n" + text[decl_end:]

    HEADER_PATH.write_text(text)


def update_cpp(ids: list[int]) -> None:
    text = CPP_PATH.read_text()

    extern_start = text.index("extern const char *const kModelJsonText1;")
    extern_start = text.rindex("\n", 0, extern_start) + 1
    extern_end = text.index("\n\n", extern_start) + 1
    externs = "".join(f"extern const char *const kModelJsonText{mid};\n" for mid in ids)
    text = text[:extern_start] + externs + text[extern_end:]

    def_marker = "const SunspecModelDef SunspecModelDef::modelDef1(kModelJsonText1);"
    def_start = text.index(def_marker)
    def_end = text.index("\n\n", def_start) + 1
    defs = "".join(
        f"const SunspecModelDef SunspecModelDef::modelDef{mid}(kModelJsonText{mid});\n" for mid in ids
    )
    text = text[:def_start] + defs + text[def_end:]

    table_start = text.index("const ModelEntry kAllModels[] = {")
    table_open = text.index("{", table_start)
    table_close = text.index("};", table_open)
    rows = "".join(
        f"    {{SunspecModelList_kModel{mid}, &SunspecModelDef::modelDef{mid}}},\n" for mid in ids
    )
    text = text[: table_open + 1] + "\n" + rows + text[table_close:]

    CPP_PATH.write_text(text)


def update_cmakelists(ids: list[int]) -> None:
    text = CMAKE_PATH.read_text()
    anchor = "if(SUNSPEC_JSON_IMPLEMENTATION)\nset(MODEL_FILES\n"
    start = text.index(anchor) + len(anchor)
    end = text.index(")", start)
    files = "".join(f"        models/json/model_json_{mid}.cpp\n" for mid in ids)
    text = text[:start] + files + text[end:]
    CMAKE_PATH.write_text(text)


def main() -> None:
    ids = load_model_ids()
    written = ensure_model_json_cpp_files(ids)
    update_header(ids)
    update_cpp(ids)
    update_cmakelists(ids)
    print(f"Wrote {len(written)} model_json_<id>.cpp files.")
    print(f"Wired up all {len(ids)} models in the header, cpp, and CMakeLists.txt.")


if __name__ == "__main__":
    main()
