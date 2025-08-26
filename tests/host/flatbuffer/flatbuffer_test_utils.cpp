#include "flatbuffer_test_utils.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"

using std::string;

void CheckPoint(const SunspecPointDef &pointDef, const string &expectedId, SunspecPointData dataType, uint16_t count, const string &count_point_id, uint16_t size, uint16_t sf, const string &sf_id, const string &units, SunspecPointAccessType access, SunspecPointMandatoryType mandatory, const string &label)
{
    CHECK_EQUAL(expectedId, FlatbufferStringToString(pointDef.id()));
    ENUMS_EQUAL_INT(dataType, pointDef.data_type());
    LONGS_EQUAL(count, pointDef.count());
    CHECK_EQUAL(count_point_id, FlatbufferStringToString(pointDef.count_point_id()));
    LONGS_EQUAL(size, pointDef.size());
    LONGS_EQUAL(sf, pointDef.sf());
    CHECK_EQUAL(sf_id, FlatbufferStringToString(pointDef.sf_id()));
    CHECK_EQUAL(units, FlatbufferStringToString(pointDef.units()));
    ENUMS_EQUAL_INT(access, pointDef.access());
    ENUMS_EQUAL_INT(mandatory, pointDef.mandatory());
    CHECK_EQUAL(label, FlatbufferStringToString(pointDef.label()));
}

void CheckGroup(const SunspecGroupPointDef &group, const string &id, SunspecGroupType type, uint16_t count, const string &count_point_id, uint16_t pointLength, uint16_t groupLength)
{
    CHECK_EQUAL(id, FlatbufferStringToString(group.id()));
    ENUMS_EQUAL_INT(type, group.type());
    LONGS_EQUAL(count, group.count());
    CHECK_EQUAL(count_point_id, FlatbufferStringToString(group.count_point_id()));
    LONGS_EQUAL(pointLength, group.points()->size());
    LONGS_EQUAL(groupLength, group.groups()->size());

}