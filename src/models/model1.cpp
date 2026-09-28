#include "c_model_definition.h"

// Corrected model1 definition
const SunspecModelDef SunspecModelDef::modelDef1{
        SunspecModelList_kModel1,
        "Common",
        // _topLevelGroupPoint
        {
            "common", // Group name from JSON
            "Common", // Group label from JSON
            1,
            "",
            SunspecGroupType_kGroup,

            {
                {"ID", 1, "", "", "", 1, SunspecPointData_kUint16, kUint16(1), SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model ID"},

                {"L", 1, "", "", "", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model Length"},

                {"Mn", 1, "", "", "", 16, SunspecPointData_kStringx, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Manufacturer"},

                {"Md", 1, "", "", "", 16, SunspecPointData_kStringx, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model"},

                {"Opt", 1, "", "", "", 8, SunspecPointData_kStringx, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Options"}, // Corrected Mandatory

                {"Vr", 1, "", "", "", 8, SunspecPointData_kStringx, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Version"}, // Corrected Mandatory

                {"SN", 1, "", "", "", 16, SunspecPointData_kStringx, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Serial Number"},

                {"DA", 1, "", "", "", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kRW, SunspecPointMandatoryType_kO, "Device Address"}, // Corrected Access and Mandatory

                {"Pad", 1, "", "", "", 1, SunspecPointData_kPad16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, ""} // Corrected Type and Mandatory
            },
            {} // Empty vector for nested groups, as there are none in Model 1
        },
    };
