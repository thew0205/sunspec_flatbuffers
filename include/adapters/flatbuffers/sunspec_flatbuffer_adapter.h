#pragma once

#include <stdint.h>

#include <string>

#include "sunspec.h"
#include "sunspec_model_definition_generated.h"

inline int16_t FormatSunspecPointDefToSint16_t(const SunspecPointDef &def)
{
    const Sint16 *sint16 = def.data_as_Sint16();
    return {sint16 == nullptr ? kSint16UnimplementedValue : sint16->value()};
}

inline raw16_t FormatSunspecPointDefTotoRaw16_t(const SunspecPointDef &def)
{
    const Raw16 *raw16 = def.data_as_Raw16();
    return {raw16 == nullptr ? kRaw16UnimplementedValue : raw16->value()};
}

inline bitfield16_t FormatSunspecPointDefToBit16_t(const SunspecPointDef &def)
{
    const Bitfield16 *bit16 = def.data_as_Bitfield16();

    return {bit16 == nullptr ? kBit16UnimplementedValue : bit16->value()};
}

inline acc16_t FormatSunspecPointDefToAcc16_t(const SunspecPointDef &def)
{
    const Acc16 *acc16 = def.data_as_Acc16();
    return {acc16 == nullptr ? kAcc16UnimplementedValue : acc16->value()};
}

inline enum16_t FormatSunspecPointDefToEnum16_t(const SunspecPointDef &def)
{
    const Enum16 *enum16 = def.data_as_Enum16();
    return {enum16 == nullptr ? kEnum16UnimplementedValue : enum16->value()};
}

inline uint16_t FormatSunspecPointDefToUint16_t(const SunspecPointDef &def)
{
    const Uint16 *uint16 = def.data_as_Uint16();
    return {uint16 == nullptr ? kUint16UnimplementedValue : uint16->value()};
}

inline int32_t FormatSunspecPointDefToSint32_t(const SunspecPointDef &def)
{
    const Sint32 *sint32 = def.data_as_Sint32();
    return {sint32 == nullptr ? kSint32UnimplementedValue : sint32->value()};
}

inline uint32_t FormatSunspecPointDefToUint32_t(const SunspecPointDef &def)
{
    const Uint32 *uint32 = def.data_as_Uint32();
    return {uint32 == nullptr ? kUint32UnimplementedValue : uint32->value()};
}

inline acc32_t FormatSunspecPointDefToAcc32_t(const SunspecPointDef &def)
{
    const Acc32 *acc32 = def.data_as_Acc32();
    return {acc32 == nullptr ? kAcc32UnimplementedValue : acc32->value()};
}

inline bitfield32_t FormatSunspecPointDefToBit32_t(const SunspecPointDef &def)
{
    const Bitfield32 *bit32 = def.data_as_Bitfield32();
    return {bit32 == nullptr ? kBit32UnimplementedValue : bit32->value()};
}

inline enum32_t FormatSunspecPointDefToEnum32_t(const SunspecPointDef &def)
{
    const Enum32 *enum32 = def.data_as_Enum32();
    return {enum32 == nullptr ? kEnum32UnimplementedValue : enum32->value()};
}

inline ipAddr_t FormatSunspecPointDefToIpAddr_t(const SunspecPointDef &def)
{
    const IpAddr *ipAddr = def.data_as_IpAddr();
    if (ipAddr == nullptr)
    {
        return kIpAddrUnimplementedValue;
    }
    return {ipAddr->octet1(), ipAddr->octet2(), ipAddr->octet3(), ipAddr->octet4()};
}

inline sunsSf_t FormatSunspecPointDefToSunsSf_t(const SunspecPointDef &def)
{
    const SunsSf *sunsSf = def.data_as_SunsSf();
    return {sunsSf == nullptr ? kSunsSfUnimplementedValue : sunsSf->value()};
}

inline pad16_t FormatSunspecPointDefToPad16_t(const SunspecPointDef &def)
{
    const Pad16 *pad16 = def.data_as_Pad16();
    return {pad16 == nullptr ? kPad16UnimplementedValue : pad16->value()};
}

inline int64_t FormatSunspecPointDefToSint64_t(const SunspecPointDef &def)
{
    const Sint64 *sint64 = def.data_as_Sint64();
    return {sint64 == nullptr ? kSint64UnimplementedValue : sint64->value()};
}

inline uint64_t FormatSunspecPointDefToUint64_t(const SunspecPointDef &def)
{
    const Uint64 *uint64 = def.data_as_Uint64();
    return {uint64 == nullptr ? kUint64UnimplementedValue : uint64->value()};
}

inline acc64_t FormatSunspecPointDefToAcc64_t(const SunspecPointDef &def)
{
    const Acc64 *acc64 = def.data_as_Acc64();
    return {acc64 == nullptr ? kAcc64UnimplementedValue : acc64->value()};
}

inline bitfield64_t FormatSunspecPointDefToBit64_t(const SunspecPointDef &def)
{
    const Bitfield64 *bit64 = def.data_as_Bitfield64();
    return {bit64 == nullptr ? kBit64UnimplementedValue : bit64->value()};
}

inline float FormatSunspecPointDefToFloat32(const SunspecPointDef &def)
{
    const Float32 *float32 = def.data_as_Float32();
    return {float32 == nullptr ? kFloat32UnimplementedValue : float32->value()};
}

inline double FormatSunspecPointDefToFloat64(const SunspecPointDef &def)
{
    const Float64 *float64 = def.data_as_Float64();
    return {float64 == nullptr ? kFloat64UnimplementedValue : float64->value()};
}

inline const char *FormatSunspecPointDefToString(const SunspecPointDef &def)
{
    const Stringx *flatbufferString = def.data_as_Stringx();
    return (flatbufferString == nullptr) || (flatbufferString->value() == nullptr) ? kStringUnimplementedValue : flatbufferString->value()->c_str();
}

inline const char *FormatStringToString(const flatbuffers::String *flatbufferSTring)
{
    return flatbufferSTring == nullptr ? kStringUnimplementedValue : flatbufferSTring->c_str();
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

inline SunspecPointDataType FormatSunspecPointDataType(const SunspecPointData data_type)
{
    switch (data_type)
    {

    case SunspecPointData_Sint16:
        return SunspecPointDataType_Sint16;

    case SunspecPointData_SunsSf:
        return SunspecPointDataType_SunsSf;

    case SunspecPointData_Pad16:
        return SunspecPointDataType_Pad16;

    case SunspecPointData_Bitfield16:
        return SunspecPointDataType_Bitfield16;
    case SunspecPointData_Acc16:
        return SunspecPointDataType_Acc16;

    case SunspecPointData_Enum16:
        return SunspecPointDataType_Enum16;

    case SunspecPointData_Raw16:
        return SunspecPointDataType_Raw16;

    case SunspecPointData_Uint16:
        return SunspecPointDataType_Uint16;

    case SunspecPointData_Sint32:
        return SunspecPointDataType_Sint32;

    case SunspecPointData_Float32:
        return SunspecPointDataType_Float32;

    case SunspecPointData_Uint32:
        return SunspecPointDataType_Uint32;

    case SunspecPointData_Acc32:
        return SunspecPointDataType_Acc32;

    case SunspecPointData_Bitfield32:
        return SunspecPointDataType_Bitfield32;

    case SunspecPointData_Enum32:
        return SunspecPointDataType_Enum32;

    case SunspecPointData_IpAddr:
        return SunspecPointDataType_IpAddr;

    case SunspecPointData_Float64:
        return SunspecPointDataType_Float64;

    case SunspecPointData_Sint64:
        return SunspecPointDataType_Sint64;

    case SunspecPointData_Uint64:
        return SunspecPointDataType_Uint64;

    case SunspecPointData_Acc64:
        return SunspecPointDataType_Acc64;

    case SunspecPointData_Bitfield64:
        return SunspecPointDataType_Bitfield64;

    case SunspecPointData_Stringx:
        return SunspecPointDataType_Stringx;

    case SunspecPointData_Ipv6Addr:
        return SunspecPointDataType_Ipv6Addr;

    case SunspecPointData_Eui48:
        return SunspecPointDataType_Eui48;

    case SunspecPointData_NONE:
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

    inline int16_t data_as_Sint16_t() const
    {
        const Sint16 *sint16 = def_.data_as_Sint16();
        return {sint16 == nullptr ? kSint16UnimplementedValue : sint16->value()};
    }

    inline raw16_t data_as_Raw16_t() const
    {
        const Raw16 *raw16 = def_.data_as_Raw16();
        return {raw16 == nullptr ? kRaw16UnimplementedValue : raw16->value()};
    }

    inline bitfield16_t data_as_Bit16_t() const
    {
        const Bitfield16 *bit16 = def_.data_as_Bitfield16();

        return {bit16 == nullptr ? kBit16UnimplementedValue : bit16->value()};
    }

    inline acc16_t data_as_Acc16_t() const
    {
        const Acc16 *acc16 = def_.data_as_Acc16();
        return {acc16 == nullptr ? kAcc16UnimplementedValue : acc16->value()};
    }

    inline enum16_t data_as_Enum16_t() const
    {
        const Enum16 *enum16 = def_.data_as_Enum16();
        return {enum16 == nullptr ? kEnum16UnimplementedValue : enum16->value()};
    }

    inline uint16_t data_as_Uint16_t() const
    {
        const Uint16 *uint16 = def_.data_as_Uint16();
        return {uint16 == nullptr ? kUint16UnimplementedValue : uint16->value()};
    }

    inline int32_t data_as_Sint32_t() const
    {
        const Sint32 *sint32 = def_.data_as_Sint32();
        return {sint32 == nullptr ? kSint32UnimplementedValue : sint32->value()};
    }

    inline uint32_t data_as_Uint32_t() const
    {
        const Uint32 *uint32 = def_.data_as_Uint32();
        return {uint32 == nullptr ? kUint32UnimplementedValue : uint32->value()};
    }

    inline acc32_t data_as_Acc32_t() const
    {
        const Acc32 *acc32 = def_.data_as_Acc32();
        return {acc32 == nullptr ? kAcc32UnimplementedValue : acc32->value()};
    }

    inline bitfield32_t data_as_Bit32_t() const
    {
        const Bitfield32 *bit32 = def_.data_as_Bitfield32();
        return {bit32 == nullptr ? kBit32UnimplementedValue : bit32->value()};
    }

    inline enum32_t data_as_Enum32_t() const
    {
        const Enum32 *enum32 = def_.data_as_Enum32();
        return {enum32 == nullptr ? kEnum32UnimplementedValue : enum32->value()};
    }

    inline ipAddr_t data_as_IpAddr_t() const
    {
        const IpAddr *ipAddr = def_.data_as_IpAddr();
        if (ipAddr == nullptr)
        {
            return kIpAddrUnimplementedValue;
        }
        return {ipAddr->octet1(), ipAddr->octet2(), ipAddr->octet3(), ipAddr->octet4()};
    }

    inline sunsSf_t data_as_SunsSf_t() const
    {
        const SunsSf *sunsSf = def_.data_as_SunsSf();
        return {sunsSf == nullptr ? kSunsSfUnimplementedValue : sunsSf->value()};
    }

    inline pad16_t data_as_Pad16_t() const
    {
        const Pad16 *pad16 = def_.data_as_Pad16();
        return {pad16 == nullptr ? kPad16UnimplementedValue : pad16->value()};
    }

    inline int64_t data_as_Sint64_t() const
    {
        const Sint64 *sint64 = def_.data_as_Sint64();
        return {sint64 == nullptr ? kSint64UnimplementedValue : sint64->value()};
    }

    inline uint64_t data_as_Uint64_t() const
    {
        const Uint64 *uint64 = def_.data_as_Uint64();
        return {uint64 == nullptr ? kUint64UnimplementedValue : uint64->value()};
    }

    inline acc64_t data_as_Acc64_t() const
    {
        const Acc64 *acc64 = def_.data_as_Acc64();
        return {acc64 == nullptr ? kAcc64UnimplementedValue : acc64->value()};
    }

    inline bitfield64_t data_as_Bit64_t() const
    {
        const Bitfield64 *bit64 = def_.data_as_Bitfield64();
        return {bit64 == nullptr ? kBit64UnimplementedValue : bit64->value()};
    }

    inline float data_as_Float32() const
    {
        const Float32 *float32 = def_.data_as_Float32();
        return {float32 == nullptr ? kFloat32UnimplementedValue : float32->value()};
    }

    inline double data_as_Float64() const
    {
        const Float64 *float64 = def_.data_as_Float64();
        return {float64 == nullptr ? kFloat64UnimplementedValue : float64->value()};
    }

    inline const char *data_as_String() const
    {
        const Stringx *flatbufferString = def_.data_as_Stringx();
        return (flatbufferString == nullptr) || (flatbufferString->value() == nullptr) ? kStringUnimplementedValue : flatbufferString->value()->c_str();
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
    const SunspecPointDef &def_;
};

struct SunspecGroupDefWrapper
{
    SunspecGroupDefWrapper(const SunspecGroupDef *def) : def_{def} {}

    inline const char *id() const
    {
        return FormatStringToString(def_->id());
    }

    inline SunspecGroupTypeType type() const
    {
        return FormatSunspecGroupType(def_->type());
    }

    inline uint16_t count() const
    {
        return def_->count();
    }

    inline const char *count_point_id() const
    {
        return FormatStringToString(def_->count_point_id());
    }

    inline const char *label() const
    {
        return FormatStringToString(def_->label());
    }

    inline const std::vector<SunspecPointDefWrapper> points() const
    {

        const size_t size = vector_size(def_->points());
        std::vector<SunspecPointDefWrapper> ret_vec;
        ret_vec.reserve(size);

        for (const auto &point : *def_->points())
        {
            ret_vec.emplace_back(*point);
        }
        return ret_vec;
    }

    inline const std::vector<SunspecGroupDefWrapper> groups() const
    {

        const size_t size = vector_size(def_->groups());
        std::vector<SunspecGroupDefWrapper> ret_vec;
        ret_vec.reserve(size);

        for (const auto &group : *def_->groups())
        {
            ret_vec.emplace_back(group);
        }
        return ret_vec;
    }

private:
    const SunspecGroupDef *def_;
};

struct SunspecModelDefWrapper
{
    SunspecModelDefWrapper() : def_{nullptr} {}
    SunspecModelDefWrapper(const SunspecModelDef &def) : def_{&def} {}

    inline uint16_t id() const
    {
        return def_->id();
    }

    inline const SunspecGroupDefWrapper group() const
    {
        auto a = def_->group();

        return SunspecGroupDefWrapper{a};
    }

private:
    const SunspecModelDef *def_;
};

inline SunspecModelDefWrapper FormatSunspecModelBinaryToSunspecModelDef(const unsigned char *buffer, const size_t size)
{
    auto a = GetSunspecModelDef(buffer);
    return SunspecModelDefWrapper{*a};
}