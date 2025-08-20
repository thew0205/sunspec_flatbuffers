#include "writer/sunspec_model_writer.h"

#include "sunspec_utils.h"
#include "writer/sunspec_device_writer.h"

using std::to_string;

SunspecModelWriter::SunspecModelWriter(const SunspecModelDef &def, uint16_t address, SunspecDeviceWriter &device) : def_{def}, relativeAddress_{address}, device_{device}, topLevelGroupPoint_{*def.group(), address, this, nullptr}, registerLength_{0}
{
}

uint16_t SunspecModelWriter::init(uint16_t address)
{
    registerLength_ = topLevelGroupPoint_.init(relativeAddress_);
    return registerLength_;
}
void SunspecModelWriter::setConstantIdentifiersInBuffer(uint16_t *buffer)
{
    const uint16_t modelConstantIdentifierBuffer[2] = {def_.id(), registerLength_ - 2};

    memcpy(buffer, modelConstantIdentifierBuffer, sizeof(uint16_t) * 2);
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
void SunspecModelWriter::setToDeviceBuffer(uint16_t *buffer)
{

    topLevelGroupPoint_.setAllToBuffer(buffer);
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
