
#include "sunspec.h"



const SunspecPointDef *findPointById(const SunspecGroupDef *group, const std::string_view &id)
{
    const auto& points = *group->points();
    for (unsigned int i = 0; i < points.size(); ++i)
    {
        const auto &point = REFERENCE_POINTER_FLATBUFFER(points[i]);
        if (FlatbufferStringToString(point->id()) == id)
        {
            return point;
        }
    }
    return nullptr;
}


#if SUNSPEC_FLATBUFFERS_IMPLEMENTATION
#include "flatbuffers_model_definition_declaration.h"


const SunspecModelDef *getModelDefinition(uint16_t id)
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
#else 
const SunspecModelDef *getModelDefinition(uint16_t id)
{
    // NOTE: Think of a better way to do this, maybe a map of some sort.
    switch (id)
    {
    case 1:
        return &SunspecModelDef::modelDef1;

    case 112:

        return &SunspecModelDef::modelDef112;
    case 113:

        return &SunspecModelDef::modelDef113;
    case 160:
        return &SunspecModelDef::modelDef160;

    default:
        return nullptr;
        break;
    }
}
#endif