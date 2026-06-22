

#pragma once /**< Ensure the header is included only once */

#include <string> /**< For std::string type */

#include "sunspec.h"                            /**< SunSpec type definitions */
#include "sunspec_model_definition_generated.h" /**< FlatBuffer generated model definitions */

class SunspecGroupReader; /**< Forward declaration for group reader */

/**
 * @brief Reads and interprets a single SunSpec point from a Modbus buffer.
 */
class SunspecPointReader
{
    using string = std::string;
    union SunspecValue; /**< Forward declaration for value union (if used) */

public:
    /**
     * @brief Constructs a SunSpecPointReader for a given point definition and buffer.
     * @param def Point definition
     * @param modbusBuffer Pointer to Modbus buffer
     * @param groupPoint Reference to parent group reader
     */
    SunspecPointReader(const SunspecPointDef &def, const uint16_t *modbusBuffer, SunspecGroupReader &groupPoint);

    /**
     * @brief Copy constructor
     */
    SunspecPointReader(const SunspecPointReader &_point) = default;

    /**
     * @brief Move constructor
     */
    SunspecPointReader(SunspecPointReader &&_point) noexcept = default;

    /**
     * @brief Destructor
     */
    ~SunspecPointReader() = default;

    /**
     * @brief Returns the point definition
     * @return Reference to SunspecPointDef
     */
    const SunspecPointDef &def() const
    {
        return def_;
    }

    /**
     * @brief Returns the size of the point (number of registers)
     * @return Size in registers
     */
    uint16_t size() const
    {
        return def_.size();
    }

    /**
     * @brief Returns the value as int16_t
     * @return int16_t value
     */
    int16_t valueAsInt16() const
    {
        return modbusRegisterFormatToSint16(modbusBuffer_);
    }

    /**
     * @brief Returns the value as int32_t
     * @return int32_t value
     */
    int32_t valueAsInt32() const
    {
        return modbusRegisterFormatToSint32(modbusBuffer_);
    }

    /**
     * @brief Returns the value as int64_t
     * @return int64_t value
     */
    int64_t valueAsInt64() const
    {
        return modbusRegisterFormatToSint64(modbusBuffer_);
    }

    /**
     * @brief Returns the value as raw16_t
     * @return raw16_t value
     */
    raw16_t valueAsRaw16() const
    {
        return modbusRegisterFormatToRaw16(modbusBuffer_);
    }

    /**
     * @brief Returns the value as uint16_t
     * @return uint16_t value
     */
    uint16_t valueAsUint16() const
    {
        return modbusRegisterFormatToUint16(modbusBuffer_);
    }

    /**
     * @brief Returns the value as uint32_t
     * @return uint32_t value
     */
    uint32_t valueAsUint32() const
    {
        return modbusRegisterFormatToUint32(modbusBuffer_);
    }

    /**
     * @brief Returns the value as uint64_t
     * @return uint64_t value
     */
    uint64_t valueAsUint64() const
    {
        return modbusRegisterFormatToUint64(modbusBuffer_);
    }

    /**
     * @brief Returns the value as acc16_t
     * @return acc16_t value
     */
    acc16_t valueAsAcc16() const
    {
        return modbusRegisterFormatToAcc16(modbusBuffer_);
    }

    /**
     * @brief Returns the value as acc32_t
     * @return acc32_t value
     */
    acc32_t valueAsAcc32() const
    {
        return modbusRegisterFormatToAcc32(modbusBuffer_);
    }

    /**
     * @brief Returns the value as acc64_t
     * @return acc64_t value
     */
    acc64_t valueAsAcc64() const
    {
        return modbusRegisterFormatToAcc64(modbusBuffer_);
    }

    /**
     * @brief Returns the value as bitfield16_t
     * @return bitfield16_t value
     */
    bitfield16_t valueAsBitfield16() const
    {
        return modbusRegisterFormatToBitfield16(modbusBuffer_);
    }

    /**
     * @brief Returns the value as bitfield32_t
     * @return bitfield32_t value
     */
    bitfield32_t valueAsBitfield32() const
    {
        return modbusRegisterFormatToBitfield32(modbusBuffer_);
    }

    /**
     * @brief Returns the value as bitfield64_t
     * @return bitfield64_t value
     */
    bitfield64_t valueAsBitfield64() const
    {
        return modbusRegisterFormatToBitfield64(modbusBuffer_);
    }

    /**
     * @brief Returns the value as enum16_t
     * @return enum16_t value
     */
    enum16_t valueAsEnum16() const
    {
        return modbusRegisterFormatToEnum16(modbusBuffer_);
    }

    /**
     * @brief Returns the value as enum32_t
     * @return enum32_t value
     */
    enum32_t valueAsEnum32() const
    {
        return modbusRegisterFormatToEnum32(modbusBuffer_);
    }

    /**
     * @brief Returns the value as float
     * @return float value
     */
    float valueAsFloat32() const
    {
        return modbusRegisterFormatToFloat(modbusBuffer_);
    }

    /**
     * @brief Returns the value as double
     * @return double value
     */
    double valueAsFloat64() const
    {
        return modbusRegisterFormatToDouble(modbusBuffer_);
    }

    /**
     * @brief Returns the value as string
     * @return string value
     */
    string valueAsString() const
    {
        return modbusRegisterFormatToString(modbusBuffer_, def_.size());
    }

    /**
     * @brief Returns the value as sunsSf_t
     * @return sunsSf_t value
     */
    sunsSf_t valueAsSunsSf() const
    {
        return modbusRegisterFormatToSunsSf(modbusBuffer_);
    }

    /**
     * @brief Returns the value as pad16_t
     * @return pad16_t value
     */
    pad16_t valueAsPad16() const
    {
        return modbusRegisterFormatToPad16(modbusBuffer_);
    }

    // TODO Implement the rest of the data type
    // ipAddr_t valueAsIpAddr()const{
    // }

    /**
     * @brief Returns the value as a string (custom getter)
     * @return string value
     */
    string getValueAsString() const;

    // /**
    //  * @brief Converts point data to JSON format
    //  * @param includeSf Include scale factors
    //  * @param includeUnits Include units
    //  * @return JSON string
    //  */
    // string toJson(bool includeSf = false, bool includeUnits = false) const;

private:
    const SunspecPointDef &def_;     /**< Reference to point definition */
    SunspecGroupReader &groupPoint_; /**< Reference to parent group reader */
    const uint16_t *modbusBuffer_;   /**< Pointer to Modbus buffer */

    SunspecPointReader &operator=(const SunspecPointReader &_point) = delete; /**< Copy assignment deleted */
    SunspecPointReader &operator=(SunspecPointReader &&_point) = delete;      /**< Move assignment deleted */
};