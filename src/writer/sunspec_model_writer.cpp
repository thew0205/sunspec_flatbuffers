#include "writer/sunspec_model_writer.h"

#include "sunspec.h"
#include "writer/sunspec_device_writer.h"

using std::to_string;

uint16_t SunspecModelWriter::initTopLevel()
{

    topLevelGroupPoint_.initPoint();

    return registerLength_;
}
uint16_t SunspecModelWriter::initSubLevels()
{
    registerLength_ = 0; // Start with 2 for the base address and model end marker.
    topLevelGroupPoint_.initGroups();
    registerLength_ += topLevelGroupPoint_.registerLength();
    return registerLength_;
}

void SunspecModelWriter::setAllModbusBuffer(uint16_t *modbusBuffer)
{
    setModbusBuffer(modbusBuffer);
    topLevelGroupPoint_.setAllModbusBuffer(modbusBuffer);
}

SunspecModelWriter::SunspecModelWriter(const SunspecModelDef &def, SunspecDeviceWriter &device) : def_{def}, /*relativeAddress_{address},*/ device_{device}, topLevelGroupPoint_{*def.group(), this, nullptr}, registerLength_{0}
{
}

void SunspecModelWriter::setConstantIdentifiersInBuffer()
{
    assert(registerLength_ >= 2);
    assert(modbusBuffer_ != nullptr);

    const uint16_t modelConstantIdentifierBuffer[2] = {uint16_tToModbusRegisterFormat(def_.id()), uint16_tToModbusRegisterFormat(static_cast<uint16_t>(registerLength_ - 2))};

    memcpy(modbusBuffer_, modelConstantIdentifierBuffer, sizeof(uint16_t) * 2);
}

SunspecPointWriter *SunspecModelWriter::getTopLevelPoint(const string_view countName)
{

    return topLevelGroupPoint_.getPoint(countName, false);
}

const SunspecPointWriter *SunspecModelWriter::getTopLevelPoint(const string_view pointName) const
{

    return topLevelGroupPoint_.getPoint(pointName, false);
}

SunspecPointWriter *SunspecModelWriter::getPoint(const string_view countName, bool findRecursively)
{

    return topLevelGroupPoint_.getPoint(countName, findRecursively);
}

const SunspecPointWriter *SunspecModelWriter::getPoint(const string_view pointName, bool findRecursively) const
{

    return topLevelGroupPoint_.getPoint(pointName, findRecursively);
}

SunspecGroupWriter *SunspecModelWriter::getGroupPoint(const string_view &groupPointName, bool findRecursively)
{
    return topLevelGroupPoint_.getGroupPoint(groupPointName, findRecursively);
}
const SunspecGroupWriter *SunspecModelWriter::getGroupPoint(const string_view &groupPointName, bool findRecursively) const
{
    return topLevelGroupPoint_.getGroupPoint(groupPointName, findRecursively);
}
uint16_t SunspecModelWriter::setAllToBuffer()
{

    topLevelGroupPoint_.setAllToBuffer();
    setConstantIdentifiersInBuffer();
    return topLevelGroupPoint_.registerLength();
}
std::string SunspecModelWriter::toJson(bool includeSf, bool includeUnits) const
{
    std::string ret;
    ret += "{\"id\"";
    ret += " : \" " + to_string(def_.id()) + "\"" + "," + " \"topLevelGroupPoint\"" + " : ";
    ret += topLevelGroupPoint_.toJson(includeSf, includeUnits);
    ret += " }";
    return ret;
}
