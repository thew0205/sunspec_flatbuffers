
#include "sunspec.h"

const SunspecPointDef *findPointById(const SunspecGroupDef *group, const std::string_view &id)
{
    const auto &points = *group->points();
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
#elif defined(SUNSPEC_JSON_IMPLEMENTATION)
const SunspecModelDef *getModelDefinition(uint16_t id)
{
    switch (id)
    {
    case 1:
        return &SunspecModelDef::modelDef1;
        break;

    case 2:
        return &SunspecModelDef::modelDef2;
        break;

    case 3:
        return &SunspecModelDef::modelDef3;
        break;

    case 4:
        return &SunspecModelDef::modelDef4;
        break;

    case 5:
        return &SunspecModelDef::modelDef5;
        break;

    case 6:
        return &SunspecModelDef::modelDef6;
        break;

    case 7:
        return &SunspecModelDef::modelDef7;
        break;

    case 8:
        return &SunspecModelDef::modelDef8;
        break;

    case 9:
        return &SunspecModelDef::modelDef9;
        break;

    case 10:
        return &SunspecModelDef::modelDef10;
        break;

    case 11:
        return &SunspecModelDef::modelDef11;
        break;

    case 12:
        return &SunspecModelDef::modelDef12;
        break;

    case 13:
        return &SunspecModelDef::modelDef13;
        break;

    case 14:
        return &SunspecModelDef::modelDef14;
        break;

    case 15:
        return &SunspecModelDef::modelDef15;
        break;

    case 16:
        return &SunspecModelDef::modelDef16;
        break;

    case 17:
        return &SunspecModelDef::modelDef17;
        break;

    case 18:
        return &SunspecModelDef::modelDef18;
        break;

    case 19:
        return &SunspecModelDef::modelDef19;
        break;

    case 101:
        return &SunspecModelDef::modelDef101;
        break;

    case 102:
        return &SunspecModelDef::modelDef102;
        break;

    case 103:
        return &SunspecModelDef::modelDef103;
        break;

    case 111:
        return &SunspecModelDef::modelDef111;
        break;

    case 112:
        return &SunspecModelDef::modelDef112;
        break;

    case 113:
        return &SunspecModelDef::modelDef113;
        break;

    case 120:
        return &SunspecModelDef::modelDef120;
        break;

    case 121:
        return &SunspecModelDef::modelDef121;
        break;

    case 122:
        return &SunspecModelDef::modelDef122;
        break;

    case 123:
        return &SunspecModelDef::modelDef123;
        break;

    case 124:
        return &SunspecModelDef::modelDef124;
        break;

    case 125:
        return &SunspecModelDef::modelDef125;
        break;

    case 126:
        return &SunspecModelDef::modelDef126;
        break;

    case 127:
        return &SunspecModelDef::modelDef127;
        break;

    case 128:
        return &SunspecModelDef::modelDef128;
        break;

    case 129:
        return &SunspecModelDef::modelDef129;
        break;

    case 130:
        return &SunspecModelDef::modelDef130;
        break;

    case 131:
        return &SunspecModelDef::modelDef131;
        break;

    case 132:
        return &SunspecModelDef::modelDef132;
        break;

    case 133:
        return &SunspecModelDef::modelDef133;
        break;

    case 134:
        return &SunspecModelDef::modelDef134;
        break;

    case 135:
        return &SunspecModelDef::modelDef135;
        break;

    case 136:
        return &SunspecModelDef::modelDef136;
        break;

    case 137:
        return &SunspecModelDef::modelDef137;
        break;

    case 138:
        return &SunspecModelDef::modelDef138;
        break;

    case 139:
        return &SunspecModelDef::modelDef139;
        break;

    case 140:
        return &SunspecModelDef::modelDef140;
        break;

    case 141:
        return &SunspecModelDef::modelDef141;
        break;

    case 142:
        return &SunspecModelDef::modelDef142;
        break;

    case 143:
        return &SunspecModelDef::modelDef143;
        break;

    case 144:
        return &SunspecModelDef::modelDef144;
        break;

    case 145:
        return &SunspecModelDef::modelDef145;
        break;

    case 160:
        return &SunspecModelDef::modelDef160;
        break;

    case 201:
        return &SunspecModelDef::modelDef201;
        break;

    case 202:
        return &SunspecModelDef::modelDef202;
        break;

    case 203:
        return &SunspecModelDef::modelDef203;
        break;

    case 204:
        return &SunspecModelDef::modelDef204;
        break;

    case 211:
        return &SunspecModelDef::modelDef211;
        break;

    case 212:
        return &SunspecModelDef::modelDef212;
        break;

    case 213:
        return &SunspecModelDef::modelDef213;
        break;

    case 214:
        return &SunspecModelDef::modelDef214;
        break;

    case 220:
        return &SunspecModelDef::modelDef220;
        break;

    case 302:
        return &SunspecModelDef::modelDef302;
        break;

    case 303:
        return &SunspecModelDef::modelDef303;
        break;

    case 304:
        return &SunspecModelDef::modelDef304;
        break;

    case 305:
        return &SunspecModelDef::modelDef305;
        break;

    case 306:
        return &SunspecModelDef::modelDef306;
        break;

    case 307:
        return &SunspecModelDef::modelDef307;
        break;

    case 308:
        return &SunspecModelDef::modelDef308;
        break;

    case 401:
        return &SunspecModelDef::modelDef401;
        break;

    case 402:
        return &SunspecModelDef::modelDef402;
        break;

    case 403:
        return &SunspecModelDef::modelDef403;
        break;

    case 404:
        return &SunspecModelDef::modelDef404;
        break;

    case 501:
        return &SunspecModelDef::modelDef501;
        break;

    case 502:
        return &SunspecModelDef::modelDef502;
        break;

    case 601:
        return &SunspecModelDef::modelDef601;
        break;

    case 701:
        return &SunspecModelDef::modelDef701;
        break;

    case 702:
        return &SunspecModelDef::modelDef702;
        break;

    case 703:
        return &SunspecModelDef::modelDef703;
        break;

    case 704:
        return &SunspecModelDef::modelDef704;
        break;

    case 705:
        return &SunspecModelDef::modelDef705;
        break;

    case 706:
        return &SunspecModelDef::modelDef706;
        break;

    case 707:
        return &SunspecModelDef::modelDef707;
        break;

    case 708:
        return &SunspecModelDef::modelDef708;
        break;

    case 709:
        return &SunspecModelDef::modelDef709;
        break;

    case 710:
        return &SunspecModelDef::modelDef710;
        break;

    case 711:
        return &SunspecModelDef::modelDef711;
        break;

    case 712:
        return &SunspecModelDef::modelDef712;
        break;

    case 713:
        return &SunspecModelDef::modelDef713;
        break;

    case 714:
        return &SunspecModelDef::modelDef714;
        break;

    case 715:
        return &SunspecModelDef::modelDef715;
        break;

    case 801:
        return &SunspecModelDef::modelDef801;
        break;

    case 802:
        return &SunspecModelDef::modelDef802;
        break;

    case 803:
        return &SunspecModelDef::modelDef803;
        break;

    case 804:
        return &SunspecModelDef::modelDef804;
        break;

    case 805:
        return &SunspecModelDef::modelDef805;
        break;

    case 806:
        return &SunspecModelDef::modelDef806;
        break;

    case 807:
        return &SunspecModelDef::modelDef807;
        break;

    case 808:
        return &SunspecModelDef::modelDef808;
        break;

    case 809:
        return &SunspecModelDef::modelDef809;
        break;

    case 63001:
        return &SunspecModelDef::modelDef63001;
        break;

    case 63002:
        return &SunspecModelDef::modelDef63002;
        break;

    case 64001:
        return &SunspecModelDef::modelDef64001;
        break;

    case 64020:
        return &SunspecModelDef::modelDef64020;
        break;

    case 64101:
        return &SunspecModelDef::modelDef64101;
        break;

    case 64111:
        return &SunspecModelDef::modelDef64111;
        break;

    case 64112:
        return &SunspecModelDef::modelDef64112;
        break;

    case 64410:
        return &SunspecModelDef::modelDef64410;
        break;

    case 64411:
        return &SunspecModelDef::modelDef64411;
        break;

    case 64412:
        return &SunspecModelDef::modelDef64412;
        break;

    case 64413:
        return &SunspecModelDef::modelDef64413;
        break;

    case 64414:
        return &SunspecModelDef::modelDef64414;
        break;

    case 64415:
        return &SunspecModelDef::modelDef64415;
        break;

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