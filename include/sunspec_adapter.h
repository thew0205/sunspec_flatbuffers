#pragma once

#if SUNSPEC_ADAPTER_IMPLEMENTATION == FLATBUFFER
#include "adapters/flatbuffers/sunspec_flatbuffer_adapter.h"
#elif SUNSPEC_ADAPTER_IMPLEMENTATION == NAKEDBYTES
#include "adapters/nakedbytes/sunspec_nakedbytes_adapter.h"
#else
#error "SUNSPEC_ADAPTER_IMPLEMENTATION is not defined or has an invalid value."
#endif