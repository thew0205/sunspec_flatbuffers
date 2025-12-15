#include "reader/sunspec_point_reader.h"

#include <cmath>

#include "sunspec.h"
// #include "reader/sunspec_device_reader.h"

using std::string;
using std::to_string;

using namespace Sunspec;

SunspecPointReader::SunspecPointReader(const SunspecPointDefWrapper &def, const uint16_t *modbusBuffer, SunspecGroupReader &groupPoint) : def_{def}, modbusBuffer_{modbusBuffer}, groupPoint_{groupPoint}
{
}

// void SunspecPointReader::setValueFromBuffer()
// {
//     char tempBuf[def_.size() * sizeof(uint16_t) + 1];
//     uint16_t *temp;
//     tempBuf[def_.size() * sizeof(uint16_t)] = '\0';

//     switch (def_.data_type())
//     {

//     case SunspecPointDataType_Sint16:
//     case SunspecPointDataType_SunsSf:
//     case SunspecPointDataType_Pad16:
//     case SunspecPointDataType_Bitfield16:
//     case SunspecPointDataType_Acc16:
//     case SunspecPointDataType_Enum16:
//     case SunspecPointDataType_Raw16:
//     case SunspecPointDataType_Uint16:
// value_.u16 = registersToUint16(modbusBuffer_[0]);
//         break;

//     case SunspecPointDataType_Sint32:
//     case SunspecPointDataType_Float32:
//     case SunspecPointDataType_Uint32:
//     case SunspecPointDataType_Acc32:
//     case SunspecPointDataType_Bitfield32:
//     case SunspecPointDataType_Enum32:
//     case SunspecPointDataType_IpAddr:
//         value_.u32 = registersToUint32(modbusBuffer_[0], modbusBuffer_[1]);
//         break;

//     case SunspecPointDataType_Float64:
//     case SunspecPointDataType_Sint64:
//     case SunspecPointDataType_Uint64:
//     case SunspecPointDataType_Acc64:
//     case SunspecPointDataType_Bitfield64:
//         value_.u64 = registersToUint64(modbusBuffer_[0], modbusBuffer_[1], modbusBuffer_[2], modbusBuffer_[3]);
//         break;

//     case SunspecPointDataType_Stringx:
//         for (int i = 0; i < def_.size(); ++i)
//         {
//             tempBuf[i * sizeof(uint16_t)] = modbusBuffer_[i] >> 8;
//             tempBuf[i * sizeof(uint16_t) + 1] = modbusBuffer_[i] & 0xFF;
//         }

//         value_.str.assign(tempBuf);
//         break;

//     // TODO (Matthew): Implementation of variable length types
//     case SunspecPointDataType_Ipv6Addr:
//     case SunspecPointDataType_Eui48:

//     case SunspecPointDataType_ONE:
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

//     case SunspecPointDataType_Sint16:
//         ret += (includeSf && !def_.sf_id()->size()) ? to_string(value_.s16 * pow(10, sf_)) : to_string(value_.s16);
//         break;
//     case SunspecPointDataType_SunsSf:
//         ret += to_string(value_.s16);
//         break;

//     case SunspecPointDataType_Pad16:
//     case SunspecPointDataType_Bitfield16:
//     case SunspecPointDataType_Acc16:
//     case SunspecPointDataType_Enum16:
//     case SunspecPointDataType_Raw16:
//         ret += to_string(value_.u16);
//         break;
//     case SunspecPointDataType_Uint16:
//         ret += (includeSf && !def_.sf_id()->size()) ? to_string(value_.u16 * pow(10, sf_)) : to_string(value_.u16);
//         break;

//     case SunspecPointDataType_Sint32:
//         ret += (includeSf && !def_.sf_id()->size()) ? to_string(value_.s32 * pow(10, sf_)) : to_string(value_.s32);
//         break;
//     case SunspecPointDataType_Uint32:
//         ret += (includeSf && !def_.sf_id()->size()) ? to_string(value_.u32 * pow(10, sf_)) : to_string(value_.u32);
//         break;
//     case SunspecPointDataType_Acc32:
//     case SunspecPointDataType_Bitfield32:
//     case SunspecPointDataType_Enum32:
//     case SunspecPointDataType_IpAddr:
//         ret += to_string(value_.u32);
//         break;

//     case SunspecPointDataType_Sint64:
//         ret += (includeSf && !def_.sf_id()->size()) ? to_string(value_.s64 * pow(10, sf_)) : to_string(value_.s64);
//         break;
//         break;

//     case SunspecPointDataType_Uint64:
//         ret += (includeSf && !def_.sf_id()->size()) ? to_string(value_.u64 * pow(10, sf_)) : to_string(value_.u64);
//         break;
//     case SunspecPointDataType_Acc64:
//     case SunspecPointDataType_Bitfield64:
//         ret += to_string(value_.u64);
//         break;

//     case SunspecPointDataType_Float32:
//         ret += to_string(value_.f32);
//         break;

//     case SunspecPointDataType_Float64:
//         ret += to_string(value_.f64);
//         break;

//         // TODO: Implementation of variable length types
//     case SunspecPointDataType_Stringx:
//         ret += "\"" + value_.str + "\"";
//         break;
//     case SunspecPointDataType_Ipv6Addr:
//     case SunspecPointDataType_Eui48:
//     case SunspecPointDataType_ONE:
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

    case SunspecPointDataType_Sint16:
        ret = to_string(modbusRegisterFormatToSint16(modbusBuffer_));
        break;
    case SunspecPointDataType_SunsSf:
        ret += to_string(modbusRegisterFormatToSunsSf(modbusBuffer_));
        break;

    case SunspecPointDataType_Uint16:
    case SunspecPointDataType_Pad16:
    case SunspecPointDataType_Bitfield16:
    case SunspecPointDataType_Acc16:
    case SunspecPointDataType_Enum16:
    case SunspecPointDataType_Raw16:
        ret += to_string(modbusRegisterFormatToUint16(modbusBuffer_));
        break;

    case SunspecPointDataType_Sint32:
        ret += to_string(modbusRegisterFormatToSint32(modbusBuffer_));
        break;
    case SunspecPointDataType_Uint32:
    case SunspecPointDataType_Acc32:
    case SunspecPointDataType_Bitfield32:
    case SunspecPointDataType_Enum32:
        ret += to_string(modbusRegisterFormatToUint64(modbusBuffer_));
        break;

    case SunspecPointDataType_Sint64:
        ret += to_string(modbusRegisterFormatToSint64(modbusBuffer_));
        break;

    case SunspecPointDataType_Uint64:
    case SunspecPointDataType_Acc64:
    case SunspecPointDataType_Bitfield64:
        ret += to_string(modbusRegisterFormatToUint64(modbusBuffer_));
        break;

    case SunspecPointDataType_Float32:
        ret += to_string(modbusRegisterFormatToFloat(modbusBuffer_));
        break;

    case SunspecPointDataType_Float64:
        ret += to_string(modbusRegisterFormatToDouble(modbusBuffer_));
        break;

    case SunspecPointDataType_Stringx:
        ret += modbusRegisterFormatToString(modbusBuffer_, def_.size());
        break;
        // TODO: Implementation of variable length types

    case SunspecPointDataType_IpAddr:
    case SunspecPointDataType_Ipv6Addr:
    case SunspecPointDataType_Eui48:
    case SunspecPointDataType_NONE:
    default:

        break;
    }

    return ret;
}