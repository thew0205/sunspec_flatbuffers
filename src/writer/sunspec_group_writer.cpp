#include "writer/sunspec_group_writer.h"

#include "sunspec.h"
#include "writer/sunspec_device_writer.h"

using std::to_string;

SunspecDeviceWriter *SunspecGroupWriter::getDevice() const
{
    return model() == nullptr ? nullptr : &(model()->device());
}

uint16_t SunspecGroupWriter::setAllToBuffer()
{

    uint16_t currOffset = 0;
    for (auto &point : points_)
    {
        point.setValueToBuffer();
        currOffset += point.size();
    }
    for (auto &group : groupPoints_)
    {
        group.setAllToBuffer();
        currOffset += group.registerLength_;
    }
    return registerLength_;
}

std::string SunspecGroupWriter::toJson(bool includeSf, bool includeUnits) const
{
    std::string ret;
    ret += "{\"id\":\"" + string_view(def_.label()->c_str()) + "\",";
    ret += "\"name\":\"" + string_view(def_.id()->c_str()) + "\",";
    if (!points_.empty())
    {

        ret += "\"points\":{";
        for (auto &point : points_)
        {

            ret += point.toJson(includeSf, includeUnits) + ",";
        }
        if (!ret.empty() && ret.back() == ',')
        {
            ret.pop_back(); // Remove the last comma
        }
        ret += "}";
    }

    if (!groupPoints_.empty())
    {
        ret += ",\"groups\":[";
        for (auto &group : groupPoints_)
        {
            ret += group.toJson(includeSf, includeUnits) + ",";
        }
        if (!ret.empty() && ret.back() == ',')
        {
            ret.pop_back(); // Remove the last comma
        }
        ret += "]";
    }

    ret += " }";
    return ret;
}

SunspecGroupWriter::SunspecGroupWriter(const SunspecGroupDef &def, SunspecModelWriter *model, SunspecGroupWriter *group) : def_{def}, model_{model}, group_{group}, registerLength_{0}, points_{}, groupPoints_{}, modbusBuffer_{nullptr}
{
    // Either model or group must be non-null, but not both.
    assert((model != nullptr) ^ (group != nullptr));
}

void SunspecGroupWriter::initPoint()
{
    registerLength_ = 0;
    points_.clear();
    groupPoints_.clear();
    for (const auto &pointDef : *def_.points())
    {
        uint16_t count = pointDef->count();
        if (0 == count)
        {
            // NOTE Count is always in the top levelgroup
            // NOTE All toplevel points have fixed count
            SunspecPointWriter *countPoint = model_->getTopLevelPoint(pointDef->count_point_id()->c_str());

            count = countPoint == nullptr ? 0 : countPoint->getValueAsUint16();
        }
        for (size_t i = 0; i < count; i++)
        {
            points_.emplace_back(*pointDef, *this);
            registerLength_ += pointDef->size();
        }
    }
}
uint16_t SunspecGroupWriter::initGroups()
{

    for (const auto &groupDef : *def_.groups())
    {
        uint16_t count = groupDef->count();
        if (0 == count)
        {
            SunspecPointWriter *countPoint = model_->getTopLevelPoint(groupDef->count_point_id()->c_str());

            count = (countPoint == nullptr) ? 0 : countPoint->getValueAsUint16();
            count = (count == kUint16UnimplementedValue) ? 0 : count;
        }
        for (size_t i = 0; i < count; i++)
        {
            groupPoints_.emplace_back(*groupDef, nullptr, this).initPoint();
            registerLength_ += groupPoints_.back().initGroups();
        }
    }

    return registerLength_;
}
void SunspecGroupWriter::setAllModbusBuffer(uint16_t *modbusBuffer)
{
    setModbusBuffer(modbusBuffer);

    uint16_t offset = 0;
    for (auto &point : points_)
    {
        point.setModbusBuffer(&modbusBuffer[offset]);
        offset += point.size();
    }
    for (auto &group : groupPoints_)
    {
        group.setAllModbusBuffer(&modbusBuffer[offset]);
        offset += group.registerLength_;
    }
}

// void SunspecGroupWriter::setRelativeAddress(uint16_t relativeAddress)
// {
//     relativeAddress_ = relativeAddress;

//     uint16_t offset = 0;
//     for (auto &point : points_)
//     {
//         point.setRelativeAddress(relativeAddress_ + offset);
//         offset += point.size();
//     }
//     for (auto &group : groupPoints_)
//     {
//         group.setRelativeAddress(relativeAddress_ + offset);
//         offset += group.registerLength_;
//     }
// }
bool SunspecGroupWriter::isTopLevelGroupPoint() const
{
    assert(group_ == nullptr ^ model_ == nullptr);

    // If it belongs to a group then it is not a toplevel group
    return (group_ == nullptr) && (model_ != nullptr);
}
// It get the model by recursively going through the model group till it is a toplevel group
SunspecModelWriter *SunspecGroupWriter::model() const
{
    if (isTopLevelGroupPoint())
    {
        return model_;
    }
    else
    {
        return group_->model();
    }
}

SunspecPointWriter *SunspecGroupWriter::getPoint(const string_view pointName, bool findRecursively)
{
    for (auto &point : points_)
    {
        if (pointName == point.def().id()->c_str())
        {
            return &point;
        }
    }

    return (isTopLevelGroupPoint() || !findRecursively) ? nullptr : group_->getPoint(pointName);
}

SunspecGroupWriter *SunspecGroupWriter::getGroupPoint(const string_view &groupPointName, bool findRecursively)
{
    for (auto &groupPoint : groupPoints_)
    {
        if (groupPointName == groupPoint.def().id()->c_str())
        {
            return &groupPoint;
        }
    }

    return (isTopLevelGroupPoint() || !findRecursively) ? nullptr : group_->getGroupPoint(groupPointName);
}

const SunspecGroupWriter *SunspecGroupWriter::getGroupPoint(const string_view &groupPointName, bool findRecursively) const
{
    for (auto &groupPoint : groupPoints_)
    {
        if (groupPointName == groupPoint.def().id()->c_str())
        {
            return &groupPoint;
        }
    }

    return (isTopLevelGroupPoint() || !findRecursively) ? nullptr : group_->getGroupPoint(groupPointName);
}

const SunspecPointWriter *SunspecGroupWriter::getPoint(const string_view pointName, bool findRecursively) const
{
    for (auto &point : points_)
    {
        if (pointName == point.def().id()->c_str())
        {
            return &point;
        }
    }

    return (isTopLevelGroupPoint() || !findRecursively) ? nullptr : group_->getPoint(pointName);
}