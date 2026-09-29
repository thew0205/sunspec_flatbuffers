#include <stdio.h>

#include <iostream>
#include <string>
#include <stdint.h>
#include <iostream>

#include "sunspec.h"

#include "sunspec.h"
#include "backend_test_utils.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"

using std::cout;
using std::endl;
using std::string;

TEST_GROUP(Flatbuffer_Model160)
{
    const SunspecModelDef *model160;
    void setup()
    {
        model160 = getModelDefinition(SunspecModelList_kModel160);
    }

    void teardown()
    {
        deinitializeAllModels();
    }
};

TEST(Flatbuffer_Model160, ID)
{
    LONGS_EQUAL(SunspecModelList_kModel160, model160->id());
}

TEST(Flatbuffer_Model160, POINT_ID)
{
    const auto &points = *model160->group()->points();
    const auto &point = DEREFERENCE_POINTER_FLATBUFFER(points[0]);
    CheckPoint(point, "ID", SunspecPointData_kUint16, 1, "", 1, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model ID");
    LONGS_EQUAL(160, point.data_as_kUint16()->value());
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.count_point_id()));
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.sf_id()));
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.units()));
}

TEST(Flatbuffer_Model160, POINT_L)
{
    const auto &points = *model160->group()->points();
    const auto &point = DEREFERENCE_POINTER_FLATBUFFER(points[1]);
    CheckPoint(point, "L", SunspecPointData_kUint16, 1, "", 1, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model Length");
    // POINTERS_EQUAL(nullptr, point.data());
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.count_point_id()));
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.sf_id()));
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.units()));
}

TEST(Flatbuffer_Model160, ToplevelGroup)
{
    const auto &group = *model160->group();
    CheckGroup(group, "mppt", SunspecGroupType_kGroup, 1, "", 9, 1);
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(group.count_point_id()));
}

TEST(Flatbuffer_Model160, Sub_Group_Module)
{
    const auto &subGroup = DEREFERENCE_POINTER_FLATBUFFER((*model160->group()->groups())[0]);
    CheckGroup(subGroup, "module", SunspecGroupType_kGroup, 0, "N", 10, 0);
}

TEST(Flatbuffer_Model160, Sub_Group_Module_POINT_ID)
{
    const auto &point = DEREFERENCE_POINTER_FLATBUFFER((*DEREFERENCE_POINTER_FLATBUFFER((*model160->group()->groups())[0]).points())[0]);

    CheckPoint(point, "ID", SunspecPointData_kUint16, 1, "", 1, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Input ID");
    // POINTERS_EQUAL(nullptr, point.data());
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.count_point_id()));
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.sf_id()));
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.units()));
}

TEST(Flatbuffer_Model160, Sub_Group_Module_POINT_IDStr)
{
    const auto &point = DEREFERENCE_POINTER_FLATBUFFER((*DEREFERENCE_POINTER_FLATBUFFER((*model160->group()->groups())[0]).points())[1]);
    CheckPoint(point, "IDStr", SunspecPointData_kStringx, 1, "", 8, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Input ID String");
    CHECK_EQUAL("", FlatbufferKStringxToString(point.data_as_kStringx()));
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.count_point_id()));
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.sf_id()));
    CHECK_EQUAL(FlatbufferStringToString(nullptr), FlatbufferStringToString(point.units()));
}