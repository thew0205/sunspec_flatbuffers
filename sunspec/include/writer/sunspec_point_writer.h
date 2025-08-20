/**
 * @file sunspec_point.h
 * @brief This file defines the SunspecPoint class, which represents a single data point within a Sunspec model.
 *
 * The SunspecPoint class encapsulates the data value, its definition, and its relationship to a parent group.
 *
 * @author Tolulope Matthew Busoye PowerLabs
 */

#pragma once

#include <string>

#include "sunspec_model_definition_generated.h"
#include "sunspec.h"
class SunspecGroupWriter;

/**
 * @brief Represents a single data point in a Sunspec model.
 *
 * This class holds the actual value of a point, its definition from the model, and
 * its address within the Sunspec register map.
 */
class SunspecPointWriter
{
    using string = std::string;
    union SunspecValue;

public:
    /**
     * @brief Returns the size of the point's data in 16-bit words.
     * @return The size of the point.
     */
    uint16_t size() const
    {
        return def_.size();
    }

void setValueFunction(SunspecValueFunction valueFunction){
    valueFunction_ = valueFunction;
}

    /**
     * @brief Returns the definition of the point.
     * @return A const reference to the SunspecPointDef object.
     */
    const SunspecPointDef &def() const
    {
        return def_;
    }

    /**
     * @brief Sets the point's value from a raw buffer of 16-bit words.
     * @param [in] buf A pointer to the buffer containing the raw data.
     */
    void setValueToBuffer(uint16_t *buf);

    /**
     * @brief Generates a JSON representation of the point's data.
     * @param [in] includeSf Whether to include the scale factor in the JSON output.
     * @param [in] includeUnits Whether to include the units in the JSON output.
     * @return A string containing the JSON representation.
     */
    string toJson(bool includeSf = false, bool includeUnits = false) const;

    /**
     * @brief Class constructor.
     * @param [in] _def The definition of the point.
     * @param [in] _addr The starting address of the point in the register map.
     * @param [in] _groupPoint A reference to the parent SunspecGroupPoint.
     */
    SunspecPointWriter(const SunspecPointDef &def, uint16_t address, SunspecGroupWriter &groupPoint, SunspecValueFunction valueFunction);
    SunspecPointWriter(const SunspecPointDef &def, uint16_t address, SunspecGroupWriter &groupPoint);
    /**
     * @brief Copy constructor.
     */
    SunspecPointWriter(const SunspecPointWriter &_point) noexcept = default;

    /**
     * @brief Move constructor.
     */
    SunspecPointWriter(SunspecPointWriter &&_point) noexcept = default;

    /**
     * @brief Destructor.
     */
    ~SunspecPointWriter();

private:
    const SunspecPointDef &def_;
    SunspecValueFunction valueFunction_;
    uint16_t relativeAddress_;
    SunspecGroupWriter &groupPoint_;
    SunspecPointWriter &operator=(const SunspecPointWriter &_point) = delete;
    SunspecPointWriter &operator=(SunspecPointWriter &&_point) = delete;
};