#include <stdio.h>

#include <iostream>
#include <string>
#include <stdint.h>
#include <iostream>

#include "sunspec_model_definition_generated.h"
#include "sunspec.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"
#include "flatbuffer_test_utils.h"

using std::cout;
using std::endl;
using std::string;
extern unsigned char modelDefinition1[];

TEST_GROUP(Flatbuffer_Model1)
{
    const SunspecModelDef *model1;
    void setup()
    {
        model1 = GetSunspecModelDef(modelDefinition1);
    }

    void teardown()
    {
    }
};

TEST(Flatbuffer_Model1, ID)
{
    LONGS_EQUAL(SunspecModelList_kModel1, model1->id());
}

TEST(Flatbuffer_Model1, POINT_ID_Uint16)
{
    const auto &points = *model1->group()->points();
    const auto &point = *points.Get(0);
    CheckPoint(point, "ID", SunspecPointData_kUint16, 1, "", 1, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model ID");
    LONGS_EQUAL(1, point.data_as_kUint16()->value());
    POINTERS_EQUAL(nullptr, point.count_point_id());
    POINTERS_EQUAL(nullptr, point.sf_id());
    POINTERS_EQUAL(nullptr, point.units());
}

TEST(Flatbuffer_Model1, POINT_L_Uint16)
{
    const auto &points = *model1->group()->points();
    const auto &point = *points.Get(1);
    CheckPoint(point, "L", SunspecPointData_kUint16, 1, "", 1, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model Length");
    POINTERS_EQUAL(nullptr, point.data());
    POINTERS_EQUAL(nullptr, point.count_point_id());
    POINTERS_EQUAL(nullptr, point.sf_id());
    POINTERS_EQUAL(nullptr, point.units());
}

TEST(Flatbuffer_Model1, POINT_Mn_String)
{
    const auto &points = *model1->group()->points();
    const auto &point = *points.Get(2);
    CheckPoint(point, "Mn", SunspecPointData_kStringx, 1, "", 16, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Manufacturer");
    POINTERS_EQUAL(nullptr, point.data());
    POINTERS_EQUAL(nullptr, point.count_point_id());
    POINTERS_EQUAL(nullptr, point.sf_id());
    POINTERS_EQUAL(nullptr, point.units());
}

TEST(Flatbuffer_Model1, POINT_Pad_Pad16)
{
    const auto &points = *model1->group()->points();
    const auto &point = *points.Get(8);
    CheckPoint(point, "Pad", SunspecPointData_kPad16, 1, "", 1, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "");
    POINTERS_EQUAL(nullptr, point.data());
    POINTERS_EQUAL(nullptr, point.count_point_id());
    POINTERS_EQUAL(nullptr, point.sf_id());
    POINTERS_EQUAL(nullptr, point.units());
}

IGNORE_TEST(Flatbuffer_Model1, POINT_Pad_Pad16)
{
    const auto &points = *model1->group()->points();
    const auto &point = *points.Get(8);
    CheckPoint(point, "Pad", SunspecPointData_kUint16, 1, "", 1, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "");
    // LONGS_EQUAL(65535, point.data_as_kUint16()->value());
    POINTERS_EQUAL(nullptr, point.count_point_id());
    POINTERS_EQUAL(nullptr, point.sf_id());
    POINTERS_EQUAL(nullptr, point.units());
}
TEST(Flatbuffer_Model1, ToplevelGroup)
{
    const auto &group = *model1->group();
    CheckGroup(group, "common", SunspecGroupType_kGroup, 1, "", 9, 0);
    POINTERS_EQUAL(nullptr, group.count_point_id());
}