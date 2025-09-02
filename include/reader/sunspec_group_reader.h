/**
 * @file sunspec_group_point.h
 * @brief This file defines the SunspecGroupPoint class, which is a sunspec block that can hold a list of SunspecPoint as well as nested SunspecGroupPoint within it.
 *
 * @author Tolulope Matthew Busoye PowerLabs
 */

#pragma once

#include <string>
#include <list>

#include "reader/sunspec_point_reader.h"

class SunspecModelReader;
class SunspecDeviceReader;

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
    using list = std::list<T>;

public:
    /**
     * @brief Returns the groupPoint's definition.
     * @return A const reference to the SunspecModelDef object.
     */
    const SunspecGroupDef &def() const
    {
        return def_;
    }
    /**
     * @brief Reads all points within the group and its nested groups from the device and sets their values.
     */
    void readAndSetFromDevice();

    /**
     * @brief Sets the values of all points within the group from a raw buffer of 16-bit words.
     * @param [in] buf A pointer to the buffer containing the raw data.
     */
    void setAllFromBuffer(uint16_t *buf);

    /**
     * @brief Sets the scale factors for all points within the group.
     */
    void setAllSf();

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
    SunspecModelReader *model() const;

    /**
     * @brief Retrieves a point from the group by its name.
     * @param [in] pointName The name of the point to find.
     * @param [in] findRecursively Whether to search in nested groups as well.
     * @return A pointer to the SunspecPoint, or nullptr if not found.
     */
    SunspecPointReader *getPoint(const string_view pointName, bool findRecursively = true);

    /**
     * @brief Retrieves a point from the group by its name.
     * @param [in] pointName The name of the point to find.
     * @param [in] findRecursively Whether to search in nested groups as well.
     * @return A pointer to the SunspecPoint, or nullptr if not found.
     */
    const SunspecPointReader *getPoint(const string_view pointName, bool findRecursively = true) const;

    /**
     * @brief Retrieves a groupPoint from the group by its name.
     * @param [in] groupPointName The name of the point to find.
     * @param [in] findRecursively Whether to search in nested groups as well.
     * @return A pointer to the SunspecPoint, or nullptr if not found.
     */
    SunspecGroupReader *getGroupPoint(const string_view &groupPointName, bool findRecursively = true);

    /**
     * @brief Retrieves a groupPoint from the group by its name.
     * @param [in] groupPointName The name of the point to find.
     * @param [in] findRecursively Whether to search in nested groups as well.
     * @return A pointer to the SunspecPoint, or nullptr if not found.
     */
    const SunspecGroupReader *getGroupPoint(const string_view &groupPointName, bool findRecursively = true) const;

    /**
     * @brief Returns a pointer to the parent SunspecDevice.
     * @return A pointer to the SunspecDevice object.
     */
    SunspecDeviceReader *getDevice() const;

    /**
     * @brief Returns the number of points directly contained within this group.
     * @return The number of points.
     */
    uint16_t pointLength() const
    {
        return points_.size();
    }

    /**
     * @brief Returns the number of groupPoint directly contained within this group.
     * @return The number of groupPoints in this group.
     */
    uint16_t groupPointLength() const
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
    SunspecGroupReader(const SunspecGroupDef &def, uint16_t addr, SunspecModelReader *model, SunspecGroupReader *groupPoint);

    /**
     * @brief Copy constructor.
     */
    SunspecGroupReader(const SunspecGroupReader &groupPoints) = default;

    /**
     * @brief Move constructor.
     */
    SunspecGroupReader(SunspecGroupReader &&group) noexcept = default;

    /**
     * @brief Destructor.
     */
    ~SunspecGroupReader() = default;

private:
    uint16_t address_;
    uint16_t len_;

    /** Const pointer was used here rather than reference because the we are using the logic that if the group is not null, the it is not a top level point else the model will be not null and it is a toplevel point */
    SunspecModelReader *const model_{nullptr};
    SunspecGroupReader *const group_{nullptr};
    const SunspecGroupDef &def_;
    list<SunspecPointReader> points_;
    list<SunspecGroupReader> groupPoints_;

    SunspecGroupReader &operator=(const SunspecGroupReader &groupPoints) = delete;
    SunspecGroupReader &operator=(SunspecGroupReader &&groupPoints) = delete;
};