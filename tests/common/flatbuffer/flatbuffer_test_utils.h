#pragma once

#include <string>
#include <stdint.h>

#include "sunspec_model_definition_generated.h"
#include "sunspec.h"

void CheckPoint(const SunspecPointDef &pointDef, const std::string &expectedId, SunspecPointData dataType, uint16_t count, const std::string &count_point_id, uint16_t size, uint16_t sf, const std::string &sf_id, const std::string &units, SunspecPointAccessType access, SunspecPointMandatoryType mandatory, const std::string &label);

void CheckGroup(const SunspecGroupDef &group, const std::string &id, SunspecGroupType type, uint16_t count, const std::string &count_point_id, uint16_t pointLength, uint16_t groupLength);
