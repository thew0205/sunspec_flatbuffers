#include "writer/sunspec_point_writer.h"

#include <cmath>

#include "sunspec.h"
#include <algorithm>
// #include "writer/sunspec_device_writer.h"
#define MIN(a, b) ((a) < (b) ? (a) : (b))
using std::string;
using std::to_string;

using namespace Sunspec;

SunspecPointWriter::SunspecPointWriter(const SunspecPointDef &def, SunspecGroupWriter &groupPoint, SunspecPointFunction valueFunction) : def_{def}, pointFunction_{valueFunction}, groupPoint_{groupPoint}
{
}

SunspecPointWriter::SunspecPointWriter(const SunspecPointDef &def, uint16_t address, SunspecGroupWriter &groupPoint) : def_{def}, relativeAddress_{address}, groupPoint_{groupPoint}, pointFunction_{.uint64 = {.param = nullptr, .function = nullptr}}
{
}

SunspecPointWriter::~SunspecPointWriter()
{
}

void SunspecPointWriter::setValueToBuffer(uint16_t *buf)
{

    // uint16_t tempBuf[def_.size()];
    string temp{def_.id()->c_str()};
    switch (def_.data_type())
    {

    case SunspecPointData_kSint16:
    {
        const int16_t valueSint16 = sint16_tToModbusRegisterFormat(getValueAsSint16());
        memcpy(buf, &valueSint16, sizeof(int16_t));
        break;
    }

    case SunspecPointData_kSunsSf:
    {
        const sunsSf_t valueSunsSf = uint16_tToModbusRegisterFormat(getValueAsSunsSf());
        memcpy(buf, &valueSunsSf, sizeof(kSunsSf));
        break;
    }

    case SunspecPointData_kPad16:
    {
        const pad16_t valuePad16 = uint16_tToModbusRegisterFormat(getValueAsPad16());
        memcpy(buf, &valuePad16, sizeof(kPad16));
        break;
    }

    case SunspecPointData_kBitfield16:
    {
        const bitfield16_t valueBit16 = uint16_tToModbusRegisterFormat(getValueAsBit16());
        memcpy(buf, &valueBit16, sizeof(bitfield16_t));
        break;
    }

    case SunspecPointData_kAcc16:
    {
        const acc16_t valueAcc16 = uint16_tToModbusRegisterFormat(getValueAsAcc16());
        memcpy(buf, &valueAcc16, sizeof(acc16_t));
        break;
    }

    case SunspecPointData_kEnum16:
    {
        const enum16_t valueEnum16 = uint16_tToModbusRegisterFormat(getValueAsEnum16());
        memcpy(buf, &valueEnum16, sizeof(enum16_t));
        break;
    }

    case SunspecPointData_kRaw16:
    {
        const raw16_t valueRaw16 = uint16_tToModbusRegisterFormat(getValueAsRaw16());
        memcpy(buf, &valueRaw16, sizeof(raw16_t));
        break;
    }

    case SunspecPointData_kUint16:
    {
        const uint16_t valueUint16 = uint16_tToModbusRegisterFormat(getValueAsUint16());
        memcpy(buf, &valueUint16, sizeof(uint16_t));
        break;
    }

    case SunspecPointData_kSint32:
    {
        const int32_t valueSint32 = sint16_tToModbusRegisterFormat(getValueAsSint32());
        memcpy(buf, &valueSint32, sizeof(int32_t));
        break;
    }

    case SunspecPointData_kFloat32:
    {
        const float valueFloat32 = floatToModbusRegisterFormat(getValueAsFloat32());
        memcpy(buf, &valueFloat32, sizeof(float));
        break;
    }

    case SunspecPointData_kUint32:
    {
        const uint32_t valueUint32 = uint32_tToModbusRegisterFormat(getValueAsUint32());
        memcpy(buf, &valueUint32, sizeof(uint32_t));
        break;
    }

    case SunspecPointData_KAcc32:
    {
        const acc32_t valueAcc32 = uint32_tToModbusRegisterFormat(getValueAsAcc32());
        memcpy(buf, &valueAcc32, sizeof(acc32_t));
        break;
    }

    case SunspecPointData_kBitfield32:
    {
        const bit32_t valueBit32 = uint32_tToModbusRegisterFormat(getValueAsBit32());
        memcpy(buf, &valueBit32, sizeof(bit32_t));
        break;
    }

    case SunspecPointData_kEnum32:
    {
        const enum32_t valueEnum32 = uint32_tToModbusRegisterFormat(getValueAsEnum32());
        memcpy(buf, &valueEnum32, sizeof(enum32_t));
        break;
    }
        // Check the Endianess
    case SunspecPointData_kIpAddr:
    {
        const ipAddr_t valueIpAddr = getValueAsIpAddr();
        memcpy(buf, &valueIpAddr, sizeof(kIpAddr));
        break;
    }

    case SunspecPointData_kFloat64:
    {
        const double valueFloat64 = doubleToModbusRegisterFormat(getValueAsFloat64());
        memcpy(buf, &valueFloat64, sizeof(double));
        break;
    }

    case SunspecPointData_kSint64:
    {
        const int64_t valueSint64 = sint64_tToModbusRegisterFormat(getValueAsSint64());
        memcpy(buf, &valueSint64, sizeof(int64_t));
        break;
    }

    case SunspecPointData_kUint64:
    {
        const uint64_t valueUint64 = uint64_tToModbusRegisterFormat(getValueAsUint64());
        memcpy(buf, &valueUint64, sizeof(uint64_t));
        break;
    }
    case SunspecPointData_kAcc64:
    {
        const acc64_t valueAcc64 = uint64_tToModbusRegisterFormat(getValueAsAcc64());
        memcpy(buf, &valueAcc64, sizeof(acc64_t));
        break;
    }
    case SunspecPointData_kBitfield64:
    {
        const bit64_t valueBit64 = uint64_tToModbusRegisterFormat(getValueAsBit64());
        memcpy(buf, &valueBit64, sizeof(bit64_t));
        break;
    }

    case SunspecPointData_kStringx:
    {

        const string valueString{getValueAsString()};
        const auto strLength = valueString.size();
        stringToModbusRegisterFormat(valueString, buf, def_.size());
        // memcpy(buf, valueString.c_str(), strLength);
        // memset(&(reinterpret_cast<uint8_t *>(buf)[strLength]), 0, def_.size() * sizeof(uint16_t) - strLength); // terminate with a null character
        break;
    }

    // TODO (Matthew): Implementation of variable length types
    case SunspecPointData_kIpv6Addr:

    case SunspecPointData_kEui48:

    case SunspecPointData_NONE:
    default:

        break;
    }
}

string SunspecPointWriter::toJson(bool includeSf, bool includeUnits) const
{
    string ret;
    ret += "\"";
    ret += FlatbufferStringToString(def_.id());
    ret += "\":";

    uint16_t tempBuf[def_.size()];
    string tempString{};
    switch (def_.data_type())
    {

    // case SunspecPointData_kSint16:
    //     *reinterpret_cast<int16_t *>(tempBuf) = valueFunction_.sint16 == nullptr ? def_.data_as_kSint16()->value() : valueFunction_.sint16();
    //     ret += to_string(*reinterpret_cast<int16_t *>(tempBuf));

    //     break;
    // case SunspecPointData_kSunsSf:
    // case SunspecPointData_kPad16:
    // case SunspecPointData_kBitfield16:
    // case SunspecPointData_kAcc16:
    // case SunspecPointData_kEnum16:
    // case SunspecPointData_kRaw16:
    // case SunspecPointData_kUint16:
    //     *reinterpret_cast<uint16_t *>(tempBuf) = valueFunction_.uint16 == nullptr ? def_.data_as_kUint16()->value() : valueFunction_.uint16();
    //     ret += to_string(*reinterpret_cast<uint16_t *>(tempBuf));

    //     break;

    // case SunspecPointData_kSint32:
    //     *reinterpret_cast<int32_t *>(tempBuf) = valueFunction_.sint32 == nullptr ? def_.data_as_kSint32()->value() : valueFunction_.sint32();
    //     ret += to_string(*reinterpret_cast<int32_t *>(tempBuf));

    //     break;

    // case SunspecPointData_kFloat32:
    //     *reinterpret_cast<float *>(tempBuf) = valueFunction_.float32 == nullptr ? def_.data_as_kFloat32()->value() : valueFunction_.float32();
    //     ret += to_string(*reinterpret_cast<float *>(tempBuf));

    //     break;

    // case SunspecPointData_kUint32:
    // case SunspecPointData_KAcc32:
    // case SunspecPointData_kBitfield32:
    // case SunspecPointData_kEnum32:
    // case SunspecPointData_kIpAddr:
    //     *reinterpret_cast<uint32_t *>(tempBuf) = valueFunction_.uint32 == nullptr ? def_.data_as_kUint32()->value() : valueFunction_.uint32();
    //     ret += to_string(*reinterpret_cast<uint32_t *>(tempBuf));

    //     break;

    // case SunspecPointData_kFloat64:
    //     *reinterpret_cast<double *>(tempBuf) = valueFunction_.float64 == nullptr ? def_.data_as_kFloat64()->value() : valueFunction_.float64();
    //     ret += to_string(*reinterpret_cast<double *>(tempBuf));

    //     break;
    // case SunspecPointData_kSint64:
    //     *reinterpret_cast<int64_t *>(tempBuf) = valueFunction_.sint64 == nullptr ? def_.data_as_kSint64()->value() : valueFunction_.sint64();
    //     ret += to_string(*reinterpret_cast<int64_t *>(tempBuf));

    //     break;
    // case SunspecPointData_kUint64:
    // case SunspecPointData_kAcc64:
    // case SunspecPointData_kBitfield64:
    //     *reinterpret_cast<uint64_t *>(tempBuf) = valueFunction_.uint64 == nullptr ? def_.data_as_kUint64()->value() : valueFunction_.uint64();
    //     ret += to_string(*reinterpret_cast<uint64_t *>(tempBuf));

    //     break;

    // case SunspecPointData_kStringx:
    //     ret += valueFunction_.str == nullptr ? FlatbufferStringToString(def_.data_as_kStringx()->value()) : valueFunction_.str();
    //     break;

    // TODO (Matthew): Implementation of variable length types
    case SunspecPointData_kIpv6Addr:
    case SunspecPointData_kEui48:

    case SunspecPointData_NONE:
    default:

        break;
    }

    ret += includeUnits ? FlatbufferStringToString(def_.units()) : "";
    return ret;
}
