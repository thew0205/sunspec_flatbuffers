#include <stdio.h>

#include <iostream>
#include <string>
#include <stdint.h>
#include <iostream>

#include "sunspec_adapter.h"

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
    SunspecDeviceWriter writer{client};
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(Sunspec_Set_Value, TestMemoryInitialisation_AfterSetBuffer_1_113)
{
    writer.initAll({1, 113});
    SunspecPointFunction functMn{.str = {.function = [](void *param) -> string
                                         { return "Matthew"; }}};

    writer.getModel(1)->getPoint("Mn")->setPointFunction(functMn);
    writer.getModel(1)->getPoint("Opt")->setPointFunction({.str = {.function = [](void *param) -> string
                                                                                          { return "Busoye Tolulope Matthew"; }}});
    writer.getModel(1)->getPoint("DA")->setPointFunction({.uint16 = {.function = [](void *param) -> uint16_t
                                                                                            { return 0xDEAD; }}});

    writer.setAllValueToModbusBuffer();

    CHECK_EQUAL("Matthew", writer.getModel(1)->getPoint("Mn")->getValueAsString());
    STRCMP_EQUAL("Busoye Tolulope", writer.getModel(1)->getPoint("Opt")->getValueAsString().c_str());
    LONGS_EQUAL(0XDEAD, writer.getModel(1)->getPoint("DA")->getValueAsUint16());

    LONGS_EQUAL(0xDEAD, client.getValueHoldingRegister(68));

    LONGS_EQUAL(0x7FC0, client.getValueHoldingRegister(74));
    LONGS_EQUAL(0x0000, client.getValueHoldingRegister(74 + 1));
    LONGS_EQUAL(0xFFFF, client.getValueHoldingRegister(118));
    LONGS_EQUAL(0xFFFF, client.getValueHoldingRegister(120));
    LONGS_EQUAL(0xFFFF, client.getValueHoldingRegister(120 + 1));
}

TEST(Sunspec_Set_Value, TestMemoryInitialisation_AfterSetBuffer_1_160)
{
    writer.initTopLevel({1, 160});
    writer.getModel(160)->getPoint("N")->setPointFunction({.uint16 = {.function = [](void *param) -> uint16_t
                                                                                             { return 7; }}});

    writer.initSubLevels();
    writer.setAllValueToModbusBuffer();

    LONGS_EQUAL(7, writer.getModel(160)->getPoint("N")->getValueAsUint16());

    LONGS_EQUAL(0x5375, client.getValueHoldingRegister(0));
    LONGS_EQUAL(0x6E53, client.getValueHoldingRegister(1));
    LONGS_EQUAL(7, client.getValueHoldingRegister(78));
    LONGS_EQUAL(0x8000, client.getValueHoldingRegister(72));
    LONGS_EQUAL(0x8000, client.getValueHoldingRegister(73));

    POINTERS_EQUAL(&writer, &writer.getModel(1)->device());
    POINTERS_EQUAL(&writer, writer.getModel(1)->getPoint("ID")->getDevice());
    POINTERS_EQUAL(&writer, writer.getModel(1)->topLevelGroup().getDevice());

    POINTERS_EQUAL(&writer, &writer.getModel(160)->device());
    POINTERS_EQUAL(&writer, writer.getModel(160)->getGroup("module")->getDevice());
    POINTERS_EQUAL(&writer, writer.getModel(160)->getGroup("module")->getPoint("ID")->getDevice());
    POINTERS_EQUAL(&writer, writer.getModel(160)->getGroup("module")->getDevice());
}

TEST(Sunspec_Set_Value, TestMemoryInitialisation_AfterSetBuffer_1_160_No_Count_set)
{
    writer.initTopLevel({1, 160});

    writer.initSubLevels();
    writer.setAllValueToModbusBuffer();

    LONGS_EQUAL(0XFFFF, writer.getModel(160)->getPoint("N")->getValueAsUint16());
}