/**
 * @file sunspec_model.h
 * @brief This file defines the SunspecModel class, which is a represent a Sunspec Model.
 *
 * @author Tolulope Matthew Busoye PowerLabs
 */

#pragma once

#include <string>
#include <stdint.h>

#include "sunspec_adapter.h"
#include "reader/sunspec_group_reader.h"

class SunspecDeviceReader;

/**
 * @brief Represents a Sunspec model as defined by a specific model definition.
 *
 * This class encapsulates a complete Sunspec model, including its top-level group of points,
 * and provides methods for interacting with the model's data on a physical device.
 */

/**
 * @brief Represents a Sunspec model as defined by a specific model definition.
 *
 * This class encapsulates a complete Sunspec model, including its top-level group of points,
 * and provides methods for interacting with the model's data on a physical device.
 */
class SunspecModelReader
{
    using string_view = std::string_view; /**< Alias for string_view type */

public:
    /**
     * @brief Constructs a SunspecModelReader for a given model definition and buffer.
     * @param def Model definition
     * @param modbusBuffer Pointer to Modbus buffer
     * @param address Modbus address of the model
     * @param device Reference to parent device reader
     */
    SunspecModelReader(const SunspecModelDef &def, uint16_t *modbusBuffer, const uint16_t address, SunspecDeviceReader &device);

    /**
     * @brief Copy constructor
     */
    SunspecModelReader(const SunspecModelReader &groupPoints) = default;

    /**
     * @brief Move constructor
     */
    SunspecModelReader(SunspecModelReader &&groupPoints) noexcept = default;

    /**
     * @brief Destructor
     */
    ~SunspecModelReader() = default;

    /**
     * @brief Returns the model definition
     * @return Reference to SunspecModelDef
     */
    const SunspecModelDef &def() const
    {
        return def_;
    }

    /**
     * @brief Returns the top-level group of points in the model
     * @return Reference to SunspecGroupReader
     */
    const SunspecGroupReader &topLevelGroupPoint() const
    {
        return topLevelGroupPoint_;
    }

    /**
     * @brief Returns the parent device reader
     * @return Reference to SunspecDeviceReader
     */
    SunspecDeviceReader &device()
    {
        return device_;
    }

    /**
     * @brief Returns the register length of the model
     * @return Register length
     */
    uint16_t registerLength() const
    {
        return topLevelGroupPoint_.registerLength();
    }

    /**
     * @brief Returns the Modbus address of the model
     * @return Address
     */
    uint16_t address() const
    {
        return address_;
    }

    /**
     * @brief Converts model data to JSON format
     * @param includeSf Include scale factors
     * @param includeUnits Include units
     * @return JSON string
     */
    std::string toJson(bool includeSf = false, bool includeUnits = false) const;

    /**
     * @brief Gets a pointer to a point by its ID
     * @param pointId Point identifier
     * @return Pointer to SunspecPointReader
     */
    SunspecPointReader *getPoint(const string_view pointId);

    /**
     * @brief Gets a const pointer to a point by its ID
     * @param pointId Point identifier
     * @return Const pointer to SunspecPointReader
     */
    const SunspecPointReader *getPoint(const string_view pointId) const;

    /**
     * @brief Gets a pointer to a group by its ID
     * @param groupId Group identifier
     * @return Pointer to SunspecGroupReader
     */
    SunspecGroupReader *getGroup(const string_view &groupId);

    /**
     * @brief Gets a const pointer to a group by its ID
     * @param groupId Group identifier
     * @return Const pointer to SunspecGroupReader
     */
    const SunspecGroupReader *getGroup(const string_view &groupId) const;

    /**
     * @brief Initializes all points in the model
     */
    void initPoints();

    /**
     * @brief Initializes all groups in the model
     * @param maxRegisterLength Maximum register length allowed
     * @return Total register length used by groups
     */
    uint16_t initGroups(uint16_t maxRegisterLength);

    void read();

private:
    SunspecDeviceReader &device_;           /**< Reference to parent device reader */
    SunspecGroupReader topLevelGroupPoint_; /**< Top-level group of points */
    const SunspecModelDef &def_;            /**< Reference to model definition */
    uint16_t *modbusBuffer_;                /**< Pointer to Modbus buffer */
    uint16_t address_;                      /**< Modbus address of the model */

    SunspecModelReader &operator=(const SunspecModelReader &groupPoints) = delete; /**< Copy assignment deleted */
    SunspecModelReader &operator=(SunspecModelReader &&groupPoints) = delete;      /**< Move assignment deleted */
};