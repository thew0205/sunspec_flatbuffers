/**
 * @brief A union to hold the different possible data types of a Sunspec point.
 *
 * The union allows the class to store any of the defined SunspecPointDataType types
 * in the same memory space.
 */

#pragma once
#include <cmath>

#ifndef VIRTUAL_TEST
#define VIRTUAL_TEST
#endif // VIRTUAL_TEST
struct ipAddr_t
{
    uint8_t octet1;
    uint8_t octet2;
    uint8_t octet3;
    uint8_t octet4;
};
typedef uint16_t raw16_t;
typedef uint16_t acc16_t;
typedef uint32_t acc32_t;
typedef uint64_t acc64_t;
typedef uint16_t bitfield16_t;
typedef uint32_t bit32_t;
typedef uint64_t bit64_t;
typedef uint16_t enum16_t;
typedef uint32_t enum32_t;
typedef uint16_t sunsSf_t;
typedef uint16_t pad16_t;

// TODO (Matthew) Correct implementation for the remaining types
typedef uint64_t ipv6Addr_t;
typedef uint64_t eui48_t;

typedef int16_t (*functionSint16)();
typedef int32_t (*functionSint32)();
typedef int64_t (*functionSint64)();
typedef raw16_t (*functionRaw16)();
typedef uint16_t (*functionUint16)();
typedef uint32_t (*functionUint32)();
typedef uint64_t (*functionUint64)();
typedef acc16_t (*functionAcc16)();
typedef acc32_t (*functionAcc32)();
typedef acc64_t (*functionAcc64)();
typedef bitfield16_t (*functionBit16)();
typedef bit32_t (*functionBit32)();
typedef bit64_t (*functionBit64)();
typedef enum16_t (*functionEnum16)();
typedef enum32_t (*functionEnum32)();
typedef float (*functionFloat32)();
typedef double (*functionFloat64)();
typedef std::string (*functionString)();
typedef sunsSf_t (*functionSunsSf)();
typedef pad16_t (*functionPad16)();
typedef ipAddr_t (*functionIpAddr)();
typedef ipv6Addr_t (*functionIpv6Addr)();
typedef eui48_t (*functionEui48)();

union SunspecValueFunction
{
    functionSint16 sint16;
    functionSint32 sint32;
    functionSint64 sint64;
    functionRaw16 raw16;
    functionUint16 uint16;
    functionUint32 uint32;
    functionUint64 uint64;
    functionAcc16 acc16;
    functionAcc32 acc32;
    functionAcc64 acc64;
    functionBit16 bit16;
    functionBit32 bit32;
    functionBit64 bit64;
    functionEnum16 enum16;
    functionEnum32 enum32;
    functionFloat32 float32;
    functionFloat64 float64;
    functionString str;
    functionSunsSf sunsSf;
    functionPad16 pad16;
    functionIpAddr ipAddr;
    functionIpv6Addr ipv6Addr;
    functionEui48 eui48;
};

constexpr int16_t kSint16UnimplementedValue = 0x8000;
constexpr pad16_t kPad16UnimplementedValue = 0x8000;
constexpr sunsSf_t kSunsSfUnimplementedValue = 0x8000;
constexpr uint16_t kUint16UnimplementedValue = 0xFFFF;
constexpr raw16_t kRaw16UnimplementedValue = 0xFFFF;
constexpr bitfield16_t kBit16UnimplementedValue = 0xFFFF;
constexpr acc16_t kAcc16UnimplementedValue = 0;
constexpr enum16_t kEnum16UnimplementedValue = 0xFFFF;
constexpr int32_t kSint32UnimplementedValue = 0x80000000;
constexpr uint32_t kUint32UnimplementedValue = 0xFFFFFFFF;
constexpr bit32_t kBit32UnimplementedValue = 0xFFFFFFFF;
constexpr acc32_t kAcc32UnimplementedValue = 0;
constexpr enum32_t kEnum32UnimplementedValue = 0xFFFFFFFF;
constexpr ipAddr_t kIpAddrUnimplementedValue = {0x00, 0x00, 0x00, 0x00};

constexpr int64_t kSint64UnimplementedValue = 0x8000000000000000;
constexpr uint64_t kUint64UnimplementedValue = 0xFFFFFFFFFFFFFFFF;
constexpr bit64_t kBit64UnimplementedValue = 0xFFFFFFFFFFFFFFFF;
constexpr acc64_t kAcc64UnimplementedValue = 0;

constexpr std::string_view kStringUnimplementedValue{""};

constexpr uint32_t kFloat32UnimplementedValueAsUint32_t = 0x7FC00000; // NaN
const float kFloat32UnimplementedValue = *reinterpret_cast<const float *>(&kFloat32UnimplementedValueAsUint32_t);
constexpr uint64_t kFloat64UnimplementedValueAsUint64_t = 0x7FF8000000000000; // NaN
const double kFloat64UnimplementedValue = *reinterpret_cast<const double *>(&kFloat64UnimplementedValueAsUint64_t);

inline int16_t FlatbufferKSint16toSint16_t(const kSint16 *sint16)
{
    return {sint16 == nullptr ? kSint16UnimplementedValue : sint16->value()};
}
inline raw16_t FlatbufferKRaw16toRaw16_t(const kRaw16 *raw16)
{
    return {raw16 == nullptr ? kRaw16UnimplementedValue : raw16->value()};
}
inline bitfield16_t FlatbufferKBit16toBit16_t(const kBitfield16 *bit16)
{
    return {bit16 == nullptr ? kBit16UnimplementedValue : bit16->value()};
}
inline acc16_t FlatbufferKAcc16toAcc16_t(const kAcc16 *acc16)
{
    return {acc16 == nullptr ? kAcc16UnimplementedValue : acc16->value()};
}

inline enum16_t FlatbufferKEnum16toEnum16_t(const kEnum16 *enum16)
{
    return {enum16 == nullptr ? kEnum16UnimplementedValue : enum16->value()};
}
inline int32_t FlatbufferKSint32toSint32_t(const kSint32 *sint32)
{
    return {sint32 == nullptr ? kSint32UnimplementedValue : sint32->value()};
}
inline uint32_t FlatbufferKUint32toUint32_t(const kUint32 *uint32)
{
    return {uint32 == nullptr ? kUint32UnimplementedValue : uint32->value()};
}
inline acc32_t FlatbufferKAcc32toAcc32_t(const KAcc32 *acc32)
{
    return {acc32 == nullptr ? kAcc32UnimplementedValue : acc32->value()};
}
inline bit32_t FlatbufferKBit32toBit32_t(const kBitfield32 *bit32)
{
    return {bit32 == nullptr ? kBit32UnimplementedValue : bit32->value()};
}
inline enum32_t FlatbufferKEnum32toEnum32_t(const kEnum32 *enum32)
{
    return {enum32 == nullptr ? kEnum32UnimplementedValue : enum32->value()};
}
inline ipAddr_t FlatbufferKIpAddrtoIpAddr_t(const kIpAddr *ipAddr)
{
    if (ipAddr == nullptr)
    {
        return kIpAddrUnimplementedValue;
    }
    return {ipAddr->octet1(), ipAddr->octet2(), ipAddr->octet3(), ipAddr->octet4()};
}

inline sunsSf_t FlatbufferKSunsSftoSunsSf_t(const kSunsSf *sunsSf)
{
    return {sunsSf == nullptr ? kSunsSfUnimplementedValue : sunsSf->value()};
}
inline uint16_t FlatbufferKUint16toUint16_t(const kUint16 *uint16)
{
    return {uint16 == nullptr ? kUint16UnimplementedValue : uint16->value()};
}
inline pad16_t FlatbufferKPad16toPad16_t(const kPad16 *pad16)
{
    return {pad16 == nullptr ? kPad16UnimplementedValue : pad16->value()};
}
inline int64_t FlatbufferKSint64toSint64_t(const kSint64 *sint64)
{
    return {sint64 == nullptr ? kSint64UnimplementedValue : sint64->value()};
}
inline uint64_t FlatbufferKUint64toUint64_t(const kUint64 *uint64)
{
    return {uint64 == nullptr ? kUint64UnimplementedValue : uint64->value()};
}
inline acc64_t FlatbufferKAcc64toAcc64_t(const kAcc64 *acc64)
{
    return {acc64 == nullptr ? kAcc64UnimplementedValue : acc64->value()};
}
inline bit64_t FlatbufferKBit64toBit64_t(const kBitfield64 *bit64)
{
    return {bit64 == nullptr ? kBit64UnimplementedValue : bit64->value()};
}
inline double FlatbufferKFloat64toDouble(const kFloat64 *float64)
{
    return {float64 == nullptr ? kFloat64UnimplementedValue : float64->value()};
}
inline float FlatbufferKFloat32toFloat(const kFloat32 *float32)
{
    return {float32 == nullptr ? kFloat32UnimplementedValue : float32->value()};
}
inline std::string FlatbufferStringToString(const flatbuffers::String *flatbufferSTring)
{
    return std::string{flatbufferSTring == nullptr ? kStringUnimplementedValue : flatbufferSTring->c_str()};
}

inline std::string FlatbufferKStringxToString(const kStringx *stringx)
{
    return {stringx == nullptr ? "" : FlatbufferStringToString(stringx->value())};
}

inline uint16_t uint16_tToBigEndian(uint16_t val)
{
    return val;
}
inline uint32_t uint32_tToBigEndian(uint32_t val)
{
    return ((val << 16) & 0xffff0000) | ((val >> 16) & 0x0000ffff);
}
inline uint64_t uint64_tToBigEndian(uint64_t val)
{
    return ((val << 16 * 3) & 0xFFFF000000000000) |
           ((val << 16 * 1) & 0x0000FFFF00000000) |
           ((val >> 16 * 1) & 0x00000000FFFF0000) |
           ((val >> 16 * 3) & 0x000000000000FFFF);
}

inline int64_t sint64_tToBigEndian(int64_t val)
{
    return ((val << 16 * 3) & 0xFFFF000000000000) |
           ((val << 16 * 1) & 0x0000FFFF00000000) |
           ((val >> 16 * 1) & 0x00000000FFFF0000) |
           ((val >> 16 * 3) & 0x000000000000FFFF);
}
inline int16_t sint16_tToBigEndian(int16_t val)
{
    return val;
}

inline int32_t sint32_tToBigEndian(int32_t val)
{
    return ((val << 16) & 0xffff0000) | ((val >> 16) & 0x0000ffff);
}

inline float floatToBigEndian(float val)
{
    uint32_t temp = *reinterpret_cast<uint32_t *>(&val);
    temp = uint32_tToBigEndian(temp);
    return *reinterpret_cast<float *>(&temp);
}

inline double doubleToBigEndian(double val)
{
    uint64_t temp = *reinterpret_cast<uint64_t *>(&val);
    temp = uint64_tToBigEndian(temp);
    return *reinterpret_cast<double *>(&temp);
}

inline void stringToBigEndian(const std::string &str, uint16_t *buffer, uint16_t bufferSize)
{
    const char *raw = str.data();
    bufferSize = std::min(static_cast<size_t>((bufferSize * 2) - 1), str.size()); // The minus one is space for a compulsory null.
  
    if (((bufferSize * 2) - 1) < str.size())
    {
        for (int i = 0; i < bufferSize; i++)
        {
            buffer[i] = (raw[(i * 2) + 0] << 8) | raw[(i * 2) + 1];
        }
        // Adding the compulsory null terminator since the buffer size is less than the string length;
        // Remember that it is little endian which will be swap on the host side.
        buffer[bufferSize - 1] = buffer[bufferSize] >> 8 & 0x00FF;
    }
    else
    {
        for (int i = 0; i < (str.size() + 1) / 2; i++)
        {
            buffer[i] = (raw[(i * 2) + 0] << 8) | raw[(i * 2) + 1];
        }
        // just fill the rest with null terminator.
        // There is no need for manual swapping as the null terminator will be placed correct wither being even or odd.
        for (int i = (str.size() + 1) / 2; i < bufferSize; i++)
        {
            buffer[i] = '\0';
        }
    }
}
