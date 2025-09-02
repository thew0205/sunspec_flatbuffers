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
    // uint16_t relativeAddress() const
    // {
    //     return relativeAddress_;
    // }
    void setPointFunction(const SunspecPointFunction &pointFunction)
    {
        pointFunction_ = pointFunction;
    }

    void setModbusBuffer(uint16_t *modbusBuffer)
    {
        modbusBuffer_ = modbusBuffer;
    }
    int16_t getValueAsSint16() const
    {
        return pointFunction_.sint16.function == nullptr ? FlatbufferKSint16toSint16_t(def_.data_as_kSint16()) : pointFunction_.sint16.call();
    }

    uint16_t getValueAsUint16() const
    {
        return pointFunction_.uint16.function == nullptr ? FlatbufferKUint16toUint16_t(def_.data_as_kUint16()) : pointFunction_.uint16.call();
    }

    pad16_t getValueAsPad16() const
    {
        return pointFunction_.pad16.function == nullptr ? FlatbufferKPad16toPad16_t(def_.data_as_kPad16()) : pointFunction_.pad16.call();
    }
    sunsSf_t getValueAsSunsSf() const
    {
        return pointFunction_.sunsSf.function == nullptr ? FlatbufferKSunsSftoSunsSf_t(def_.data_as_kSunsSf()) : pointFunction_.sunsSf.call();
    }
    acc16_t getValueAsAcc16() const
    {
        return pointFunction_.acc16.function == nullptr ? FlatbufferKAcc16toAcc16_t(def_.data_as_kAcc16()) : pointFunction_.acc16.call();
    }
    bitfield16_t getValueAsBit16() const
    {
        return pointFunction_.bit16.function == nullptr ? FlatbufferKBit16toBit16_t(def_.data_as_kBitfield16()) : pointFunction_.bit16.call();
    }
    enum16_t getValueAsEnum16() const
    {
        return pointFunction_.enum16.function == nullptr ? FlatbufferKEnum16toEnum16_t(def_.data_as_kEnum16()) : pointFunction_.enum16.call();
    }
    raw16_t getValueAsRaw16() const
    {
        return pointFunction_.raw16.function == nullptr ? FlatbufferKRaw16toRaw16_t(def_.data_as_kRaw16()) : pointFunction_.raw16.call();
    }
    int32_t getValueAsSint32() const
    {
        return pointFunction_.sint32.function == nullptr ? FlatbufferKSint32toSint32_t(def_.data_as_kSint32()) : pointFunction_.sint32.call();
    }
    uint32_t getValueAsUint32() const
    {
        return pointFunction_.uint32.function == nullptr ? FlatbufferKUint32toUint32_t(def_.data_as_kUint32()) : pointFunction_.uint32.call();
    }
    acc32_t getValueAsAcc32() const
    {
        return pointFunction_.acc32.function == nullptr ? FlatbufferKAcc32toAcc32_t(def_.data_as_KAcc32()) : pointFunction_.acc32.call();
    }
    bit32_t getValueAsBit32() const
    {
        return pointFunction_.bit32.function == nullptr ? FlatbufferKBit32toBit32_t(def_.data_as_kBitfield32()) : pointFunction_.bit32.call();
    }
    enum32_t getValueAsEnum32() const
    {
        return pointFunction_.enum32.function == nullptr ? FlatbufferKEnum32toEnum32_t(def_.data_as_kEnum32()) : pointFunction_.enum32.call();
    }
    ipAddr_t getValueAsIpAddr() const
    {
        return pointFunction_.ipAddr.function == nullptr ? FlatbufferKIpAddrtoIpAddr_t(def_.data_as_kIpAddr()) : pointFunction_.ipAddr.call();
    }
    float getValueAsFloat32() const
    {
        return pointFunction_.float32.function == nullptr ? FlatbufferKFloat32toFloat(def_.data_as_kFloat32()) : pointFunction_.float32.call();
    }
    double getValueAsFloat64() const
    {
        return pointFunction_.float64.function == nullptr ? FlatbufferKFloat64toDouble(def_.data_as_kFloat64()) : pointFunction_.float64.call();
    }
    int64_t getValueAsSint64() const
    {
        return pointFunction_.sint64.function == nullptr ? FlatbufferKSint64toSint64_t(def_.data_as_kSint64()) : pointFunction_.sint64.call();
    }
    uint64_t getValueAsUint64() const
    {
        return pointFunction_.uint64.function == nullptr ? FlatbufferKUint64toUint64_t(def_.data_as_kUint64()) : pointFunction_.uint64.call();
    }

    acc64_t getValueAsAcc64() const
    {
        return pointFunction_.acc64.function == nullptr ? FlatbufferKAcc64toAcc64_t(def_.data_as_kAcc64()) : pointFunction_.acc64.call();
    }
    bit64_t getValueAsBit64() const
    {
        return pointFunction_.bit64.function == nullptr ? FlatbufferKBit64toBit64_t(def_.data_as_kBitfield64()) : pointFunction_.bit64.call();
    }

    string getValueAsString() const
    {
        string tempString = pointFunction_.str.function == nullptr ? FlatbufferKStringxToString(def_.data_as_kStringx()) : pointFunction_.str.call();
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
    void setValueToBuffer();

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
    SunspecPointWriter(const SunspecPointDef &def, SunspecGroupWriter &groupPoint, SunspecPointFunction valueFunction);
    SunspecPointWriter(const SunspecPointDef &def, SunspecGroupWriter &groupPoint);
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
    SunspecPointFunction pointFunction_;
    // uint16_t relativeAddress_;
    uint16_t *modbusBuffer_;
    SunspecGroupWriter &groupPoint_;
    SunspecPointWriter &operator=(const SunspecPointWriter &_point) = delete;
    SunspecPointWriter &operator=(SunspecPointWriter &&_point) = delete;
};