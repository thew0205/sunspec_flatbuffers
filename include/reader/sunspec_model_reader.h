/**
 * @file sunspec_model.h
 * @brief This file defines the SunspecModel class, which is a represent a Sunspec Model.
 *
 * @author Tolulope Matthew Busoye PowerLabs
 */

#pragma once

#include <string>
#include <stdint.h>

#include "sunspec_model_definition_generated.h"
#include "reader/sunspec_group_reader.h"

class SunspecDeviceReader;

/**
 * @brief Represents a Sunspec model as defined by a specific model definition.
 *
 * This class encapsulates a complete Sunspec model, including its top-level group of points,
 * and provides methods for interacting with the model's data on a physical device.
 */
class SunspecModelReader
{
    using string_view = std::string_view;

public:
    SunspecModelReader(const SunspecModelDef &def, const uint16_t *modbusBuffer, const uint16_t address, SunspecDeviceReader &device);

    SunspecModelReader(const SunspecModelReader &groupPoints) = default;

    SunspecModelReader(SunspecModelReader &&groupPoints) noexcept = default;

    ~SunspecModelReader() = default;

    const SunspecModelDef &def() const
    {
        return def_;
    }

    const SunspecGroupReader &topLevelGroupPoint() const
    {
        return topLevelGroupPoint_;
    }

    SunspecDeviceReader &device()
    {
        return device_;
    }

    uint16_t registerLength() const
    {
        return topLevelGroupPoint_.registerLength();
    }

    uint16_t address() const
    {
        return address_;
    }
    // void readAndSetFromDevice();

    std::string toJson(bool includeSf = false, bool includeUnits = false) const;

    SunspecPointReader *getPoint(const string_view pointId);

    const SunspecPointReader *getPoint(const string_view pointId) const;

    SunspecGroupReader *getGroup(const string_view &groupId);

    const SunspecGroupReader *getGroup(const string_view &groupId) const;

    void initPoints();
    uint16_t initGroups(uint16_t maxRegisterLength);

private:
    SunspecModelReader &operator=(const SunspecModelReader &groupPoints) = delete;
    SunspecModelReader &operator=(SunspecModelReader &&groupPoints) = delete;

    SunspecDeviceReader &device_;

    SunspecGroupReader topLevelGroupPoint_;
    const SunspecModelDef &def_;
    const uint16_t *modbusBuffer_;
    uint16_t address_;
    // uint16_t registerLength_;
};