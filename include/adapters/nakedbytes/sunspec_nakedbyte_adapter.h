#pragma once

#include <stdint.h>

#include <string>

#include "sunspec.h"
#include "adapters/nakedbytes/sunspec_model_generated_struct_offset.h"

inline int16_t FormatSunspecPointDefToSint16_t(const SunspecPointDef &def)
{
    const SunspecPointData data = def.data();
    return {data.is_null() ? kSint16UnimplementedValue : data.data_as_int16()};
}

inline raw16_t FormatSunspecPointDefTotoRaw16_t(const SunspecPointDef &def)
{
    const SunspecPointData data = def.data();
    return {data.is_null() ? kRaw16UnimplementedValue : data.data_as_uint16()};
}

inline bitfield16_t FormatSunspecPointDefToBit16_t(const SunspecPointDef &def)
{
    const SunspecPointData data = def.data();
    return {data.is_null() ? kBit16UnimplementedValue : data.data_as_bitfield16().value()};
}

inline acc16_t FormatSunspecPointDefToAcc16_t(const SunspecPointDef &def)
{
    const SunspecPointData data = def.data();
    return {data.is_null() ? kAcc16UnimplementedValue : data.data_as_acc16().value()};
}

inline enum16_t FormatSunspecPointDefToEnum16_t(const SunspecPointDef &def)
{
    const SunspecPointData data = def.data();
    return {data.is_null() ? kEnum16UnimplementedValue : data.data_as_enum16().value()};
}

inline uint16_t FormatSunspecPointDefToUint16_t(const SunspecPointDef &def)
{
    const SunspecPointData data = def.data();
    return {data.is_null() ? kUint16UnimplementedValue : data.data_as_uint16()};
}

inline int32_t FormatSunspecPointDefToSint32_t(const SunspecPointDef &def)
{
    const SunspecPointData data = def.data();
    return {data.is_null() ? kSint32UnimplementedValue : data.data_as_int32()};
}

inline uint32_t FormatSunspecPointDefToUint32_t(const SunspecPointDef &def)
{
    const SunspecPointData data = def.data();
    return {data.is_null() ? kUint32UnimplementedValue : data.data_as_uint32()};
}

inline acc32_t FormatSunspecPointDefToAcc32_t(const SunspecPointDef &def)
{
    const SunspecPointData data = def.data();
    return {data.is_null() ? kAcc32UnimplementedValue : data.data_as_acc32().value()};
}

inline bitfield32_t FormatSunspecPointDefToBit32_t(const SunspecPointDef &def)
{
    const SunspecPointData data = def.data();
    return {data.is_null() ? kBit32UnimplementedValue : data.data_as_bitfield32().value()};
}

inline enum32_t FormatSunspecPointDefToEnum32_t(const SunspecPointDef &def)
{
    const SunspecPointData data = def.data();
    return {data.is_null() ? kEnum32UnimplementedValue : data.data_as_enum32().value()};
}

inline ipAddr_t FormatSunspecPointDefToIpAddr_t(const SunspecPointDef &def)
{
    const SunspecPointData data = def.data();

    if (data.is_null())
    {
        return kIpAddrUnimplementedValue;
    }
    const auto ipAddr = data.data_as_ipaddr();
    return {ipAddr.value0(), ipAddr.value1(), ipAddr.value2(), ipAddr.value3()};
}

inline sunsSf_t FormatSunspecPointDefToSunsSf_t(const SunspecPointDef &def)
{
    const SunspecPointData data = def.data();
    return {data.is_null() ? kSunsSfUnimplementedValue : data.data_as_sunssf().value()};
}

inline pad16_t FormatSunspecPointDefToPad16_t(const SunspecPointDef &def)
{
    const SunspecPointData data = def.data();
    return {data.is_null() ? kPad16UnimplementedValue : data.data_as_pad().value()};
}
inline int64_t FormatSunspecPointDefToSint64_t(const SunspecPointDef &def)
{
    const SunspecPointData data = def.data();
    return {data.is_null() ? kSint64UnimplementedValue : data.data_as_int64()};
}

inline uint64_t FormatSunspecPointDefToUint64_t(const SunspecPointDef &def)
{
    const SunspecPointData data = def.data();
    return {data.is_null() ? kUint64UnimplementedValue : data.data_as_uint64()};
}
inline acc64_t FormatSunspecPointDefToAcc64_t(const SunspecPointDef &def)
{
    const SunspecPointData data = def.data();
    return {data.is_null() ? kAcc64UnimplementedValue : data.data_as_acc64().value()};
}

inline bitfield64_t FormatSunspecPointDefToBit64_t(const SunspecPointDef &def)
{
    const SunspecPointData data = def.data();
    return {data.is_null() ? kBit64UnimplementedValue : data.data_as_bitfield64().value()};
}

inline float FormatSunspecPointDefToFloat(const SunspecPointDef &def)
{
    const SunspecPointData data = def.data();
    return {data.is_null() ? kFloat32UnimplementedValue : data.data_as_float32()};
}

inline double FormatSunspecPointDefToDouble(const SunspecPointDef &def)
{
    const SunspecPointData data = def.data();
    return {data.is_null() ? kFloat64UnimplementedValue : data.data_as_float64()};
}

inline std::string FormatSunspecPointDefToString(const SunspecPointDef &def)
{
    const SunspecPointData data = def.data();
    return std::string{data.is_null() || data.data_as_string().is_null() ? kStringUnimplementedValue : data.data_as_string().value().c_str()};
}

inline std::string FormatStringToString(const Offset<String> &string)
{
    return std::string{string.is_null() ? kStringUnimplementedValue : string.value().c_str()};
}

inline std::string FormatStringToString(const String &string)
{
    return std::string{string.c_str()};
}