#include <stdio.h>

#include <iostream>
#include <string>
#include <stdint.h>
#include <iostream>

#include "sunspec_model_definition_generated.h"
#include "sunspec.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"
#include "writer/sunspec_device_writer.h"
#include "ModbusRTUSlave.h"
#define lowByte(w) ((uint8_t)((w) & 0xff))
#define highByte(w) ((uint8_t)((w) >> 8))
using std::cout;
using std::endl;
using std::string;
extern unsigned char modelDefinition1[];
class Stream
{
};

class MockModbusWriter : public ModbusRTUSlave
{

    Stream stream;

public:
    MockModbusWriter() : ModbusRTUSlave{stream, 0, 0} {}

    uint16_t getValueHoldingRegister(uint16_t offset)
    {

        return _holdingRegisters[offset];
    }

    uint16_t getNumHoldingRegisters()
    {
        return _numHoldingRegisters;
    }
};

TEST_GROUP(Sunspec_Set_Value)
{
    Stream stream{};
    MockModbusWriter client{};
    SunspecDeviceWriter writer{
        1, client, 40000};
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(Sunspec_Set_Value, TestMemoryInitialisation_AfterSetBuffer_1_113)
{
    writer.initAll({SunspecModelList_kModel1, SunspecModelList_kModel113});

    SunspecPointFunction functMn{.str = {.function = [](void *param) -> string
                                         { return "Matthew"; }}};

    writer.getModel(SunspecModelList_kModel1)->getTopLevelPoint("Mn")->setPointFunction(functMn);
    writer.getModel(SunspecModelList_kModel1)->getTopLevelPoint("Opt")->setPointFunction({.str = {.function = [](void *param) -> string
                                                                                                  { return "Busoye Tolulope Matthew"; }}});
    writer.getModel(SunspecModelList_kModel1)->getTopLevelPoint("DA")->setPointFunction({.uint16 = {.function = [](void *param) -> uint16_t
                                                                                                    { return 0XDEAD; }}});

    writer.setBuffer();

    CHECK_EQUAL("Matthew", writer.getModel(SunspecModelList_kModel1)->getTopLevelPoint("Mn")->getValueAsString());
    STRCMP_EQUAL("Busoye Tolulope", writer.getModel(SunspecModelList_kModel1)->getTopLevelPoint("Opt")->getValueAsString().c_str());
    LONGS_EQUAL(0XDEAD, writer.getModel(SunspecModelList_kModel1)->getTopLevelPoint("DA")->getValueAsUint16());

    LONGS_EQUAL(0xDEAD, client.getValueHoldingRegister(writer.getModel(SunspecModelList_kModel1)->getTopLevelPoint("DA")->relativeAddress()));

    LONGS_EQUAL(0x7FC0, client.getValueHoldingRegister(writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("AphA")->relativeAddress()));
    LONGS_EQUAL(0x0000, client.getValueHoldingRegister(writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("AphA")->relativeAddress() + 1));
    LONGS_EQUAL(0xFFFF, client.getValueHoldingRegister(writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("St")->relativeAddress()));
    LONGS_EQUAL(0xFFFF, client.getValueHoldingRegister(writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("Evt1")->relativeAddress()));
    LONGS_EQUAL(0xFFFF, client.getValueHoldingRegister(writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("Evt1")->relativeAddress() + 1));
}

TEST(Sunspec_Set_Value, TestMemoryInitialisation_AfterSetBuffer_1_160)
{
    writer.initTopLevel({SunspecModelList_kModel1, SunspecModelList_kModel160});
    writer.getModel(SunspecModelList_kModel160)->getTopLevelPoint("N")->setPointFunction({.uint16 = {.function = [](void *param) -> uint16_t
                                                                                                     { return 2; }}});

    writer.initSubLevels();
    writer.setBuffer();

    LONGS_EQUAL(2, writer.getModel(SunspecModelList_kModel160)->getTopLevelPoint("N")->getValueAsUint16());

    LONGS_EQUAL(0x5375, client.getValueHoldingRegister(0));
    LONGS_EQUAL(0x6E53, client.getValueHoldingRegister(1));
    LONGS_EQUAL(2, client.getValueHoldingRegister(writer.getModel(SunspecModelList_kModel160)->getTopLevelPoint("N")->relativeAddress()));
    LONGS_EQUAL(0x8000, client.getValueHoldingRegister(writer.getModel(SunspecModelList_kModel160)->getTopLevelPoint("DCA_SF")->relativeAddress()));
    LONGS_EQUAL(0x8000, client.getValueHoldingRegister(writer.getModel(SunspecModelList_kModel160)->getTopLevelPoint("DCV_SF")->relativeAddress()));
}

TEST(Sunspec_Set_Value, TestMemoryInitialisation_AfterSetBuffer_1_160_No_Count_set)
{
    writer.initTopLevel({SunspecModelList_kModel1, SunspecModelList_kModel160});

    writer.initSubLevels();
    writer.setBuffer();

    LONGS_EQUAL(0XFFFF, writer.getModel(SunspecModelList_kModel160)->getTopLevelPoint("N")->getValueAsUint16());
}