#include "writer/sunspec_point_writer.h"

#include <cmath>

#include "sunspec_utils.h"
// #include "writer/sunspec_device_writer.h"

using std::string;
using std::to_string;

using namespace Sunspec;

SunspecPointWriter::SunspecPointWriter(const SunspecPointDef &def, uint16_t address, SunspecGroupWriter &groupPoint, SunspecValueFunction valueFunction) : def_{def}, address_{address}, valueFunction_{valueFunction}, groupPoint_{groupPoint}
{
}

SunspecPointWriter::SunspecPointWriter(const SunspecPointDef &def, uint16_t address, SunspecGroupWriter &groupPoint) : def_{def}, address_{address}, valueFunction_{nullptr}, groupPoint_{groupPoint}
{
}

SunspecPointWriter::~SunspecPointWriter()
{
}

void SunspecPointWriter::setValueToBuffer(uint16_t *buf)
{
    uint16_t tempBuf[def_.size()];
    string tempString{def_.id()->c_str()};
    switch (def_.type())
    {

    case SunspecPointDataType_kInt16:
        *reinterpret_cast<int16_t *>(tempBuf) = valueFunction_.sint16 == nullptr ? kSint16UnimplementedValue : valueFunction_.sint16();
        memcpy(buf, tempBuf, sizeof(int16_t));
        break;
    case SunspecPointDataType_kSunsSf:
    case SunspecPointDataType_kPad:
    case SunspecPointDataType_kBitField16:
    case SunspecPointDataType_kAcc16:
    case SunspecPointDataType_kEnum16:
    case SunspecPointDataType_kRaw16:
    case SunspecPointDataType_kUint16:
        *reinterpret_cast<uint16_t *>(tempBuf) = valueFunction_.uint16 == nullptr ? kUint16UnimplementedValue : valueFunction_.uint16();
        memcpy(buf, tempBuf, sizeof(uint16_t));
        break;

    case SunspecPointDataType_kInt32:
        *reinterpret_cast<int32_t *>(tempBuf) = valueFunction_.sint32 == nullptr ? kSint32UnimplementedValue : valueFunction_.sint32();
        memcpy(buf, tempBuf, sizeof(int32_t));
        break;

    case SunspecPointDataType_kFloat32:
        if (valueFunction_.float64 == nullptr)
        {
            *reinterpret_cast<uint32_t *>(tempBuf) = 0x7FC00000;
        }
        else
        {
            *reinterpret_cast<float *>(tempBuf) = valueFunction_.float32();
        }
        memcpy(buf, tempBuf, sizeof(float));
        break;

    case SunspecPointDataType_kUint32:
    case SunspecPointDataType_KAcc32:
    case SunspecPointDataType_kBitField32:
    case SunspecPointDataType_kEnum32:
    case SunspecPointDataType_kIpAddr:
        *reinterpret_cast<uint32_t *>(tempBuf) = valueFunction_.uint32 == nullptr ? kSint32UnimplementedValue : valueFunction_.uint32();
        memcpy(buf, tempBuf, sizeof(uint32_t));
        break;

    case SunspecPointDataType_kFloat64:
        if (valueFunction_.float64 == nullptr)
        {
            *reinterpret_cast<uint64_t *>(tempBuf) = 0x7FF8000000000000;
        }
        else
        {
            *reinterpret_cast<double *>(tempBuf) = valueFunction_.float64();
        }
        memcpy(buf, tempBuf, sizeof(double));
        break;
    case SunspecPointDataType_kInt64:
        *reinterpret_cast<int64_t *>(tempBuf) = valueFunction_.sint64 == nullptr ? kSint64UnimplementedValue : valueFunction_.sint64();
        memcpy(buf, tempBuf, sizeof(int64_t));
        break;
    case SunspecPointDataType_kUint64:
    case SunspecPointDataType_kAcc64:
    case SunspecPointDataType_kBitField64:
        *reinterpret_cast<uint64_t *>(tempBuf) = valueFunction_.uint64 == nullptr ? kUint64UnimplementedValue : valueFunction_.uint64();
        memcpy(buf, tempBuf, sizeof(uint64_t));
        break;

    case SunspecPointDataType_kString:
        tempString = valueFunction_.str == nullptr ? "" : valueFunction_.str();
        // TODO (Matthew) Compare the string length to the size of buffer and cut off excess.
        memcpy(buf, tempString.c_str(), tempString.size());
        // memset(reinterpret_cast<char*> (buf) + tempString.size(), '\0', def_.size()- )
        break;

    // TODO (Matthew): Implementation of variable length types
    case SunspecPointDataType_kIpv6Addr:
    case SunspecPointDataType_kEui48:

    case SunspecPointDataType_kUndefinedType:
    default:

        break;
    }
}

string SunspecPointWriter::toJson(bool includeSf, bool includeUnits) const
{
    string ret;
    ret += "\"";
    ret += def_.id()->c_str();
    ret += "\":";

    uint16_t tempBuf[def_.size()];
    string tempString{};
    switch (def_.type())
    {

    case SunspecPointDataType_kInt16:
        *reinterpret_cast<int16_t *>(tempBuf) = valueFunction_.sint16 == nullptr ? kSint16UnimplementedValue : valueFunction_.sint16();
        ret += to_string(*reinterpret_cast<int16_t *>(tempBuf));

        break;
    case SunspecPointDataType_kSunsSf:
    case SunspecPointDataType_kPad:
    case SunspecPointDataType_kBitField16:
    case SunspecPointDataType_kAcc16:
    case SunspecPointDataType_kEnum16:
    case SunspecPointDataType_kRaw16:
    case SunspecPointDataType_kUint16:
        *reinterpret_cast<uint16_t *>(tempBuf) = valueFunction_.uint16 == nullptr ? kUint16UnimplementedValue : valueFunction_.uint16();
        ret += to_string(*reinterpret_cast<uint16_t *>(tempBuf));

        break;

    case SunspecPointDataType_kInt32:
        *reinterpret_cast<int32_t *>(tempBuf) = valueFunction_.sint32 == nullptr ? kSint32UnimplementedValue : valueFunction_.sint32();
        ret += to_string(*reinterpret_cast<int32_t *>(tempBuf));

        break;

    case SunspecPointDataType_kFloat32:
        *reinterpret_cast<float *>(tempBuf) = valueFunction_.float32 == nullptr ? 0.f : valueFunction_.float32();
        ret += to_string(*reinterpret_cast<float *>(tempBuf));

        break;

    case SunspecPointDataType_kUint32:
    case SunspecPointDataType_KAcc32:
    case SunspecPointDataType_kBitField32:
    case SunspecPointDataType_kEnum32:
    case SunspecPointDataType_kIpAddr:
        *reinterpret_cast<uint32_t *>(tempBuf) = valueFunction_.uint32 == nullptr ? kSint32UnimplementedValue : valueFunction_.uint32();
        ret += to_string(*reinterpret_cast<uint32_t *>(tempBuf));

        break;

    case SunspecPointDataType_kFloat64:
        *reinterpret_cast<double *>(tempBuf) = valueFunction_.float64 == nullptr ? 0.00f : valueFunction_.float64();
        ret += to_string(*reinterpret_cast<double *>(tempBuf));

        break;
    case SunspecPointDataType_kInt64:
        *reinterpret_cast<int64_t *>(tempBuf) = valueFunction_.sint64 == nullptr ? kSint64UnimplementedValue : valueFunction_.sint64();
        ret += to_string(*reinterpret_cast<int64_t *>(tempBuf));

        break;
    case SunspecPointDataType_kUint64:
    case SunspecPointDataType_kAcc64:
    case SunspecPointDataType_kBitField64:
        *reinterpret_cast<uint64_t *>(tempBuf) = valueFunction_.uint64 == nullptr ? kSint64UnimplementedValue : valueFunction_.uint64();
        ret += to_string(*reinterpret_cast<uint64_t *>(tempBuf));

        break;

    case SunspecPointDataType_kString:
        ret += valueFunction_.str == nullptr ? "" : valueFunction_.str();
        break;

    // TODO (Matthew): Implementation of variable length types
    case SunspecPointDataType_kIpv6Addr:
    case SunspecPointDataType_kEui48:

    case SunspecPointDataType_kUndefinedType:
    default:

        break;
    }

    ret += includeUnits ? def_.units()->c_str() : "";
    return ret;
}
