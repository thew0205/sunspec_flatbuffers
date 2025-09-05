

#pragma once

#include <string>

#include "sunspec.h"
#include "sunspec_model_definition_generated.h"

class SunspecGroupReader;

class SunspecPointReader
{
    using string = std::string;
    union SunspecValue;

public:
    SunspecPointReader(const SunspecPointDef &def, const uint16_t *modbusBuffer, SunspecGroupReader &groupPoint);

    SunspecPointReader(const SunspecPointReader &_point) = default;

    SunspecPointReader(SunspecPointReader &&_point) noexcept = default;

    ~SunspecPointReader() = default;

    const SunspecPointDef &def() const
    {
        return def_;
    }
    // void setSf(int16_t sf)
    // {
    //     sf_ = sf;
    // }

    // int16_t sf() const
    // {
    //     return sf_;
    // }

    uint16_t size() const
    {
        return def_.size();
    }

    int16_t valueAsInt16() const
    {
        return modbusRegisterFormatToSint16(modbusBuffer_);
    }

    int32_t valueAsInt32() const
    {
        return modbusRegisterFormatToSint32(modbusBuffer_);
    }

    int64_t valueAsInt64() const
    {
        return modbusRegisterFormatToSint64(modbusBuffer_);
    }

    raw16_t valueAsRaw16() const
    {
        return modbusRegisterFormatToRaw16(modbusBuffer_);
    }

    uint16_t valueAsUint16() const
    {
        return modbusRegisterFormatToUint16(modbusBuffer_);
    }

    uint32_t valueAsUint32() const
    {
        return modbusRegisterFormatToUint32(modbusBuffer_);
    }

    uint64_t valueAsUint64() const
    {
        return modbusRegisterFormatToUint64(modbusBuffer_);
    }

    acc16_t valueAsAcc16() const
    {
        return modbusRegisterFormatToAcc16(modbusBuffer_);
    }

    acc32_t valueAsAcc32() const
    {
        return modbusRegisterFormatToAcc32(modbusBuffer_);
    }

    acc64_t valueAsAcc64() const
    {
        return modbusRegisterFormatToAcc64(modbusBuffer_);
    }

    bitfield16_t valueAsBitfield16() const
    {
        return modbusRegisterFormatToBitfield16(modbusBuffer_);
    }

    bitfield32_t valueAsBitfield32() const
    {
        return modbusRegisterFormatToBitfield32(modbusBuffer_);
    }

    bitfield64_t valueAsBitfield64() const
    {
        return modbusRegisterFormatToBitfield64(modbusBuffer_);
    }

    enum16_t valueAsEnum16() const
    {
        return modbusRegisterFormatToEnum16(modbusBuffer_);
    }

    enum32_t valueAsEnum32() const
    {
        return modbusRegisterFormatToEnum32(modbusBuffer_);
    }
    float valueAsFloat32() const
    {
        return modbusRegisterFormatToFloat(modbusBuffer_);
    }

    double valueAsFloat64() const
    {
        return modbusRegisterFormatToDouble(modbusBuffer_);
    }

    string valueAsString() const
    {
        return modbusRegisterFormatToString(modbusBuffer_, def_.size());
    }

    sunsSf_t valueAsSunsSf() const
    {
        return modbusRegisterFormatToSunsSf(modbusBuffer_);
    }

    pad16_t valueAsPad16() const
    {
        return modbusRegisterFormatToPad16(modbusBuffer_);
    }

    // TODO Implement the rest of the data type
    // ipAddr_t valueAsIpAddr()const{

    // }

    string getValueAsString() const;

    // const SunspecPointReader::SunspecValue &readFromDevice();

    // string toJson(bool includeSf = false, bool includeUnits = false) const;

private:
    const SunspecPointDef &def_;
    SunspecGroupReader &groupPoint_;
    const uint16_t *modbusBuffer_;

    SunspecPointReader &operator=(const SunspecPointReader &_point) = delete;
    SunspecPointReader &operator=(SunspecPointReader &&_point) = delete;
};