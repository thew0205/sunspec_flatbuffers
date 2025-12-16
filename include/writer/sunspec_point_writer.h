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

#include "sunspec_adapter.h"

#include "sunspec_adapter.h"

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
    SunspecPointWriter(const SunspecPointDefWrapper &def, SunspecGroupWriter &groupPoint);

    /**
     * @brief Class constructor.
     * @param [in] _def The definition of the point.
     * @param [in] _groupPoint A reference to the parent SunspecGroupPoint.
     * @param [in] valueFunction The SunspecPointFunction to be used for this point.
     */
    SunspecPointWriter(const SunspecPointDefWrapper &def, SunspecGroupWriter &groupPoint, SunspecPointFunction valueFunction);

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
     * @return A const reference to the SunspecPointDefWrapper object.
     */
    const SunspecPointDefWrapper &def() const
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
        return pointFunction_.sint16.function == nullptr ? def_.data_as_Sint16_t() : pointFunction_.sint16.call();
    }

    /**
     * @brief Gets the value of the point as a uint16_t.
     * @return The uint16 value of the point.
     */
    uint16_t getValueAsUint16() const
    {
        return pointFunction_.uint16.function == nullptr ? def_.data_as_Uint16_t() : pointFunction_.uint16.call();
    }

    /**
     * @brief Gets the value of the point as a pad16_t.
     * @return The pad16 value of the point.
     */
    pad16_t getValueAsPad16() const
    {
        return pointFunction_.pad16.function == nullptr ? def_.data_as_Pad16_t() : pointFunction_.pad16.call();
    }

    /**
     * @brief Gets the value of the point as a sunsSf_t.
     * @return The sunsSf value of the point.
     */
    sunsSf_t getValueAsSunsSf() const
    {
        return pointFunction_.sunsSf.function == nullptr ? def_.data_as_SunsSf_t() : pointFunction_.sunsSf.call();
    }
    acc16_t getValueAsAcc16() const
    {
        return pointFunction_.acc16.function == nullptr ? def_.data_as_Acc16_t() : pointFunction_.acc16.call();
    }

    /**
     * @brief Gets the value of the point as a bitfield16_t.
     * @return The bitfield16 value of the point.
     */
    bitfield16_t getValueAsBit16() const
    {
        return pointFunction_.bit16.function == nullptr ? def_.data_as_Bit16_t() : pointFunction_.bit16.call();
    }

    /**
     * @brief Gets the value of the point as an enum16_t.
     * @return The enum16 value of the point.
     */
    enum16_t getValueAsEnum16() const
    {
        return pointFunction_.enum16.function == nullptr ? def_.data_as_Enum16_t() : pointFunction_.enum16.call();
    }

    /**
     * @brief Gets the value of the point as a raw16_t.
     * @return The raw16 value of the point.
     */
    raw16_t getValueAsRaw16() const
    {
        return pointFunction_.raw16.function == nullptr ? def_.data_as_Raw16_t() : pointFunction_.raw16.call();
    }

    /**
     * @brief Gets the value of the point as an int32_t.
     * @return The int32 value of the point.
     */
    int32_t getValueAsSint32() const
    {
        return pointFunction_.sint32.function == nullptr ? def_.data_as_Sint16_t() : pointFunction_.sint32.call();
    }

    /**
     * @brief Gets the value of the point as a uint32_t.
     * @return The uint32 value of the point.
     */
    uint32_t getValueAsUint32() const
    {
        return pointFunction_.uint32.function == nullptr ? def_.data_as_Uint32_t() : pointFunction_.uint32.call();
    }

    /**
     * @brief Gets the value of the point as an acc32_t.
     * @return The acc32 value of the point.
     */
    acc32_t getValueAsAcc32() const
    {
        return pointFunction_.acc32.function == nullptr ? def_.data_as_Acc32_t() : pointFunction_.acc32.call();
    }

    /**
     * @brief Gets the value of the point as a bit32_t.
     * @return The bit32 value of the point.
     */
    bitfield32_t getValueAsBit32() const
    {
        return pointFunction_.bit32.function == nullptr ? def_.data_as_Bit32_t() : pointFunction_.bit32.call();
    }

    /**
     * @brief Gets the value of the point as an enum32_t.
     * @return The enum32 value of the point.
     */
    enum32_t getValueAsEnum32() const
    {
        return pointFunction_.enum32.function == nullptr ? def_.data_as_Enum32_t() : pointFunction_.enum32.call();
    }

    /**
     * @brief Gets the value of the point as an ipAddr_t.
     * @return The ipAddr value of the point.
     */
    ipAddr_t getValueAsIpAddr() const
    {
        return pointFunction_.ipAddr.function == nullptr ? def_.data_as_IpAddr_t() : pointFunction_.ipAddr.call();
    }

    /**
     * @brief Gets the value of the point as float.
     * @return The float value of the point.
     */
    float getValueAsFloat32() const
    {
        return pointFunction_.float32.function == nullptr ? def_.data_as_Float32() : pointFunction_.float32.call();
    }

    /**
     * @brief Gets the value of the point as double.
     * @return The double value of the point.
     */
    double getValueAsFloat64() const
    {
        return pointFunction_.float64.function == nullptr ? def_.data_as_Float64() : pointFunction_.float64.call();
    }

    /**
     * @brief Gets the value of the point as an int64_t.
     * @return The int64 value of the point.
     */
    int64_t getValueAsSint64() const
    {
        return pointFunction_.sint64.function == nullptr ? def_.data_as_Sint64_t() : pointFunction_.sint64.call();
    }

    /**
     * @brief Gets the value of the point as a uint64_t.
     * @return The uint64 value of the point.
     */
    uint64_t getValueAsUint64() const
    {
        return pointFunction_.uint64.function == nullptr ? def_.data_as_Uint64_t() : pointFunction_.uint64.call();
    }

    /**
     * @brief Gets the value of the point as an acc64_t.
     * @return The acc64 value of the point.
     */
    acc64_t getValueAsAcc64() const
    {
        return pointFunction_.acc64.function == nullptr ? def_.data_as_Acc64_t() : pointFunction_.acc64.call();
    }

    /**
     * @brief Gets the value of the point as a bit64_t.
     * @return The bit64 value of the point.
     */
    bitfield64_t getValueAsBit64() const
    {
        return pointFunction_.bit64.function == nullptr ? def_.data_as_Bit64_t() : pointFunction_.bit64.call();
    }

    /**
     * @brief Gets the value of the point as a string.
     * @return The string value of the point.
     */
    string getValueAsString() const
    {
        string tempString = pointFunction_.str.function == nullptr ? def_.data_as_String() : pointFunction_.str.call();
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
    SunspecGroupWriter &group_;         /**< A reference to the parent group point of this point. */
    uint16_t *modbusBuffer_;            /**< A pointer to the inplace modbus buffer where the point's data is to be stored. */
    const SunspecPointDefWrapper def_; /**< The sunspec point definition of this point. */

    // Disable assignment operators
    SunspecPointWriter &operator=(const SunspecPointWriter &_point) = delete;
    SunspecPointWriter &operator=(SunspecPointWriter &&_point) = delete;
};