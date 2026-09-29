#include "adapters/c_define/c_model_definition.h"
const SunspecModelDef SunspecModelDef::modelDef126{
        SunspecModelList_kModel126,
        "Static Volt-VAR", // Model label from JSON: "label": "Static Volt-VAR"
        {
            "volt_var",        // Top-level group name from JSON: "name": "volt_var"
            "Static Volt-VAR", // Top-level group label from JSON: "label": "Static Volt-VAR"
            1,
            "",
            SunspecGroupType_kGroup,
            {
                // Points for the top-level 'volt_var' group
                {"ID", 1, "", "", "", 1, SunspecPointData_kUint16, kUint16(126), SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model ID"},
                {"L", 1, "", "", "", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model Length"},
                {"ActCrv", 1, "", "", "", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kM, "ActCrv"},
                {"ModEna", 1, "", "", "", 1, SunspecPointData_kBitfield16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kM, "ModEna"},
                {"WinTms", 1, "", "", "Secs", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "WinTms"},
                {"RvrtTms", 1, "", "", "Secs", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "RvrtTms"},
                {"RmpTms", 1, "", "", "Secs", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "RmpTms"},
                {"NCrv", 1, "", "", "", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "NCrv"},
                {"NPt", 1, "", "", "", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "NPt"},
                {"V_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "V_SF"},
                {"DeptRef_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "DeptRef_SF"},
                // Note: RmpIncDec_SF has no label in JSON, so it becomes ""
                {"RmpIncDec_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, ""},
            },
            {
                // Nested groups start here (only one 'curve' group in this model}
                {
                    "curve",                 // Nested group name from JSON: "name": "curve"
                    "",                      // Nested group has no explicit 'label' in JSON, so it's ""
                    0, // "count": 0 typically implies a fixed group (though it could be repeating if 'count_id' was present}
                    "NCrv",
                    SunspecGroupType_kGroup,
                    {// Points for the nested 'curve' group
                     {"ActPt", 1, "", "", "", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kM, "ActPt"},
                     {"DeptRef", 1, "", "", "", 1, SunspecPointData_kEnum16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kM, "DeptRef"},
                     {"V1", 1, "", "V_SF", "% VRef", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kM, "V1"},
                     {"VAr1", 1, "", "DeptRef_SF", "", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kM, "VAr1"},
                     {"V2", 1, "", "V_SF", "% VRef", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "V2"},
                     {"VAr2", 1, "", "DeptRef_SF", "", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "VAr2"},
                     {"V3", 1, "", "V_SF", "% VRef", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "V3"},
                     {"VAr3", 1, "", "DeptRef_SF", "", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "VAr3"},
                     {"V4", 1, "", "V_SF", "% VRef", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "V4"},
                     {"VAr4", 1, "", "DeptRef_SF", "", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "VAr4"},
                     {"V5", 1, "", "V_SF", "% VRef", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "V5"},
                     {"VAr5", 1, "", "DeptRef_SF", "", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "VAr5"},
                     {"V6", 1, "", "V_SF", "% VRef", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "V6"},
                     {"VAr6", 1, "", "DeptRef_SF", "", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "VAr6"},
                     {"V7", 1, "", "V_SF", "% VRef", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "V7"},
                     {"VAr7", 1, "", "DeptRef_SF", "", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "VAr7"},
                     {"V8", 1, "", "V_SF", "% VRef", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "V8"},
                     {"VAr8", 1, "", "DeptRef_SF", "", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "VAr8"},
                     {"V9", 1, "", "V_SF", "% VRef", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "V9"},
                     {"VAr9", 1, "", "DeptRef_SF", "", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "VAr9"},
                     {"V10", 1, "", "V_SF", "% VRef", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "V10"},
                     {"VAr10", 1, "", "DeptRef_SF", "", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "VAr10"},
                     {"V11", 1, "", "V_SF", "% VRef", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "V11"},
                     {"VAr11", 1, "", "DeptRef_SF", "", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "VAr11"},
                     {"V12", 1, "", "V_SF", "% VRef", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "V12"},
                     {"VAr12", 1, "", "DeptRef_SF", "", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "VAr12"},
                     {"V13", 1, "", "V_SF", "% VRef", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "V13"},
                     {"VAr13", 1, "", "DeptRef_SF", "", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "VAr13"},
                     {"V14", 1, "", "V_SF", "% VRef", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "V14"},
                     {"VAr14", 1, "", "DeptRef_SF", "", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "VAr14"},
                     {"V15", 1, "", "V_SF", "% VRef", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "V15"},
                     {"VAr15", 1, "", "DeptRef_SF", "", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "VAr15"},
                     {"V16", 1, "", "V_SF", "% VRef", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "V16"},
                     {"VAr16", 1, "", "DeptRef_SF", "", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "VAr16"},
                     {"V17", 1, "", "V_SF", "% VRef", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "V17"},
                     {"VAr17", 1, "", "DeptRef_SF", "", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "VAr17"},
                     {"V18", 1, "", "V_SF", "% VRef", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "V18"},
                     {"VAr18", 1, "", "DeptRef_SF", "", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "VAr18"},
                     {"V19", 1, "", "V_SF", "% VRef", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "V19"},
                     {"VAr19", 1, "", "DeptRef_SF", "", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "VAr19"},
                     {"V20", 1, "", "V_SF", "% VRef", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "V20"},
                     {"VAr20", 1, "", "DeptRef_SF", "", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "VAr20"},
                     {"CrvNam", 1, "", "", "", 8, SunspecPointData_kStringx, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "CrvNam"},
                     {"RmpTms", 1, "", "", "Secs", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "RmpTms"},
                     {"RmpDecTmm", 1, "", "RmpIncDec_SF", "% ref_value/min", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "RmpDecTmm"},
                     {"RmpIncTmm", 1, "", "RmpIncDec_SF", "% ref_value/min", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "RmpIncTmm"},
                     {"ReadOnly", 1, "", "", "", 1, SunspecPointData_kEnum16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "ReadOnly"}},
                    {} // No further nested groups within 'curve'
                },
            },
        },
    };
