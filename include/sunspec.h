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

#ifndef VIRTUAL_TEST
#define VIRTUAL_TEST
#endif // VIRTUAL_TEST

typedef uint16_t raw16_t;
typedef uint16_t acc16_t;
typedef uint32_t acc32_t;
typedef uint64_t acc64_t;
typedef uint16_t bitfield16_t;
typedef uint32_t bitfield32_t;
typedef uint64_t bitfield64_t;
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
    void *param;                         /**< Pointer to the parameter to be passed to the function. */
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
    SunspecValueFunction<bitfield32_t> bit32;
    SunspecValueFunction<bitfield64_t> bit64;
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

constexpr int16_t kSint16UnimplementedValue = 0x8000;                    /**< The sunspec unimplemented type for int16 type. */
constexpr pad16_t kPad16UnimplementedValue = 0x8000;                     /**< The sunspec unimplemented value for the pad16 type. */
constexpr sunsSf_t kSunsSfUnimplementedValue = 0x8000;                   /**< The sunspec unimplemented value for the sunsSf type. */
constexpr uint16_t kUint16UnimplementedValue = 0xFFFF;                   /**< The sunspec unimplemented value for the uint16 type. */
constexpr raw16_t kRaw16UnimplementedValue = 0xFFFF;                     /**< The sunspec unimplemented value for the raw16 type. */
constexpr bitfield16_t kBit16UnimplementedValue = 0xFFFF;                /**< The sunspec unimplemented value for the bitfield16 type. */
constexpr acc16_t kAcc16UnimplementedValue = 0;                          /**< The sunspec unimplemented value for the acc16 type. */
constexpr enum16_t kEnum16UnimplementedValue = 0xFFFF;                   /**< The sunspec unimplemented value for the enum16 type. */
constexpr int32_t kSint32UnimplementedValue = 0x80000000;                /**< The sunspec unimplemented value for the int32 type. */
constexpr uint32_t kUint32UnimplementedValue = 0xFFFFFFFF;               /**< The sunspec unimplemented value for the uint32 type. */
constexpr bitfield32_t kBit32UnimplementedValue = 0xFFFFFFFF;            /**< The sunspec unimplemented value for the bit32 type. */
constexpr acc32_t kAcc32UnimplementedValue = 0;                          /**< The sunspec unimplemented value for the acc32 type. */
constexpr enum32_t kEnum32UnimplementedValue = 0xFFFFFFFF;               /**< The sunspec unimplemented value for the enum32 type. */
constexpr ipAddr_t kIpAddrUnimplementedValue = {0x00, 0x00, 0x00, 0x00}; /**< The sunspec unimplemented value for the ipAddr type. */

constexpr int64_t kSint64UnimplementedValue = 0x8000000000000000;     /**< The sunspec unimplemented value of the int64 type. */
constexpr uint64_t kUint64UnimplementedValue = 0xFFFFFFFFFFFFFFFF;    /**< The sunspec unimplemented value for the uint64 type. */
constexpr bitfield64_t kBit64UnimplementedValue = 0xFFFFFFFFFFFFFFFF; /**< The sunspec unimplemented value for the bit64 type. */
constexpr acc64_t kAcc64UnimplementedValue = 0;                       /**< The sunspec unimplemented value for the acc64 type. */

constexpr std::string_view kStringUnimplementedValue{""}; /**< The sunspec unimplemented value for the string type. */

constexpr uint32_t kFloat32UnimplementedValueAsUint32_t = 0x7FC00000;                                               // NaN /**< The sunspec unimplemented value for the float32 type(NaN), represented in the uint32 value. */
const float kFloat32UnimplementedValue = *reinterpret_cast<const float *>(&kFloat32UnimplementedValueAsUint32_t);   /**< The sunspec unimplemented value for the float32 type. */
constexpr uint64_t kFloat64UnimplementedValueAsUint64_t = 0x7FF8000000000000;                                       // NaN  /**< The sunspec unimplemented value for the float64 type (NaN), represented in the uint64 value. */
const double kFloat64UnimplementedValue = *reinterpret_cast<const double *>(&kFloat64UnimplementedValueAsUint64_t); /**< The sunspec unimplemented value for the float64 type. */

/**
 * @brief Converts a uint16_t value to Modbus register format by swapping the uint16_t bytes order.
 */
inline uint16_t uint16_tToModbusRegisterFormat(const uint16_t val)
{
    return val;
}

/**
 * @brief Converts a uint32_t value to Modbus register format by swapping the two uint16_t words order.
 */
inline uint32_t uint32_tToModbusRegisterFormat(const uint32_t val)
{
    return ((val << 16) & 0xffff0000) | ((val >> 16) & 0x0000ffff);
}

/**
 * @brief Converts a uint64_t value to Modbus register format by swapping the four uint16_t words order.
 */
inline uint64_t uint64_tToModbusRegisterFormat(const uint64_t val)
{
    return ((val << 16 * 3) & 0xFFFF000000000000) |
           ((val << 16 * 1) & 0x0000FFFF00000000) |
           ((val >> 16 * 1) & 0x00000000FFFF0000) |
           ((val >> 16 * 3) & 0x000000000000FFFF);
}

// /**
//  * @brief Converts a int64_t value to Modbus register format by swapping the four uint16_t words order.
//  */
// inline int64_t sint64_tToModbusRegisterFormat(const int64_t val)
// {
//     return ((val << 16 * 3) & 0xFFFF000000000000) |
//            ((val << 16 * 1) & 0x0000FFFF00000000) |
//            ((val >> 16 * 1) & 0x00000000FFFF0000) |
//            ((val >> 16 * 3) & 0x000000000000FFFF);
// }

// /**
//  * @brief Converts a int16_t value to Modbus register format by swapping the int16_t bytes order.
//  */
// inline int16_t sint16_tToModbusRegisterFormat(const int16_t val)
// {
//     return val;
// }

/**
 * @brief Converts a int32_t value to Modbus register format by swapping the two uint16_t words order.
 */
inline int32_t sint32_tToModbusRegisterFormat(const int32_t val)
{
    return ((val << 16) & 0xffff0000) | ((val >> 16) & 0x0000ffff);
}

/**
 * @brief Converts a float value to Modbus register format by swapping the two uint16_t words order.
 */
inline float floatToModbusRegisterFormat(const float val)
{
    uint32_t temp = *reinterpret_cast<const uint32_t *>(&val);
    temp = uint32_tToModbusRegisterFormat(temp);
    return *reinterpret_cast<float *>(&temp);
}

/**
 * @brief Converts a double value to Modbus register format by swapping the four uint16_t words order.
 */
inline double doubleToModbusRegisterFormat(const double val)
{
    uint64_t temp = *reinterpret_cast<const uint64_t *>(&val);
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
inline void stringToModbusRegisterFormat(const std::string &str, uint16_t *buffer, const uint16_t bufferSize)
{

    // TODO Write test for this
    const char *raw = str.data();
    // bufferSize = std::min(static_cast<size_t>((bufferSize * 2) - 1), str.size()); // The minus one is space for a compulsory null.

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

inline uint16_t modbusRegisterFormatToUint16(const uint16_t *buffer)
{
    return buffer[0];
}

inline int16_t modbusRegisterFormatToSint16(const uint16_t *buffer)
{
    return static_cast<int16_t>(modbusRegisterFormatToUint16(buffer));
}
inline raw16_t modbusRegisterFormatToRaw16(const uint16_t *buffer)
{
    return static_cast<raw16_t>(modbusRegisterFormatToUint16(buffer));
}
inline bitfield16_t modbusRegisterFormatToBitfield16(const uint16_t *buffer)
{
    return static_cast<bitfield16_t>(modbusRegisterFormatToUint16(buffer));
}
inline acc16_t modbusRegisterFormatToAcc16(const uint16_t *buffer)
{
    return static_cast<acc16_t>(modbusRegisterFormatToUint16(buffer));
}
inline enum16_t modbusRegisterFormatToEnum16(const uint16_t *buffer)
{
    return static_cast<enum16_t>(modbusRegisterFormatToUint16(buffer));
}

inline sunsSf_t modbusRegisterFormatToSunsSf(const uint16_t *buffer)
{
    return static_cast<sunsSf_t>(modbusRegisterFormatToUint16(buffer));
}

inline pad16_t modbusRegisterFormatToPad16(const uint16_t *buffer)
{
    return static_cast<pad16_t>(modbusRegisterFormatToUint16(buffer));
}

inline uint32_t modbusRegisterFormatToUint32(const uint16_t *buffer)
{
    return ((static_cast<uint32_t>(buffer[0])) << 1 * 16) | ((static_cast<uint32_t>(buffer[1])));
}

inline int32_t modbusRegisterFormatToSint32(const uint16_t *buffer)
{
    return static_cast<int32_t>(modbusRegisterFormatToUint32(buffer));
}
inline bitfield32_t modbusRegisterFormatToBitfield32(const uint16_t *buffer)
{
    return static_cast<bitfield32_t>(modbusRegisterFormatToUint32(buffer));
}
inline acc32_t modbusRegisterFormatToAcc32(const uint16_t *buffer)
{
    return static_cast<acc32_t>(modbusRegisterFormatToUint32(buffer));
}
inline enum32_t modbusRegisterFormatToEnum32(const uint16_t *buffer)
{
    return static_cast<enum32_t>(modbusRegisterFormatToUint32(buffer));
}

inline uint64_t modbusRegisterFormatToUint64(const uint16_t *buffer)
{
    return ((static_cast<uint64_t>(buffer[0])) << 3 * 16) | ((static_cast<uint64_t>(buffer[1])) << 2 * 16) | ((static_cast<uint64_t>(buffer[2])) << 1 * 16) | ((static_cast<uint64_t>(buffer[3])));
}

inline int64_t modbusRegisterFormatToSint64(const uint16_t *buffer)
{
    return static_cast<int64_t>(modbusRegisterFormatToUint64(buffer));
}
inline bitfield64_t modbusRegisterFormatToBitfield64(const uint16_t *buffer)
{
    return static_cast<bitfield64_t>(modbusRegisterFormatToUint64(buffer));
}
inline acc64_t modbusRegisterFormatToAcc64(const uint16_t *buffer)
{
    return static_cast<acc64_t>(modbusRegisterFormatToUint64(buffer));
}

inline float modbusRegisterFormatToFloat(const uint16_t *buffer)
{
    const uint32_t combined = modbusRegisterFormatToUint32(buffer);
    return *reinterpret_cast<const float *>(&combined);
}

inline double modbusRegisterFormatToDouble(const uint16_t *buffer)
{
    const uint64_t combined = modbusRegisterFormatToUint64(buffer);
    return *reinterpret_cast<const double *>(&combined);
}

inline const std::string modbusRegisterFormatToString(const uint16_t *buffer, const uint16_t bufferSize)
{
    char charBuffer[bufferSize * 2];
    for (size_t i = 0; i < bufferSize; i++)
    {
        charBuffer[i * 2] = (buffer[i] >> 8) & 0x00FF;
        charBuffer[i * 2 + 1] = buffer[i] & 0x00FF;
    }
    charBuffer[bufferSize * 2 - 1] = '\0';

    return std::string{charBuffer};
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
struct SunspecModelDef;

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

    /**
     * @brief Retrieves the model definition for a given model ID.
     * This function looks up the model definition based on the provided model ID.
     * @param [in] id The ID of the model to look up.
     * @return A pointer to the SunspecModelDef if found, or nullptr if not supported.
     */
    const SunspecModelDef *getModelDefinition(uint16_t id);
}; // namespace Sunspec