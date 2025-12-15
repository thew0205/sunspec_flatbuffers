#pragma once

#include <string>
#include <stdint.h>

#include "sunspec_adapter.h"
#include "sunspec.h"

void CheckPoint(const SunspecPointDefWrapper &pointDef, const std::string &expectedId, SunspecPointDataType dataType, uint16_t count, const std::string &count_point_id, uint16_t size, uint16_t sf, const std::string &sf_id, const std::string &units, SunspecPointAccessType access, SunspecPointMandatoryType mandatory, const std::string &label);

void CheckGroup(const SunspecGroupDefWrapper &group, const std::string &id, SunspecGroupTypeType type, uint16_t count, const std::string &count_point_id, uint16_t pointLength, uint16_t groupLength);
