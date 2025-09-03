/**
 * @file sunspec_model_writer.h
 * @brief This file defines the SunspecModelWriter class, which is a represent a Sunspec Model
 * It can set modbus register map for reading by other sunspec compliant devices. It is basically a container for the top-level SunspecGroupWriter of the model, with the setting of the constant identifier (model ID and length) in the modbus buffer.
 *
 * @author Tolulope Matthew Busoye PowerLabs
 */

#pragma once

#include <string>
#include <stdint.h>

#include "sunspec_model_definition_generated.h"
#include "writer/sunspec_group_writer.h"

class SunspecDeviceWriter;

/**
 * @brief Represents a Sunspec model as defined by a specific model definition.
 *
 * This class encapsulates a complete Sunspec model, including its top-level group of points,
 * and provides methods for interacting with the model's data on a physical device.
 */
class SunspecModelWriter
{
    using string_view = std::string_view;

public:
    /**
     * @brief Class constructor.
     * @param [in] _def The definition of the model.
     * @param [in] relativeAddress The starting address of the model in the register map.
     * @param [in] _device A reference to the parent SunspecDevice.
     */
    SunspecModelWriter(const SunspecModelDef &_def, SunspecDeviceWriter &_device);

    /**
     * @brief Copy constructor.
     */
    SunspecModelWriter(const SunspecModelWriter &groupPoints) = default;

    /**
     * @brief Move constructor.
     */
    SunspecModelWriter(SunspecModelWriter &&groupPoints) noexcept = default;

    /**
     * @brief Destructor.
     */
    ~SunspecModelWriter() = default;

    /**
     * @brief Returns the model's definition.
     * @return A const reference to the SunspecModelDef object.
     */
    const SunspecModelDef &def() const
    {
        return def_;
    }

    /**
     * @brief Returns the toplevel  groupPoint of this model.
     * @return A const reference to the SunspecGroupPoint object.
     */
    const SunspecGroupWriter &topLevelGroup() const
    {
        return topLevelGroup_;
    }

    /**
     * @brief Returns the length of the model in number of modbus registers.
     * @return The length in number of modbus registers.
     */
    uint16_t registerLength() const
    {
        return registerLength_;
    }
    /**
     * @brief Returns a reference to the parent Sunspec device.
     * @return A reference to the SunspecDevice object.
     */
    SunspecDeviceWriter &device()
    {
        return device_;
    }

    /**
     * @brief Retrieves a point from the model by its id.
     * @param [in] pointId The id of the point to retrieve.
     * @return A pointer to the SunspecPoint, or nullptr if not found.
     */
    SunspecPointWriter *getPoint(const string_view pointId);

    /**
     * @brief Retrieves a point from the model by its id.
     * @param [in] pointId The id of the point to retrieve.
     * @return A pointer to the SunspecPoint, or nullptr if not found.
     */
    const SunspecPointWriter *getPoint(const string_view pointId) const;

    /**
     * @brief Retrieves a groupPoint from the model by its id.
     * @param [in] groupId The id of the point to find.
     * @return A pointer to the SunspecPoint, or nullptr if not found.
     */
    SunspecGroupWriter *getGroup(const string_view &groupId);

    /**
     * @brief Retrieves a groupPoint from the model by its name.
     * @param [in] groupId The name of the point to find.
     * @return A pointer to the SunspecPoint, or nullptr if not found.
     */
    const SunspecGroupWriter *getGroup(const string_view &groupId) const;

    /**
     * @brief Initializes only the top-level group of SunspecPointWriter in the model.
     * This method sets up the toplevel points according to the model definition. This must be called before initSubLevels.
     * @return The total register length of the model after initialization.
     */
    uint16_t initTopLevel();
    /**
     * @brief Initializes all sub-level groups of SunspecPointWriter in the model.
     * This method recursively sets up all nested groups and their points according to the model definition. This must be called after initTopLevel.
     * @return The total register length of the model after initialization.
     */
    uint16_t initSubLevels();

    /**
     * @brief Sets the modbus buffer for the model and all its points.
     * This method assigns the provided modbusBuffer to the model and propagates it to all contained points and groups.
     * It must be called after initSubLevels to ensure all points are initialized, as it relies on the registerLength_ for all containing sunspec elements being set.
     * @param [in] modbusBuffer A pointer to the modbus buffer where the model's data is to be stored.
     */
    void setAllModbusBuffer(uint16_t *modbusBuffer);

    /**
     * @brief Sets the values of modbus buffer by calling all the setValueToModbusBuffer function for toplevel SunspecGroupWriter for the model.
     */
    uint16_t setAllValueToModbusBuffer();

    /**
     * @brief Generates a JSON representation of the entire model.
     * @param [in] includeSf Whether to include scale factors in the JSON output.
     * @param [in] includeUnits Whether to include units in the JSON output.
     * @return A string containing the JSON representation.
     */
    std::string toJson(bool includeSf = false, bool includeUnits = false) const;

private:
    /**
     * @brief Sets the constant identifiers (model ID and length) in the modbus buffer.
     */
    void setConstantIdentifiersInBuffer();

    /**
     * @brief Sets the pointer to the inplace modbus buffer where the model's data is to be stored.
     * Called by setAllModbusBuffer to set the modbus buffer for this model.
     * @param [in] modbusBuffer A pointer to the inplace modbus buffer where the model's data is to be stored.
     */
    void setModbusBuffer(uint16_t *modbusBuffer)
    {
        modbusBuffer_ = modbusBuffer;
    }

    SunspecDeviceWriter &device_; /**< A reference to the parent device of this model. */

    SunspecGroupWriter topLevelGroup_; /**< The top-level group of the model that contains all the point and subgroup of the model. */
    const SunspecModelDef &def_;       /**< The sunspec model definition of this model. */
    uint16_t *modbusBuffer_;           /**< A pointer to the inplace modbus buffer where the model's data is to be stored. */
    uint16_t registerLength_;          /**< The length of the model in number of modbus registers, including the 2 registers for the model ID and length. */

    SunspecModelWriter &operator=(const SunspecModelWriter &groupPoints) = delete;
    SunspecModelWriter &operator=(SunspecModelWriter &&groupPoints) = delete;
};