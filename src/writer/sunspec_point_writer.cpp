#include "writer/sunspec_point_writer.h"

#include <cmath>

#include "sunspec_utils.h"
// #include "writer/sunspec_device_writer.h"

using std::string;
using std::to_string;

using namespace Sunspec;

SunspecPointWriter::SunspecPointWriter(const SunspecPointDef &def, uint16_t address, SunspecGroupWriter &groupPoint, SunspecValueFunction valueFunction) : def_{def}, relativeAddress_{address}, valueFunction_{valueFunction}, groupPoint_{groupPoint}
{
}

SunspecPointWriter::SunspecPointWriter(const SunspecPointDef &def, uint16_t address, SunspecGroupWriter &groupPoint) : def_{def}, relativeAddress_{address}, valueFunction_{nullptr}, groupPoint_{groupPoint}
{
}

SunspecPointWriter::~SunspecPointWriter()
{
}

void SunspecPointWriter::setValueToBuffer(uint16_t *buf)
{

    uint16_t tempBuf[def_.size()];
    string tempString{def_.id()->c_str()};
    switch (def_.data_type())
    {

    case SunspecPointData_kSint16:
        *reinterpret_cast<int16_t *>(tempBuf) = valueFunction_.sint16 == nullptr ? def_.data_as_kSint16()->value() : valueFunction_.sint16();
        memcpy(buf, tempBuf, sizeof(int16_t));
        break;
    case SunspecPointData_kSunsSf:
    case SunspecPointData_kPad16:
    case SunspecPointData_kBitField16:
    case SunspecPointData_kAcc16:
    case SunspecPointData_kEnum16:
    case SunspecPointData_kRaw16:
    case SunspecPointData_kUint16:
        *reinterpret_cast<uint16_t *>(tempBuf) = valueFunction_.uint16 == nullptr ? def_.data_as_kUint16()->value() : valueFunction_.uint16();
        memcpy(buf, tempBuf, sizeof(uint16_t));
        break;

    case SunspecPointData_kSint32:
        *reinterpret_cast<int32_t *>(tempBuf) = valueFunction_.sint32 == nullptr ? def_.data_as_kSint32()->value() : valueFunction_.sint32();
        break;

    case SunspecPointData_kFloat32:
        *reinterpret_cast<float *>(tempBuf) = valueFunction_.float32 == nullptr ? def_.data_as_kFloat32()->value() : valueFunction_.float32();
        memcpy(buf, tempBuf, sizeof(float));
        break;

    case SunspecPointData_kUint32:
    case SunspecPointData_KAcc32:
    case SunspecPointData_kBitField32:
    case SunspecPointData_kEnum32:
    case SunspecPointData_kIpAddr:
        *reinterpret_cast<uint32_t *>(tempBuf) = valueFunction_.uint32 == nullptr ? def_.data_as_kUint32()->value() : valueFunction_.uint32();
        memcpy(buf, tempBuf, sizeof(uint32_t));
        break;

    case SunspecPointData_kFloat64:
        *reinterpret_cast<double *>(tempBuf) = valueFunction_.float64 == nullptr ? def_.data_as_kFloat64()->value() : valueFunction_.float64();
        memcpy(buf, tempBuf, sizeof(double));
        break;
    case SunspecPointData_kSint64:
        *reinterpret_cast<int64_t *>(tempBuf) = valueFunction_.sint64 == nullptr ? def_.data_as_kSint64()->value() : valueFunction_.sint64();
        memcpy(buf, tempBuf, sizeof(int64_t));
        break;
    case SunspecPointData_kUint64:
    case SunspecPointData_kAcc64:
    case SunspecPointData_kBitField64:
        *reinterpret_cast<uint64_t *>(tempBuf) = valueFunction_.uint64 == nullptr ? def_.data_as_kUint64()->value() : valueFunction_.uint64();
        memcpy(buf, tempBuf, sizeof(uint64_t));
        break;

    case SunspecPointData_kStringx:
        tempString = valueFunction_.str == nullptr ? def_.data_as_kStringx()->value()->c_str() : valueFunction_.str();
        // TODO (Matthew) Compare the string length to the size of buffer and cut off excess.
        memcpy(buf, tempString.c_str(), tempString.size());
        // memset(reinterpret_cast<char*> (buf) + tempString.size(), '\0', def_.size()- )
        break;

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
    ret += def_.id()->c_str();
    ret += "\":";

    uint16_t tempBuf[def_.size()];
    string tempString{};
    switch (def_.data_type())
    {

    case SunspecPointData_kSint16:
        *reinterpret_cast<int16_t *>(tempBuf) = valueFunction_.sint16 == nullptr ? def_.data_as_kSint16()->value() : valueFunction_.sint16();
        ret += to_string(*reinterpret_cast<int16_t *>(tempBuf));

        break;
    case SunspecPointData_kSunsSf:
    case SunspecPointData_kPad16:
    case SunspecPointData_kBitField16:
    case SunspecPointData_kAcc16:
    case SunspecPointData_kEnum16:
    case SunspecPointData_kRaw16:
    case SunspecPointData_kUint16:
        *reinterpret_cast<uint16_t *>(tempBuf) = valueFunction_.uint16 == nullptr ? def_.data_as_kUint16()->value() : valueFunction_.uint16();
        ret += to_string(*reinterpret_cast<uint16_t *>(tempBuf));

        break;

    case SunspecPointData_kSint32:
        *reinterpret_cast<int32_t *>(tempBuf) = valueFunction_.sint32 == nullptr ? def_.data_as_kSint32()->value() : valueFunction_.sint32();
        ret += to_string(*reinterpret_cast<int32_t *>(tempBuf));

        break;

    case SunspecPointData_kFloat32:
        *reinterpret_cast<float *>(tempBuf) = valueFunction_.float32 == nullptr ? def_.data_as_kFloat32()->value() : valueFunction_.float32();
        ret += to_string(*reinterpret_cast<float *>(tempBuf));

        break;

    case SunspecPointData_kUint32:
    case SunspecPointData_KAcc32:
    case SunspecPointData_kBitField32:
    case SunspecPointData_kEnum32:
    case SunspecPointData_kIpAddr:
        *reinterpret_cast<uint32_t *>(tempBuf) = valueFunction_.uint32 == nullptr ? def_.data_as_kUint32()->value() : valueFunction_.uint32();
        ret += to_string(*reinterpret_cast<uint32_t *>(tempBuf));

        break;

    case SunspecPointData_kFloat64:
        *reinterpret_cast<double *>(tempBuf) = valueFunction_.float64 == nullptr ? def_.data_as_kFloat64()->value() : valueFunction_.float64();
        ret += to_string(*reinterpret_cast<double *>(tempBuf));

        break;
    case SunspecPointData_kSint64:
        *reinterpret_cast<int64_t *>(tempBuf) = valueFunction_.sint64 == nullptr ? def_.data_as_kSint64()->value() : valueFunction_.sint64();
        ret += to_string(*reinterpret_cast<int64_t *>(tempBuf));

        break;
    case SunspecPointData_kUint64:
    case SunspecPointData_kAcc64:
    case SunspecPointData_kBitField64:
        *reinterpret_cast<uint64_t *>(tempBuf) = valueFunction_.uint64 == nullptr ? def_.data_as_kUint64()->value() : valueFunction_.uint64();
        ret += to_string(*reinterpret_cast<uint64_t *>(tempBuf));

        break;

    case SunspecPointData_kStringx:
        ret += valueFunction_.str == nullptr ? def_.data_as_kStringx()->value()->c_str() : valueFunction_.str();
        break;

    // TODO (Matthew): Implementation of variable length types
    case SunspecPointData_kIpv6Addr:
    case SunspecPointData_kEui48:

    case SunspecPointData_NONE:
    default:

        break;
    }

    ret += includeUnits ? def_.units()->c_str() : "";
    return ret;
}
