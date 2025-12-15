#include <stdio.h>

#include <iostream>
#include <string>
#include <stdint.h>
#include <iostream>

#include "sunspec_adapter.h"
#include "flatbuffer_test_utils.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"

using std::cout;
using std::endl;
using std::string;

TEST_GROUP(Flatbuffer_Model160)
{
    SunspecModelDefWrapper model160;
    void setup()
    {
        Sunspec::getModelDefinition(160, &model160);
    }

    void teardown()
    {
    }
};

// TEST(Flatbuffer_Model160, ID)
// {
//     LONGS_EQUAL(160, model160->id());
// }

// TEST(Flatbuffer_Model160, POINT_ID)
// {
//     const auto &points = *model160->group()->points();
//     const auto &point = *points.Get(0);
//     CheckPoint(point, "ID", SunspecPointDataType_Uint16, 1, "", 1, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model ID");
//     LONGS_EQUAL(160, point.data_as_Uint16()->value());
//     POINTERS_EQUAL(nullptr, point.count_point_id());
//     POINTERS_EQUAL(nullptr, point.sf_id());
//     POINTERS_EQUAL(nullptr, point.units());
// }

// TEST(Flatbuffer_Model160, POINT_L)
// {
//     const auto &points = *model160->group()->points();
//     const auto &point = *points.Get(1);
//     CheckPoint(point, "L", SunspecPointDataType_Uint16, 1, "", 1, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model Length");
//     POINTERS_EQUAL(nullptr, point.data());
//     POINTERS_EQUAL(nullptr, point.count_point_id());
//     POINTERS_EQUAL(nullptr, point.sf_id());
//     POINTERS_EQUAL(nullptr, point.units());
// }

// TEST(Flatbuffer_Model160, ToplevelGroup)
// {
//     const auto &group = *model160->group();
//     CheckGroup(group, "mppt", SunspecGroupTypeType_kGroup, 1, "", 9, 1);
//     POINTERS_EQUAL(nullptr, group.count_point_id());
// }

// TEST(Flatbuffer_Model160, Sub_Group_Module)
// {
//     const auto &subGroup = *model160->group()->groups()->Get(0);
//     CheckGroup(subGroup, "module", SunspecGroupTypeType_kGroup, 0, "N", 10, 0);
// }

// TEST(Flatbuffer_Model160, Sub_Group_Module_POINT_ID)
// {
//     const auto &point = *model160->group()->groups()->Get(0)->points()->Get(0);

//     CheckPoint(point, "ID", SunspecPointDataType_Uint16, 1, "", 1, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Input ID");
//     POINTERS_EQUAL(nullptr, point.data());

//     POINTERS_EQUAL(nullptr, point.count_point_id());
//     POINTERS_EQUAL(nullptr, point.sf_id());
//     POINTERS_EQUAL(nullptr, point.units());
// }

// TEST(Flatbuffer_Model160, Sub_Group_Module_POINT_IDStr)
// {
//     const auto &point = *model160->group()->groups()->Get(0)->points()->Get(1);
//     CheckPoint(point, "IDStr", SunspecPointDataType_Stringx, 1, "", 8, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kO, "Input ID String");
//     CHECK_EQUAL("", FormatSunspecPointDefToString(point));
//     POINTERS_EQUAL(nullptr, point.count_point_id());
//     POINTERS_EQUAL(nullptr, point.sf_id());
//     POINTERS_EQUAL(nullptr, point.units());
// }