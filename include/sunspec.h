/**
 * @brief A union to hold the different possible data types of a Sunspec point.
 *
 * The union allows the class to store any of the defined SunspecPointDataType types
 * in the same memory space.
 */

#pragma once

#include <cmath>
#include <stdint.h>

#include <string>
#include <string_view>

#include "sunspec_model_definition_generated.h"

#ifndef VIRTUAL_TEST
#define VIRTUAL_TEST
#endif // VIRTUAL_TEST

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

/**
 * @brief A struct to represent an IPv4 address.
 *
 * The struct holds the four octets of an IPv4 address as separate 8-bit unsigned integers.
 */
struct ipAddr_t
{
    uint8_t octet1;
    uint8_t octet2;
    uint8_t octet3;
    uint8_t octet4;
};

// TODO (Matthew) Correct implementation for the remaining types
typedef uint64_t ipv6Addr_t;
typedef uint64_t eui48_t;

/**
 * @brief A template struct to hold a function pointer and its parameter for retrieving Sunspec point values.
 *
 * The struct is a functor but with out the call operator being overloaded to an explicit call method. It can take a parameter that has bee ntype erased allowing for the passing any any type of parameter to the function.
 *
 * @tparam ReturnType The return type of the function i.e. the type of the Sunspec point value.
 */
template <typename ReturnType>
struct SunspecValueFunction
{
    void *param; /**< Pointer to the parameter to be passed to the function. */
    ReturnType (*function)(void *param); /**< Function pointer to be called with the parameter. */

    /**
     * @brief Calls the function with the stored parameter and returns the result.
     * @return The result of the function call.
     */
    ReturnType call() const
    {
        return function(param);
    }
};

/**
 * @brief A union to hold SunspecValueFunction for all possible Sunspec point data types.
 *
 * Each member of the union corresponds to a specific Sunspec data type and holds a
 * SunspecValueFunction which contains a function pointer and a parameter for retrieving the value of that type. The parameter lifetime is managed by the user of the union as no copy is done.
 *
 */
union SunspecPointFunction
{

    SunspecValueFunction<int16_t> sint16;
    SunspecValueFunction<int32_t> sint32;
    SunspecValueFunction<int64_t> sint64;
    SunspecValueFunction<raw16_t> raw16;
    SunspecValueFunction<uint16_t> uint16;
    SunspecValueFunction<uint32_t> uint32;
    SunspecValueFunction<uint64_t> uint64;
    SunspecValueFunction<acc16_t> acc16;
    SunspecValueFunction<acc32_t> acc32;
    SunspecValueFunction<acc64_t> acc64;
    SunspecValueFunction<bitfield16_t> bit16;
    SunspecValueFunction<bit32_t> bit32;
    SunspecValueFunction<bit64_t> bit64;
    SunspecValueFunction<enum16_t> enum16;
    SunspecValueFunction<enum32_t> enum32;
    SunspecValueFunction<float> float32;
    SunspecValueFunction<double> float64;
    SunspecValueFunction<std::string> str;
    SunspecValueFunction<sunsSf_t> sunsSf;
    SunspecValueFunction<pad16_t> pad16;
    SunspecValueFunction<ipAddr_t> ipAddr;
    SunspecValueFunction<ipv6Addr_t> ipv6Addr;
    SunspecValueFunction<eui48_t> eui48;
};

constexpr int16_t kSint16UnimplementedValue = 0x8000; /**< The sunspec unimplemented type for int16 type. */
constexpr pad16_t kPad16UnimplementedValue = 0x8000; /**< The sunspec unimplemented value for the pad16 type. */
constexpr sunsSf_t kSunsSfUnimplementedValue = 0x8000; /**< The sunspec unimplemented value for the sunsSf type. */
constexpr uint16_t kUint16UnimplementedValue = 0xFFFF; /**< The sunspec unimplemented value for the uint16 type. */
constexpr raw16_t kRaw16UnimplementedValue = 0xFFFF; /**< The sunspec unimplemented value for the raw16 type. */
constexpr bitfield16_t kBit16UnimplementedValue = 0xFFFF; /**< The sunspec unimplemented value for the bitfield16 type. */
constexpr acc16_t kAcc16UnimplementedValue = 0; /**< The sunspec unimplemented value for the acc16 type. */
constexpr enum16_t kEnum16UnimplementedValue = 0xFFFF; /**< The sunspec unimplemented value for the enum16 type. */
constexpr int32_t kSint32UnimplementedValue = 0x80000000; /**< The sunspec unimplemented value for the int32 type. */
constexpr uint32_t kUint32UnimplementedValue = 0xFFFFFFFF; /**< The sunspec unimplemented value for the uint32 type. */
constexpr bit32_t kBit32UnimplementedValue = 0xFFFFFFFF; /**< The sunspec unimplemented value for the bit32 type. */
constexpr acc32_t kAcc32UnimplementedValue = 0; /**< The sunspec unimplemented value for the acc32 type. */
constexpr enum32_t kEnum32UnimplementedValue = 0xFFFFFFFF; /**< The sunspec unimplemented value for the enum32 type. */
constexpr ipAddr_t kIpAddrUnimplementedValue = {0x00, 0x00, 0x00, 0x00}; /**< The sunspec unimplemented value for the ipAddr type. */

constexpr int64_t kSint64UnimplementedValue = 0x8000000000000000;  /**< The sunspec unimplemented value of the int64 type. */
constexpr uint64_t kUint64UnimplementedValue = 0xFFFFFFFFFFFFFFFF; /**< The sunspec unimplemented value for the uint64 type. */
constexpr bit64_t kBit64UnimplementedValue = 0xFFFFFFFFFFFFFFFF; /**< The sunspec unimplemented value for the bit64 type. */
constexpr acc64_t kAcc64UnimplementedValue = 0; /**< The sunspec unimplemented value for the acc64 type. */

constexpr std::string_view kStringUnimplementedValue{""}; /**< The sunspec unimplemented value for the string type. */

constexpr uint32_t kFloat32UnimplementedValueAsUint32_t = 0x7FC00000; // NaN /**< The sunspec unimplemented value for the float32 type(NaN), represented in the uint32 value. */
const float kFloat32UnimplementedValue = *reinterpret_cast<const float *>(&kFloat32UnimplementedValueAsUint32_t); /**< The sunspec unimplemented value for the float32 type. */
constexpr uint64_t kFloat64UnimplementedValueAsUint64_t = 0x7FF8000000000000; // NaN  /**< The sunspec unimplemented value for the float64 type (NaN), represented in the uint64 value. */
const double kFloat64UnimplementedValue = *reinterpret_cast<const double *>(&kFloat64UnimplementedValueAsUint64_t); /**< The sunspec unimplemented value for the float64 type. */

/**
 * @brief Converts a Flatbuffers kSint16 to a native int16_t, handling unimplemented values represented as nullptr.
 * 
 * If the input pointer is nullptr, it returns the predefined unimplemented value for int16_t. Otherwise, it retrieves the value from the kSint16 structure.
 * 
 * @param sint16 Pointer to a Flatbuffers kSint16 structure.
 * @return int16_t The corresponding native int16_t value or the unimplemented value if input is nullptr.
 */
inline int16_t FlatbufferKSint16toSint16_t(const kSint16 *sint16)
{
    return {sint16 == nullptr ? kSint16UnimplementedValue : sint16->value()};
}

/**
 * @brief Converts a Flatbuffers kRaw16 to a native raw16_t, handling unimplemented values represented as nullptr.
 * 
 * If the input pointer is nullptr, it returns the predefined unimplemented value for raw16_t. Otherwise, it retrieves the value from the kRaw16 structure.
 * 
 * @param raw16 Pointer to a Flatbuffers kRaw16 structure.
 * @return raw16_t The corresponding native raw16_t value or the unimplemented value if input is nullptr. 
 */
inline raw16_t FlatbufferKRaw16toRaw16_t(const kRaw16 *raw16)
{
    return {raw16 == nullptr ? kRaw16UnimplementedValue : raw16->value()};
}

/**
 * @brief Converts a Flatbuffers kUint16 to a native uint16_t, handling unimplemented values represented as nullptr.
 * 
 * If the input pointer is nullptr, it returns the predefined unimplemented value for uint16_t. Otherwise, it retrieves the value from the kUint16 structure.
 * 
 * @param uint16 Pointer to a Flatbuffers kUint16 structure.
 * @return uint16_t The corresponding native uint16_t value or the unimplemented value if input is nullptr.
 */
inline bitfield16_t FlatbufferKBit16toBit16_t(const kBitfield16 *bit16)
{
    return {bit16 == nullptr ? kBit16UnimplementedValue : bit16->value()};
}

/**
 * @brief Converts a Flatbuffers kAcc16 to a native acc16_t, handling unimplemented values represented as nullptr.
 * 
 * If the input pointer is nullptr, it returns the predefined unimplemented value for acc16_t. Otherwise, it retrieves the value from the kAcc16 structure.
 * 
 * @param acc16 Pointer to a Flatbuffers kAcc16 structure.
 * @return acc16_t The corresponding native acc16_t value or the unimplemented value if input is nullptr.
 */
inline acc16_t FlatbufferKAcc16toAcc16_t(const kAcc16 *acc16)
{
    return {acc16 == nullptr ? kAcc16UnimplementedValue : acc16->value()};
}

/**
 * @brief Converts a Flatbuffers kEnum16 to a native enum16_t, handling unimplemented values represented as nullptr.
 * 
 * If the input pointer is nullptr, it returns the predefined unimplemented value for enum16_t. Otherwise, it retrieves the value from the kEnum16 structure.
 * 
 * @param enum16 Pointer to a Flatbuffers kEnum16 structure.
 * @return enum16_t The corresponding native enum16_t value or the unimplemented value if input is nullptr.
 */
inline enum16_t FlatbufferKEnum16toEnum16_t(const kEnum16 *enum16)
{
    return {enum16 == nullptr ? kEnum16UnimplementedValue : enum16->value()};
}

/**
 * @brief Converts a Flatbuffers kSint32 to a native int32_t, handling unimplemented values represented as nullptr.
 * 
 * If the input pointer is nullptr, it returns the predefined unimplemented value for int32_t. Otherwise, it retrieves the value from the kSint32 structure.
 * 
 * @param sint32 Pointer to a Flatbuffers kSint32 structure.
 * @return int32_t The corresponding native int32_t value or the unimplemented value if input is nullptr.
 */
inline int32_t FlatbufferKSint32toSint32_t(const kSint32 *sint32)
{
    return {sint32 == nullptr ? kSint32UnimplementedValue : sint32->value()};
}

/**
 * @brief Converts a Flatbuffers kUint32 to a native uint32_t, handling unimplemented values represented as nullptr.
 * 
 * If the input pointer is nullptr, it returns the predefined unimplemented value for uint32_t. Otherwise, it retrieves the value from the kUint32 structure.
 * 
 * @param uint32 Pointer to a Flatbuffers kUint32 structure.
 * @return uint32_t The corresponding native uint32_t value or the unimplemented value if input is nullptr.
 */
inline uint32_t FlatbufferKUint32toUint32_t(const kUint32 *uint32)
{
    return {uint32 == nullptr ? kUint32UnimplementedValue : uint32->value()};
}

/**
 * @brief Converts a Flatbuffers KAcc32 to a native acc32_t, handling unimplemented values represented as nullptr.
 * 
 * If the input pointer is nullptr, it returns the predefined unimplemented value for acc32_t. Otherwise, it retrieves the value from the KAcc32 structure.
 * 
 * @param acc32 Pointer to a Flatbuffers KAcc32 structure.
 * @return acc32_t The corresponding native acc32_t value or the unimplemented value if input is nullptr.
 */
inline acc32_t FlatbufferKAcc32toAcc32_t(const KAcc32 *acc32)
{
    return {acc32 == nullptr ? kAcc32UnimplementedValue : acc32->value()};
}

/**
 * @brief Converts a Flatbuffers kBit32 to a native bit32_t, handling unimplemented values represented as nullptr.
 * 
 * If the input pointer is nullptr, it returns the predefined unimplemented value for bit32_t. Otherwise, it retrieves the value from the kBitfield32 structure.
 * 
 * @param bit32 Pointer to a Flatbuffers kBitfield32 structure.
 * @return bit32_t The corresponding native bit32_t value or the unimplemented value if input is nullptr.
 */
inline bit32_t FlatbufferKBit32toBit32_t(const kBitfield32 *bit32)
{
    return {bit32 == nullptr ? kBit32UnimplementedValue : bit32->value()};
}

/**
 * @brief Converts a Flatbuffers kEnum32 to a native enum32_t, handling unimplemented values represented as nullptr.
 * 
 * If the input pointer is nullptr, it returns the predefined unimplemented value for enum32_t. Otherwise, it retrieves the value from the kEnum32 structure.
 * 
 * @param enum32 Pointer to a Flatbuffers kEnum32 structure.
 * @return enum32_t The corresponding native enum32_t value or the unimplemented value if input is nullptr.
 */
inline enum32_t FlatbufferKEnum32toEnum32_t(const kEnum32 *enum32)
{
    return {enum32 == nullptr ? kEnum32UnimplementedValue : enum32->value()};
}

/**
 * @brief Converts a Flatbuffers kSint64 to a native int64_t, handling unimplemented values represented as nullptr. 
 * 
 * If the input pointer is nullptr, it returns the predefined unimplemented value for int64_t. Otherwise, it retrieves the value from the kSint64 structure.
 * @param sint64 Pointer to a Flatbuffers kSint64 structure.
 * @return int64_t The corresponding native int64_t value or the unimplemented value if input is nullptr.
 */
inline ipAddr_t FlatbufferKIpAddrtoIpAddr_t(const kIpAddr *ipAddr)
{
    if (ipAddr == nullptr)
    {
        return kIpAddrUnimplementedValue;
    }
    return {ipAddr->octet1(), ipAddr->octet2(), ipAddr->octet3(), ipAddr->octet4()};
}

/**
 * @brief Converts a Flatbuffers kSunsSf to a native sunsSf_t, handling unimplemented values represented as nullptr.
 * 
 * If the input pointer is nullptr, it returns the predefined unimplemented value for sunsSf_t. Otherwise, it retrieves the value from the kSunsSf structure.
 * 
 * @param sunsSf Pointer to a Flatbuffers kSunsSf structure.
 * @return sunsSf_t The corresponding native sunsSf_t value or the unimplemented value if input is nullptr.
 */
inline sunsSf_t FlatbufferKSunsSftoSunsSf_t(const kSunsSf *sunsSf)
{
    return {sunsSf == nullptr ? kSunsSfUnimplementedValue : sunsSf->value()};
}

/**
 * @brief Converts a Flatbuffers kUint16 to a native uint16_t, handling unimplemented values represented as nullptr.
 * 
 * If the input pointer is nullptr, it returns the predefined unimplemented value for uint16_t. Otherwise, it retrieves the value from the kUint16 structure.
 * 
 * @param uint16 Pointer to a Flatbuffers kUint16 structure.
 * @return uint16_t The corresponding native uint16_t value or the unimplemented value if input is nullptr.
 */
inline uint16_t FlatbufferKUint16toUint16_t(const kUint16 *uint16)
{
    return {uint16 == nullptr ? kUint16UnimplementedValue : uint16->value()};
}

/**
 * @brief Converts a Flatbuffers kPad16 to a native pad16_t, handling unimplemented values represented as nullptr.
 * 
 * If the input pointer is nullptr, it returns the predefined unimplemented value for pad16_t. Otherwise, it retrieves the value from the kPad16 structure.
 * 
 * @param pad16 Pointer to a Flatbuffers kPad16 structure.
 * @return pad16_t The corresponding native pad16_t value or the unimplemented value if input is nullptr.
 */
inline pad16_t FlatbufferKPad16toPad16_t(const kPad16 *pad16)
{
    return {pad16 == nullptr ? kPad16UnimplementedValue : pad16->value()};
}

/**
 * @brief Converts a Flatbuffers kSint64 to a native int64_t, handling unimplemented values represented as nullptr.
 * 
 * If the input pointer is nullptr, it returns the predefined unimplemented value for int64_t. Otherwise, it retrieves the value from the kSint64 structure.
 * @param sint64 Pointer to a Flatbuffers kSint64 structure.
 * @return int64_t The corresponding native int64_t value or the unimplemented value if input is nullptr.
 */
inline int64_t FlatbufferKSint64toSint64_t(const kSint64 *sint64)
{
    return {sint64 == nullptr ? kSint64UnimplementedValue : sint64->value()};
}

/**
 * @brief Converts a Flatbuffers kUint64 to a native uint64_t, handling unimplemented values represented as nullptr.
 * 
 * If the input pointer is nullptr, it returns the predefined unimplemented value for uint64_t. Otherwise, it retrieves the value from the kUint64 structure.
 * 
 * @param uint64 Pointer to a Flatbuffers kUint64 structure.
 * @return uint64_t The corresponding native uint64_t value or the unimplemented value if input is nullptr.
 */
inline uint64_t FlatbufferKUint64toUint64_t(const kUint64 *uint64)
{
    return {uint64 == nullptr ? kUint64UnimplementedValue : uint64->value()};
}

/**
 * @brief Converts a Flatbuffers kAcc64 to a native acc64_t, handling unimplemented values represented as nullptr.
 * 
 * If the input pointer is nullptr, it returns the predefined unimplemented value for acc64_t. Otherwise, it retrieves the value from the kAcc64 structure.
 * 
 * @param acc64 Pointer to a Flatbuffers kAcc64 structure.
 * @return acc64_t The corresponding native acc64_t value or the unimplemented value if input is nullptr.
 */
inline acc64_t FlatbufferKAcc64toAcc64_t(const kAcc64 *acc64)
{
    return {acc64 == nullptr ? kAcc64UnimplementedValue : acc64->value()};
}

/**
 * @brief Converts a Flatbuffers kBit64 to a native bit64_t, handling unimplemented values represented as nullptr.
 * 
 * If the input pointer is nullptr, it returns the predefined unimplemented value for bit64_t. Otherwise, it retrieves the value from the kBitfield64 structure.
 * 
 * @param bit64 Pointer to a Flatbuffers kBitfield64 structure.
 * @return bit64_t The corresponding native bit64_t value or the unimplemented value if input is nullptr.
 */
inline bit64_t FlatbufferKBit64toBit64_t(const kBitfield64 *bit64)
{
    return {bit64 == nullptr ? kBit64UnimplementedValue : bit64->value()};
}

/**
 * @brief Converts a Flatbuffers kFloat64 to a native double, handling unimplemented values represented as nullptr.
 * 
 * If the input pointer is nullptr, it returns the predefined unimplemented value for double. Otherwise, it retrieves the value from the kFloat64 structure.
 * 
 * @param float64 Pointer to a Flatbuffers kFloat64 structure.
 * @return double The corresponding native double value or the unimplemented value if input is nullptr.
 */
inline double FlatbufferKFloat64toDouble(const kFloat64 *float64)
{
    return {float64 == nullptr ? kFloat64UnimplementedValue : float64->value()};
}

/**
 * @brief Converts a Flatbuffers kFloat32 to a native float, handling unimplemented values represented as nullptr.
 * 
 * If the input pointer is nullptr, it returns the predefined unimplemented value for float. Otherwise, it retrieves the value from the kFloat32 structure.
 * 
 * @param float32 Pointer to a Flatbuffers kFloat32 structure.
 * @return float The corresponding native float value or the unimplemented value if input is nullptr.
 */
inline float FlatbufferKFloat32toFloat(const kFloat32 *float32)
{
    return {float32 == nullptr ? kFloat32UnimplementedValue : float32->value()};
}

/**
 * @brief Converts a Flatbuffers String to a native std::string, handling unimplemented values represented as nullptr.
 * 
 * If the input pointer is nullptr, it returns the predefined unimplemented value for std::string. Otherwise, it retrieves the C-style string from the Flatbuffers String and constructs a std::string from it.
 * 
 * @param flatbufferSTring Pointer to a Flatbuffers String structure.
 * @return std::string The corresponding native std::string value or the unimplemented value if input is nullptr.
 */
inline std::string FlatbufferStringToString(const flatbuffers::String *flatbufferSTring)
{
    return std::string{flatbufferSTring == nullptr ? kStringUnimplementedValue : flatbufferSTring->c_str()};
}

/**
 * @brief Converts a Flatbuffers kStringx to a native std::string, handling unimplemented values represented as nullptr.
 * 
 * If the input pointer is nullptr, it returns the predefined unimplemented value for std::string. Otherwise, it retrieves the value from the kStringx structure and constructs a std::string from it.
 * 
 * @param stringx Pointer to a Flatbuffers kStringx structure.
 * @return std::string The corresponding native std::string value or the unimplemented value if input is nullptr.
 */
inline std::string FlatbufferKStringxToString(const kStringx *stringx)
{
    return {stringx == nullptr ? "" : FlatbufferStringToString(stringx->value())};
}

/**
 * @brief Converts a uint16_t value to Modbus register format by swapping the uint16_t bytes order.
 */
inline uint16_t uint16_tToModbusRegisterFormat(uint16_t val)
{
    return val;
}

/**
 * @brief Converts a uint32_t value to Modbus register format by swapping the two uint16_t words order.
 */
inline uint32_t uint32_tToModbusRegisterFormat(uint32_t val)
{
    return ((val << 16) & 0xffff0000) | ((val >> 16) & 0x0000ffff);
}

/**
 * @brief Converts a uint64_t value to Modbus register format by swapping the four uint16_t words order.
 */
inline uint64_t uint64_tToModbusRegisterFormat(uint64_t val)
{
    return ((val << 16 * 3) & 0xFFFF000000000000) |
           ((val << 16 * 1) & 0x0000FFFF00000000) |
           ((val >> 16 * 1) & 0x00000000FFFF0000) |
           ((val >> 16 * 3) & 0x000000000000FFFF);
}

/**
 * @brief Converts a int64_t value to Modbus register format by swapping the four uint16_t words order.
 */
inline int64_t sint64_tToModbusRegisterFormat(int64_t val)
{
    return ((val << 16 * 3) & 0xFFFF000000000000) |
           ((val << 16 * 1) & 0x0000FFFF00000000) |
           ((val >> 16 * 1) & 0x00000000FFFF0000) |
           ((val >> 16 * 3) & 0x000000000000FFFF);
}

/**
 * @brief Converts a int16_t value to Modbus register format by swapping the int16_t bytes order.
 */
inline int16_t sint16_tToModbusRegisterFormat(int16_t val)
{
    return val;
}


/**
 * @brief Converts a int32_t value to Modbus register format by swapping the two uint16_t words order.
 */
inline int32_t sint32_tToModbusRegisterFormat(int32_t val)
{
    return ((val << 16) & 0xffff0000) | ((val >> 16) & 0x0000ffff);
}

/**
 * @brief Converts a float value to Modbus register format by swapping the two uint16_t words order.
 */
inline float floatToModbusRegisterFormat(float val)
{
    uint32_t temp = *reinterpret_cast<uint32_t *>(&val);
    temp = uint32_tToModbusRegisterFormat(temp);
    return *reinterpret_cast<float *>(&temp);
}

/**
 * @brief Converts a double value to Modbus register format by swapping the four uint16_t words order.
 */
inline double doubleToModbusRegisterFormat(double val)
{
    uint64_t temp = *reinterpret_cast<uint64_t *>(&val);
    temp = uint64_tToModbusRegisterFormat(temp);
    return *reinterpret_cast<double *>(&temp);
}

/**
 * @brief Converts a std::string to Modbus register format and stores it in a provided buffer.
 * 
 * The function takes a std::string and converts it into a format suitable for Modbus registers,
 * storing the result in a provided buffer of uint16_t. The conversion handles both even and odd
 * length strings, ensuring that the string is null-terminated within the buffer.
 * 
 * @param str The input std::string to be converted.
 * @param buffer A pointer to the buffer where the Modbus register formatted data will be stored.
 * @param bufferSize The size of the buffer in terms of number of uint16_t elements.
 * 
 * @note The function ensures that the string fits within the buffer, truncating if necessary,
 * and always includes a null terminator. The buffer size is considered in terms of uint16_t elements,
 * meaning that the actual byte size is twice the bufferSize.
 */
inline void stringToModbusRegisterFormat(const std::string &str, uint16_t *buffer, uint16_t bufferSize)
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

/**
 * @brief Overloaded addition operator to concatenate a `std::string` and a `std::string_view`.
 * @param [in] str1 The `std::string` to which the `std::string_view` will be appended.
 * @param [in] str2 The `std::string_view` to be appended.
 * @return A new `std::string` containing the concatenated result.
 */
inline std::string operator+(const std::string &str1, const std::string_view &str2)
{
    return str1 + std::string{str2};
}

/**
 * @brief Overloaded addition operator to concatenate a `std::string_view` and a `std::string`.
 * @param [in] str1 The `std::string_view` to which the `std::string` will be appended.
 * @param [in] str2 The `std::string` to be appended.
 * @return A new `std::string` containing the concatenated result.
 */
inline std::string operator+(const std::string_view &str1, const std::string &str2)
{
    return std::string{str1} + str2;
}


/**
 * @namespace Sunspec
 */
namespace Sunspec
{
    /**
     * @brief Converts two 16-bit registers into a 32-bit floating-point number.
     * @param [in] reg0 The first 16-bit register (most significant word).
     * @param [in] reg1 The second 16-bit register (least significant word).
     * @return A 32-bit floating-point number.
     */
    float registersToFloat(uint16_t reg0, uint16_t reg1);

    /**
     * @brief Converts a single 16-bit register into an unsigned 16-bit integer.
     * @param [in] reg The 16-bit register.
     * @return An unsigned 16-bit integer.
     */
    uint16_t registersToUint16(uint16_t reg);

    /**
     * @brief Converts two 16-bit registers into an unsigned 32-bit integer.
     * @param [in] reg0 The first 16-bit register (most significant word).
     * @param [in] reg1 The second 16-bit register (least significant word).
     * @return An unsigned 32-bit integer.
     */
    uint32_t registersToUint32(uint16_t reg0, uint16_t reg1);

    /**
     * @brief Converts four 16-bit registers into an unsigned 64-bit integer.
     * @param [in] reg0 The first 16-bit register (most significant word).
     * @param [in] reg1 The second 16-bit register.
     * @param [in] reg2 The third 16-bit register.
     * @param [in] reg3 The fourth 16-bit register (least significant word).
     * @return An unsigned 64-bit integer.
     */
    uint64_t registersToUint64(uint16_t reg0, uint16_t reg1, uint16_t reg2, uint16_t reg3);

}; // namespace Sunspec
