#pragma once

#include <stdint.h>

#include <string>

#include "sunspec.h"
#include "sunspec_model_definition_generated.h"

inline int16_t FormatSunspecPointDefToSint16_t(const SunspecPointDef &def)
{
    const kSint16 *sint16 = def.data_as_kSint16();
    return {sint16 == nullptr ? kSint16UnimplementedValue : sint16->value()};
}

inline raw16_t FormatSunspecPointDefTotoRaw16_t(const SunspecPointDef &def)
{
    const kRaw16 *raw16 = def.data_as_kRaw16();
    return {raw16 == nullptr ? kRaw16UnimplementedValue : raw16->value()};
}

inline bitfield16_t FormatSunspecPointDefToBit16_t(const SunspecPointDef &def)
{
    const kBitfield16 *bit16 = def.data_as_kBitfield16();

    return {bit16 == nullptr ? kBit16UnimplementedValue : bit16->value()};
}

inline acc16_t FormatSunspecPointDefToAcc16_t(const SunspecPointDef &def)
{
    const kAcc16 *acc16 = def.data_as_kAcc16();
    return {acc16 == nullptr ? kAcc16UnimplementedValue : acc16->value()};
}

inline enum16_t FormatSunspecPointDefToEnum16_t(const SunspecPointDef &def)
{
    const kEnum16 *enum16 = def.data_as_kEnum16();
    return {enum16 == nullptr ? kEnum16UnimplementedValue : enum16->value()};
}

inline uint16_t FormatSunspecPointDefToUint16_t(const SunspecPointDef &def)
{
    const kUint16 *uint16 = def.data_as_kUint16();
    return {uint16 == nullptr ? kUint16UnimplementedValue : uint16->value()};
}

inline int32_t FormatSunspecPointDefToSint32_t(const SunspecPointDef &def)
{
    const kSint32 *sint32 = def.data_as_kSint32();
    return {sint32 == nullptr ? kSint32UnimplementedValue : sint32->value()};
}

inline uint32_t FormatSunspecPointDefToUint32_t(const SunspecPointDef &def)
{
    const kUint32 *uint32 = def.data_as_kUint32();
    return {uint32 == nullptr ? kUint32UnimplementedValue : uint32->value()};
}

inline acc32_t FormatSunspecPointDefToAcc32_t(const SunspecPointDef &def)
{
    const KAcc32 *acc32 = def.data_as_KAcc32();
    return {acc32 == nullptr ? kAcc32UnimplementedValue : acc32->value()};
}

inline bitfield32_t FormatSunspecPointDefToBit32_t(const SunspecPointDef &def)
{
    const kBitfield32 *bit32 = def.data_as_kBitfield32();
    return {bit32 == nullptr ? kBit32UnimplementedValue : bit32->value()};
}

inline enum32_t FormatSunspecPointDefToEnum32_t(const SunspecPointDef &def)
{
    const kEnum32 *enum32 = def.data_as_kEnum32();
    return {enum32 == nullptr ? kEnum32UnimplementedValue : enum32->value()};
}

inline ipAddr_t FormatSunspecPointDefToIpAddr_t(const SunspecPointDef &def)
{
    const kIpAddr *ipAddr = def.data_as_kIpAddr();
    if (ipAddr == nullptr)
    {
        return kIpAddrUnimplementedValue;
    }
    return {ipAddr->octet1(), ipAddr->octet2(), ipAddr->octet3(), ipAddr->octet4()};
}

inline sunsSf_t FormatSunspecPointDefToSunsSf_t(const SunspecPointDef &def)
{
    const kSunsSf *sunsSf = def.data_as_kSunsSf();
    return {sunsSf == nullptr ? kSunsSfUnimplementedValue : sunsSf->value()};
}

inline pad16_t FormatSunspecPointDefToPad16_t(const SunspecPointDef &def)
{
    const kPad16 *pad16 = def.data_as_kPad16();
    return {pad16 == nullptr ? kPad16UnimplementedValue : pad16->value()};
}

inline int64_t FormatSunspecPointDefToSint64_t(const SunspecPointDef &def)
{
    const kSint64 *sint64 = def.data_as_kSint64();
    return {sint64 == nullptr ? kSint64UnimplementedValue : sint64->value()};
}

inline uint64_t FormatSunspecPointDefToUint64_t(const SunspecPointDef &def)
{
    const kUint64 *uint64 = def.data_as_kUint64();
    return {uint64 == nullptr ? kUint64UnimplementedValue : uint64->value()};
}

inline acc64_t FormatSunspecPointDefToAcc64_t(const SunspecPointDef &def)
{
    const kAcc64 *acc64 = def.data_as_kAcc64();
    return {acc64 == nullptr ? kAcc64UnimplementedValue : acc64->value()};
}

inline bitfield64_t FormatSunspecPointDefToBit64_t(const SunspecPointDef &def)
{
    const kBitfield64 *bit64 = def.data_as_kBitfield64();
    return {bit64 == nullptr ? kBit64UnimplementedValue : bit64->value()};
}

inline float FormatSunspecPointDefToFloat32(const SunspecPointDef &def)
{
    const kFloat32 *float32 = def.data_as_kFloat32();
    return {float32 == nullptr ? kFloat32UnimplementedValue : float32->value()};
}

inline double FormatSunspecPointDefToFloat64(const SunspecPointDef &def)
{
    const kFloat64 *float64 = def.data_as_kFloat64();
    return {float64 == nullptr ? kFloat64UnimplementedValue : float64->value()};
}

inline std::string FormatSunspecPointDefToString(const SunspecPointDef &def)
{
    const kStringx *flatbufferString = def.data_as_kStringx();
    return std::string{(flatbufferString == nullptr) || (flatbufferString->value() == nullptr) ? kStringUnimplementedValue : flatbufferString->value()->c_str()};
}

inline std::string FormatStringToString(const flatbuffers::String *flatbufferSTring)
{
    return std::string{flatbufferSTring == nullptr ? kStringUnimplementedValue : flatbufferSTring->c_str()};
}