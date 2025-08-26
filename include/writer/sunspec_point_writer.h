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
    uint16_t relativeAddress() const
    {
        return relativeAddress_;
    }
    void setValueFunction(SunspecValueFunction valueFunction)
    {
        valueFunction_ = valueFunction;
    }

    void setRelativeAddress(uint16_t relativeAddress)
    {
        relativeAddress_ = relativeAddress;
    }
    int16_t getValueAsSint16() const
    {
        return valueFunction_.sint16 == nullptr ? FlatbufferKSint16toSint16_t(def_.data_as_kSint16()) : valueFunction_.sint16();
    }

    uint16_t getValueAsUint16() const
    {
        return valueFunction_.uint16 == nullptr ? FlatbufferKUint16toUint16_t(def_.data_as_kUint16()) : valueFunction_.uint16();
    }

    pad16_t getValueAsPad16() const
    {
        return valueFunction_.pad16 == nullptr ? FlatbufferKPad16toPad16_t(def_.data_as_kPad16()) : valueFunction_.pad16();
    }
    sunsSf_t getValueAsSunsSf() const
    {
        return valueFunction_.sunsSf == nullptr ? FlatbufferKSunsSftoSunsSf_t(def_.data_as_kSunsSf()) : valueFunction_.sunsSf();
    }
    acc16_t getValueAsAcc16() const
    {
        return valueFunction_.acc16 == nullptr ? FlatbufferKAcc16toAcc16_t(def_.data_as_kAcc16()) : valueFunction_.acc16();
    }
    bitfield16_t getValueAsBit16() const
    {
        return valueFunction_.bit16 == nullptr ? FlatbufferKBit16toBit16_t(def_.data_as_kBitfield16()) : valueFunction_.bit16();
    }
    enum16_t getValueAsEnum16() const
    {
        return valueFunction_.enum16 == nullptr ? FlatbufferKEnum16toEnum16_t(def_.data_as_kEnum16()) : valueFunction_.enum16();
    }
    raw16_t getValueAsRaw16() const
    {
        return valueFunction_.raw16 == nullptr ? FlatbufferKRaw16toRaw16_t(def_.data_as_kRaw16()) : valueFunction_.raw16();
    }
    int32_t getValueAsSint32() const
    {
        return valueFunction_.sint32 == nullptr ? FlatbufferKSint32toSint32_t(def_.data_as_kSint32()) : valueFunction_.sint32();
    }
    uint32_t getValueAsUint32() const
    {
        return valueFunction_.uint32 == nullptr ? FlatbufferKUint32toUint32_t(def_.data_as_kUint32()) : valueFunction_.uint32();
    }
    acc32_t getValueAsAcc32() const
    {
        return valueFunction_.acc32 == nullptr ? FlatbufferKAcc32toAcc32_t(def_.data_as_KAcc32()) : valueFunction_.acc32();
    }
    bit32_t getValueAsBit32() const
    {
        return valueFunction_.bit32 == nullptr ? FlatbufferKBit32toBit32_t(def_.data_as_kBitfield32()) : valueFunction_.bit32();
    }
    enum32_t getValueAsEnum32() const
    {
        return valueFunction_.enum32 == nullptr ? FlatbufferKEnum32toEnum32_t(def_.data_as_kEnum32()) : valueFunction_.enum32();
    }
    ipAddr_t getValueAsIpAddr() const
    {
        return valueFunction_.ipAddr == nullptr ? FlatbufferKIpAddrtoIpAddr_t(def_.data_as_kIpAddr()) : valueFunction_.ipAddr();
    }
    float getValueAsFloat32() const
    {
        return valueFunction_.float32 == nullptr ? FlatbufferKFloat32toFloat(def_.data_as_kFloat32()) : valueFunction_.float32();
    }
    double getValueAsFloat64() const
    {
        return valueFunction_.float64 == nullptr ? FlatbufferKFloat64toDouble(def_.data_as_kFloat64()) : valueFunction_.float64();
    }
    int64_t getValueAsSint64() const
    {
        return valueFunction_.sint64 == nullptr ? FlatbufferKSint64toSint64_t(def_.data_as_kSint64()) : valueFunction_.sint64();
    }
    uint64_t getValueAsUint64() const
    {
        return valueFunction_.uint64 == nullptr ? FlatbufferKUint64toUint64_t(def_.data_as_kUint64()) : valueFunction_.uint64();
    }

    acc64_t getValueAsAcc64() const
    {
        return valueFunction_.acc64 == nullptr ? FlatbufferKAcc64toAcc64_t(def_.data_as_kAcc64()) : valueFunction_.acc64();
    }
    bit64_t getValueAsBit64() const
    {
        return valueFunction_.bit64 == nullptr ? FlatbufferKBit64toBit64_t(def_.data_as_kBitfield64()) : valueFunction_.bit64();
    }

    string getValueAsString() const
    {
        string tempString = valueFunction_.str == nullptr ? FlatbufferKStringxToString(def_.data_as_kStringx()) : valueFunction_.str();
        std::size_t newLength = std::min(static_cast<size_t>((def_.size() * sizeof(uint16_t)) - 1), tempString.size());

        tempString.resize(newLength);
        return tempString;
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
    SunspecPointWriter(const SunspecPointDef &def, SunspecGroupWriter &groupPoint, SunspecValueFunction valueFunction);
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