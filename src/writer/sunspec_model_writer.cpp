#include "writer/sunspec_model_writer.h"

#include "sunspec.h"
#include "writer/sunspec_device_writer.h"

using std::to_string;

SunspecModelWriter::SunspecModelWriter(const SunspecModelDef &def, SunspecDeviceWriter &device) : def_{def}, device_{device}, topLevelGroup_{*def.group(), this, nullptr}
{
}

SunspecPointWriter *SunspecModelWriter::getPoint(const string_view countName)
{

    return topLevelGroup_.getPoint(countName);
}

const SunspecPointWriter *SunspecModelWriter::getPoint(const string_view pointName) const
{

    return topLevelGroup_.getPoint(pointName);
}

SunspecGroupWriter *SunspecModelWriter::getGroup(const string_view &groupId)
{
    return topLevelGroup_.getGroup(groupId);
}
const SunspecGroupWriter *SunspecModelWriter::getGroup(const string_view &groupId) const
{
    return topLevelGroup_.getGroup(groupId);
}

void SunspecModelWriter::initTopLevel()
{

    return topLevelGroup_.initPoints();

    ;
}

uint16_t SunspecModelWriter::initSubLevels()
{
    return topLevelGroup_.initGroups();
}

void SunspecModelWriter::setAllModbusBuffer(uint16_t *modbusBuffer)
{
    setModbusBuffer(modbusBuffer);
    topLevelGroup_.setAllModbusBuffer(modbusBuffer);
}

uint16_t SunspecModelWriter::setAllValueToModbusBuffer()
{

    topLevelGroup_.setAllValueToModbusBuffer();
    setConstantIdentifiersInBuffer();
    return topLevelGroup_.registerLength();
}

std::string SunspecModelWriter::toJson(bool includeSf, bool includeUnits) const
{
    std::string ret;
    ret += "{\"id\"";
    ret += " : \" " + to_string(def_.id()) + "\"" + "," + " \"topLevelGroupPoint\"" + " : ";
    ret += topLevelGroup_.toJson(includeSf, includeUnits);
    ret += " }";
    return ret;
}

void SunspecModelWriter::setConstantIdentifiersInBuffer()
{
    assert(registerLength() >= 2);
    assert(modbusBuffer_ != nullptr);

    const uint16_t modelConstantIdentifierBuffer[2] = {uint16_tToModbusRegisterFormat(def_.id()), uint16_tToModbusRegisterFormat(static_cast<uint16_t>(registerLength() - 2))};

    memcpy(modbusBuffer_, modelConstantIdentifierBuffer, sizeof(uint16_t) * 2);
}
