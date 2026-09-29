#include "adapters/c_define/c_model_definition.h"
SunspecModelDef SunspecModelDef::modelDef120(){
        return SunspecModelDef{
        SunspecModelList_kModel120,
        "Nameplate", // Model label from JSON: "label": "Nameplate"
        {
            "nameplate", // Group name from JSON: "name": "nameplate"
            "Nameplate", // Group label from JSON: "label": "Nameplate"
            1,
            "",
            SunspecGroupType_kGroup,
            {
                // Points start here {using 'label' field from JSON, or "" if missing}
                {"ID", 1, "", "", "", 1, SunspecPointData_kUint16, kUint16(120), SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model ID"},
                {"L", 1, "", "", "", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model Length"},
                {"DERTyp", 1, "", "", "", 1, SunspecPointData_kEnum16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "DERTyp"},                             // Label for DERTyp from JSON
                {"WRtg", 1, "", "WRtg_SF", "W", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "WRtg"},                         // Label for WRtg from JSON
                {"WRtg_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "WRtg_SF"},                           // Label for WRtg_SF from JSON
                {"VARtg", 1, "", "VARtg_SF", "VA", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "VARtg"},                     // Label for VARtg from JSON
                {"VARtg_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "VARtg_SF"},                         // Label for VARtg_SF from JSON
                {"VArRtgQ1", 1, "", "VArRtg_SF", "var", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "VArRtgQ1"},              // Label for VArRtgQ1 from JSON
                {"VArRtgQ2", 1, "", "VArRtg_SF", "var", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "VArRtgQ2"},              // Label for VArRtgQ2 from JSON
                {"VArRtgQ3", 1, "", "VArRtg_SF", "var", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "VArRtgQ3"},              // Label for VArRtgQ3 from JSON
                {"VArRtgQ4", 1, "", "VArRtg_SF", "var", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "VArRtgQ4"},              // Label for VArRtgQ4 from JSON
                {"VArRtg_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "VArRtg_SF"},                       // Label for VArRtg_SF from JSON
                {"ARtg", 1, "", "ARtg_SF", "A", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "ARtg"},                         // Label for ARtg from JSON
                {"ARtg_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "ARtg_SF"},                           // Label for ARtg_SF from JSON
                {"PFRtgQ1", 1, "", "PFRtg_SF", "cos{}", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "PFRtgQ1"},               // Label for PFRtgQ1 from JSON
                {"PFRtgQ2", 1, "", "PFRtg_SF", "cos{}", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "PFRtgQ2"},               // Label for PFRtgQ2 from JSON
                {"PFRtgQ3", 1, "", "PFRtg_SF", "cos{}", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "PFRtgQ3"},               // Label for PFRtgQ3 from JSON
                {"PFRtgQ4", 1, "", "PFRtg_SF", "cos{}", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "PFRtgQ4"},               // Label for PFRtgQ4 from JSON
                {"PFRtg_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "PFRtg_SF"},                         // Label for PFRtg_SF from JSON
                {"WHRtg", 1, "", "WHRtg_SF", "Wh", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "WHRtg"},                     // Label for WHRtg from JSON
                {"WHRtg_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "WHRtg_SF"},                         // Label for WHRtg_SF from JSON
                {"AhrRtg", 1, "", "AhrRtg_SF", "AH", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "AhrRtg"},                  // Label for AhrRtg from JSON
                {"AhrRtg_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "AhrRtg_SF"},                       // Label for AhrRtg_SF from JSON
                {"MaxChaRte", 1, "", "MaxChaRte_SF", "W", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "MaxChaRte"},          // Label for MaxChaRte from JSON
                {"MaxChaRte_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "MaxChaRte_SF"},                 // Label for MaxChaRte_SF from JSON
                {"MaxDisChaRte", 1, "", "MaxDisChaRte_SF", "W", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "MaxDisChaRte"}, // Label for MaxDisChaRte from JSON
                {"MaxDisChaRte_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "MaxDisChaRte_SF"},           // Label for MaxDisChaRte_SF from JSON
                {"Pad", 1, "", "", "", 1, SunspecPointData_kPad16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Pad"}                                       // Label for Pad from JSON
            },
            {} // Empty vector for nested groups
        },
    };
}
