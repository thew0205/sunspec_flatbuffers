#include "c_model_definition.h"

const SunspecModelDef SunspecModelDef::modelDef113{
        SunspecModelList_kModel113,
        "Inverter (Three Phase) FLOAT", // Model label
        {
            "inverter_three_phase_float",   // Group name
            "Inverter (Three Phase) FLOAT", // Group label
            1,
            "",
            SunspecGroupType_kGroup,
            {// Points for the 'inverter_three_phase_float' group
             {"ID", 1, "", "", "", 1, SunspecPointData_kUint16, kUint16(113), SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model ID"},
             {"L", 1, "", "", "", 1, SunspecPointData_kUint16, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model Length"},
             {"A", 1, "", "", "A", 2, SunspecPointData_kFloat32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Amps"},
             {"AphA", 1, "", "", "A", 2, SunspecPointData_kFloat32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Amps PhaseA"},
             {"AphB", 1, "", "", "A", 2, SunspecPointData_kFloat32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Amps PhaseB"},
             {"AphC", 1, "", "", "A", 2, SunspecPointData_kFloat32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Amps PhaseC"},
             {"PPVphAB", 1, "", "", "V", 2, SunspecPointData_kFloat32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Phase Voltage AB"},
             {"PPVphBC", 1, "", "", "V", 2, SunspecPointData_kFloat32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Phase Voltage BC"},
             {"PPVphCA", 1, "", "", "V", 2, SunspecPointData_kFloat32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Phase Voltage CA"},
             {"PhVphA", 1, "", "", "V", 2, SunspecPointData_kFloat32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Phase Voltage AN"},
             {"PhVphB", 1, "", "", "V", 2, SunspecPointData_kFloat32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Phase Voltage BN"},
             {"PhVphC", 1, "", "", "V", 2, SunspecPointData_kFloat32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Phase Voltage CN"},
             {"W", 1, "", "", "W", 2, SunspecPointData_kFloat32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Watts"},
             {"Hz", 1, "", "", "Hz", 2, SunspecPointData_kFloat32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Hz"},
             {"VA", 1, "", "", "VA", 2, SunspecPointData_kFloat32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "VA"},
             {"VAr", 1, "", "", "var", 2, SunspecPointData_kFloat32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "VAr"},
             {"PF", 1, "", "", "Pct", 2, SunspecPointData_kFloat32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "PF"},
             {"WH", 1, "", "", "Wh", 2, SunspecPointData_kFloat32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "WattHours"},
             {"DCA", 1, "", "", "A", 2, SunspecPointData_kFloat32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "DC Amps"},
             {"DCV", 1, "", "", "V", 2, SunspecPointData_kFloat32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "DC Voltage"},
             {"DCW", 1, "", "", "W", 2, SunspecPointData_kFloat32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "DC Watts"},
             {"TmpCab", 1, "", "", "C", 2, SunspecPointData_kFloat32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Cabinet Temperature"},
             {"TmpSnk", 1, "", "", "C", 2, SunspecPointData_kFloat32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Heat Sink Temperature"},
             {"TmpTrns", 1, "", "", "C", 2, SunspecPointData_kFloat32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Transformer Temperature"},
             {"TmpOt", 1, "", "", "C", 2, SunspecPointData_kFloat32, {}, SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Other Temperature"},
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
