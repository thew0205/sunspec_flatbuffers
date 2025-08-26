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

void TestHoldingRegisterBigEndian(MockModbusWriter &slave, uint16_t offset, uint8_t expectedByte0, uint8_t expectedByte1)
{

    uint16_t value = slave.getValueHoldingRegister(offset); // Get the value from the holding register in little endian
    uint8_t byte0 = lowByte(value);
    uint8_t byte1 = highByte(value);

    LONGS_EQUAL(expectedByte0, byte0);
    LONGS_EQUAL(expectedByte1, byte1);
}
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

    writer.getModel(SunspecModelList_kModel1)->getTopLevelPoint("Mn")->setValueFunction({.str = []() -> string
                                                                                         { return "Matthew"; }});
    writer.getModel(SunspecModelList_kModel1)->getTopLevelPoint("Opt")->setValueFunction({.str = []() -> string
                                                                                          { return "Busoye Tolulope Matthew"; }});
    writer.getModel(SunspecModelList_kModel1)->getTopLevelPoint("DA")->setValueFunction({.uint16 = []() -> uint16_t
                                                                                         { return 0XDEAD; }});

    writer.setBuffer();

    CHECK_EQUAL("Matthew", writer.getModel(SunspecModelList_kModel1)->getTopLevelPoint("Mn")->getValueAsString());
    STRCMP_EQUAL("Busoye Tolulope", writer.getModel(SunspecModelList_kModel1)->getTopLevelPoint("Opt")->getValueAsString().c_str());
    LONGS_EQUAL(0XDEAD, writer.getModel(SunspecModelList_kModel1)->getTopLevelPoint("DA")->getValueAsUint16());

    TestHoldingRegisterBigEndian(client, writer.getModel(SunspecModelList_kModel1)->getTopLevelPoint("DA")->relativeAddress(), 0xDE, 0xAD);

    TestHoldingRegisterBigEndian(client, writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("AphA")->relativeAddress(), 0x7F, 0xC0);
    TestHoldingRegisterBigEndian(client, writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("AphA")->relativeAddress() + 1, 0x00, 0x00);

    TestHoldingRegisterBigEndian(client, writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("St")->relativeAddress(), 0xFF, 0xFF);

    TestHoldingRegisterBigEndian(client, writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("Evt1")->relativeAddress(), 0xFF, 0xFF);

    TestHoldingRegisterBigEndian(client, writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("Evt1")->relativeAddress() + 1, 0xFF, 0xFF);
}

TEST(Sunspec_Set_Value, TestMemoryInitialisation_AfterSetBuffer_1_160)
{
    writer.initTopLevel({SunspecModelList_kModel1, SunspecModelList_kModel160});
    writer.getModel(SunspecModelList_kModel160)->getTopLevelPoint("N")->setValueFunction({.uint16 = []() -> uint16_t
                                                                                          { return 2; }});

    writer.initSubLevels();
    writer.setBuffer();

    LONGS_EQUAL(2, writer.getModel(SunspecModelList_kModel160)->getTopLevelPoint("N")->getValueAsUint16());

    TestHoldingRegisterBigEndian(client, writer.getModel(SunspecModelList_kModel160)->getTopLevelPoint("N")->relativeAddress(), 0x00, 2);

    TestHoldingRegisterBigEndian(client, writer.getModel(SunspecModelList_kModel160)->getTopLevelPoint("DCA_SF")->relativeAddress(), 0x80, 00);
    TestHoldingRegisterBigEndian(client, writer.getModel(SunspecModelList_kModel160)->getTopLevelPoint("DCV_SF")->relativeAddress(), 0x80, 00);

}

TEST(Sunspec_Set_Value, TestMemoryInitialisation_AfterSetBuffer_1_160_No_Count_set)
{
    writer.initTopLevel({SunspecModelList_kModel1, SunspecModelList_kModel160});

    writer.initSubLevels();
    writer.setBuffer();

    LONGS_EQUAL(0XFFFF, writer.getModel(SunspecModelList_kModel160)->getTopLevelPoint("N")->getValueAsUint16());
}