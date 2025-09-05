/**
 * @file sunspec_point_writer.h
 * @brief This file defines the SunspecPointWriter class, which represents a single data point within a Sunspec model.
 *
 * The SunspecPoint class encapsulates the SunspecPointFuction that returns the SunspecPoint value, a pointer to the inplace modbus buffer, its definition, and its relationship to a parent group.
 *
 * @author Tolulope Matthew Busoye PowerLabs
 */

#pragma once

#include <string>

#include "sunspec_model_definition_generated.h"
#include "sunspec.h"
class SunspecGroupWriter;
class SunspecDeviceWriter;

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
     * @brief Class constructor.
     * @param [in] _def The definition of the point.
     * @param [in] _groupPoint A reference to the parent SunspecGroupPoint.
     *
     * The pointFunction will be set to nullptr, and the default value from the definition will be used.
     */
    SunspecPointWriter(const SunspecPointDef &def, SunspecGroupWriter &groupPoint);

    /**
     * @brief Class constructor.
     * @param [in] _def The definition of the point.
     * @param [in] _groupPoint A reference to the parent SunspecGroupPoint.
     * @param [in] valueFunction The SunspecPointFunction to be used for this point.
     */
    SunspecPointWriter(const SunspecPointDef &def, SunspecGroupWriter &groupPoint, SunspecPointFunction valueFunction);

    /**
     * @brief Copy constructor.
     */
    SunspecPointWriter(const SunspecPointWriter &_point) noexcept = default;

    /**
     * @brief Move constructor.
     */
    SunspecPointWriter(SunspecPointWriter &&_point) noexcept = default;

    /**
     * @brief Class destructor.
     */
    ~SunspecPointWriter();

    /**
     * @brief Returns the definition of the point.
     * @return A const reference to the SunspecPointDef object.
     */
    const SunspecPointDef &def() const
    {
        return def_;
    }

    /**
     * @brief Return the SunspecGroupWriter of this point.
     * @return A const reference to the SunspecGroupWriter of this object.
     */
    const SunspecGroupWriter &group() const
    {
        return group_;
    }

    /**
     * @brief Returns the size of the point's data in 16-bit words.
     * @return The size of the point.
     */
    uint16_t size() const
    {
        return def_.size();
    }

    /**
     * @brief Sets the SunspecPointFunction for this point.
     *
     * Ensure the correct member of the union is set based on the point's data type.
     * @param [in] pointFunction The SunspecPointFunction to set.
     */
    void setPointFunction(const SunspecPointFunction &pointFunction)
    {
        pointFunction_ = pointFunction;
    }

    /**
     * @brief Sets the pointer to the inplace modbus buffer where the point's data is  to be stored.
     * @param [in] modbusBuffer A pointer to the modbus buffer.
     */
    void setModbusBuffer(uint16_t *modbusBuffer)
    {
        modbusBuffer_ = modbusBuffer;
    }

    /**
     * @brief Gets the value of the point as an int16_t.
     * @return The int16 value of the point.
     */
    int16_t getValueAsSint16() const
    {
        return pointFunction_.sint16.function == nullptr ? FlatbufferKSint16toSint16_t(def_.data_as_kSint16()) : pointFunction_.sint16.call();
    }

    /**
     * @brief Gets the value of the point as a uint16_t.
     * @return The uint16 value of the point.
     */
    uint16_t getValueAsUint16() const
    {
        return pointFunction_.uint16.function == nullptr ? FlatbufferKUint16toUint16_t(def_.data_as_kUint16()) : pointFunction_.uint16.call();
    }

    /**
     * @brief Gets the value of the point as a pad16_t.
     * @return The pad16 value of the point.
     */
    pad16_t getValueAsPad16() const
    {
        return pointFunction_.pad16.function == nullptr ? FlatbufferKPad16toPad16_t(def_.data_as_kPad16()) : pointFunction_.pad16.call();
    }

    /**
     * @brief Gets the value of the point as a sunsSf_t.
     * @return The sunsSf value of the point.
     */
    sunsSf_t getValueAsSunsSf() const
    {
        return pointFunction_.sunsSf.function == nullptr ? FlatbufferKSunsSftoSunsSf_t(def_.data_as_kSunsSf()) : pointFunction_.sunsSf.call();
    }
    acc16_t getValueAsAcc16() const
    {
        return pointFunction_.acc16.function == nullptr ? FlatbufferKAcc16toAcc16_t(def_.data_as_kAcc16()) : pointFunction_.acc16.call();
    }

    /**
     * @brief Gets the value of the point as a bitfield16_t.
     * @return The bitfield16 value of the point.
     */
    bitfield16_t getValueAsBit16() const
    {
        return pointFunction_.bit16.function == nullptr ? FlatbufferKBit16toBit16_t(def_.data_as_kBitfield16()) : pointFunction_.bit16.call();
    }

    /**
     * @brief Gets the value of the point as an enum16_t.
     * @return The enum16 value of the point.
     */
    enum16_t getValueAsEnum16() const
    {
        return pointFunction_.enum16.function == nullptr ? FlatbufferKEnum16toEnum16_t(def_.data_as_kEnum16()) : pointFunction_.enum16.call();
    }

    /**
     * @brief Gets the value of the point as a raw16_t.
     * @return The raw16 value of the point.
     */
    raw16_t getValueAsRaw16() const
    {
        return pointFunction_.raw16.function == nullptr ? FlatbufferKRaw16toRaw16_t(def_.data_as_kRaw16()) : pointFunction_.raw16.call();
    }

    /**
     * @brief Gets the value of the point as an int32_t.
     * @return The int32 value of the point.
     */
    int32_t getValueAsSint32() const
    {
        return pointFunction_.sint32.function == nullptr ? FlatbufferKSint32toSint32_t(def_.data_as_kSint32()) : pointFunction_.sint32.call();
    }

    /**
     * @brief Gets the value of the point as a uint32_t.
     * @return The uint32 value of the point.
     */
    uint32_t getValueAsUint32() const
    {
        return pointFunction_.uint32.function == nullptr ? FlatbufferKUint32toUint32_t(def_.data_as_kUint32()) : pointFunction_.uint32.call();
    }

    /**
     * @brief Gets the value of the point as an acc32_t.
     * @return The acc32 value of the point.
     */
    acc32_t getValueAsAcc32() const
    {
        return pointFunction_.acc32.function == nullptr ? FlatbufferKAcc32toAcc32_t(def_.data_as_KAcc32()) : pointFunction_.acc32.call();
    }

    /**
     * @brief Gets the value of the point as a bit32_t.
     * @return The bit32 value of the point.
     */
    bitfield32_t getValueAsBit32() const
    {
        return pointFunction_.bit32.function == nullptr ? FlatbufferKBit32toBit32_t(def_.data_as_kBitfield32()) : pointFunction_.bit32.call();
    }

    /**
     * @brief Gets the value of the point as an enum32_t.
     * @return The enum32 value of the point.
     */
    enum32_t getValueAsEnum32() const
    {
        return pointFunction_.enum32.function == nullptr ? FlatbufferKEnum32toEnum32_t(def_.data_as_kEnum32()) : pointFunction_.enum32.call();
    }

    /**
     * @brief Gets the value of the point as an ipAddr_t.
     * @return The ipAddr value of the point.
     */
    ipAddr_t getValueAsIpAddr() const
    {
        return pointFunction_.ipAddr.function == nullptr ? FlatbufferKIpAddrtoIpAddr_t(def_.data_as_kIpAddr()) : pointFunction_.ipAddr.call();
    }

    /**
     * @brief Gets the value of the point as float.
     * @return The float value of the point.
     */
    float getValueAsFloat32() const
    {
        return pointFunction_.float32.function == nullptr ? FlatbufferKFloat32toFloat(def_.data_as_kFloat32()) : pointFunction_.float32.call();
    }

    /**
     * @brief Gets the value of the point as double.
     * @return The double value of the point.
     */
    double getValueAsFloat64() const
    {
        return pointFunction_.float64.function == nullptr ? FlatbufferKFloat64toDouble(def_.data_as_kFloat64()) : pointFunction_.float64.call();
    }

    /**
     * @brief Gets the value of the point as an int64_t.
     * @return The int64 value of the point.
     */
    int64_t getValueAsSint64() const
    {
        return pointFunction_.sint64.function == nullptr ? FlatbufferKSint64toSint64_t(def_.data_as_kSint64()) : pointFunction_.sint64.call();
    }

    /**
     * @brief Gets the value of the point as a uint64_t.
     * @return The uint64 value of the point.
     */
    uint64_t getValueAsUint64() const
    {
        return pointFunction_.uint64.function == nullptr ? FlatbufferKUint64toUint64_t(def_.data_as_kUint64()) : pointFunction_.uint64.call();
    }

    /**
     * @brief Gets the value of the point as an acc64_t.
     * @return The acc64 value of the point.
     */
    acc64_t getValueAsAcc64() const
    {
        return pointFunction_.acc64.function == nullptr ? FlatbufferKAcc64toAcc64_t(def_.data_as_kAcc64()) : pointFunction_.acc64.call();
    }

    /**
     * @brief Gets the value of the point as a bit64_t.
     * @return The bit64 value of the point.
     */
    bitfield64_t getValueAsBit64() const
    {
        return pointFunction_.bit64.function == nullptr ? FlatbufferKBit64toBit64_t(def_.data_as_kBitfield64()) : pointFunction_.bit64.call();
    }

    /**
     * @brief Gets the value of the point as a string.
     * @return The string value of the point.
     */
    string getValueAsString() const
    {
        string tempString = pointFunction_.str.function == nullptr ? FlatbufferKStringxToString(def_.data_as_kStringx()) : pointFunction_.str.call();
        std::size_t newLength = std::min(static_cast<size_t>((def_.size() * sizeof(uint16_t)) - 1), tempString.size());

        tempString.resize(newLength);
        return tempString;
    }

    /**
     * @brief Returns a pointer to the SunspecDeviceWriter associated with this point.
     * @return A pointer to the SunspecDeviceWriter object.
     */
    const SunspecDeviceWriter *getDevice() const;

    /**
     * @brief Sets the value of the point in the modbus buffer using the point's SunspecPointFunction.
     *
     * If no function is set, it uses the default value from the definition.
     * This function writes the value into the modbusBuffer_ at the appropriate offset.
     */
    void setValueToModbusBuffer();

    /**
     * @brief Generates a JSON representation of the point's data.
     * @param [in] includeSf Whether to include the scale factor in the JSON output.
     * @param [in] includeUnits Whether to include the units in the JSON output.
     * @return A string containing the JSON representation.
     */
    string toJson(bool includeSf = false, bool includeUnits = false) const;

private:
    SunspecPointFunction pointFunction_; /**< The function of the point ensures the union member is initialised based on the type in the point definition. */
    // uint16_t relativeAddress_;
    SunspecGroupWriter &group_;  /**< A reference to the parent group point of this point. */
    uint16_t *modbusBuffer_;     /**< A pointer to the inplace modbus buffer where the point's data is to be stored. */
    const SunspecPointDef &def_; /**< The sunspec point definition of this point. */

    // Disable assignment operators
    SunspecPointWriter &operator=(const SunspecPointWriter &_point) = delete;
    SunspecPointWriter &operator=(SunspecPointWriter &&_point) = delete;
};