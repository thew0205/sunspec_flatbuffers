/**
 * @file sunspec_group_writer.h
 * @brief This file defines the SunspecGroupWriter class, which is a sunspec block that can hold a list of SunspecPointWriter as well as nested SunspecGroupWriter within it.
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
 * @brief Represents a group of SunspecPointWriter as well as other nested SunspecGroupWriter.
 *
 * This class encapsulates a collection of Sunspec points and potentially other nested groups,
 * following the structure of a Sunspec model definition. It provides methods for storing data for each point to the device modbus memory buffer, accessing individual points
 * converting the data to JSON for printing and debugging.
 */
class SunspecGroupWriter
{
    using string_view = std::string_view;
    template <typename T>
    using list = std::list<T>;

public:
    /**
     * @brief Class constructor.
     * @param [in] def The definition of the group.
     * @param [in] model A pointer to the parent SunspecModel.
     * @param [in] groupPoint A pointer to the parent SunspecGroupPoint (nullptr for top-level groups).
     */
    SunspecGroupWriter(const SunspecGroupDef &def, SunspecModelWriter *model, SunspecGroupWriter *groupPoint);

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

    /**
     * @brief Returns the SunspecGroupDef definition.
     * @return A const reference to the SunspecGroupDef object.
     */
    const SunspecGroupDef &def() const
    {
        return def_;
    }

    /**
     * @brief length of the number of modbus registers occupied by this groupPoint and its children.
     * @return The length in number of modbus registers.
     */
    uint16_t registerLength() const
    {
        return registerLength_;
    }

    /**
     * @brief Returns the number of SunspecPointWriter directly contained within this group.
     * @return The number of points.
     */
    uint16_t pointCount() const
    {
        return points_.size();
    }

    /**
     * @brief Returns the number of SunspecGroupWriter directly contained within this group.
     * @return The number of groupPoints in this group.
     */
    uint16_t groupPointCount() const
    {
        return groupPoints_.size();
    }

    /**
     * @brief Checks if this group is the top-level group of a model.
     * @return true if it is the top-level group, false otherwise.
     */
    bool isTopLevelGroupPoint() const;

    /**
     * @brief Returns a pointer to the parent SunspecModelWriter.
     * It get the model by recursively going through the model group till it is a toplevel group
     * @return A pointer to the SunspecModelWriter object.
     */
    SunspecModelWriter *getModel() const;

    /**
     * @brief Retrieves a SunspecPointWriter from the group by its name.
     * @param [in] pointId The name of the point to find.
     * @param [in] findRecursively Whether to search in nested groups as well.
     * @return A pointer to the SunspecPointWriter, or nullptr if not found.
     */
    SunspecPointWriter *getPoint(const string_view pointId, bool findRecursively);

    /**
     * @brief Retrieves a SunspecPointWriter from the group by its name.
     * @param [in] pointId The name of the point to find.
     * @param [in] findRecursively Whether to search in nested groups as well.
     * @return A pointer to the SunspecPointWriter, or nullptr if not found.
     */
    const SunspecPointWriter *getPoint(const string_view pointId, bool findRecursively) const;

    /**
     * @brief Retrieves a SunspecGroupWriter from the group by its name.
     * @param [in] groupPointName The name of the point to find.
     * @param [in] findRecursively Whether to search in nested groups as well.
     * @return A pointer to the SunspecPointWriter, or nullptr if not found.
     */
    SunspecGroupWriter *getGroupPoint(const string_view &groupPointName, bool findRecursively = true);

    /**
     * @brief Retrieves a SunspecGroupWriter from the group by its name.
     * @param [in] groupPointName The name of the point to find.
     * @param [in] findRecursively Whether to search in nested groups as well.
     * @return A pointer to the SunspecPointWriter, or nullptr if not found.
     */
    const SunspecGroupWriter *getGroupPoint(const string_view &groupPointName, bool findRecursively = true) const;

    /**
     * @brief Returns a pointer to the parent SunspecDeviceWriter.
     * @return A pointer to the SunspecDeviceWriter object.
     */
    SunspecDeviceWriter *getDevice() const;

    /**
     * @brief Initializes the toplevel SunspecPointWriter within the group based on the group definition.
     * This method populates the points_ list with SunspecPointWriter instances.
     */
    void initPoint();

    /**
     * @brief Initializes the nested SunspecGroupWriter within the group based on the group definition.
     * This method populates the groupPoints_ list with SunspecGroupWriter instances.
     * @return The total register length of this group including its nested groups and points.
     */
    uint16_t initGroups();

    /**
     * @brief Sets the modbus buffer for this group and all its points and nested groups.
     * @param [in] modbusBuffer A pointer to the inplace modbus buffer where the group's data is to be stored.
     */
    void setAllModbusBuffer(uint16_t *modbusBuffer);

    /**
     * @brief Sets the values of modbus buffer by calling all the setValueToModbusBuffer function for all SunspecPointWriter within the group.
     */
    uint16_t setAllValueToModbusBuffer();

    /**
     * @brief Generates a JSON representation of the group and its points.
     * @param [in] includeSf Whether to include scale factors in the JSON output.
     * @param [in] includeUnits Whether to include units in the JSON output.
     * @return A string containing the JSON representation.
     */
    std::string toJson(bool includeSf = false, bool includeUnits = false) const;

private:
    /**
     * @brief Sets the pointer to the inplace modbus buffer where the group's data is to be stored.
     * Called by setAllModbusBuffer to set the modbus buffer for this group.
     * @param [in] modbusBuffer A pointer to the modbus buffer.
     */
    void setModbusBuffer(uint16_t *modbusBuffer)
    {
        modbusBuffer_ = modbusBuffer;
    }

    const SunspecGroupDef &def_; /**< The sunspec group definition of this group. */
    uint16_t *modbusBuffer_;     /**< A pointer to the inplace modbus buffer where the group's data is to be stored. */

    /* Const pointer was used here rather than reference because the we are using the logic that if the group is not null, the it is not a top level point else the model will be not null and it is a toplevel point */
    SunspecModelWriter *const model_{nullptr}; /**< A pointer to the parent model of this group (nullptr for non top-level groups). */
    SunspecGroupWriter *const group_{nullptr}; /**< A pointer to the parent group of this group (nullptr for top-level groups). */

    list<SunspecPointWriter> points_;      /**< A list of SunspecPointWriter directly contained within this group. */
    list<SunspecGroupWriter> groupPoints_; /**< A list of SunspecGroupWriter directly contained within this group. */
    uint16_t registerLength_;              /**< length of the number of modbus registers occupied by this group and its children. */

    SunspecGroupWriter &operator=(const SunspecGroupWriter &groupPoints) = delete;
    SunspecGroupWriter &operator=(SunspecGroupWriter &&groupPoints) = delete;
};