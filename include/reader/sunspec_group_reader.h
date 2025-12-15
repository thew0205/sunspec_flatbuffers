/**
 * @file sunspec_group_point.h
 * @brief This file defines the SunspecGroupPoint class, which is a sunspec block that can hold a list of SunspecPoint as well as nested SunspecGroupPoint within it.
 *
 * @author Tolulope Matthew Busoye PowerLabs
 */

#pragma once

#include <string>
#include <vector>

#include "sunspec_adapter.h"

#include "reader/sunspec_point_reader.h"

class SunspecModelReader;

/**
 * @brief Represents a group of Sunspec points.
 *
 * This class encapsulates a collection of Sunspec points and potentially other nested groups,
 * following the structure of a Sunspec model definition. It provides methods for reading data
 * from a device, converting the data to JSON, and accessing individual points.
 */

/**
 * @brief Represents a group of Sunspec points.
 *
 * This class encapsulates a collection of Sunspec points and potentially other nested groups,
 * following the structure of a Sunspec model definition. It provides methods for reading data
 * from a device, converting the data to JSON, and accessing individual points.
 */
class SunspecGroupReader
{
    using string_view = std::string_view; /**< Alias for string_view type */
    template <typename T>
    using vector = std::vector<T>; /**< Alias for std::vector */

public:
    /**
     * @brief Constructs a group reader for a top-level group.
     * @param def Group definition
     * @param modbusBuffer Pointer to Modbus buffer
     * @param model Pointer to parent model reader
     */
    SunspecGroupReader(const SunspecGroupDefWrapper &def, const uint16_t *modbusBuffer, SunspecModelReader *model);

    /**
     * @brief Constructs a group reader for a nested group.
     * @param def Group definition
     * @param modbusBuffer Pointer to Modbus buffer
     * @param group Pointer to parent group reader
     */
    SunspecGroupReader(const SunspecGroupDefWrapper &def, const uint16_t *modbusBuffer, SunspecGroupReader *group);

    /**
     * @brief Copy constructor
     */
    SunspecGroupReader(const SunspecGroupReader &groupPoints) = default;

    /**
     * @brief Move constructor
     */
    SunspecGroupReader(SunspecGroupReader &&group) noexcept = default;

    /**
     * @brief Destructor
     */
    ~SunspecGroupReader() = default;

    /**
     * @brief Returns the group definition
     * @return Reference to SunspecGroupDef
     */
    const SunspecGroupDefWrapper &def() const
    {
        return def_;
    }

    /**
     * @brief Returns the number of points in the group
     * @return Number of points
     */
    size_t pointLength() const
    {
        return points_.size();
    }

    /**
     * @brief Returns the number of nested groups
     * @return Number of groups
     */
    size_t groupLength() const
    {
        return groups_.size();
    }

    /**
     * @brief Returns the register length of the group
     * @return Register length
     */
    uint16_t registerLength() const
    {
        return registerLength_;
    }

    /**
     * @brief Initializes all points in the group
     */
    void initPoints();

    /**
     * @brief Initializes all nested groups
     * @param maxRegisterLength Maximum register length allowed
     * @return Total register length used by groups
     */
    uint16_t initGroups(uint16_t maxRegisterLength);

    /**
     * @brief Checks if this group is the top-level group
     * @return True if top-level, false otherwise
     */
    bool isTopLevelGroupPoint() const;

    /**
     * @brief Gets the parent model reader
     * @return Pointer to SunspecModelReader
     */
    SunspecModelReader *getModel() const;

    /**
     * @brief Gets a pointer to a point by its ID
     * @param pointId Point identifier
     * @return Pointer to SunspecPointReader
     */
    SunspecPointReader *getPoint(const string_view pointId);

    /**
     * @brief Gets a const pointer to a point by its ID
     * @param pointId Point identifier
     * @return Const pointer to SunspecPointReader
     */
    const SunspecPointReader *getPoint(const string_view pointId) const;

    /**
     * @brief Gets a pointer to a nested group by its ID
     * @param groupId Group identifier
     * @return Pointer to SunspecGroupReader
     */
    SunspecGroupReader *getGroup(const string_view &groupId);

    /**
     * @brief Gets a const pointer to a nested group by its ID
     * @param groupId Group identifier
     * @return Const pointer to SunspecGroupReader
     */
    const SunspecGroupReader *getGroup(const string_view &groupId) const;

    // /**
    //  * @brief Converts group data to JSON format
    //  * @param includeSf Include scale factors
    //  * @param includeUnits Include units
    //  * @return JSON string
    //  */
    // std::string toJson(bool includeSf = false, bool includeUnits = false) const;

private:
    const uint16_t *modbusBuffer_; /**< Pointer to Modbus buffer */
    uint16_t registerLength_;      /**< Register length of the group */

    SunspecModelReader *const model_;   /**< Pointer to parent model reader */
    SunspecGroupReader *const group_;   /**< Pointer to parent group reader (if nested) */
    const SunspecGroupDefWrapper &def_;        /**< Reference to group definition */
    vector<SunspecPointReader> points_; /**< List of points in the group */
    vector<SunspecGroupReader> groups_; /**< List of nested groups */

    SunspecGroupReader &operator=(const SunspecGroupReader &groupPoints) = delete; /**< Copy assignment deleted */
    SunspecGroupReader &operator=(SunspecGroupReader &&groupPoints) = delete;      /**< Move assignment deleted */
};