#include <stdio.h>

#include <iostream>
#include <string>
#include <stdint.h>
#include <iostream>

#include "sunspec.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"
#include "backend_test_utils.h"

using std::cout;
using std::endl;
using std::string;

TEST_GROUP(Flatbuffer_Model1)
{
    const SunspecModelDef *model1;
    void setup()
    {
        model1 = getModelDefinition(SunspecModelList_kModel1);
    }

    void teardown()
    {
       deinitializeAllModels();
    }
};

TEST(Flatbuffer_Model1, ID)
{
    LONGS_EQUAL(SunspecModelList_kModel1, model1->id());
}

TEST(Flatbuffer_Model1, POINT_ID_Uint16)
{
    const auto &points = *model1->group()->points();
    const auto &point = DEREFERENCE_POINTER_FLATBUFFER(points[0]);
    CheckPoint(point, "ID", SunspecPointData_kUint16, 1, "", 1, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model ID");
    LONGS_EQUAL(1, point.data_as_kUint16()->value());
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.count_point_id()));
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.sf_id()));
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.units()));
}

TEST(Flatbuffer_Model1, POINT_L_Uint16)
{
    const auto &points = *model1->group()->points();
    const auto &point = DEREFERENCE_POINTER_FLATBUFFER(points[1]);
    CheckPoint(point, "L", SunspecPointData_kUint16, 1, "", 1, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model Length");
    // CHECK_EQUAL(nullptr, point.data());
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.count_point_id()));
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.sf_id()));
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.units()));
}

TEST(Flatbuffer_Model1, POINT_Mn_String)
{
    const auto &points = *model1->group()->points();
    const auto &point = DEREFERENCE_POINTER_FLATBUFFER(points[2]);
    CheckPoint(point, "Mn", SunspecPointData_kStringx, 1, "", 16, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Manufacturer");
    // POINTERS_EQUAL(nullptr, point.data());
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.count_point_id()));
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.sf_id()));
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.units()));
}

TEST(Flatbuffer_Model1, POINT_Pad_Pad1i6)
{
    const auto &points = *model1->group()->points();
    const auto &point = DEREFERENCE_POINTER_FLATBUFFER(points[8]);
    CheckPoint(point, "Pad", SunspecPointData_kPad16, 1, "", 1, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "");
    // POINTERS_EQUAL(nullptr, point.data());
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.count_point_id()));
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.sf_id()));
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.units()));
}

TEST(Flatbuffer_Model1, ToplevelGroup)
{
    const auto &group = *model1->group();
    CheckGroup(group, "common", SunspecGroupType_kGroup, 1, "", 9, 0);
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(group.count_point_id()));
}