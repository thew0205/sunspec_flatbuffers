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
#include "reader/sunspec_model_reader.h"

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

TEST_GROUP(Sunspec_Model_Reader_Model1)
{
    const SunspecModelDef *modelDef;
    const uint16_t buffer[68] = {
        0x1, 0x41, 0x4672, 0x6f6e, 0x6975, 0x7300, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4652, 0x4f4e, 0x4955, 0x5320, 0x4563, 0x6f20, 0x3237, 0x2e30, 0x2d33, 0x2d53, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x332e, 0x3237, 0x2e31, 0x2d33, 0x0, 0x0, 0x0, 0x0, 0x302e, 0x332e, 0x3238, 0x2e30, 0x0, 0x0, 0x0, 0x0, 0x3332, 0x3039, 0x3137, 0x3937, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x8000};
    void setup()
    {
        modelDef = GetSunspecModelDef(modelDefinition1);
    }

    void teardown()
    {
    }
};

TEST(Sunspec_Model_Reader_Model1, ReadModel1_Init)
{
    CHECK(modelDef != nullptr);
    SunspecModelReader model{*modelDef, buffer, 0, *(SunspecDeviceReader *)nullptr};
    LONGS_EQUAL(0, model.registerLength());
}

TEST(Sunspec_Model_Reader_Model1, ReadModel1_After_Point_Init)
{
    CHECK(modelDef != nullptr);
    SunspecModelReader model{*modelDef, buffer, 0, *(SunspecDeviceReader *)nullptr};
    model.initPoints();
    LONGS_EQUAL(68, model.registerLength());
    auto &group = model.topLevelGroupPoint();
    LONGS_EQUAL(9, group.pointLength());
    LONGS_EQUAL(0, group.groupLength());
    LONGS_EQUAL(68, group.registerLength());
}

TEST(Sunspec_Model_Reader_Model1, ReadModel1_After_Group_Init)
{
    CHECK(modelDef != nullptr);
    SunspecModelReader model(*modelDef, buffer, 0, *(SunspecDeviceReader *)nullptr);
    model.initPoints();
    model.initGroups(1000);
    auto &group = model.topLevelGroupPoint();
    LONGS_EQUAL(9, group.pointLength());
    LONGS_EQUAL(0, group.groupLength());
    LONGS_EQUAL(68, group.registerLength());
}

TEST_GROUP(Sunspec_Model_Reader_Model160)
{
    const SunspecModelDef *modelDef;
    const uint16_t buffer[68] = {
        0xa0, 0x30, 0xfffe, 0xfffe, 0x0, 0x0, 0x0, 0x0, 0x2, 0xffff, 0x1, 0x5374, 0x7269, 0x6e67, 0x2031, 0x0, 0x0, 0x0, 0x0, 0x981, 0xf17c, 0x3ac0, 0x179, 0xbf84, 0x3001, 0x3575, 0x8000, 0x4, 0xffff, 0xffff, 0x2, 0x5374, 0x7269, 0x6e67, 0x2032, 0x0, 0x0, 0x0, 0x0, 0x564, 0xf17c, 0x2153, 0xdb, 0xf339, 0x3001, 0x3575, 0x8000, 0x4, 0xffff};
    void setup()
    {
        modelDef = GetSunspecModelDef(modelDefinition160);
    }

    void teardown()
    {
    }
};

TEST(Sunspec_Model_Reader_Model160, ReadModel1_After_Group_Init)
{

    CHECK(modelDef != nullptr);
    SunspecModelReader model{*modelDef, buffer,0, *(SunspecDeviceReader *)nullptr};
    model.initPoints();
    model.initGroups(1000);
    auto &group = model.topLevelGroupPoint();
    LONGS_EQUAL(9, group.pointLength());
    LONGS_EQUAL(2, group.groupLength());
    LONGS_EQUAL(50, group.registerLength());
}
