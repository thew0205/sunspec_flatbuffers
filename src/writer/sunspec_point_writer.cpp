#include "writer/sunspec_point_writer.h"

#include <cmath>

#include <algorithm>

#include "sunspec_adapter.h"

#include "writer/sunspec_group_writer.h"

using std::string;
using std::to_string;

using namespace Sunspec;

SunspecPointWriter::SunspecPointWriter(const SunspecPointDefWrapper &def, SunspecGroupWriter &groupPoint) : def_{def}, group_{groupPoint}, modbusBuffer_{nullptr}, pointFunction_{.uint64 = {.param = nullptr, .function = nullptr}}
{
}

SunspecPointWriter::SunspecPointWriter(const SunspecPointDefWrapper &def, SunspecGroupWriter &groupPoint, SunspecPointFunction valueFunction) : def_{def}, pointFunction_{valueFunction}, group_{groupPoint}, modbusBuffer_{nullptr}
{
}

SunspecPointWriter::~SunspecPointWriter()
{
}

const SunspecDeviceWriter *SunspecPointWriter::getDevice() const
{
    return group_.getDevice();
}

void SunspecPointWriter::setValueToModbusBuffer()
{
    assert(modbusBuffer_ != nullptr && "Modbus buffer pointer is null. Call setModbusBuffer() before setting value to buffer.");
    if (modbusBuffer_ == nullptr)
    {
        return;
    }

    string temp{def_.id()};
    switch (def_.data_type())
    {

    case SunspecPointDataType_Sint16:
    {
        const int16_t valueSint16 = static_cast<int16_t>(uint16_tToModbusRegisterFormat(static_cast<uint16_t>(getValueAsSint16())));
        memcpy(modbusBuffer_, &valueSint16, sizeof(int16_t));
        break;
    }

    case SunspecPointDataType_SunsSf:
    {
        const sunsSf_t valueSunsSf = static_cast<sunsSf_t>(uint16_tToModbusRegisterFormat(getValueAsSunsSf()));
        memcpy(modbusBuffer_, &valueSunsSf, sizeof(sunsSf_t));
        break;
    }

    case SunspecPointDataType_Pad16:
    {
        const pad16_t valuePad16 = static_cast<pad16_t>(uint16_tToModbusRegisterFormat(getValueAsPad16()));
        memcpy(modbusBuffer_, &valuePad16, sizeof(pad16_t));
        break;
    }

    case SunspecPointDataType_Bitfield16:
    {
        const bitfield16_t valueBit16 = static_cast<bitfield16_t>(uint16_tToModbusRegisterFormat(getValueAsBit16()));
        memcpy(modbusBuffer_, &valueBit16, sizeof(bitfield16_t));
        break;
    }

    case SunspecPointDataType_Acc16:
    {
        const acc16_t valueAcc16 = static_cast<acc16_t>(uint16_tToModbusRegisterFormat(getValueAsAcc16()));
        memcpy(modbusBuffer_, &valueAcc16, sizeof(acc16_t));
        break;
    }

    case SunspecPointDataType_Enum16:
    {
        const enum16_t valueEnum16 = static_cast<enum16_t>(uint16_tToModbusRegisterFormat(getValueAsEnum16()));
        memcpy(modbusBuffer_, &valueEnum16, sizeof(enum16_t));
        break;
    }

    case SunspecPointDataType_Raw16:
    {
        const raw16_t valueRaw16 = static_cast<raw16_t>(uint16_tToModbusRegisterFormat(getValueAsRaw16()));
        memcpy(modbusBuffer_, &valueRaw16, sizeof(raw16_t));
        break;
    }

    case SunspecPointDataType_Uint16:
    {
        const uint16_t valueUint16 = static_cast<uint16_t>(uint16_tToModbusRegisterFormat(getValueAsUint16()));
        memcpy(modbusBuffer_, &valueUint16, sizeof(uint16_t));
        break;
    }

    case SunspecPointDataType_Sint32:
    {
        const int32_t valueSint32 = static_cast<int32_t>(uint32_tToModbusRegisterFormat(static_cast<uint32_t>(getValueAsSint32())));
        memcpy(modbusBuffer_, &valueSint32, sizeof(int32_t));
        break;
    }

    case SunspecPointDataType_Float32:
    {
        const float valueFloat32 = floatToModbusRegisterFormat(getValueAsFloat32());
        memcpy(modbusBuffer_, &valueFloat32, sizeof(float));
        break;
    }

    case SunspecPointDataType_Uint32:
    {
        const uint32_t valueUint32 = static_cast<uint32_t>(uint32_tToModbusRegisterFormat(getValueAsUint32()));
        memcpy(modbusBuffer_, &valueUint32, sizeof(uint32_t));
        break;
    }

    case SunspecPointDataType_Acc32:
    {
        const acc32_t valueAcc32 = static_cast<acc32_t>(uint32_tToModbusRegisterFormat(getValueAsAcc32()));
        memcpy(modbusBuffer_, &valueAcc32, sizeof(acc32_t));
        break;
    }

    case SunspecPointDataType_Bitfield32:
    {
        const bitfield32_t valueBit32 = static_cast<bitfield32_t>(uint32_tToModbusRegisterFormat(getValueAsBit32()));
        memcpy(modbusBuffer_, &valueBit32, sizeof(bitfield32_t));
        break;
    }

    case SunspecPointDataType_Enum32:
    {
        const enum32_t valueEnum32 = static_cast<enum32_t>(uint32_tToModbusRegisterFormat(getValueAsEnum32()));
        memcpy(modbusBuffer_, &valueEnum32, sizeof(enum32_t));
        break;
    }
        // Check the Endianess
    case SunspecPointDataType_IpAddr:
    {
        const ipAddr_t valueIpAddr = getValueAsIpAddr();
        memcpy(modbusBuffer_, &valueIpAddr, sizeof(ipAddr_t));
        break;
    }

    case SunspecPointDataType_Float64:
    {
        const double valueFloat64 = doubleToModbusRegisterFormat(getValueAsFloat64());
        memcpy(modbusBuffer_, &valueFloat64, sizeof(double));
        break;
    }

    case SunspecPointDataType_Sint64:
    {
        const int64_t valueSint64 = static_cast<int64_t>(uint64_tToModbusRegisterFormat(static_cast<uint64_t>(getValueAsSint64())));
        memcpy(modbusBuffer_, &valueSint64, sizeof(int64_t));
        break;
    }

    case SunspecPointDataType_Uint64:
    {
        const uint64_t valueUint64 = static_cast<uint64_t>(uint64_tToModbusRegisterFormat(getValueAsUint64()));
        memcpy(modbusBuffer_, &valueUint64, sizeof(uint64_t));
        break;
    }
    case SunspecPointDataType_Acc64:
    {
        const acc64_t valueAcc64 = static_cast<acc64_t>(uint64_tToModbusRegisterFormat(getValueAsAcc64()));
        memcpy(modbusBuffer_, &valueAcc64, sizeof(acc64_t));
        break;
    }
    case SunspecPointDataType_Bitfield64:
    {
        const bitfield64_t valueBit64 = static_cast<bitfield64_t>(uint64_tToModbusRegisterFormat(getValueAsBit64()));
        memcpy(modbusBuffer_, &valueBit64, sizeof(bitfield64_t));
        break;
    }

    case SunspecPointDataType_Stringx:
    {

        const string valueString{getValueAsString()};
        const auto strLength = valueString.size();
        stringToModbusRegisterFormat(valueString, modbusBuffer_, def_.size());
        break;
    }

    // TODO (Matthew): Implementation of variable length types
    case SunspecPointDataType_Ipv6Addr:

    case SunspecPointDataType_Eui48:

    case SunspecPointDataType_NONE:
    default:

        break;
    }
}

string SunspecPointWriter::toJson(bool includeSf, bool includeUnits) const
{
    string ret;
    ret += "\"";
    ret += def_.id();
    ret += "\":";

    uint16_t tempBuf[def_.size()];
    string tempString{};
    // switch (def_.data_type())
    // {

    // case SunspecPointData_Sint16:
    //     *reinterpret_cast<int16_t *>(tempBuf) = valueFunction_.sint16 == nullptr ? def_.data_as_Sint16()->value() : valueFunction_.sint16();
    //     ret += to_string(*reinterpret_cast<int16_t *>(tempBuf));

    //     break;
    // case SunspecPointData_SunsSf:
    // case SunspecPointData_Pad16:
    // case SunspecPointData_Bitfield16:
    // case SunspecPointData_Acc16:
    // case SunspecPointData_Enum16:
    // case SunspecPointData_Raw16:
    // case SunspecPointData_Uint16:
    //     *reinterpret_cast<uint16_t *>(tempBuf) = valueFunction_.uint16 == nullptr ? def_.data_as_Uint16()->value() : valueFunction_.uint16();
    //     ret += to_string(*reinterpret_cast<uint16_t *>(tempBuf));

    //     break;

    // case SunspecPointData_Sint32:
    //     *reinterpret_cast<int32_t *>(tempBuf) = valueFunction_.sint32 == nullptr ? def_.data_as_Sint32()->value() : valueFunction_.sint32();
    //     ret += to_string(*reinterpret_cast<int32_t *>(tempBuf));

    //     break;

    // case SunspecPointData_Float32:
    //     *reinterpret_cast<float *>(tempBuf) = valueFunction_.float32 == nullptr ? def_.data_as_Float32()->value() : valueFunction_.float32();
    //     ret += to_string(*reinterpret_cast<float *>(tempBuf));

    //     break;

    // case SunspecPointData_Uint32:
    // case SunspecPointData_Acc32:
    // case SunspecPointData_Bitfield32:
    // case SunspecPointData_Enum32:
    // case SunspecPointData_IpAddr:
    //     *reinterpret_cast<uint32_t *>(tempBuf) = valueFunction_.uint32 == nullptr ? def_.data_as_Uint32()->value() : valueFunction_.uint32();
    //     ret += to_string(*reinterpret_cast<uint32_t *>(tempBuf));

    //     break;

    // case SunspecPointData_Float64:
    //     *reinterpret_cast<double *>(tempBuf) = valueFunction_.float64 == nullptr ? def_.data_as_Float64()->value() : valueFunction_.float64();
    //     ret += to_string(*reinterpret_cast<double *>(tempBuf));

    //     break;
    // case SunspecPointData_Sint64:
    //     *reinterpret_cast<int64_t *>(tempBuf) = valueFunction_.sint64 == nullptr ? def_.data_as_Sint64()->value() : valueFunction_.sint64();
    //     ret += to_string(*reinterpret_cast<int64_t *>(tempBuf));

    //     break;
    // case SunspecPointData_Uint64:
    // case SunspecPointData_Acc64:
    // case SunspecPointData_Bitfield64:
    //     *reinterpret_cast<uint64_t *>(tempBuf) = valueFunction_.uint64 == nullptr ? def_.data_as_Uint64()->value() : valueFunction_.uint64();
    //     ret += to_string(*reinterpret_cast<uint64_t *>(tempBuf));

    //     break;

    // case SunspecPointData_Stringx:
    //     ret += valueFunction_.str == nullptr ? FormatStringToString(def_.data_as_Stringx()->value()) : valueFunction_.str();
    //     break;

    // // TODO (Matthew): Implementation of variable length types
    // case SunspecPointData_Ipv6Addr:
    // case SunspecPointData_Eui48:

    // case SunspecPointData_NONE:
    // default:

    //     break;
    // }

    ret += includeUnits ? def_.units() : "";
    return ret;
}
