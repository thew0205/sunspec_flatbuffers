#include "model_definitions.h"

const SunspecModelDef *Sunspec::getModelDefinition(uint16_t id)
{
    // NOTE: Think of a better way to do this, maybe a map of some sort.
    switch (id)
    {
    case 1:
        return GetSunspecModelDef(modelDefinition1);

    case 112:
        return GetSunspecModelDef(modelDefinition112);
    case 113:

        return GetSunspecModelDef(modelDefinition113);
    case 160:
        return GetSunspecModelDef(modelDefinition160);

    default:
        return nullptr;
        break;
    }
}
