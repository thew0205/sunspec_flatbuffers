#include <stdio.h>

#include <iostream>
#include <string>
#include <stdint.h>
#include <iostream>

#include "sunspec_adapter.h"

#include "sunspec_adapter.h"

#include "model_definitions.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"
#include "reader/sunspec_model_reader.h"

#include "fake_modbus_master.h"
#include "reader/sunspec_device_reader.h"

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

TEST_GROUP(Sunspec_Model_Reader_Model1)
{
    const SunspecModelDef *modelDef = nullptr;

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
    SunspecModelReader model{*modelDef, nullptr, 0, *(SunspecDeviceReader *)nullptr};
    LONGS_EQUAL(0, model.registerLength());
}

TEST(Sunspec_Model_Reader_Model1, ReadModel1_After_Point_Init)
{
    SunspecModelReader model{*modelDef, nullptr, 0, *(SunspecDeviceReader *)nullptr};
    model.initPoints();
    LONGS_EQUAL(68, model.registerLength());
    auto &group = model.topLevelGroupPoint();
    LONGS_EQUAL(9, group.pointLength());
    LONGS_EQUAL(0, group.groupLength());
    LONGS_EQUAL(68, group.registerLength());
}

TEST(Sunspec_Model_Reader_Model1, ReadModel1_After_Group_Init)
{
    SunspecModelReader model(*modelDef, nullptr, 0, *(SunspecDeviceReader *)nullptr);
    model.initPoints();
    model.initGroups(1000);
    auto &group = model.topLevelGroupPoint();
    LONGS_EQUAL(9, group.pointLength());
    LONGS_EQUAL(0, group.groupLength());
    LONGS_EQUAL(68, group.registerLength());
}

TEST(Sunspec_Model_Reader_Model1, Get_Point)
{
    SunspecModelReader model(*modelDef, nullptr, 0, *(SunspecDeviceReader *)nullptr);
    model.initPoints();
    model.initGroups(1000);
    CHECK(nullptr != model.getPoint("ID"));
    CHECK(nullptr != model.getPoint("L"));
    CHECK(nullptr != model.getPoint("DA"));
    CHECK(nullptr == model.getPoint("da"));
}

TEST(Sunspec_Model_Reader_Model1, Get_Group)
{
    SunspecModelReader model(*modelDef, nullptr, 0, *(SunspecDeviceReader *)nullptr);
    model.initPoints();
    model.initGroups(1000);
    CHECK(nullptr == model.getGroup("ID"));
    CHECK(nullptr == model.getGroup("L"));
    CHECK(nullptr == model.getGroup("DA"));
    CHECK(nullptr == model.getGroup("da"));
}

TEST_GROUP(Sunspec_Model_Reader_Model160)
{
    const SunspecModelDef *modelDef = nullptr;
    uint16_t buffer[50] = {
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
    SunspecModelReader model{*modelDef, buffer, 0, *(SunspecDeviceReader *)nullptr};
    model.initPoints();
    model.initGroups(1000);
    auto &group = model.topLevelGroupPoint();
    LONGS_EQUAL(9, group.pointLength());
    LONGS_EQUAL(2, group.groupLength());
    LONGS_EQUAL(50, group.registerLength());
}

TEST(Sunspec_Model_Reader_Model160, Get_Point)
{
    SunspecModelReader model{*modelDef, buffer, 0, *(SunspecDeviceReader *)nullptr};
    model.initPoints();
    model.initGroups(1000);
    CHECK(nullptr != model.getPoint("ID"));
    CHECK(nullptr != model.getPoint("L"));
    CHECK(nullptr != model.getPoint("N"));
    CHECK(nullptr == model.getPoint("DA"));
    CHECK(nullptr == model.getPoint("da"));
}

TEST(Sunspec_Model_Reader_Model160, Get_Group)
{

    SunspecModelReader model{*modelDef, buffer, 0, *(SunspecDeviceReader *)nullptr};
    model.initPoints();
    model.initGroups(1000);
    CHECK(nullptr != model.getGroup("module"));
    CHECK(nullptr == model.getGroup("L"));
    CHECK(nullptr == model.getGroup("DA"));
    CHECK(nullptr == model.getGroup("da"));
}

TEST_GROUP(Sunspec_Model1_Reader_Read)
{

    uint16_t buffer[68] = {
        0x1, 0x42, 0x4672, 0x6f6e, 0x6975, 0x7300, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4652, 0x4f4e, 0x4955, 0x5320, 0x4563, 0x6f20, 0x3237, 0x2e30, 0x2d33, 0x2d53, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x332e, 0x3237, 0x2e31, 0x2d33, 0x0, 0x0, 0x0, 0x0, 0x302e, 0x332e, 0x3238, 0x2e30, 0x0, 0x0, 0x0, 0x0, 0x3332, 0x3039, 0x3137, 0x3937, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x8000};
    uint16_t modelBuffer[68];

    FakeModbusMaster client{};

    SunspecDeviceReader device{1, client, 0};
    const SunspecModelDef *modelDef = nullptr;

    void setup()
    {
        memset(modelBuffer, 0, sizeof(modelBuffer));
        modelDef = GetSunspecModelDef(modelDefinition1);
        client.setFakeBuffer(buffer, sizeof(buffer) / sizeof(buffer[0]));
    }
};

TEST(Sunspec_Model1_Reader_Read, ReadModel1_Before_Read)
{
    SunspecModelReader model{*modelDef, modelBuffer, 0, device};
    model.initPoints();
    model.initGroups(1000);
    LONGS_EQUAL(0, model.address());
    LONGS_EQUAL(68, model.registerLength());
    LONGS_EQUAL(0, model.getPoint("ID")->valueAsUint16());
    LONGS_EQUAL(0, model.getPoint("L")->valueAsUint16());
    LONGS_EQUAL(0, model.getPoint("DA")->valueAsUint16());
    CHECK_EQUAL("", model.getPoint("Mn")->valueAsString());
}

TEST(Sunspec_Model1_Reader_Read, ReadModel1_After_Read)
{
    SunspecModelReader model{*modelDef, modelBuffer, 0, device};
    model.initPoints();
    model.initGroups(1000);
    model.read();
    LONGS_EQUAL(0, model.address());
    LONGS_EQUAL(68, model.registerLength());
    LONGS_EQUAL(1, model.getPoint("ID")->valueAsUint16());
    LONGS_EQUAL(66, model.getPoint("L")->valueAsUint16());
    LONGS_EQUAL(1, model.getPoint("DA")->valueAsUint16());
}

TEST_GROUP(Sunspec_Model160_Reader_Read)
{
    uint16_t buffer[50] = {
        0xa0, 0x30, 0xfffe, 0xfffe, 0x0, 0x0, 0x0, 0x0, 0x2, 0xffff, 0x1, 0x5374, 0x7269, 0x6e67, 0x2031, 0x0, 0x0, 0x0, 0x0, 0x981, 0xf17c, 0x3ac0, 0x179, 0xbf84, 0x3001, 0x3575, 0x8000, 0x4, 0xffff, 0xffff, 0x2, 0x5374, 0x7269, 0x6e67, 0x2032, 0x0, 0x0, 0x0, 0x0, 0x564, 0xf17c, 0x2153, 0xdb, 0xf339, 0x3001, 0x3575, 0x8000, 0x4, 0xffff};
    uint16_t modelBuffer[50] = {
        0xa0, 0x30, 0xfffe, 0xfffe, 0x0, 0x0, 0x0, 0x0, 0x2, 0xffff, 0x1, 0x5374, 0x7269, 0x6e67, 0x2031, 0x0, 0x0, 0x0, 0x0, 0x981, 0xf17c, 0x3ac0, 0x179, 0xbf84, 0x3001, 0x3575, 0x8000, 0x4, 0xffff, 0xffff, 0x2, 0x5374, 0x7269, 0x6e67, 0x2032, 0x0, 0x0, 0x0, 0x0, 0x564, 0xf17c, 0x2153, 0xdb, 0xf339, 0x3001, 0x3575, 0x8000, 0x4, 0xffff};

    FakeModbusMaster client{};

    SunspecDeviceReader device{1, client, 0};
    const SunspecModelDef *modelDef = nullptr;

    void setup()
    {
        modelDef = GetSunspecModelDef(modelDefinition160);
        client.setFakeBuffer(buffer, sizeof(buffer) / sizeof(buffer[0]));
    }
};

TEST(Sunspec_Model160_Reader_Read, ReadModel1_Before_Read)
{
    SunspecModelReader model{*modelDef, modelBuffer, 0, device};
    model.initPoints();
    model.initGroups(1000);
    memset(modelBuffer, 0, sizeof(modelBuffer));
    LONGS_EQUAL(0, model.address());
    LONGS_EQUAL(50, model.registerLength());
    LONGS_EQUAL(0, model.getPoint("ID")->valueAsUint16());
    LONGS_EQUAL(0, model.getPoint("L")->valueAsUint16());
    LONGS_EQUAL(0, model.getPoint("N")->valueAsUint16());
}

TEST(Sunspec_Model160_Reader_Read, ReadModel1_After_Read)
{
    SunspecModelReader model{*modelDef, modelBuffer, 0, device};
    model.initPoints();
    model.initGroups(1000);
    memset(modelBuffer, 0, sizeof(modelBuffer));
    model.read();
    LONGS_EQUAL(0, model.address());
    LONGS_EQUAL(50, model.registerLength());
    LONGS_EQUAL(160, model.getPoint("ID")->valueAsUint16());
    LONGS_EQUAL(48, model.getPoint("L")->valueAsUint16());
    LONGS_EQUAL(2, model.getPoint("N")->valueAsUint16());
}