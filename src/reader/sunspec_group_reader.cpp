#include "reader/sunspec_group_reader.h"

#include "sunspec.h"
#include "reader/sunspec_device_reader.h"

using std::to_string;

void SunspecGroupReader::readAndSetFromDevice()
{

    uint16_t buf[len_];

    if (getDevice() != nullptr && getDevice()->read(address_, buf, len_))
    {
        uint16_t currOffset = 0;
        for (auto &point : points_)
        {
            point.setValueFromBuffer(buf + currOffset);
            currOffset += point.def().size();
        }
        for (auto &group : groupPoints_)
        {
            group.setAllFromBuffer(buf + currOffset);
            currOffset += group.len_;
        }
        setAllSf();
    }
}

void SunspecGroupReader::setAllSf()
{
    for (auto &point : points_)
    {
        if (!point.def().sf_id()->size())
        {

            SunspecPointReader *sfPoint = getPoint(point.def().sf_id()->c_str(), true);
            if (sfPoint != nullptr)
            {
                point.setSf(sfPoint->valueSf());
            }
        }
    }
    for (auto &group : groupPoints_)
    {
        group.setAllSf();
    }
}
SunspecDeviceReader *SunspecGroupReader::getDevice() const
{
    return model() == nullptr ? nullptr : &(model()->device());
}

void SunspecGroupReader::setAllFromBuffer(uint16_t *buf)
{

    uint16_t currOffset = 0;
    for (auto &point : points_)
    {
        point.setValueFromBuffer(buf + currOffset);
        currOffset += point.size();
    }
    for (auto &group : groupPoints_)
    {
        group.setAllFromBuffer(buf + currOffset);
        currOffset += group.len_;
    }
}

std::string SunspecGroupReader::toJson(bool includeSf, bool includeUnits) const
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

SunspecGroupReader::SunspecGroupReader(const SunspecGroupPointDef &def, uint16_t addr, SunspecModelReader *model, SunspecGroupReader *group) : def_{def}, address_{addr}, model_{model}, group_{group}, len_{0}, points_{}, groupPoints_{}
{

    for (const auto &pointDef : *def_.points())
    {
        uint16_t count = pointDef->count();
        if (0 == count)
        {
            // NOTE Count is always in the top levelgroup
            SunspecPointReader *countPoint = model_->getPoint(pointDef->count_point_id()->c_str(), false);

            count = countPoint == nullptr ? 0 : countPoint->readFromDevice().u16;
        }
        for (size_t i = 0; i < count; i++)
        {
            points_.emplace_back(*pointDef, addr + len_, *this);
            len_ += pointDef->size();
        }
    }
    for (const auto &groupDef : *def_.groups())
    {
        uint16_t count = groupDef->count();
        if (0 == count)
        {
            SunspecPointReader *countPoint = model_->getPoint(groupDef->count_point_id()->c_str(), false);

            count = countPoint == nullptr ? 0 : countPoint->readFromDevice().u16;
        }
        for (size_t i = 0; i < count; i++)
        {
            groupPoints_.emplace_back(*groupDef, addr + len_, nullptr, this);
            len_ += groupPoints_.back().len_;
        }
    }
}

bool SunspecGroupReader::isTopLevelGroupPoint() const
{
    // static_assert(group_  == nullptr && model_ == nullptr);

    // If it belongs to a group then it is not a toplevel group
    return (group_ == nullptr) && (model_ != nullptr);
}
// It get the model by recursively going through the model group till it is a toplevel group
SunspecModelReader *SunspecGroupReader::model() const
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

SunspecPointReader *SunspecGroupReader::getPoint(const string_view pointName, bool findRecursively)
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

SunspecGroupReader *SunspecGroupReader::getGroupPoint(const string_view &groupPointName, bool findRecursively)
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

const SunspecGroupReader *SunspecGroupReader::getGroupPoint(const string_view &groupPointName, bool findRecursively) const
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

const SunspecPointReader *SunspecGroupReader::getPoint(const string_view pointName, bool findRecursively) const
{
    // TODO To implement it to be recursive.
    for (auto &point : points_)
    {
        if (pointName == point.def().id()->c_str())
        {
            return &point;
        }
    }

    return (isTopLevelGroupPoint() || !findRecursively) ? nullptr : group_->getPoint(pointName);
}