#include <stdio.h>

#include <iostream>
#include <string>
#include <stdint.h>
#include <iostream>

#include "sunspec_model_definition_generated.h"
#include "sunspec.h"
#include "model_definitions.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"
#include "reader/sunspec_point_reader.h"

#define lowByte(w) ((uint8_t)((w) & 0xff))
#define highByte(w) ((uint8_t)((w) >> 8))
using std::cout;
using std::endl;
using std::string;

const SunspecPointDef *findPointById(const SunspecGroupDef *group, const string &id)
{
    auto points = group->points();
    for (unsigned int i = 0; i < points->size(); ++i)
    {
        const auto &point = *points->Get(i);
        if (FlatbufferStringToString(points->Get(i)->id()) == id)
        {
            return &point;
        }
    }
    return nullptr;
}

TEST_GROUP(Sunspec_Point_Reader_Model1)
{
    const SunspecGroupDef *model1;

    void setup()
    {
        model1 = GetSunspecModelDef(modelDefinition1)->group();
    }

    void teardown()
    {
    }
};

TEST(Sunspec_Point_Reader_Model1, Point_Uint16)
{
    uint16_t buf[1] = {0x1234};
    const SunspecPointDef *pointDef = findPointById(model1, "ID");
    SunspecPointReader point = SunspecPointReader(*pointDef, buf, *(SunspecGroupReader *)nullptr);
    ENUMS_EQUAL_INT(SunspecPointData_kUint16, point.def().data_type());
    LONGS_EQUAL(1, point.size());
    LONGS_EQUAL(0x1234, point.valueAsUint16());
    STRCMP_EQUAL("4660", point.getValueAsString().c_str());
}

TEST(Sunspec_Point_Reader_Model1, Point_String_Odd)
{
    uint8_t buf[] = {'u', 'b', 'o', 's', 'e', 'y', '\0'};
    const SunspecPointDef *pointDef = findPointById(model1, "Mn");
    SunspecPointReader point = SunspecPointReader(*pointDef, (uint16_t *)buf, *(SunspecGroupReader *)nullptr);
    ENUMS_EQUAL_INT(SunspecPointData_kStringx, point.def().data_type());
    LONGS_EQUAL(16, point.size());

    STRCMP_EQUAL("busoye", point.valueAsString().c_str());
    STRCMP_EQUAL("busoye", point.getValueAsString().c_str());
}

TEST(Sunspec_Point_Reader_Model1, Point_String_Even)
{
    uint8_t buf[] = {'a', 'M', 't', 't', 'e', 'h', '\0', 'w'};
    const SunspecPointDef *pointDef = findPointById(model1, "Opt");
    SunspecPointReader point = SunspecPointReader(*pointDef, (uint16_t *)buf, *(SunspecGroupReader *)nullptr);
    ENUMS_EQUAL_INT(SunspecPointData_kStringx, point.def().data_type());
    LONGS_EQUAL(8, point.size());

    STRCMP_EQUAL("Matthew", point.valueAsString().c_str());
    STRCMP_EQUAL("Matthew", point.getValueAsString().c_str());
}

TEST(Sunspec_Point_Reader_Model1, Point_Pad16)
{
    uint16_t buf[1] = {0x8000};
    const SunspecPointDef *pointDef = findPointById(model1, "Pad");
    SunspecPointReader point = SunspecPointReader(*pointDef, buf, *(SunspecGroupReader *)nullptr);
    ENUMS_EQUAL_INT(SunspecPointData_kPad16, point.def().data_type());
    LONGS_EQUAL(1, point.size());

    LONGS_EQUAL(0x8000, point.valueAsPad16());
    STRCMP_EQUAL("32768", point.getValueAsString().c_str());
}