/**
 * @brief A union to hold the different possible data types of a Sunspec point.
 *
 * The union allows the class to store any of the defined SunspecPointDataType types
 * in the same memory space.
 */

 #pragma once
// typedef uint16_t raw16_t;
// typedef uint16_t acc16_t;
// typedef uint32_t acc32_t;
// typedef uint64_t acc64_t;
// typedef uint16_t bit16_t;
// typedef uint32_t bit32_t;
// typedef uint64_t bit64_t;
// typedef uint16_t enum16_t;
// typedef uint32_t enum32_t;
// typedef uint16_t sunsSf_t;
// typedef uint16_t pad16_t;
// typedef uint32_t ipAddr_t;

// TODO (Matthew) Correct implementation for the remaining types
typedef uint64_t ipv6Addr_t;
typedef uint64_t eui48_t;

typedef int16_t (*functionSint16)();
typedef int32_t (*functionSint32)();
typedef int64_t (*functionSint64)();
// typedef raw16_t (*functionRaw16)();
typedef uint16_t (*functionUint16)();
typedef uint32_t (*functionUint32)();
typedef uint64_t (*functionUint64)();
// typedef acc16_t (*functionAcc16)();
// typedef acc32_t (*functionAcc32)();
// typedef acc64_t (*functionAcc64)();
// typedef bit16_t (*functionBit16)();
// typedef bit32_t (*functionBit32)();
// typedef bit64_t (*functionBit64)();
// typedef enum16_t (*functionEnum16)();
// typedef enum32_t (*functionEnum32)();
typedef float (*functionFloat32)();
typedef double (*functionFloat64)();
typedef std::string (*functionString)();
// typedef sunsSf_t (*functionSunsSf)();
// typedef pad16_t (*functionPad16)();
// typedef ipAddr_t (*functionIpAddr)();
typedef ipv6Addr_t (*functionIpv6Addr)();
typedef eui48_t (*functionEui48)();

union SunspecValueFunction
{
    functionSint16 sint16;
    functionSint32 sint32;
    functionSint64 sint64;
    // functionRaw16 raw16;
    functionUint16 uint16;
    functionUint32 uint32;
    functionUint64 uint64;
    // functionAcc16 acc16;
    // functionAcc32 acc32;
    // functionAcc64 acc64;
    // functionBit16 bit16;
    // functionBit32 bit32;
    // functionBit64 bit64;
    // functionEnum16 enum16;
    // functionEnum32 enum32;
    functionFloat32 float32;
    functionFloat64 float64;
    functionString str;
    // functionSunsSf sunsSf;
    // functionPad16 pad16;
    // functionIpAddr ipAddr;
    functionIpv6Addr ipv6Addr;
    functionEui48 eui48;
};

constexpr int16_t kSint16UnimplementedValue = 0x8000;
constexpr uint16_t kUint16UnimplementedValue = 0xFFFF;
constexpr int32_t kSint32UnimplementedValue = 0x80000000;
constexpr uint32_t kUint32UnimplementedValue = 0xFFFFFFFF;
constexpr int64_t kSint64UnimplementedValue = 0x8000000000000000;
constexpr uint64_t kUint64UnimplementedValue = 0xFFFFFFFFFFFFFFFF;


inline std::string FlatbufferStringToString(const flatbuffers::String *flatbufferSTring)
{
    return {flatbufferSTring == nullptr ? "" : flatbufferSTring->c_str()};
}