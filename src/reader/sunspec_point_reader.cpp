#include "reader/sunspec_point_reader.h"

#include <cmath>

#include "sunspec.h"
// #include "reader/sunspec_device_reader.h"

using std::string;
using std::to_string;

using namespace Sunspec;

SunspecPointReader::SunspecPointReader(const SunspecPointDef &def, const uint16_t *modbusBuffer, SunspecGroupReader &groupPoint) : def_{def}, modbusBuffer_{modbusBuffer}, groupPoint_{groupPoint}
{
}

// void SunspecPointReader::setValueFromBuffer()
// {
//     char tempBuf[def_.size() * sizeof(uint16_t) + 1];
//     uint16_t *temp;
//     tempBuf[def_.size() * sizeof(uint16_t)] = '\0';

//     switch (def_.data_type())
//     {

//     case SunspecPointData_kSint16:
//     case SunspecPointData_kSunsSf:
//     case SunspecPointData_kPad16:
//     case SunspecPointData_kBitfield16:
//     case SunspecPointData_kAcc16:
//     case SunspecPointData_kEnum16:
//     case SunspecPointData_kRaw16:
//     case SunspecPointData_kUint16:
// value_.u16 = registersToUint16(modbusBuffer_[0]);
//         break;

//     case SunspecPointData_kSint32:
//     case SunspecPointData_kFloat32:
//     case SunspecPointData_kUint32:
//     case SunspecPointData_KAcc32:
//     case SunspecPointData_kBitfield32:
//     case SunspecPointData_kEnum32:
//     case SunspecPointData_kIpAddr:
//         value_.u32 = registersToUint32(modbusBuffer_[0], modbusBuffer_[1]);
//         break;

//     case SunspecPointData_kFloat64:
//     case SunspecPointData_kSint64:
//     case SunspecPointData_kUint64:
//     case SunspecPointData_kAcc64:
//     case SunspecPointData_kBitfield64:
//         value_.u64 = registersToUint64(modbusBuffer_[0], modbusBuffer_[1], modbusBuffer_[2], modbusBuffer_[3]);
//         break;

//     case SunspecPointData_kStringx:
//         for (int i = 0; i < def_.size(); ++i)
//         {
//             tempBuf[i * sizeof(uint16_t)] = modbusBuffer_[i] >> 8;
//             tempBuf[i * sizeof(uint16_t) + 1] = modbusBuffer_[i] & 0xFF;
//         }

//         value_.str.assign(tempBuf);
//         break;

//     // TODO (Matthew): Implementation of variable length types
//     case SunspecPointData_kIpv6Addr:
//     case SunspecPointData_kEui48:

//     case SunspecPointData_NONE:
//     default:

//         break;
//     }
// }

// SunspecPointReader::SunspecValue const &SunspecPointReader::readFromDevice()
// {
//     uint16_t buf[def_.size() + 1];
//     SunspecDeviceReader *const device = groupPoint_.getDevice();
//     if (device != nullptr && device->read(addr_, buf, def_.size()))
//     {
//         buf[def_.size()] = 0;
//         setValueFromBuffer(buf);
//     }
//     return value_;
// }

// string SunspecPointReader::toJson(bool includeSf, bool includeUnits) const
// {
//     string ret;
//     ret += "\"";
//     ret += def_.id()->c_str();
//     ret += "\":";
//     switch (def_.data_type())
//     {

//     case SunspecPointData_kSint16:
//         ret += (includeSf && !def_.sf_id()->size()) ? to_string(value_.s16 * pow(10, sf_)) : to_string(value_.s16);
//         break;
//     case SunspecPointData_kSunsSf:
//         ret += to_string(value_.s16);
//         break;

//     case SunspecPointData_kPad16:
//     case SunspecPointData_kBitfield16:
//     case SunspecPointData_kAcc16:
//     case SunspecPointData_kEnum16:
//     case SunspecPointData_kRaw16:
//         ret += to_string(value_.u16);
//         break;
//     case SunspecPointData_kUint16:
//         ret += (includeSf && !def_.sf_id()->size()) ? to_string(value_.u16 * pow(10, sf_)) : to_string(value_.u16);
//         break;

//     case SunspecPointData_kSint32:
//         ret += (includeSf && !def_.sf_id()->size()) ? to_string(value_.s32 * pow(10, sf_)) : to_string(value_.s32);
//         break;
//     case SunspecPointData_kUint32:
//         ret += (includeSf && !def_.sf_id()->size()) ? to_string(value_.u32 * pow(10, sf_)) : to_string(value_.u32);
//         break;
//     case SunspecPointData_KAcc32:
//     case SunspecPointData_kBitfield32:
//     case SunspecPointData_kEnum32:
//     case SunspecPointData_kIpAddr:
//         ret += to_string(value_.u32);
//         break;

//     case SunspecPointData_kSint64:
//         ret += (includeSf && !def_.sf_id()->size()) ? to_string(value_.s64 * pow(10, sf_)) : to_string(value_.s64);
//         break;
//         break;

//     case SunspecPointData_kUint64:
//         ret += (includeSf && !def_.sf_id()->size()) ? to_string(value_.u64 * pow(10, sf_)) : to_string(value_.u64);
//         break;
//     case SunspecPointData_kAcc64:
//     case SunspecPointData_kBitfield64:
//         ret += to_string(value_.u64);
//         break;

//     case SunspecPointData_kFloat32:
//         ret += to_string(value_.f32);
//         break;

//     case SunspecPointData_kFloat64:
//         ret += to_string(value_.f64);
//         break;

//         // TODO: Implementation of variable length types
//     case SunspecPointData_kStringx:
//         ret += "\"" + value_.str + "\"";
//         break;
//     case SunspecPointData_kIpv6Addr:
//     case SunspecPointData_kEui48:
//     case SunspecPointData_NONE:
//     default:

//         break;
//     }

//     ret += includeUnits ? def_.units()->c_str() : "";
//     return ret;
// }

string SunspecPointReader::getValueAsString() const
{
    string ret;

    switch (def_.data_type())
    {

    case SunspecPointData_kSint16:
        ret = to_string(modbusRegisterFormatToSint16(modbusBuffer_));
        break;
    case SunspecPointData_kSunsSf:
        ret += to_string(modbusRegisterFormatToSunsSf(modbusBuffer_));
        break;

    case SunspecPointData_kUint16:
    case SunspecPointData_kPad16:
    case SunspecPointData_kBitfield16:
    case SunspecPointData_kAcc16:
    case SunspecPointData_kEnum16:
    case SunspecPointData_kRaw16:
        ret += to_string(modbusRegisterFormatToUint16(modbusBuffer_));
        break;

    case SunspecPointData_kSint32:
        ret += to_string(modbusRegisterFormatToSint32(modbusBuffer_));
        break;
    case SunspecPointData_kUint32:
    case SunspecPointData_KAcc32:
    case SunspecPointData_kBitfield32:
    case SunspecPointData_kEnum32:
        ret += to_string(modbusRegisterFormatToUint64(modbusBuffer_));
        break;

    case SunspecPointData_kSint64:
        ret += to_string(modbusRegisterFormatToSint64(modbusBuffer_));
        break;

    case SunspecPointData_kUint64:
    case SunspecPointData_kAcc64:
    case SunspecPointData_kBitfield64:
        ret += to_string(modbusRegisterFormatToUint64(modbusBuffer_));
        break;

    case SunspecPointData_kFloat32:
        ret += to_string(modbusRegisterFormatToFloat(modbusBuffer_));
        break;

    case SunspecPointData_kFloat64:
        ret += to_string(modbusRegisterFormatToDouble(modbusBuffer_));
        break;

    case SunspecPointData_kStringx:
        ret += modbusRegisterFormatToString(modbusBuffer_, def_.size());
        break;
        // TODO: Implementation of variable length types

    case SunspecPointData_kIpAddr:
    case SunspecPointData_kIpv6Addr:
    case SunspecPointData_kEui48:
    case SunspecPointData_NONE:
    default:

        break;
    }

    return ret;
}