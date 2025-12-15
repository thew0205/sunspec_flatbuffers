#include "array_models_externs.h"
#include "sunspec_adapter.h"

bool Sunspec::getModelDefinition(uint16_t id, SunspecModelDefWrapper * model_def)
{
    // NOTE: Think of a better way to do this, maybe a map of some sort.
    switch (id)
    {
    case 1:
        *model_def = FormatSunspecModelBinaryToSunspecModelDef(modelDefinition1, modelDefinition1_len);
        break;

    case 112:
        *model_def = FormatSunspecModelBinaryToSunspecModelDef(modelDefinition112, modelDefinition112_len);
        break;
    case 113:

        *model_def = FormatSunspecModelBinaryToSunspecModelDef(modelDefinition113, modelDefinition113_len);
        break;

    case 160:
        *model_def = FormatSunspecModelBinaryToSunspecModelDef(modelDefinition160, modelDefinition160_len);
        break;

    default:
        // return nullptr;
        assert(false);
        return false;
        break;
    }
    return true;
}
