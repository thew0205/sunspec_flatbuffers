#include "adapters/c_define/c_model_definition.h"
// #include "adapters/c_define/c_model_definition.h"

const SunspecModelDef SunspecModelDef::modelDef101{
        SunspecModelList_kModel101,
        "Inverter (Single Phase)", // Model label
        {
            "inverter_single_phase",   // Group name
            "Inverter (Single Phase)", // Group label
            1,
            "",
            SunspecGroupType_kGroup,
            {// Points for the 'inverter_single_phase' group
             {"ID", 1, "", "", "", 1, SunspecPointData_kUint16, kUint16(101), SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model ID"},
             {"L", 1, "", "", "", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model Length"},
             {"A", 1, "", "A_SF", "A", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Amps"},
             {"AphA", 1, "", "A_SF", "A", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Amps PhaseA"},
             {"AphB", 1, "", "A_SF", "A", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Amps PhaseB"},
             {"AphC", 1, "", "A_SF", "A", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Amps PhaseC"},
             {"A_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, ""}, // Label is empty as per JSON
             {"PPVphAB", 1, "", "V_SF", "V", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Phase Voltage AB"},
             {"PPVphBC", 1, "", "V_SF", "V", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Phase Voltage BC"},
             {"PPVphCA", 1, "", "V_SF", "V", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Phase Voltage CA"},
             {"PhVphA", 1, "", "V_SF", "V", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Phase Voltage AN"},
             {"PhVphB", 1, "", "V_SF", "V", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Phase Voltage BN"},
             {"PhVphC", 1, "", "V_SF", "V", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Phase Voltage CN"},
             {"V_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, ""}, // Label is empty
             {"W", 1, "", "W_SF", "W", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Watts"},
             {"W_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, ""}, // Label is empty
             {"Hz", 1, "", "Hz_SF", "Hz", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Hz"},
             {"Hz_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, ""}, // Label is empty
             {"VA", 1, "", "VA_SF", "VA", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "VA"},
             {"VA_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, ""}, // Label is empty
             {"VAr", 1, "", "VAr_SF", "var", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "VAr"},
             {"VAr_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, ""}, // Label is empty
             {"PF", 1, "", "PF_SF", "Pct", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "PF"},
             {"PF_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, ""}, // Label is empty
             {"WH", 1, "", "WH_SF", "Wh", 2, SunspecPointData_kAcc32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "WattHours"},
             {"WH_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, ""}, // Label is empty
             {"DCA", 1, "", "DCA_SF", "A", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "DC Amps"},
             {"DCA_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, ""}, // Label is empty
             {"DCV", 1, "", "DCV_SF", "V", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "DC Voltage"},
             {"DCV_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, ""}, // Label is empty
             {"DCW", 1, "", "DCW_SF", "W", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "DC Watts"},
             {"DCW_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, ""}, // Label is empty
             {"TmpCab", 1, "", "Tmp_SF", "C", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Cabinet Temperature"},
             {"TmpSnk", 1, "", "Tmp_SF", "C", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Heat Sink Temperature"},
             {"TmpTrns", 1, "", "Tmp_SF", "C", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Transformer Temperature"},
             {"TmpOt", 1, "", "Tmp_SF", "C", 1, SunspecPointData_kSint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Other Temperature"},
             {"Tmp_SF", 1, "", "", "", 1, SunspecPointData_kSunsSf, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, ""}, // Label is empty
             {"St", 1, "", "", "", 1, SunspecPointData_kEnum16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Operating State"},
             {"StVnd", 1, "", "", "", 1, SunspecPointData_kEnum16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Vendor Operating State"},
             {"Evt1", 1, "", "", "", 2, SunspecPointData_kBitfield32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Event1"},
             {"Evt2", 1, "", "", "", 2, SunspecPointData_kBitfield32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Event Bitfield 2"},
             {"EvtVnd1", 1, "", "", "", 2, SunspecPointData_kBitfield32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Vendor Event Bitfield 1"},
             {"EvtVnd2", 1, "", "", "", 2, SunspecPointData_kBitfield32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Vendor Event Bitfield 2"},
             {"EvtVnd3", 1, "", "", "", 2, SunspecPointData_kBitfield32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Vendor Event Bitfield 3"},
             {"EvtVnd4", 1, "", "", "", 2, SunspecPointData_kBitfield32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Vendor Event Bitfield 4"}},
            {} // No nested groups in this model
        },
    };
