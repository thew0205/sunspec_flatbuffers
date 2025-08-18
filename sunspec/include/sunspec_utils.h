/**
 * @file sunspec_utils.h
 * @brief This file hold utility codes for Sunspec Library.
 * 
 * @author Tolulope Matthew Busoye PowerLabs
 */

#pragma once

#include <stdint.h>

#include <string>
#include <string_view>

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