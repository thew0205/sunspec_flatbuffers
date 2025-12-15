#pragma once

#if SUNSPEC_ADAPTER_IMPLEMENTATION == SUNSPEC_FLATBUFFERS_IMPLEMENTATION
#include "adapters/flatbuffers/sunspec_flatbuffer_adapter.h"
#elif SUNSPEC_ADAPTER_IMPLEMENTATION == SUNSPEC_NAKEDBYTES_IMPLEMENTATION
#include "adapters/nakedbytes/sunspec_nakedbytes_adapter.h"
#elif SUNSPEC_ADAPTER_IMPLEMENTATION == SUNSPEC_PROTOBUF_IMPLEMENTATION
#include "adapters/protobuf/sunspec_protobuf_adapter.h"
#else
#error "SUNSPEC_ADAPTER_IMPLEMENTATION is not defined or has an invalid value."
#endif

namespace Sunspec
{
    bool getModelDefinition(uint16_t id, SunspecModelDefWrapper *const model_def);
}; // namespace Sunspec