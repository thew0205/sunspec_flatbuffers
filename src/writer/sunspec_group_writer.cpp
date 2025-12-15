#include "writer/sunspec_group_writer.h"

#include "sunspec.h"
#include "writer/sunspec_device_writer.h"

using std::to_string;

SunspecGroupWriter::SunspecGroupWriter(const SunspecGroupDefWrapper &def, SunspecModelWriter *model, SunspecGroupWriter *group) : def_{def}, model_{model}, group_{group}, registerLength_{0}, points_{}, groups_{}, modbusBuffer_{nullptr}
{
    // Either model or group must be non-null, but not both.
    assert(group_ == nullptr ^ model_ == nullptr);
}

bool SunspecGroupWriter::isTopLevelGroupPoint() const
{
    assert(group_ == nullptr ^ model_ == nullptr);

    // If it belongs to a group then it is not a toplevel group
    return (group_ == nullptr) && (model_ != nullptr);
}

SunspecModelWriter *SunspecGroupWriter::getModel() const
{
    if (isTopLevelGroupPoint())
    {
        return model_;
    }
    else
    {
        return group_->getModel();
    }
}

SunspecPointWriter *SunspecGroupWriter::getPoint(const string_view pointId)
{
    for (auto &point : points_)
    {
        if (pointId == point.def().id())
        {
            return &point;
        }
    }
    return nullptr;
}

const SunspecPointWriter *SunspecGroupWriter::getPoint(const string_view pointId) const
{
    for (auto &point : points_)
    {
        if (pointId == point.def().id())
        {
            return &point;
        }
    }

    return nullptr;
}

SunspecGroupWriter *SunspecGroupWriter::getGroup(const string_view &groupId)
{
    for (auto &groupPoint : groups_)
    {
        if (groupId == groupPoint.def().id())
        {
            return &groupPoint;
        }
    }
    return nullptr;
}

const SunspecGroupWriter *SunspecGroupWriter::getGroup(const string_view &groupId) const
{
    for (auto &groupPoint : groups_)
    {
        if (groupId == groupPoint.def().id())
        {
            return &groupPoint;
        }
    }
    return nullptr;
}

SunspecDeviceWriter *SunspecGroupWriter::getDevice() const
{
    return getModel() == nullptr ? nullptr : &(getModel()->device());
}

void SunspecGroupWriter::initPoints()
{
    registerLength_ = 0;
    points_.clear();
    groups_.clear();

    vector<size_t> pointCounts;
    vector<const SunspecPointDefWrapper *> pointDefs;
    size_t totalPointCount = 0;
    for (const auto &pointDef : def_.points())
    {
        uint16_t count = pointDef.count();
        if (0 == count)
        {
            // NOTE Count is always in the top levelgroup
            // NOTE All toplevel points have fixed count
            assert(!isTopLevelGroupPoint());
            SunspecPointWriter *countPoint = getModel()->getPoint(pointDef.count_point_id());

            count = countPoint == nullptr ? 0 : countPoint->getValueAsUint16();
            count = (count == kUint16UnimplementedValue) ? 0 : count;
        }
        totalPointCount += count;
        pointCounts.push_back(count);
        pointDefs.push_back(&pointDef);
    }
    assert(pointCounts.size() == pointDefs.size() /*, "Internal error: pointCounts and pointDefs size mismatch"*/);
    points_.reserve(totalPointCount);
    for (size_t i = 0; i < pointCounts.size(); ++i)
    {
        const auto pointDef = pointDefs[i];
        const auto count = pointCounts[i];
        if (count == 0)
        {
            continue;
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
    vector<size_t> groupCounts;
    vector<const SunspecGroupDefWrapper *> groupDefs;
    size_t totalGroupCount = 0;

    for (const auto &groupDef : def_.groups())
    {
        uint16_t count = groupDef.count();
        if (0 == count)
        {
            SunspecPointWriter *countPoint = getModel()->getPoint(groupDef.count_point_id());

            count = (countPoint == nullptr) ? 0 : countPoint->getValueAsUint16();
            count = (count == kUint16UnimplementedValue) ? 0 : count;
        }

        totalGroupCount += count;
        groupCounts.push_back(count);
        groupDefs.push_back(&groupDef);
    }

    assert(groupCounts.size() == groupDefs.size() /*, "Internal error: groupCounts and groupDefs size mismatch"*/);
    groups_.reserve(totalGroupCount);
    for (size_t i = 0; i < groupCounts.size(); ++i)
    {

        const auto groupDef = groupDefs[i];
        const auto count = groupCounts[i];
        if (count == 0)
        {
            continue;
        }
        for (size_t i = 0; i < count; i++)
        {
            groups_.emplace_back(*groupDef, nullptr, this).initPoints();
            registerLength_ += groups_.back().initGroups();
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
    for (auto &group : groups_)
    {
        group.setAllModbusBuffer(&modbusBuffer[offset]);
        offset += group.registerLength_;
    }
}

uint16_t SunspecGroupWriter::setAllValueToModbusBuffer()
{

    uint16_t currOffset = 0;
    for (auto &point : points_)
    {
        point.setValueToModbusBuffer();
        currOffset += point.size();
    }
    for (auto &group : groups_)
    {
        group.setAllValueToModbusBuffer();
        currOffset += group.registerLength_;
    }
    return registerLength_;
}

std::string SunspecGroupWriter::toJson(bool includeSf, bool includeUnits) const
{
    std::string ret;
    ret += "{\"id\":\"" + string_view(def_.label()) + "\",";
    ret += "\"name\":\"" + string_view(def_.id()) + "\",";
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

    if (!groups_.empty())
    {
        ret += ",\"groups\":[";
        for (auto &group : groups_)
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