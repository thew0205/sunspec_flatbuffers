#include "reader/sunspec_model_reader.h"

#include "sunspec_utils.h"
#include "reader/sunspec_device_reader.h"

using std::to_string;

SunspecModelReader::SunspecModelReader(const SunspecModelDef &def, uint16_t address, SunspecDeviceReader &device) : def_{def}, addr_{address}, device_{device}, topLevelGroupPoint_{*def.group(), address, this, nullptr}
{
}

SunspecPointReader *SunspecModelReader::getPoint(const string_view countName, bool findRecursively)
{

    return topLevelGroupPoint_.getPoint(countName, findRecursively);
}

const SunspecPointReader *SunspecModelReader::getPoint(const string_view pointName, bool findRecursively) const
{

    return topLevelGroupPoint_.getPoint(pointName, findRecursively);
}

SunspecGroupReader *SunspecModelReader::getGroupPoint(const string_view &groupPointName, bool findRecursively)
{
    return topLevelGroupPoint_.getGroupPoint(groupPointName, findRecursively);
}
const SunspecGroupReader *SunspecModelReader::getGroupPoint(const string_view &groupPointName, bool findRecursively) const
{
    return topLevelGroupPoint_.getGroupPoint(groupPointName, findRecursively);
}
void SunspecModelReader::readAndSetFromDevice()
{

    topLevelGroupPoint_.readAndSetFromDevice();
}
std::string SunspecModelReader::toJson(bool includeSf, bool includeUnits) const
{
    std::string ret;
    ret += "{\"id\"";
    ret += " : \" " + to_string(def_.id()) + "\"" + "," + " \"topLevelGroupPoint\"" + " : ";
    ret += topLevelGroupPoint_.toJson(includeSf, includeUnits);
    ret += " }";
    return ret;
}
