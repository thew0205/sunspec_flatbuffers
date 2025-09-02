/**
 * @file sunspec_group_point.h
 * @brief This file defines the SunspecGroupPoint class, which is a sunspec block that can hold a list of SunspecPoint as well as nested SunspecGroupPoint within it.
 *
 * @author Tolulope Matthew Busoye PowerLabs
 */

#pragma once

#include <string>
#include <list>
#include <string_view>

#include "writer/sunspec_point_writer.h"

class SunspecModelWriter;
class SunspecDeviceWriter;

/**
 * @brief Represents a group of Sunspec points.
 *
 * This class encapsulates a collection of Sunspec points and potentially other nested groups,
 * following the structure of a Sunspec model definition. It provides methods for reading data
 * from a device, converting the data to JSON, and accessing individual points.
 */
class SunspecGroupWriter
{
    using string_view = std::string_view;
    template <typename T>
    using list = std::list<T>;

public:
    /**
     * @brief Returns the groupPoint's definition.
     * @return A const reference to the SunspecModelDef object.
     */
    const SunspecGroupPointDef &def() const
    {
        return def_;
    }
    uint16_t registerLength() const
    {
        return registerLength_;
    }

    /**
     * @brief Sets the values of all points within the group from a raw buffer of 16-bit words.
     * @param [in] buf A pointer to the buffer containing the raw data.
     */
    uint16_t setAllToBuffer();
    /**
     * @brief Checks if this group is the top-level group of a model.
     * @return true if it is the top-level group, false otherwise.
     */
    bool isTopLevelGroupPoint() const;

    /**
     * @brief Generates a JSON representation of the group and its points.
     * @param [in] includeSf Whether to include scale factors in the JSON output.
     * @param [in] includeUnits Whether to include units in the JSON output.
     * @return A string containing the JSON representation.
     */
    std::string toJson(bool includeSf = false, bool includeUnits = false) const;

    /**
     * @brief Returns a pointer to the parent SunspecModel.
     * @return A pointer to the SunspecModel object.
     */
    SunspecModelWriter *model() const;

    /**
     * @brief Retrieves a point from the group by its name.
     * @param [in] pointName The name of the point to find.
     * @param [in] findRecursively Whether to search in nested groups as well.
     * @return A pointer to the SunspecPoint, or nullptr if not found.
     */
    SunspecPointWriter *getPoint(const string_view pointName, bool findRecursively = true);

    /**
     * @brief Retrieves a point from the group by its name.
     * @param [in] pointName The name of the point to find.
     * @param [in] findRecursively Whether to search in nested groups as well.
     * @return A pointer to the SunspecPoint, or nullptr if not found.
     */
    const SunspecPointWriter *getPoint(const string_view pointName, bool findRecursively = true) const;

    /**
     * @brief Retrieves a groupPoint from the group by its name.
     * @param [in] groupPointName The name of the point to find.
     * @param [in] findRecursively Whether to search in nested groups as well.
     * @return A pointer to the SunspecPoint, or nullptr if not found.
     */
    SunspecGroupWriter *getGroupPoint(const string_view &groupPointName, bool findRecursively = true);

    /**
     * @brief Retrieves a groupPoint from the group by its name.
     * @param [in] groupPointName The name of the point to find.
     * @param [in] findRecursively Whether to search in nested groups as well.
     * @return A pointer to the SunspecPoint, or nullptr if not found.
     */
    const SunspecGroupWriter *getGroupPoint(const string_view &groupPointName, bool findRecursively = true) const;

    /**
     * @brief Returns a pointer to the parent SunspecDevice.
     * @return A pointer to the SunspecDevice object.
     */
    SunspecDeviceWriter *getDevice() const;

    /**
     * @brief Returns the number of points directly contained within this group.
     * @return The number of points.
     */
    uint16_t pointCount() const
    {
        return points_.size();
    }

    /**
     * @brief Returns the number of groupPoint directly contained within this group.
     * @return The number of groupPoints in this group.
     */
    uint16_t groupPointCount() const
    {
        return groupPoints_.size();
    }

    /**
     * @brief Class constructor.
     * @param [in] def The definition of the group.
     * @param [in] addr The starting address of the group in the register map.
     * @param [in] model A pointer to the parent SunspecModel.
     * @param [in] groupPoint A pointer to the parent SunspecGroupPoint (nullptr for top-level groups).
     */
    SunspecGroupWriter(const SunspecGroupPointDef &def, SunspecModelWriter *model, SunspecGroupWriter *groupPoint);

    /**
     * @brief Copy constructor.
     */
    SunspecGroupWriter(const SunspecGroupWriter &groupPoints) = default;

    /**
     * @brief Move constructor.
     */
    SunspecGroupWriter(SunspecGroupWriter &&group) noexcept = default;

    /**
     * @brief Destructor.
     */
    ~SunspecGroupWriter() = default;
    void initPoint();
    uint16_t initGroups();
    void setAllModbusBuffer(uint16_t *modbusBuffer);

private:
    void setModbusBuffer(uint16_t *modbusBuffer)
    {
        modbusBuffer_ = modbusBuffer;
    }
    // uint16_t relativeAddress_;
    uint16_t *modbusBuffer_;
    uint16_t registerLength_;

    /** Const pointer was used here rather than reference because the we are using the logic that if the group is not null, the it is not a top level point else the model will be not null and it is a toplevel point */
    SunspecModelWriter *const model_{nullptr};
    SunspecGroupWriter *const group_{nullptr};
    const SunspecGroupPointDef &def_;
    list<SunspecPointWriter> points_;
    list<SunspecGroupWriter> groupPoints_;

    SunspecGroupWriter &operator=(const SunspecGroupWriter &groupPoints) = delete;
    SunspecGroupWriter &operator=(SunspecGroupWriter &&groupPoints) = delete;
};