#include "sunspec_utils.h"

#include <cstring>

namespace Sunspec
{
    float registersToFloat(uint16_t reg0, uint16_t reg1)
    {
        uint32_t combined = (((uint32_t)reg0) << 1 * 16) | (((uint32_t)reg1));
        return *reinterpret_cast<float *>(&combined);
    }

    uint16_t registersToUint16(uint16_t reg)
    {
        return reg;
    }

    int16_t registersToInt16(uint16_t reg)
    {
        return *reinterpret_cast<int16_t *>(&reg);
    }

    uint32_t registersToUint32(uint16_t reg0, uint16_t reg1)
    {
        return (((uint32_t)reg0) << 1 * 16) | (((uint32_t)reg1));
    }

    uint64_t registersToUint64(uint16_t reg0, uint16_t reg1, uint16_t reg2, uint16_t reg3)
    {
        return (((uint64_t)reg0) << 3 * 16) | (((uint64_t)reg1) << 2 * 16) | (((uint64_t)reg0) << 1 * 16) | (((uint64_t)reg1));
    }

}; // namespace Sunspec
