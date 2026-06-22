#include <stdio.h>

#include <iostream>
#include <string>
#include <stdint.h>
#include <iostream>

#include "sunspec_model_definition_generated.h"
#include "sunspec.h"
#include "flatbuffer_test_utils.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"

using std::cout;
using std::endl;
using std::string;
extern unsigned char modelDefinition160[];

TEST_GROUP(Flatbuffer_Model160)
{
    const SunspecModelDef *model160;
    void setup()
    {
        model160 = GetSunspecModelDef(modelDefinition160);
    }

    void teardown()
    {
    }
};

TEST(Flatbuffer_Model160, ID)
{
    LONGS_EQUAL(SunspecModelList_kModel160, model160->id());
}

TEST(Flatbuffer_Model160, POINT_ID)
{
    const auto &points = *model160->group()->points();
    const auto &point = *points.Get(0);
    CheckPoint(point, "ID", SunspecPointData_kUint16, 1, "", 1, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model ID");
    LONGS_EQUAL(160, point.data_as_kUint16()->value());
    POINTERS_EQUAL(nullptr, point.count_point_id());
    POINTERS_EQUAL(nullptr, point.sf_id());
    POINTERS_EQUAL(nullptr, point.units());
}

TEST(Flatbuffer_Model160, POINT_L)
{
    const auto &points = *model160->group()->points();
    const auto &point = *points.Get(1);
    CheckPoint(point, "L", SunspecPointData_kUint16, 1, "", 1, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model Length");
    POINTERS_EQUAL(nullptr, point.data());
    POINTERS_EQUAL(nullptr, point.count_point_id());
    POINTERS_EQUAL(nullptr, point.sf_id());
    POINTERS_EQUAL(nullptr, point.units());
}

TEST(Flatbuffer_Model160, ToplevelGroup)
{
    const auto &group = *model160->group();
    CheckGroup(group, "mppt", SunspecGroupType_kGroup, 1, "", 9, 1);
    POINTERS_EQUAL(nullptr, group.count_point_id());
}

TEST(Flatbuffer_Model160, Sub_Group_Module)
{
    const auto &subGroup = *model160->group()->groups()->Get(0);
    CheckGroup(subGroup, "module", SunspecGroupType_kGroup, 0, "N", 10, 0);
}

TEST(Flatbuffer_Model160, Sub_Group_Module_POINT_ID)
{
    const auto &point = *model160->group()->groups()->Get(0)->points()->Get(0);

    CheckPoint(point, "ID", SunspecPointData_kUint16, 1, "", 1, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Input ID");
    POINTERS_EQUAL(nullptr, point.data());

    POINTERS_EQUAL(nullptr, point.count_point_id());
    POINTERS_EQUAL(nullptr, point.sf_id());
    POINTERS_EQUAL(nullptr, point.units());
}

TEST(Flatbuffer_Model160, Sub_Group_Module_POINT_IDStr)
{
    const auto &point = *model160->group()->groups()->Get(0)->points()->Get(1);
    CheckPoint(point, "IDStr", SunspecPointData_kStringx, 1, "", 8, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Input ID String");
    CHECK_EQUAL("", FlatbufferKStringxToString(point.data_as_kStringx()));
    POINTERS_EQUAL(nullptr, point.count_point_id());
    POINTERS_EQUAL(nullptr, point.sf_id());
    POINTERS_EQUAL(nullptr, point.units());
}