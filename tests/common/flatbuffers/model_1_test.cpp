#include <stdio.h>

#include <iostream>
#include <string>
#include <stdint.h>
#include <iostream>

#include "sunspec_adapter.h"
#include "sunspec.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"
#include "flatbuffer_test_utils.h"

using std::cout;
using std::endl;
using std::string;

TEST_GROUP(Flatbuffer_Model1)
{
    SunspecModelDefWrapper model1;
    void setup()
    {
        Sunspec::getModelDefinition(1, &model1);
    }

    void teardown()
    {
    }
};

TEST(Flatbuffer_Model1, ID)
{
    LONGS_EQUAL(1, model1.id());
}

TEST(Flatbuffer_Model1, POINT_ID_Uint16)
{
    const auto &points = model1.group().points();
    const auto &point = points[0];
    CheckPoint(point, "ID", SunspecPointDataType_Uint16, 1, "", 1, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model ID");
    LONGS_EQUAL(1, point.data_as_Uint16_t());
    STRCMP_EQUAL("", point.count_point_id());
    STRCMP_EQUAL("", point.sf_id());
    STRCMP_EQUAL("", point.units());
}

TEST(Flatbuffer_Model1, POINT_L_Uint16)
{
    const auto &points = model1.group().points();
    const auto &point = points[1];
    CheckPoint(point, "L", SunspecPointDataType_Uint16, 1, "", 1, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model Length");
    ENUMS_EQUAL_INT(SunspecPointDataType_Uint16, point.data_type());
    // LONGS_EQUAL(kUint16UnimplementedValue, point.data_as_Uint16_t());
    STRCMP_EQUAL("", point.count_point_id());
    STRCMP_EQUAL("", point.sf_id());
    STRCMP_EQUAL("", point.units());
}

TEST(Flatbuffer_Model1, POINT_Mn_String)
{
    const auto &points = model1.group().points();
    const auto &point = points[2];
    CheckPoint(point, "Mn", SunspecPointDataType_Stringx, 1, "", 16, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Manufacturer");
    ENUMS_EQUAL_INT(SunspecPointDataType_Stringx, point.data_type());
    STRCMP_EQUAL(kStringUnimplementedValue, point.data_as_String());

    STRCMP_EQUAL("", point.count_point_id());
    STRCMP_EQUAL("", point.sf_id());
    STRCMP_EQUAL("", point.units());
}

TEST(Flatbuffer_Model1, POINT_Pad_Pad1i6)
{
    const auto &points = model1.group().points();
    const auto &point = points[8];
    CheckPoint(point, "Pad", SunspecPointDataType_Pad16, 1, "", 1, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "");
    ENUMS_EQUAL_INT(SunspecPointDataType_Pad16, point.data_type());
    STRCMP_EQUAL("", point.count_point_id());
    STRCMP_EQUAL("", point.sf_id());
    STRCMP_EQUAL("", point.units());
}

TEST(Flatbuffer_Model1, ToplevelGroup)
{
    const auto &group = model1.group();
    CheckGroup(group, "common", SunspecGroupTypeType_kGroup, 1, "", 9, 0);
    STRCMP_EQUAL("", group.count_point_id());
}