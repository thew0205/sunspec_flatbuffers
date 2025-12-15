#include "reader/sunspec_group_reader.h"

#include "sunspec_adapter.h"

#include "reader/sunspec_model_reader.h"
#include "reader/sunspec_device_reader.h"

using std::to_string;

SunspecGroupReader::SunspecGroupReader(const SunspecGroupDefWrapper &def, const uint16_t *modbusBuffer, SunspecModelReader *model) : def_{def}, modbusBuffer_{modbusBuffer}, model_{model}, group_{nullptr}, registerLength_{0}, points_{}, groups_{}
{
}

SunspecGroupReader::SunspecGroupReader(const SunspecGroupDefWrapper &def, const uint16_t *modbusBuffer, SunspecGroupReader *group) : def_{def}, modbusBuffer_{modbusBuffer}, model_{nullptr}, group_{group}, registerLength_{0}, points_{}, groups_{}
{
}

bool SunspecGroupReader::isTopLevelGroupPoint() const
{
    assert(group_ == nullptr ^ model_ == nullptr);

    // If it belongs to a group then it is not a toplevel group
    return (group_ == nullptr) && (model_ != nullptr);
}

// It get the model by recursively going through the model group till it is a toplevel group
SunspecModelReader *SunspecGroupReader::getModel() const
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

SunspecPointReader *SunspecGroupReader::getPoint(const string_view pointId)
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

const SunspecPointReader *SunspecGroupReader::getPoint(const string_view pointId) const
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

SunspecGroupReader *SunspecGroupReader::getGroup(const string_view &groupId)
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

const SunspecGroupReader *SunspecGroupReader::getGroup(const string_view &groupId) const
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

void SunspecGroupReader::initPoints()
{
    // NOTE The toplevel point always have fixed count
    registerLength_ = 0;
    points_.clear();
    groups_.clear();

    vector<size_t> pointCounts;
    vector< SunspecPointDefWrapper > pointDefs;
    size_t totalPointCount = 0;

    for (const auto pointDef : def_.points())
    {
        uint16_t count = pointDef.count();
        if (0 == count)
        {
            // NOTE Count is always in the top levelgroup
            // NOTE All toplevel points have fixed count
            assert(!isTopLevelGroupPoint());

            SunspecPointReader *countPoint = getModel()->getPoint(pointDef.count_point_id());

            count = countPoint == nullptr ? 0 : countPoint->valueAsUint16();
            count = (count == kUint16UnimplementedValue) ? 0 : count;
        }

        totalPointCount += count;
        pointCounts.push_back(count);
        pointDefs.push_back(pointDef);
    }
    assert(pointCounts.size() == pointDefs.size() /*, "Internal error: pointCounts and pointDefs size mismatch"*/);

    points_.reserve(totalPointCount);
    for (size_t i = 0; i < pointCounts.size(); i++)
    {

        const auto pointDef = pointDefs[i];
        const auto count = pointCounts[i];
        if (count == 0)
        {
            continue;
        }

        for (size_t i = 0; i < count; i++)
        {
            points_.emplace_back(pointDef, &modbusBuffer_[registerLength_], *this);
            registerLength_ += pointDef.size();
        }
    }
}

uint16_t SunspecGroupReader::initGroups(uint16_t maxRegisterLength)
{

    vector<size_t> groupCounts;
    vector< SunspecGroupDefWrapper > groupDefs;
    size_t totalGroupCount = 0;

    for (const auto groupDef : def_.groups())
    {
        std::string temp{groupDef.id()};
        uint16_t count = groupDef.count();
        if (0 == count)
        {
            std::string temp3{groupDef.count_point_id()};
            SunspecPointReader *countPoint = getModel()->getPoint(groupDef.count_point_id());

            count = (countPoint == nullptr) ? 0 : countPoint->valueAsUint16();
            count = (count == kUint16UnimplementedValue) ? 0 : count;
        }

        totalGroupCount += count;
        groupCounts.push_back(count);
        groupDefs.push_back(groupDef);
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
            groups_.emplace_back(groupDef, &modbusBuffer_[registerLength_], this).initPoints();
            registerLength_ += groups_.back().initGroups(0xFFFF);
        }
    }
    // Clamp to the actually length read from the device incase some pad points are omitted.
    // Could there be a case the max length be greater than teh registerlength calculated.
    if (maxRegisterLength < registerLength_)
    {
        registerLength_ = maxRegisterLength;
    }
    return registerLength_;
}

// std::string SunspecGroupReader::toJson(bool includeSf, bool includeUnits) const
// {
//     std::string ret;
//     ret += "{\"id\":\"" + string_view(def_.label()->c_str()) + "\",";
//     ret += "\"name\":\"" + string_view(def_.id()->c_str()) + "\",";
//     if (!points_.empty())
//     {

//         ret += "\"points\":{";
//         for (auto &point : points_)
//         {

//             ret += point.toJson(includeSf, includeUnits) + ",";
//         }
//         if (!ret.empty() && ret.back() == ',')
//         {
//             ret.pop_back(); // Remove the last comma
//         }
//         ret += "}";
//     }

//     if (!groupPoints_.empty())
//     {
//         ret += ",\"groups\":[";
//         for (auto &group : groupPoints_)
//         {
//             ret += group.toJson(includeSf, includeUnits) + ",";
//         }
//         if (!ret.empty() && ret.back() == ',')
//         {
//             ret.pop_back(); // Remove the last comma
//         }
//         ret += "]";
//     }

//     ret += " }";
//     return ret;
// }
