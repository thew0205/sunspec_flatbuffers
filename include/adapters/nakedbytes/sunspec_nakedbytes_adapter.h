#pragma once

#include <stdint.h>

#include <string>

#include "sunspec.h"
#include "sunspec_model_definition.nbs.h"

inline sint16_t FormatSunspecPointDefToSint16_t(const SunspecPointDef &def)
{
    const SunspecPointData &sint16 = def.data();
    return {sint16.type() == SunspecPointData_enum_Sint16 ? static_cast<sint16_t>(sint16.data_as_Sint16().value().value()) : kSint16UnimplementedValue};
}

inline raw16_t FormatSunspecPointDefToRaw16_t(const SunspecPointDef &def)
{
    const SunspecPointData &raw16 = def.data();
    return {raw16.type() == SunspecPointData_enum_Raw16 ? static_cast<raw16_t>(raw16.data_as_Raw16().value().value()) : kRaw16UnimplementedValue};
}

inline bitfield16_t FormatSunspecPointDefToBit16_t(const SunspecPointDef &def)
{
    const SunspecPointData &bit16 = def.data();

    return {bit16.type() == SunspecPointData_enum_Bitfield16 ? static_cast<bitfield16_t>(bit16.data_as_Bitfield16().value().value()) : kBit16UnimplementedValue};
}

inline acc16_t FormatSunspecPointDefToAcc16_t(const SunspecPointDef &def)
{
    const SunspecPointData &acc16 = def.data();
    return {acc16.type() == SunspecPointData_enum_Acc16 ? static_cast<acc16_t>(acc16.data_as_Acc16().value().value()) : kAcc16UnimplementedValue};
}

inline enum16_t FormatSunspecPointDefToEnum16_t(const SunspecPointDef &def)
{
    const SunspecPointData &enum16 = def.data();
    return {enum16.type() == SunspecPointData_enum_Enum16 ? static_cast<enum16_t>(enum16.data_as_Enum16().value().value()) : kEnum16UnimplementedValue};
}

inline uint16_t FormatSunspecPointDefToUint16_t(const SunspecPointDef &def)
{
    const SunspecPointData &uint16 = def.data();
    return {uint16.type() == SunspecPointData_enum_Uint16 ? static_cast<uint16_t>(uint16.data_as_Uint16().value().value()) : kUint16UnimplementedValue};
}

inline sint32_t FormatSunspecPointDefToSint32_t(const SunspecPointDef &def)
{
    const SunspecPointData &sint32 = def.data();
    return {sint32.type() == SunspecPointData_enum_Sint32 ? sint32.data_as_Sint32().value().value() : kSint32UnimplementedValue};
}

inline uint32_t FormatSunspecPointDefToUint32_t(const SunspecPointDef &def)
{
    const SunspecPointData &uint32 = def.data();
    return {uint32.type() == SunspecPointData_enum_Uint32 ? uint32.data_as_Uint32().value().value() : kUint32UnimplementedValue};
}

inline acc32_t FormatSunspecPointDefToAcc32_t(const SunspecPointDef &def)
{
    const SunspecPointData &acc32 = def.data();
    return {acc32.type() == SunspecPointData_enum_Acc32 ? acc32.data_as_Acc32().value().value() : kAcc32UnimplementedValue};
}

inline bitfield32_t FormatSunspecPointDefToBit32_t(const SunspecPointDef &def)
{
    const SunspecPointData &bit32 = def.data();
    return {bit32.type() == SunspecPointData_enum_Bitfield32 ? bit32.data_as_Bitfield32().value().value() : kBit32UnimplementedValue};
}

inline enum32_t FormatSunspecPointDefToEnum32_t(const SunspecPointDef &def)
{
    const SunspecPointData &enum32 = def.data();
    return {enum32.type() == SunspecPointData_enum_Enum32 ? enum32.data_as_Enum32().value().value() : kEnum32UnimplementedValue};
}

inline ipAddr_t FormatSunspecPointDefToIpAddr_t(const SunspecPointDef &def)
{
    const SunspecPointData &ipAddr = def.data();
    if (ipAddr.type() == SunspecPointData_enum_IpAddr)
    {
        const IpAddr &ip = ipAddr.data_as_IpAddr().value();
        return {static_cast<uint8_t>(ip.octet1()), static_cast<uint8_t>(ip.octet2()), static_cast<uint8_t>(ip.octet3()), static_cast<uint8_t>(ip.octet4())};
    }
    return kIpAddrUnimplementedValue;
}

inline sunsSf_t FormatSunspecPointDefToSunsSf_t(const SunspecPointDef &def)
{
    const SunspecPointData &sunsSf = def.data();
    return {sunsSf.type() == SunspecPointData_enum_SunsSf ? static_cast<sunsSf_t>(sunsSf.data_as_SunsSf().value().value()) : kSunsSfUnimplementedValue};
}

inline pad16_t FormatSunspecPointDefToPad16_t(const SunspecPointDef &def)
{
    const SunspecPointData &pad16 = def.data();
    return {pad16.type() == SunspecPointData_enum_Pad16 ? static_cast<pad16_t>(pad16.data_as_Pad16().value().value()) : kPad16UnimplementedValue};
}

inline sint64_t FormatSunspecPointDefToSint64_t(const SunspecPointDef &def)
{
    const SunspecPointData &sint64 = def.data();
    return {sint64.type() == SunspecPointData_enum_Sint64 ? sint64.data_as_Sint64().value().value() : kSint64UnimplementedValue};
}

inline uint64_t FormatSunspecPointDefToUint64_t(const SunspecPointDef &def)
{
    const SunspecPointData &uint64 = def.data();
    return {uint64.type() == SunspecPointData_enum_Uint64 ? uint64.data_as_Uint64().value().value() : kUint64UnimplementedValue};
}

inline acc64_t FormatSunspecPointDefToAcc64_t(const SunspecPointDef &def)
{
    const SunspecPointData &acc64 = def.data();
    return {acc64.type() == SunspecPointData_enum_Acc64 ? acc64.data_as_Acc64().value().value() : kAcc64UnimplementedValue};
}

inline bitfield64_t FormatSunspecPointDefToBit64_t(const SunspecPointDef &def)
{
    const SunspecPointData &bit64 = def.data();
    return {bit64.type() == SunspecPointData_enum_Bitfield64 ? bit64.data_as_Bitfield64().value().value() : kBit64UnimplementedValue};
}

inline float FormatSunspecPointDefToFloat32(const SunspecPointDef &def)
{
    const SunspecPointData &float32 = def.data();
    return {float32.type() == SunspecPointData_enum_Float32 ? float32.data_as_Float32().value().value() : kFloat32UnimplementedValue};
}

inline double FormatSunspecPointDefToFloat64(const SunspecPointDef &def)
{
    const SunspecPointData &float64 = def.data();
    return {float64.type() == SunspecPointData_enum_Float64 ? float64.data_as_Float64().value().value() : kFloat64UnimplementedValue};
}

inline const char *FormatSunspecPointDefToString(const SunspecPointDef &def)
{
    const SunspecPointData &stringx = def.data();
    return ((stringx.type() == SunspecPointData_enum_Stringx) && (!stringx.data_as_Stringx().value().value().is_null())) ? stringx.data_as_Stringx().value().value().value().c_str() : kStringUnimplementedValue;
}

inline const char *FormatStringToString(const Offset<String> str)
{
    return str.is_null() ? kStringUnimplementedValue : str.value().c_str();
}

inline SunspecPointAccessType FormatSunspecPointAccess(const SunspecPointAccess access)
{
    switch (access)
    {
    case SunspecPointAccess_kR:
        return SunspecPointAccessType_kR;
    case SunspecPointAccess_kRW:
        return SunspecPointAccessType_kRW;
    default:
        return SunspecPointAccessType_kR;
    }
}

inline SunspecPointMandatoryType FormatSunspecPointMandatory(const SunspecPointMandatory mandatory)
{
    switch (mandatory)
    {
    case SunspecPointMandatory_kM:
        return SunspecPointMandatoryType_kM;
    case SunspecPointMandatory_kO:
        return SunspecPointMandatoryType_kO;
    default:
        return SunspecPointMandatoryType_kM;
    }
}

inline SunspecPointDataType FormatSunspecPointDataType(const SunspecPointData_enum data_type)
{
    switch (data_type)
    {

    case SunspecPointData_enum_Sint16:
        return SunspecPointDataType_Sint16;

    case SunspecPointData_enum_SunsSf:
        return SunspecPointDataType_SunsSf;

    case SunspecPointData_enum_Pad16:
        return SunspecPointDataType_Pad16;

    case SunspecPointData_enum_Bitfield16:
        return SunspecPointDataType_Bitfield16;
    case SunspecPointData_enum_Acc16:
        return SunspecPointDataType_Acc16;

    case SunspecPointData_enum_Enum16:
        return SunspecPointDataType_Enum16;

    case SunspecPointData_enum_Raw16:
        return SunspecPointDataType_Raw16;

    case SunspecPointData_enum_Uint16:
        return SunspecPointDataType_Uint16;

    case SunspecPointData_enum_Sint32:
        return SunspecPointDataType_Sint32;

    case SunspecPointData_enum_Float32:
        return SunspecPointDataType_Float32;

    case SunspecPointData_enum_Uint32:
        return SunspecPointDataType_Uint32;

    case SunspecPointData_enum_Acc32:
        return SunspecPointDataType_Acc32;

    case SunspecPointData_enum_Bitfield32:
        return SunspecPointDataType_Bitfield32;

    case SunspecPointData_enum_Enum32:
        return SunspecPointDataType_Enum32;

    case SunspecPointData_enum_IpAddr:
        return SunspecPointDataType_IpAddr;

    case SunspecPointData_enum_Float64:
        return SunspecPointDataType_Float64;

    case SunspecPointData_enum_Sint64:
        return SunspecPointDataType_Sint64;

    case SunspecPointData_enum_Uint64:
        return SunspecPointDataType_Uint64;

    case SunspecPointData_enum_Acc64:
        return SunspecPointDataType_Acc64;

    case SunspecPointData_enum_Bitfield64:
        return SunspecPointDataType_Bitfield64;

    case SunspecPointData_enum_Stringx:
        return SunspecPointDataType_Stringx;

    case SunspecPointData_enum_Ipv6Addr:
        return SunspecPointDataType_Ipv6Addr;

    case SunspecPointData_enum_Eui48:
        return SunspecPointDataType_Eui48;

    // case SunspecPointData_NONE:
    default:
        return SunspecPointDataType_NONE;
    }
}

inline SunspecGroupTypeType FormatSunspecGroupType(const SunspecGroupType group_type)
{
    switch (group_type)
    {
    case SunspecGroupType_kGroup:
        return SunspecGroupTypeType_kGroup;
    case SunspecGroupType_kSync:
        return SunspecGroupTypeType_kSync;
    default:
        return SunspecGroupTypeType_kGroup;
    }
}

template <typename T>
inline size_t vector_size(const T &vec)
{
    return vec.size();
}

template <typename T>
inline size_t vector_size(const T *vec)
{
    return vec->size();
}

struct SunspecPointDefWrapper
{

    SunspecPointDefWrapper(const SunspecPointDef &def) : def_{def} {}

    inline const char *id() const
    {
        return FormatStringToString(def_.id());
    }

    inline SunspecPointDataType data_type() const
    {
        return FormatSunspecPointDataType(def_.data_type());
    }

    inline sint16_t data_as_Sint16_t() const
    {
        const SunspecPointData &sint16 = def_.data();
        return {sint16.type() == SunspecPointData_enum_Sint16 ? static_cast<sint16_t>(sint16.data_as_Sint16().value().value()) : kSint16UnimplementedValue};
    }

    inline raw16_t data_as_Raw16_t() const
    {
        const SunspecPointData &raw16 = def_.data();
        return {raw16.type() == SunspecPointData_enum_Raw16 ? static_cast<raw16_t>(raw16.data_as_Raw16().value().value()) : kRaw16UnimplementedValue};
    }

    inline bitfield16_t data_as_Bit16_t() const
    {
        const SunspecPointData &bit16 = def_.data();

        return {bit16.type() == SunspecPointData_enum_Bitfield16 ? static_cast<bitfield16_t>(bit16.data_as_Bitfield16().value().value()) : kBit16UnimplementedValue};
    }

    inline acc16_t data_as_Acc16_t() const
    {
        const SunspecPointData &acc16 = def_.data();
        return {acc16.type() == SunspecPointData_enum_Acc16 ? static_cast<acc16_t>(acc16.data_as_Acc16().value().value()) : kAcc16UnimplementedValue};
    }

    inline enum16_t data_as_Enum16_t() const
    {
        const SunspecPointData &enum16 = def_.data();
        return {enum16.type() == SunspecPointData_enum_Enum16 ? static_cast<enum16_t>(enum16.data_as_Enum16().value().value()) : kEnum16UnimplementedValue};
    }

    inline uint16_t data_as_Uint16_t() const
    {
        const SunspecPointData &uint16 = def_.data();
        return {uint16.type() == SunspecPointData_enum_Uint16 ? static_cast<uint16_t>(uint16.data_as_Uint16().value().value()) : kUint16UnimplementedValue};
    }

    inline sint32_t data_as_Sint32_t() const
    {
        const SunspecPointData &sint32 = def_.data();
        return {sint32.type() == SunspecPointData_enum_Sint32 ? sint32.data_as_Sint32().value().value() : kSint32UnimplementedValue};
    }

    inline uint32_t data_as_Uint32_t() const
    {
        const SunspecPointData &uint32 = def_.data();
        return {uint32.type() == SunspecPointData_enum_Uint32 ? uint32.data_as_Uint32().value().value() : kUint32UnimplementedValue};
    }

    inline acc32_t data_as_Acc32_t() const
    {
        const SunspecPointData &acc32 = def_.data();
        return {acc32.type() == SunspecPointData_enum_Acc32 ? acc32.data_as_Acc32().value().value() : kAcc32UnimplementedValue};
    }

    inline bitfield32_t data_as_Bit32_t() const
    {
        const SunspecPointData &bit32 = def_.data();
        return {bit32.type() == SunspecPointData_enum_Bitfield32 ? bit32.data_as_Bitfield32().value().value() : kBit32UnimplementedValue};
    }

    inline enum32_t data_as_Enum32_t() const
    {
        const SunspecPointData &enum32 = def_.data();
        return {enum32.type() == SunspecPointData_enum_Enum32 ? enum32.data_as_Enum32().value().value() : kEnum32UnimplementedValue};
    }

    inline ipAddr_t data_as_IpAddr_t() const
    {
        const SunspecPointData &ipAddr = def_.data();
        if (ipAddr.type() == SunspecPointData_enum_IpAddr)
        {
            const IpAddr &ip = ipAddr.data_as_IpAddr().value();
            return {static_cast<uint8_t>(ip.octet1()), static_cast<uint8_t>(ip.octet2()), static_cast<uint8_t>(ip.octet3()), static_cast<uint8_t>(ip.octet4())};
        }
        return kIpAddrUnimplementedValue;
    }

    inline sunsSf_t data_as_SunsSf_t() const
    {
        const SunspecPointData &sunsSf = def_.data();
        return {sunsSf.type() == SunspecPointData_enum_SunsSf ? static_cast<sunsSf_t>(sunsSf.data_as_SunsSf().value().value()) : kSunsSfUnimplementedValue};
    }

    inline pad16_t data_as_Pad16_t() const
    {
        const SunspecPointData &pad16 = def_.data();
        return {pad16.type() == SunspecPointData_enum_Pad16 ? static_cast<pad16_t>(pad16.data_as_Pad16().value().value()) : kPad16UnimplementedValue};
    }

    inline sint64_t data_as_Sint64_t() const
    {
        const SunspecPointData &sint64 = def_.data();
        return {sint64.type() == SunspecPointData_enum_Sint64 ? sint64.data_as_Sint64().value().value() : kSint64UnimplementedValue};
    }

    inline uint64_t data_as_Uint64_t() const
    {
        const SunspecPointData &uint64 = def_.data();
        return {uint64.type() == SunspecPointData_enum_Uint64 ? uint64.data_as_Uint64().value().value() : kUint64UnimplementedValue};
    }

    inline acc64_t data_as_Acc64_t() const
    {
        const SunspecPointData &acc64 = def_.data();
        return {acc64.type() == SunspecPointData_enum_Acc64 ? acc64.data_as_Acc64().value().value() : kAcc64UnimplementedValue};
    }

    inline bitfield64_t data_as_Bit64_t() const
    {
        const SunspecPointData &bit64 = def_.data();
        return {bit64.type() == SunspecPointData_enum_Bitfield64 ? bit64.data_as_Bitfield64().value().value() : kBit64UnimplementedValue};
    }

    inline float data_as_Float32() const
    {
        const SunspecPointData &float32 = def_.data();
        return {float32.type() == SunspecPointData_enum_Float32 ? float32.data_as_Float32().value().value() : kFloat32UnimplementedValue};
    }

    inline double data_as_Float64() const
    {
        const SunspecPointData &float64 = def_.data();
        return {float64.type() == SunspecPointData_enum_Float64 ? float64.data_as_Float64().value().value() : kFloat64UnimplementedValue};
    }

    inline const char *data_as_String() const
    {
        const SunspecPointData &stringx = def_.data();
        return ((stringx.type() == SunspecPointData_enum_Stringx) && (!stringx.data_as_Stringx().value().value().is_null())) ? stringx.data_as_Stringx().value().value().value().c_str() : kStringUnimplementedValue;
    }

    inline uint16_t count() const
    {
        return def_.count();
    }

    inline const char *count_point_id() const
    {
        return FormatStringToString(def_.count_point_id());
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
        return FormatStringToString(def_.sf_id());
    }

    inline const char *units() const
    {
        return FormatStringToString(def_.units());
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
        return FormatStringToString(def_.label());
    }

private:
    const SunspecPointDef def_;
};

struct SunspecGroupDefWrapper
{
    SunspecGroupDefWrapper(const SunspecGroupDef &def) : def_{def} {}

    inline const char *id() const
    {
        return FormatStringToString(def_.id());
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
        return FormatStringToString(def_.count_point_id());
    }

    inline const char *label() const
    {
        return FormatStringToString(def_.label());
    }

    inline const std::vector<SunspecPointDefWrapper> points() const
    {

        const size_t size = vector_size(def_.points());
        std::vector<SunspecPointDefWrapper> ret_vec;
        ret_vec.reserve(size);

        for (size_t i = 0; i < size; i++)
        {
            ret_vec.emplace_back(def_.points().get(i));
        }
        return ret_vec;
    }

    inline const std::vector<SunspecGroupDefWrapper> groups() const
    {

        const size_t size = vector_size(def_.groups());
        std::vector<SunspecGroupDefWrapper> ret_vec;
        ret_vec.reserve(size);

        for (size_t i = 0; i < size; i++)
        {
            ret_vec.emplace_back(def_.groups().get(i));
        }
        return ret_vec;
    }

private:
    const SunspecGroupDef def_;
};

struct SunspecModelDefWrapper
{
    SunspecModelDefWrapper() : def_{nullptr} {}
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

inline SunspecModelDefWrapper FormatSunspecModelBinaryToSunspecModelDef(const unsigned char *buffer, const size_t size)
{
    return SunspecModelDef((unsigned char *)buffer + OFFSET_SIZE * 2);
}