#include "flatbuffer_test_utils.h"

#include "sunspec_adapter.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"

using std::string;

void CheckPoint(const SunspecPointDef &pointDef, const string &expectedId, SunspecPointData dataType, uint16_t count, const string &count_point_id, uint16_t size, uint16_t sf, const string &sf_id, const string &units, SunspecPointAccessType access, SunspecPointMandatoryType mandatory, const string &label)
{
    CHECK_EQUAL(expectedId, FormatStringToString(pointDef.id()));
    ENUMS_EQUAL_INT(dataType, pointDef.data_type());
    LONGS_EQUAL(count, pointDef.count());
    CHECK_EQUAL(count_point_id, FormatStringToString(pointDef.count_point_id()));
    LONGS_EQUAL(size, pointDef.size());
    LONGS_EQUAL(sf, pointDef.sf());
    CHECK_EQUAL(sf_id, FormatStringToString(pointDef.sf_id()));
    CHECK_EQUAL(units, FormatStringToString(pointDef.units()));
    ENUMS_EQUAL_INT(access, pointDef.access());
    ENUMS_EQUAL_INT(mandatory, pointDef.mandatory());
    CHECK_EQUAL(label, FormatStringToString(pointDef.label()));
}

void CheckGroup(const SunspecGroupDef &group, const string &id, SunspecGroupType type, uint16_t count, const string &count_point_id, uint16_t pointLength, uint16_t groupLength)
{
    CHECK_EQUAL(id, FormatStringToString(group.id()));
    ENUMS_EQUAL_INT(type, group.type());
    LONGS_EQUAL(count, group.count());
    CHECK_EQUAL(count_point_id, FormatStringToString(group.count_point_id()));
    LONGS_EQUAL(pointLength, group.points()->size());
    LONGS_EQUAL(groupLength, group.groups()->size());

}