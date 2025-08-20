#include <stdio.h>

#include <iostream>
#include <string>
#include <stdint.h>
#include <iostream>

#include "sunspec_model_definition_generated.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"

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

    void CheckPoint(const SunspecPointDef &pointDef, const string &expectedId, SunspecPointData dataType, uint16_t count, const string &count_point_id, uint16_t size, uint16_t sf, const string &sf_id, const string &units, SunspecPointAccessType access, SunspecPointMandatoryType mandatory, const string &label)
    {
        CHECK_EQUAL(expectedId, string(pointDef.id()->c_str()));
        ENUMS_EQUAL_INT(dataType, pointDef.data_type());
        LONGS_EQUAL(count, pointDef.count());
        // printf("%d\n", pointDef.count_point_id()->size());
        // printf("%d\n", pointDef.count_point_id()->size());
        // printf("%d\n", pointDef.count_point_id()->size());
        // printf("%d\n", pointDef.count_point_id()->size());
        // printf("%d\n", pointDef.count_point_id()->size());
        // printf("%d\n", pointDef.count_point_id()->size());
        // printf("%d\n", pointDef.count_point_id()->size());
        // printf("%d\n", pointDef.count_point_id()->size());
        // printf("%d\n", pointDef.count_point_id()->size());
        // printf("%d\n", pointDef.count_point_id()->size());
        volatile uint32_t si = pointDef.count_point_id()->size();
        cout << pointDef.count_point_id()->size() << endl;
        CHECK_EQUAL(count_point_id, string(pointDef.count_point_id()->c_str()));
        LONGS_EQUAL(size, pointDef.size());
        LONGS_EQUAL(sf, pointDef.sf());
        CHECK_EQUAL(sf_id, string(pointDef.sf_id()->c_str()));
        CHECK_EQUAL(units, string(pointDef.units()->c_str()));
        ENUMS_EQUAL_INT(access, SunspecPointAccessType_kR);
        ENUMS_EQUAL_INT(mandatory, SunspecPointMandatoryType_kM);
        CHECK_EQUAL(label, string(pointDef.label()->c_str()));
    }
};

TEST(Flatbuffer_Model1, ID)
{
    LONGS_EQUAL(SunspecModelList_kModel1, model1->id());
}

TEST(Flatbuffer_Model1, POINT_ID)
{
    const auto &points = *model1->group()->points();
    const auto &point = *points.Get(0);
    CheckPoint(point, "ID", SunspecPointData_kUint16, 1, "", 1, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model ID");
    LONGS_EQUAL(1, point.data_as_kUint16()->value());
}

TEST(Flatbuffer_Model1, POINT_L)
{
    const auto &points = *model1->group()->points();
    const auto &point = *points.Get(1);
    CheckPoint(point, "L", SunspecPointData_kUint16, 1, "", 1, 0, "", "", SunspecPointAccessType_kR, SunspecPointMandatoryType_kM, "Model Length");
    cout << point.data_as_kUint16() << endl;
    LONGS_EQUAL(65535, point.data_as_kUint16()->value());
}