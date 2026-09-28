#include "c_model_definition.h"
const SunspecModelDef SunspecModelDef::modelDef160{
        SunspecModelList_kModel160,
        "Multiple MPPT Inverter Extension Model", // Model label
        {
            "mppt",                                   // Top-level group name
            "Multiple MPPT Inverter Extension Model", // Top-level group label
            1,                      // The main group itself is fixed
            "",
            SunspecGroupType_kGroup,
            {
                // Points for the top-level 'mppt' group
                {"ID", 1, "", "", "", 1, SunspecPointData_kUint16, kUint16(160), SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model ID"},
                {"L", 1, "", "", "", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model Length"},
                {"DCA_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Current Scale Factor"}, // Mandatory is O (not specified}
                {"DCV_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Voltage Scale Factor"}, // Mandatory is O
                {"DCW_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Power Scale Factor"},   // Mandatory is O
                {"DCWH_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Energy Scale Factor"}, // Mandatory is O
                {"Evt", 1, "", "", "", 2, SunspecPointData_kBitfield32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Global Events"},       // Mandatory is O
                                                                                                                                                                   // 'N' is a count type, which should map to SunspecCount::repeating
                {"N", 1, "module", "", "", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Number of Modules"},
                {"TmsPer", 1, "", "", "", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Timestamp Period"} // Mandatory is O
            },
            {
                // Nested groups start here
                // The 'module' group is a repeating block, counted by the 'N' point in the parent group.
                {
                    "module",                // Nested group name
                    "",                      // Nested group has no explicit 'label' in JSON, so it's ""
                    0, // This group repeats
                    "N",                     // This group's count is given by the point named "N" in the parent.
                                             // Your struct uses 'count_id' for this, which is perfect.
                    SunspecGroupType_kGroup,
                    {// Points for the nested 'module' group
                     {"ID", 1, "", "", "", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Input ID"},
                     {"IDStr", 1, "", "", "", 8, SunspecPointData_kStringx, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Input ID String"},
                     {"DCA", 1, "", "DCA_SF", "A", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "DC Current"},
                     {"DCV", 1, "", "DCV_SF", "V", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "DC Voltage"},
                     {"DCW", 1, "", "DCW_SF", "W", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "DC Power"},
                     {"DCWH", 1, "", "DCWH_SF", "Wh", 2, SunspecPointData_kAcc32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Lifetime Energy"},
                     {"Tms", 1, "", "", "Secs", 2, SunspecPointData_kUint32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Timestamp"},
                     {"Tmp", 1, "", "", "C", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Temperature"},
                     {"DCSt", 1, "", "", "", 1, SunspecPointData_kEnum16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Operating State"},
                     {"DCEvt", 1, "", "", "", 2, SunspecPointData_kBitfield32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Module Events"}},
                    {} // No further nested groups within 'module'
                },
            },
        },
    };
