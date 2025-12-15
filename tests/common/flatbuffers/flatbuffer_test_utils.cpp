#include "flatbuffer_test_utils.h"

#include "sunspec_adapter.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"

using std::string;

void CheckPoint(const SunspecPointDefWrapper &pointDef, const string &expectedId, SunspecPointDataType dataType, uint16_t count, const string &count_point_id, uint16_t size, uint16_t sf, const string &sf_id, const string &units, SunspecPointAccessType access, SunspecPointMandatoryType mandatory, const string &label)
{
    CHECK_EQUAL(expectedId, pointDef.id());
    ENUMS_EQUAL_INT(dataType, pointDef.data_type());
    LONGS_EQUAL(count, pointDef.count());
    CHECK_EQUAL(count_point_id, pointDef.count_point_id());
    LONGS_EQUAL(size, pointDef.size());
    LONGS_EQUAL(sf, pointDef.sf());
    CHECK_EQUAL(sf_id, pointDef.sf_id());
    CHECK_EQUAL(units, pointDef.units());
    ENUMS_EQUAL_INT(access, (pointDef.access()));
    ENUMS_EQUAL_INT(mandatory, pointDef.mandatory());
    CHECK_EQUAL(label, pointDef.label());
}

void CheckGroup(const SunspecGroupDefWrapper &group, const string &id, SunspecGroupTypeType type, uint16_t count, const string &count_point_id, uint16_t pointLength, uint16_t groupLength)
{
    CHECK_EQUAL(id, group.id());
    ENUMS_EQUAL_INT(type, group.type());
    LONGS_EQUAL(count, group.count());
    CHECK_EQUAL(count_point_id, group.count_point_id());
    LONGS_EQUAL(pointLength, vector_size(group.points()));
    LONGS_EQUAL(groupLength, vector_size(group.groups()));
}