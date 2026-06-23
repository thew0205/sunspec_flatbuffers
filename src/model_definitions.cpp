#include "model_definitions.h"

// // 1. Define a helper macro locally
// #define HANDLE_MODEL(id_suffix) \
//     case SunspecModelList_kModel##id_suffix: \
//     #ifdef _INCLUDE_SUNSPEC_MODEL_##id_suffix_ \
//         return GetSunspecModelDef(modelDefinition##id_suffix); \
//     #else \
//         return nullptr; \
//     #endif

const SunspecModelDef *Sunspec::getModelDefinition(SunspecModelList id)
{
    // NOTE: Think of a better way to do this, maybe a map of some sort.
    switch (id)
    {
      case SunspecModelList_kModel1:
#ifdef _INCLUDE_SUNSPEC_MODEL_1_
        return GetSunspecModelDef(modelDefinition1);
#else
        return nullptr;
#endif
           case SunspecModelList_kModel2:
#ifdef _INCLUDE_SUNSPEC_MODEL_2_
        return GetSunspecModelDef(modelDefinition2);
#else
        return nullptr;
#endif
    case SunspecModelList_kModel3:
#ifdef _INCLUDE_SUNSPEC_MODEL_3_
        return GetSunspecModelDef(modelDefinition3);
#else
        return nullptr;
#endif
        break;
    case SunspecModelList_kModel4:
#ifdef _INCLUDE_SUNSPEC_MODEL_4_
        return GetSunspecModelDef(modelDefinition4);
#else
        return nullptr;
#endif
        break;
    case SunspecModelList_kModel5:
#ifdef _INCLUDE_SUNSPEC_MODEL_5_
        return GetSunspecModelDef(modelDefinition5);
#else
        return nullptr;
#endif
        break;
    case SunspecModelList_kModel6:
#ifdef _INCLUDE_SUNSPEC_MODEL_6_
        return GetSunspecModelDef(modelDefinition6);
#else
        return nullptr;
#endif
        break;
    case SunspecModelList_kModel7:
#ifdef _INCLUDE_SUNSPEC_MODEL_7_
        return GetSunspecModelDef(modelDefinition7);
#else
        return nullptr;
#endif
        break;
    case SunspecModelList_kModel8:
#ifdef _INCLUDE_SUNSPEC_MODEL_8_
        return GetSunspecModelDef(modelDefinition8);
#else
        return nullptr;
#endif
        break;
    case SunspecModelList_kModel9:
#ifdef _INCLUDE_SUNSPEC_MODEL_9_
        return GetSunspecModelDef(modelDefinition9);
#else
        return nullptr;
#endif
        break;
    case SunspecModelList_kModel10:
#ifdef _INCLUDE_SUNSPEC_MODEL_10_
        return GetSunspecModelDef(modelDefinition10);
#else
        return nullptr;
#endif
        break;
    case SunspecModelList_kModel11:
#ifdef _INCLUDE_SUNSPEC_MODEL_11_
        return GetSunspecModelDef(modelDefinition11);
#else
        return nullptr;
#endif
        break;
    case SunspecModelList_kModel12:
#ifdef _INCLUDE_SUNSPEC_MODEL_12_
        return GetSunspecModelDef(modelDefinition12);
#else
        return nullptr;
#endif
        break;
    case SunspecModelList_kModel13:
#ifdef _INCLUDE_SUNSPEC_MODEL_13_
        return GetSunspecModelDef(modelDefinition13);
#else
        return nullptr;
#endif
        break;
    case SunspecModelList_kModel14:
#ifdef _INCLUDE_SUNSPEC_MODEL_14_
        return GetSunspecModelDef(modelDefinition14);
#else
        return nullptr;
#endif
        break;
    case SunspecModelList_kModel15:
#ifdef _INCLUDE_SUNSPEC_MODEL_15_
        return GetSunspecModelDef(modelDefinition15);
#else
        return nullptr;
#endif
        break;
    case SunspecModelList_kModel16:
#ifdef _INCLUDE_SUNSPEC_MODEL_16_
        return GetSunspecModelDef(modelDefinition16);
#else
        return nullptr;
#endif
        break;
    case SunspecModelList_kModel17:
#ifdef _INCLUDE_SUNSPEC_MODEL_17_
        return GetSunspecModelDef(modelDefinition17);
#else
        return nullptr;
#endif
        break;
    case SunspecModelList_kModel18:
#ifdef _INCLUDE_SUNSPEC_MODEL_18_
        return GetSunspecModelDef(modelDefinition18);
#else
        return nullptr;
#endif
        break;
    case SunspecModelList_kModel19:
#ifdef _INCLUDE_SUNSPEC_MODEL_19_
        return GetSunspecModelDef(modelDefinition19);
#else
        return nullptr;
#endif
        break;
    case SunspecModelList_kModel101:
#ifdef _INCLUDE_SUNSPEC_MODEL_101_
        return GetSunspecModelDef(modelDefinition101);
#else
        return nullptr;
#endif
        break;
    case SunspecModelList_kModel102:
#ifdef _INCLUDE_SUNSPEC_MODEL_102_
        return GetSunspecModelDef(modelDefinition102);
#else
        return nullptr;
#endif
        break;
    case SunspecModelList_kModel103:
#ifdef _INCLUDE_SUNSPEC_MODEL_103_
        return GetSunspecModelDef(modelDefinition103);
#else
        return nullptr;
#endif
        break;
    case SunspecModelList_kModel111:
#ifdef _INCLUDE_SUNSPEC_MODEL_111_
        return GetSunspecModelDef(modelDefinition111);
#else
        return nullptr;
#endif
        break;
    case SunspecModelList_kModel112:
#ifdef _INCLUDE_SUNSPEC_MODEL_112_
        return GetSunspecModelDef(modelDefinition112);
#else
        return nullptr;
#endif
        break;
    case SunspecModelList_kModel113:
#ifdef _INCLUDE_SUNSPEC_MODEL_113_
        return GetSunspecModelDef(modelDefinition113);
#else
        return nullptr;
#endif
        break;
    case SunspecModelList_kModel160:
#ifdef _INCLUDE_SUNSPEC_MODEL_160_
        return GetSunspecModelDef(modelDefinition160);
#else
        return nullptr;
#endif
        break;

    default:
        return nullptr;
        break;
    }
}
