#pragma once

#include <stdint.h>

#include <string>

#include "sunspec.h"
#include "sunspec_model_definition.pb.h"

inline sint16_t FormatSunspecPointDefToSint16_t(const SunspecPointDef &def)
{
    const SunspecPointData &sint16 = def.data;
    return {sint16.has_sint16() ? static_cast<sint16_t>(sint16.sint16().value()) : kSint16UnimplementedValue};
}

inline raw16_t FormatSunspecPointDefToRaw16_t(const SunspecPointDef &def)
{
    const SunspecPointData &raw16 = def.data();
    return {raw16.has_raw16() ? static_cast<raw16_t>(raw16.raw16().value()) : kRaw16UnimplementedValue};
}

inline bitfield16_t FormatSunspecPointDefToBit16_t(const SunspecPointDef &def)
{
    const SunspecPointData &bit16 = def.data();

    return {bit16.has_bitfield16() ? static_cast<bitfield16_t>(bit16.bitfield16().value()) : kBit16UnimplementedValue};
}

inline acc16_t FormatSunspecPointDefToAcc16_t(const SunspecPointDef &def)
{
    const SunspecPointData &acc16 = def.data();
    return {acc16.has_acc16() ? static_cast<acc16_t>(acc16.acc16().value()) : kAcc16UnimplementedValue};
}

inline enum16_t FormatSunspecPointDefToEnum16_t(const SunspecPointDef &def)
{
    const SunspecPointData &enum16 = def.data();
    return {enum16.has_enum16() ? static_cast<enum16_t>(enum16.enum16().value()) : kEnum16UnimplementedValue};
}

inline uint16_t FormatSunspecPointDefToUint16_t(const SunspecPointDef &def)
{
    const SunspecPointData &uint16 = def.data();
    return {uint16.has_uint16() ? static_cast<uint16_t>(uint16.uint16().value()) : kUint16UnimplementedValue};
}

inline sint32_t FormatSunspecPointDefToSint32_t(const SunspecPointDef &def)
{
    const SunspecPointData &sint32 = def.data();
    return {sint32.has_sint32() ? sint32.sint32().value() : kSint32UnimplementedValue};
}

inline uint32_t FormatSunspecPointDefToUint32_t(const SunspecPointDef &def)
{
    const SunspecPointData &uint32 = def.data();
    return {uint32.has_uint32() ? uint32.uint32().value() : kUint32UnimplementedValue};
}

inline acc32_t FormatSunspecPointDefToAcc32_t(const SunspecPointDef &def)
{
    const SunspecPointData &acc32 = def.data();
    return {acc32.has_acc32() ? acc32.acc32().value() : kAcc32UnimplementedValue};
}

inline bitfield32_t FormatSunspecPointDefToBit32_t(const SunspecPointDef &def)
{
    const SunspecPointData &bit32 = def.data();
    return {bit32.has_bitfield16() ? bit32.bitfield32().value() : kBit32UnimplementedValue};
}

inline enum32_t FormatSunspecPointDefToEnum32_t(const SunspecPointDef &def)
{
    const SunspecPointData &enum32 = def.data();
    return {enum32.has_enum32() ? enum32.enum32().value() : kEnum32UnimplementedValue};
}

inline ipAddr_t FormatSunspecPointDefToIpAddr_t(const SunspecPointDef &def)
{
    const SunspecPointData &ipAddr = def.data();
    if (ipAddr.has_ipaddr())
    {
        const IpAddr &ip = ipAddr.ipaddr();
        return {static_cast<uint8_t>(ip.octet1()), static_cast<uint8_t>(ip.octet2()), static_cast<uint8_t>(ip.octet3()), static_cast<uint8_t>(ip.octet4())};
    }
    return kIpAddrUnimplementedValue;
}

inline sunsSf_t FormatSunspecPointDefToSunsSf_t(const SunspecPointDef &def)
{
    const SunspecPointData &sunsSf = def.data();
    return {sunsSf.has_sunssf() ? static_cast<sunsSf_t>(sunsSf.sunssf().value()) : kSunsSfUnimplementedValue};
}

inline pad16_t FormatSunspecPointDefToPad16_t(const SunspecPointDef &def)
{
    const SunspecPointData &pad16 = def.data();
    return {pad16.has_pad16() ? static_cast<pad16_t>(pad16.pad16().value()) : kPad16UnimplementedValue};
}

inline sint64_t FormatSunspecPointDefToSint64_t(const SunspecPointDef &def)
{
    const SunspecPointData &sint64 = def.data();
    return {sint64.has_sint64() ? sint64.sint64().value() : kSint64UnimplementedValue};
}

inline uint64_t FormatSunspecPointDefToUint64_t(const SunspecPointDef &def)
{
    const SunspecPointData &uint64 = def.data();
    return {uint64.has_uint64() ? uint64.uint64().value() : kUint64UnimplementedValue};
}

inline acc64_t FormatSunspecPointDefToAcc64_t(const SunspecPointDef &def)
{
    const SunspecPointData &acc64 = def.data();
    return {acc64.has_acc64() ? acc64.acc64().value() : kAcc64UnimplementedValue};
}

inline bitfield64_t FormatSunspecPointDefToBit64_t(const SunspecPointDef &def)
{
    const SunspecPointData &bit64 = def.data();
    return {bit64.has_bitfield64() ? bit64.bitfield64().value() : kBit64UnimplementedValue};
}

inline float FormatSunspecPointDefToFloat32(const SunspecPointDef &def)
{
    const SunspecPointData &float32 = def.data();
    return {float32.has_float32() ? float32.float32().value() : kFloat32UnimplementedValue};
}

inline double FormatSunspecPointDefToFloat64(const SunspecPointDef &def)
{
    const SunspecPointData &float64 = def.data();
    return {float64.has_float64() ? float64.float64().value() : kFloat64UnimplementedValue};
}

inline const char *FormatSunspecPointDefToString(const SunspecPointDef &def)
{
    const SunspecPointData &stringx = def.data();
    return (stringx.has_stringx()) ? stringx.stringx().value().c_str() : kStringUnimplementedValue;
}

inline std::string FormatStringToString(const std::string &stringx)
{
    return stringx;
}

inline SunspecPointAccessType FormatSunspecPointAccess(const SunspecPointAccess access)
{
    switch (access)
    {
    case SunspecPointAccess::kR:
        return SunspecPointAccessType_kR;
    case SunspecPointAccess::kRW:
        return SunspecPointAccessType_kRW;
    default:
        return SunspecPointAccessType_kR;
    }
}

inline SunspecPointMandatoryType FormatSunspecPointMandatory(const SunspecPointMandatory mandatory)
{
    switch (mandatory)
    {
    case SunspecPointMandatory::kM:
        return SunspecPointMandatoryType_kM;
    case SunspecPointMandatory::kO:
        return SunspecPointMandatoryType_kO;
    default:
        return SunspecPointMandatoryType_kM;
    }
}

inline SunspecGroupTypeType FormatSunspecGroupType(const SunspecGroupType group_type)
{
    switch (group_type)
    {
    case SunspecGroupType::kGroup:
        return SunspecGroupTypeType_kGroup;
    case SunspecGroupType::kSync:
        return SunspecGroupTypeType_kSync;
    default:
        return SunspecGroupTypeType_kGroup;
    }
}

inline SunspecPointDataType FormatSunspecPointDataType(const SunspecPointData::KindCase data_type)
{
    switch (data_type)
    {

    case SunspecPointData::kSint16:
        return SunspecPointDataType_Sint16;

    case SunspecPointData::kSunsSf:
        return SunspecPointDataType_SunsSf;

    case SunspecPointData::kPad16:
        return SunspecPointDataType_Pad16;

    case SunspecPointData::kBitfield16:
        return SunspecPointDataType_Bitfield16;
    case SunspecPointData::kAcc16:
        return SunspecPointDataType_Acc16;

    case SunspecPointData::kEnum16:
        return SunspecPointDataType_Enum16;

    case SunspecPointData::kRaw16:
        return SunspecPointDataType_Raw16;

    case SunspecPointData::kUint16:
        return SunspecPointDataType_Uint16;

    case SunspecPointData::kSint32:
        return SunspecPointDataType_Sint32;

    case SunspecPointData::kFloat32:
        return SunspecPointDataType_Float32;

    case SunspecPointData::kUint32:
        return SunspecPointDataType_Uint32;

    case SunspecPointData::kAcc32:
        return SunspecPointDataType_Acc32;

    case SunspecPointData::kBitfield32:
        return SunspecPointDataType_Bitfield32;

    case SunspecPointData::kEnum32:
        return SunspecPointDataType_Enum32;

    case SunspecPointData::kIpAddr:
        return SunspecPointDataType_IpAddr;

    case SunspecPointData::kFloat64:
        return SunspecPointDataType_Float64;

    case SunspecPointData::kSint64:
        return SunspecPointDataType_Sint64;

    case SunspecPointData::kUint64:
        return SunspecPointDataType_Uint64;

    case SunspecPointData::kAcc64:
        return SunspecPointDataType_Acc64;

    case SunspecPointData::kBitfield64:
        return SunspecPointDataType_Bitfield64;

    case SunspecPointData::kStringx:
        return SunspecPointDataType_Stringx;

    case SunspecPointData::kIpv6Addr:
        return SunspecPointDataType_Ipv6Addr;

    case SunspecPointData::kEui48:
        return SunspecPointDataType_Eui48;

    case SunspecPointData::KIND_NOT_SET:
    default:
        return SunspecPointDataType_NONE;
    }
}

template <typename T>
size_t vector_size(T vec)
{
    return vec.size();
}

struct SunspecPointDefWrapper
{

    SunspecPointDefWrapper(const SunspecPointDef &def) : def_{def} {}

    inline const char *id() const
    {
        return def_.id().c_str();
    }

    inline SunspecPointDataType data_type() const
    {
        return FormatSunspecPointDataType(def_.data().kind_case());
    }

    inline sint16_t data_as_Sint16_t() const
    {
        const SunspecPointData &sint16 = def_.data();
        return {sint16.has_sint16() ? static_cast<sint16_t>(sint16.sint16().value()) : kSint16UnimplementedValue};
    }

    inline raw16_t data_as_Raw16_t() const
    {
        const SunspecPointData &raw16 = def_.data();
        return {raw16.has_raw16() ? static_cast<raw16_t>(raw16.raw16().value()) : kRaw16UnimplementedValue};
    }

    inline bitfield16_t data_as_Bit16_t() const
    {
        const SunspecPointData &bit16 = def_.data();

        return {bit16.has_bitfield16() ? static_cast<bitfield16_t>(bit16.bitfield16().value()) : kBit16UnimplementedValue};
    }

    inline acc16_t data_as_Acc16_t() const
    {
        const SunspecPointData &acc16 = def_.data();
        return {acc16.has_acc16() ? static_cast<acc16_t>(acc16.acc16().value()) : kAcc16UnimplementedValue};
    }

    inline enum16_t data_as_Enum16_t() const
    {
        const SunspecPointData &enum16 = def_.data();
        return {enum16.has_enum16() ? static_cast<enum16_t>(enum16.enum16().value()) : kEnum16UnimplementedValue};
    }

    inline uint16_t data_as_Uint16_t() const
    {
        const SunspecPointData &uint16 = def_.data();
        return {uint16.has_uint16() ? static_cast<uint16_t>(uint16.uint16().value()) : kUint16UnimplementedValue};
    }

    inline sint32_t data_as_Sint32_t() const
    {
        const SunspecPointData &sint32 = def_.data();
        return {sint32.has_sint32() ? sint32.sint32().value() : kSint32UnimplementedValue};
    }

    inline uint32_t data_as_Uint32_t() const
    {
        const SunspecPointData &uint32 = def_.data();
        return {uint32.has_uint32() ? uint32.uint32().value() : kUint32UnimplementedValue};
    }

    inline acc32_t data_as_Acc32_t() const
    {
        const SunspecPointData &acc32 = def_.data();
        return {acc32.has_acc32() ? acc32.acc32().value() : kAcc32UnimplementedValue};
    }

    inline bitfield32_t data_as_Bit32_t() const
    {
        const SunspecPointData &bit32 = def_.data();
        return {bit32.has_bitfield16() ? bit32.bitfield32().value() : kBit32UnimplementedValue};
    }

    inline enum32_t data_as_Enum32_t() const
    {
        const SunspecPointData &enum32 = def_.data();
        return {enum32.has_enum32() ? enum32.enum32().value() : kEnum32UnimplementedValue};
    }

    inline ipAddr_t data_as_IpAddr_t() const
    {
        const SunspecPointData &ipAddr = def_.data();
        if (ipAddr.has_ipaddr())
        {
            const IpAddr &ip = ipAddr.ipaddr();
            return {static_cast<uint8_t>(ip.octet1()), static_cast<uint8_t>(ip.octet2()), static_cast<uint8_t>(ip.octet3()), static_cast<uint8_t>(ip.octet4())};
        }
        return kIpAddrUnimplementedValue;
    }

    inline sunsSf_t data_as_SunsSf_t() const
    {
        const SunspecPointData &sunsSf = def_.data();
        return {sunsSf.has_sunssf() ? static_cast<sunsSf_t>(sunsSf.sunssf().value()) : kSunsSfUnimplementedValue};
    }

    inline pad16_t data_as_Pad16_t() const
    {
        const SunspecPointData &pad16 = def_.data();
        return {pad16.has_pad16() ? static_cast<pad16_t>(pad16.pad16().value()) : kPad16UnimplementedValue};
    }

    inline sint64_t data_as_Sint64_t() const
    {
        const SunspecPointData &sint64 = def_.data();
        return {sint64.has_sint64() ? sint64.sint64().value() : kSint64UnimplementedValue};
    }

    inline uint64_t data_as_Uint64_t() const
    {
        const SunspecPointData &uint64 = def_.data();
        return {uint64.has_uint64() ? uint64.uint64().value() : kUint64UnimplementedValue};
    }

    inline acc64_t data_as_Acc64_t() const
    {
        const SunspecPointData &acc64 = def_.data();
        return {acc64.has_acc64() ? acc64.acc64().value() : kAcc64UnimplementedValue};
    }

    inline bitfield64_t data_as_Bit64_t() const
    {
        const SunspecPointData &bit64 = def_.data();
        return {bit64.has_bitfield64() ? bit64.bitfield64().value() : kBit64UnimplementedValue};
    }

    inline float data_as_Float32() const
    {
        const SunspecPointData &float32 = def_.data();
        return {float32.has_float32() ? float32.float32().value() : kFloat32UnimplementedValue};
    }

    inline double data_as_Float64() const
    {
        const SunspecPointData &float64 = def_.data();
        return {float64.has_float64() ? float64.float64().value() : kFloat64UnimplementedValue};
    }

    inline const char *data_as_String() const
    {
        const SunspecPointData &stringx = def_.data();
        return (stringx.has_stringx()) ? stringx.stringx().value().c_str() : kStringUnimplementedValue;
    }

    inline uint16_t count() const
    {
        return def_.count();
    }

    inline const char *count_point_id() const
    {
        return def_.count_point_id().c_str();
    }

    inline uint16_t size() const
    {
        return def_.size();
    }

    inline int16_t sf() const
    {
        return def_.sf();
    }

    inline const char *sf_id() const
    {
        return def_.sf_id().c_str();
    }

    inline const char *units() const
    {
        return def_.units().c_str();
    }

    inline SunspecPointAccessType access() const
    {
        return FormatSunspecPointAccess(def_.access());
    }

    inline SunspecPointMandatoryType mandatory() const
    {
        return FormatSunspecPointMandatory(def_.mandatory());
    }

    inline const char *label() const
    {
        return def_.label().c_str();
    }

private:
    const SunspecPointDef def_;
};

struct SunspecGroupDefWrapper
{
    SunspecGroupDefWrapper(const SunspecGroupDef &def) : def_{def} {}

    inline const char *id() const
    {
        return def_.id().c_str();
    }

    inline SunspecGroupTypeType type() const
    {
        return FormatSunspecGroupType(def_.type());
    }

    inline uint16_t count() const
    {
        return def_.count();
    }

    inline const char *count_point_id() const
    {
        return def_.count_point_id().c_str();
    }

    inline const char *label() const
    {
        return def_.label().c_str();
    }

    inline const std::vector<SunspecPointDefWrapper> points() const
    {

        const size_t size = vector_size(def_.points());
        std::vector<SunspecPointDefWrapper> ret_vec;
        ret_vec.reserve(size);

        for (const auto &point : def_.points())
        {
            // printf("type: %d id : %s\n", point.data().kind_case(), point.id().c_str());
            ret_vec.emplace_back(point);
        }
        return ret_vec;
    }

    inline const std::vector<SunspecGroupDefWrapper> groups() const
    {

        const size_t size = vector_size(def_.groups());
        std::vector<SunspecGroupDefWrapper> ret_vec;
        ret_vec.reserve(size);

        for (const auto &group : def_.groups())
        {
            ret_vec.emplace_back(group);
        }
        return ret_vec;
    }

private:
    const SunspecGroupDef def_;
};

struct SunspecModelDefWrapper
{
    SunspecModelDefWrapper() {}

    SunspecModelDefWrapper(const SunspecModelDef &def) : def_{def} {}

    inline uint16_t id() const
    {
        return def_.id();
    }

    inline const SunspecGroupDefWrapper group() const
    {
        return def_.group();
    }

private:
    SunspecModelDef def_;
};

inline const SunspecModelDefWrapper FormatSunspecModelBinaryToSunspecModelDef(const unsigned char *buffer, const size_t size)
{
    SunspecModelDef model_def;
    assert(model_def.ParseFromArray(buffer, size));
    return model_def;

    // SunspecPointDef point_def;
    // point_def.id
}