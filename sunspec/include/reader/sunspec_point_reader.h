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

class SunspecGroupReader;

/**
 * @brief Represents a single data point in a Sunspec model.
 *
 * This class holds the actual value of a point, its definition from the model, and
 * its address within the Sunspec register map.
 */
class SunspecPointReader
{
    using string = std::string;
    union SunspecValue;

public:
    /**
     * @brief Sets the scale factor for the point.
     * @param [in] sf The scale factor value.
     */
    void setSf(int16_t sf)
    {
        sf_ = sf;
    }

    /**
     * @brief Returns the scale factor of the point.
     * @return The scale factor.
     */
    int16_t sf() const
    {
        return sf_;
    }
    // TODO (Matthew) Change the doc comments
    /**
     * @brief Returns the value of the point as an unsigned 16-bit integer, if applicable.
     * @return The 16-bit unsigned value.
     */
    const int16_t valueInt16() const
    {
        return value_.s16;
    }

    /**
     * @brief Returns the value of the point as an unsigned 16-bit integer, if applicable.
     * @return The 16-bit unsigned value.
     */
    const int32_t valueInt32() const
    {
        return value_.s32;
    }

    /**
     * @brief Returns the value of the point as an unsigned 16-bit integer, if applicable.
     * @return The 16-bit unsigned value.
     */
    const int64_t valueInt64() const
    {
        return value_.s64;
    }

    /**
     * @brief Returns the value of the point as an unsigned 16-bit integer, if applicable.
     * @return The 16-bit unsigned value.
     */
    const uint16_t valueUint16() const
    {
        return value_.u16;
    }

    /**
     * @brief Returns the value of the point as an unsigned 16-bit integer, if applicable.
     * @return The 16-bit unsigned value.
     */
    const uint32_t valueUint32() const
    {
        return value_.u32;
    }

    /**
     * @brief Returns the value of the point as an unsigned 16-bit integer, if applicable.
     * @return The 16-bit unsigned value.
     */
    const uint64_t valueUint64() const
    {
        return value_.u64;
    }
    /**
     * @brief Returns the value of the point as an unsigned 16-bit integer, if applicable.
     * @return The 16-bit unsigned value.
     */
    const float valueFloat32() const
    {
        return value_.f32;
    }

    /**
     * @brief Returns the value of the point as an unsigned 16-bit integer, if applicable.
     * @return The 16-bit unsigned value.
     */
    const double valueFloat64() const
    {
        return value_.f64;
    }

    /**
     * @brief Returns the value of the point as an unsigned 16-bit integer, if applicable.
     * @return The 16-bit unsigned value.
     */
    const string &valueString() const
    {
        return value_.str;
    }

    /**
     * @brief Returns the value of the point as a signed 16-bit integer, if applicable.
     * @return The 16-bit signed value.
     */
    const uint16_t valueSf() const
    {
        return value_.s16;
    }

    /**
     * @brief Return the value in a string format based on the point type.
     * @return The point as a string.
     */
     string getValueAsString(bool includeSf = true) const;
    /**
     * @brief Returns the size of the point's data in 16-bit words.
     * @return The size of the point.
     */
    uint16_t size() const
    {
        return def_.size();
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
     * @brief Reads the point's value from the underlying device.
     * @return A const reference to the SunspecValue union containing the read value.
     */
    const SunspecPointReader::SunspecValue &readFromDevice();

    /**
     * @brief Sets the point's value from a raw buffer of 16-bit words.
     * @param [in] buf A pointer to the buffer containing the raw data.
     */
    void setValueFromBuffer(uint16_t *buf);

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
    SunspecPointReader(const SunspecPointDef &_def, uint16_t _addr, SunspecGroupReader &_groupPoint);

    /**
     * @brief Copy constructor.
     */
    SunspecPointReader(const SunspecPointReader &_point);

    /**
     * @brief Move constructor.
     */
    SunspecPointReader(SunspecPointReader &&_point) noexcept;

    /**
     * @brief Destructor.
     */
    ~SunspecPointReader();

private:
    /**
     * @brief A union to hold the different possible data types of a Sunspec point.
     *
     * The union allows the class to store any of the defined SunspecPointDataType types
     * in the same memory space.
     */
    union SunspecValue
    {
        int16_t s16;
        uint16_t u16;
        int32_t s32;
        uint32_t u32;
        int64_t s64;
        uint64_t u64;
        float f32;
        double f64;
        std::string str;
        SunspecValue() : u64(0) {}
        ~SunspecValue() {}
    } value_;

    const SunspecPointDef &def_;

    SunspecGroupReader &groupPoint_;
    int16_t sf_{0};
    uint16_t addr_;
    SunspecPointReader &operator=(const SunspecPointReader &_point) = delete;
    SunspecPointReader &operator=(SunspecPointReader &&_point) = delete;
};