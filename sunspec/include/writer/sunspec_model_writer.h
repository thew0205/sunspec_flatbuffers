/**
 * @file sunspec_model.h
 * @brief This file defines the SunspecModel class, which is a represent a Sunspec Model.
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
     * @brief Returns the model's definition.
     * @return A const reference to the SunspecModelDef object.
     */
    const SunspecModelDef &def() const
    {
        return def_;
    }
    uint16_t init(uint16_t address);

    /**
     * @brief Returns the toplevel  groupPoint of this model.
     * @return A const reference to the SunspecGroupPoint object.
     */
    const SunspecGroupWriter &topLevelGroupPoint() const
    {
        return topLevelGroupPoint_;
    }

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
     * @brief Reads all points in the model from the device and sets their values.
     */
    void setToDeviceBuffer(uint16_t *buffer);
    void setConstantIdentifiersInBuffer(uint16_t *buffer);

    /**
     * @brief Generates a JSON representation of the entire model.
     * @param [in] includeSf Whether to include scale factors in the JSON output.
     * @param [in] includeUnits Whether to include units in the JSON output.
     * @return A string containing the JSON representation.
     */
    std::string toJson(bool includeSf = false, bool includeUnits = false) const;

    /**
     * @brief Retrieves a point from the model by its name.
     * @param [in] pointName The name of the point to find.
     * @param [in] findRecursively Whether to search in nested groups as well.
     * @return A pointer to the SunspecPoint, or nullptr if not found.
     */
    SunspecPointWriter *getPoint(const string_view pointName, bool findRecursively = true);

    /**
     * @brief Retrieves a point from the model by its name.
     * @param [in] pointName The name of the point to find.
     * @param [in] findRecursively Whether to search in nested groups as well.
     * @return A pointer to the SunspecPoint, or nullptr if not found.
     */
    const SunspecPointWriter *getPoint(const string_view pointName, bool findRecursively = true) const;

    /**
     * @brief Retrieves a groupPoint from the model by its name, it cam return the top level group point.
     * @param [in] groupPointName The name of the point to find.
     * @param [in] findRecursively Whether to search in nested groups as well.
     * @return A pointer to the SunspecPoint, or nullptr if not found.
     */
    SunspecGroupWriter *getGroupPoint(const string_view &groupPointName, bool findRecursively = true);

    /**
     * @brief Retrieves a groupPoint from the model by its name, it cam return the top level group point.
     * @param [in] groupPointName The name of the point to find.
     * @param [in] findRecursively Whether to search in nested groups as well.
     * @return A pointer to the SunspecPoint, or nullptr if not found.
     */
    const SunspecGroupWriter *getGroupPoint(const string_view &groupPointName, bool findRecursively = true) const;
    /**
     * @brief Class constructor.
     * @param [in] _def The definition of the model.
     * @param [in] _addr The starting address of the model in the register map.
     * @param [in] _device A reference to the parent SunspecDevice.
     */
    SunspecModelWriter(const SunspecModelDef &_def, uint16_t _addr, SunspecDeviceWriter &_device);

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

private:
    SunspecModelWriter &operator=(const SunspecModelWriter &groupPoints) = delete;
    SunspecModelWriter &operator=(SunspecModelWriter &&groupPoints) = delete;

    SunspecDeviceWriter &device_;

    SunspecGroupWriter topLevelGroupPoint_;
    const SunspecModelDef &def_;
    uint16_t address_;
    uint16_t registerLength_;
};