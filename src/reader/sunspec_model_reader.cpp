#include "reader/sunspec_model_reader.h"

#include "sunspec.h"
#include "reader/sunspec_device_reader.h"

using std::to_string;

SunspecModelReader::SunspecModelReader(const SunspecModelDefWrapper &def, uint16_t *modbusBuffer, const uint16_t address, SunspecDeviceReader &device) : def_{def}, modbusBuffer_{modbusBuffer}, address_{address}, device_{device}, topLevelGroupPoint_{def.group(), modbusBuffer, this}
{
}

SunspecPointReader *SunspecModelReader::getPoint(const string_view pointId)
{
    return topLevelGroupPoint_.getPoint(pointId);
}

const SunspecPointReader *SunspecModelReader::getPoint(const string_view pointId) const
{

    return topLevelGroupPoint_.getPoint(pointId);
}

SunspecGroupReader *SunspecModelReader::getGroup(const string_view &groupId)
{
    return topLevelGroupPoint_.getGroup(groupId);
}
const SunspecGroupReader *SunspecModelReader::getGroup(const string_view &groupId) const
{
    return topLevelGroupPoint_.getGroup(groupId);
}

void SunspecModelReader::initPoints()
{
    return topLevelGroupPoint_.initPoints();
}
uint16_t SunspecModelReader::initGroups(uint16_t maxRegisterLength)
{
    return topLevelGroupPoint_.initGroups(maxRegisterLength);
}

void SunspecModelReader::read()
{
    device().read(address_, modbusBuffer_, topLevelGroupPoint_.registerLength());
}
// std::string SunspecModelReader::toJson(bool includeSf, bool includeUnits) const
// {
//     std::string ret;
//     ret += "{\"id\"";
//     ret += " : \" " + to_string(def_.id()) + "\"" + "," + " \"topLevelGroupPoint\"" + " : ";
//     ret += topLevelGroupPoint_.toJson(includeSf, includeUnits);
//     ret += " }";
//     return ret;
// }
