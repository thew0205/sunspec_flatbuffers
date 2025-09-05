/**
 * @file sunspec_group_point.h
 * @brief This file defines the SunspecGroupPoint class, which is a sunspec block that can hold a list of SunspecPoint as well as nested SunspecGroupPoint within it.
 *
 * @author Tolulope Matthew Busoye PowerLabs
 */

#pragma once

#include <string>
#include <vector>

#include "reader/sunspec_point_reader.h"

class SunspecModelReader;

/**
 * @brief Represents a group of Sunspec points.
 *
 * This class encapsulates a collection of Sunspec points and potentially other nested groups,
 * following the structure of a Sunspec model definition. It provides methods for reading data
 * from a device, converting the data to JSON, and accessing individual points.
 */
class SunspecGroupReader
{
    using string_view = std::string_view;
    template <typename T>
    using vector = std::vector<T>;

public:
    SunspecGroupReader(const SunspecGroupDef &def, const uint16_t *modbusBuffer, SunspecModelReader *model);

    SunspecGroupReader(const SunspecGroupDef &def, const uint16_t *modbusBuffer, SunspecGroupReader *group);

    SunspecGroupReader(const SunspecGroupReader &groupPoints) = default;

    SunspecGroupReader(SunspecGroupReader &&group) noexcept = default;

    ~SunspecGroupReader() = default;

    const SunspecGroupDef &def() const
    {
        return def_;
    }

    size_t pointLength() const
    {
        return points_.size();
    }

    size_t groupLength() const
    {
        return groups_.size();
    }

    uint16_t registerLength() const
    {
        return registerLength_;
    }

    void initPoints();
    uint16_t initGroups(uint16_t maxRegisterLength);
    // void readAndSetFromDevice();

    // void setAllFromBuffer(uint16_t *buf);

    // void setAllSf();

    bool isTopLevelGroupPoint() const;

    SunspecModelReader *getModel() const;

    SunspecPointReader *getPoint(const string_view pointId);

    const SunspecPointReader *getPoint(const string_view pointId) const;

    SunspecGroupReader *getGroup(const string_view &groupId);

    const SunspecGroupReader *getGroup(const string_view &groupId) const;

    // std::string toJson(bool includeSf = false, bool includeUnits = false) const;
    // SunspecDeviceReader *getDevice() const;

private:
    const uint16_t *modbusBuffer_;
    uint16_t registerLength_;

    SunspecModelReader *const model_;
    SunspecGroupReader *const group_;
    const SunspecGroupDef &def_;
    vector<SunspecPointReader> points_;
    vector<SunspecGroupReader> groups_;

    SunspecGroupReader &operator=(const SunspecGroupReader &groupPoints) = delete;
    SunspecGroupReader &operator=(SunspecGroupReader &&groupPoints) = delete;
};