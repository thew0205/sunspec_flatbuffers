#include <stdio.h>

#include <iostream>
#include <string>
#include <stdint.h>
#include <iostream>

#include "sunspec_adapter.h"

#include "model_definitions.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"
#include "reader/sunspec_group_reader.h"
#include "reader/sunspec_model_reader.h"
#include "reader/sunspec_device_reader.h"
#include <fake_modbus_master.h>

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
        if (FormatStringToString(points->Get(i)->id()) == id)
        {
            return &point;
        }
    }
    return nullptr;
}

TEST_GROUP(Sunspec_Group_Reader_Model1)
{
    const SunspecGroupDef *groupDef = nullptr;

    void setup()
    {
        groupDef = GetSunspecModelDef(modelDefinition1)->group();
    }

    void teardown()
    {
    }
};

TEST(Sunspec_Group_Reader_Model1, ReadModel1_Init)
{
    CHECK(groupDef != nullptr);
    SunspecGroupReader group{*groupDef, nullptr, (SunspecModelReader *)nullptr};
    LONGS_EQUAL(0, group.pointLength());
    LONGS_EQUAL(0, group.groupLength());
    LONGS_EQUAL(0, group.registerLength());
}

TEST(Sunspec_Group_Reader_Model1, ReadModel1_After_TopLevel_Init)
{
    CHECK(groupDef != nullptr);
    SunspecGroupReader group{*groupDef, nullptr, (SunspecModelReader *)nullptr};
    group.initPoints();
    LONGS_EQUAL(9, group.pointLength());
    LONGS_EQUAL(0, group.groupLength());
    LONGS_EQUAL(68, group.registerLength());
}

TEST(Sunspec_Group_Reader_Model1, ReadModel1_After_SubLevel_Init)
{
    CHECK(groupDef != nullptr);

    SunspecGroupReader group{*groupDef, nullptr, (SunspecModelReader *)nullptr};
    group.initPoints();
    group.initGroups(10000);
    LONGS_EQUAL(9, group.pointLength());
    LONGS_EQUAL(0, group.groupLength());
    LONGS_EQUAL(68, group.registerLength());
}

TEST(Sunspec_Group_Reader_Model1, ReadModel1_After_SubLevel_Init_Old)
{
    CHECK(groupDef != nullptr);

    SunspecGroupReader group{*groupDef, nullptr, (SunspecModelReader *)nullptr};
    group.initPoints();
    group.initGroups(67);
    LONGS_EQUAL(9, group.pointLength());
    LONGS_EQUAL(0, group.groupLength());
    LONGS_EQUAL(67, group.registerLength());
}

TEST_GROUP(Sunspec_Group_Reader_Model160)
{
    const SunspecGroupDef *groupDef = nullptr;
    void setup()
    {
        groupDef = GetSunspecModelDef(modelDefinition160)->group();
    }

    void teardown()
    {
    }
};

IGNORE_TEST(Sunspec_Group_Reader_Model160, ReadModel1_After_SubLevel_Init)
{
    CHECK(groupDef != nullptr);
    SunspecModelReader model{*GetSunspecModelDef(modelDefinition160),
                             nullptr, 0, *(SunspecDeviceReader *)nullptr};

    SunspecGroupReader group{*groupDef, nullptr, (SunspecModelReader *)&model};
    group.initPoints();
    group.initGroups(1000);
    LONGS_EQUAL(9, group.pointLength());
    LONGS_EQUAL(2, group.groupLength());
    LONGS_EQUAL(68, group.registerLength());
}
