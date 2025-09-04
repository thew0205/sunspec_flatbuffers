#include "model_definitions.h"

const SunspecModelDef *Sunspec::getModelDefinition(SunspecModelList id)
{
    // NOTE: Think of a better way to do this, maybe a map of some sort.
    switch (id)
    {
    case SunspecModelList_kModel1:
        return GetSunspecModelDef(modelDefinition1);

    case SunspecModelList_kModel112:

        return GetSunspecModelDef(modelDefinition112);
    case SunspecModelList_kModel113:

        return GetSunspecModelDef(modelDefinition113);
    case SunspecModelList_kModel160:
        return GetSunspecModelDef(modelDefinition160);

    default:
        return nullptr;
        break;
    }
}
