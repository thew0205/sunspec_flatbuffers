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

TEST_GROUP(Sunspec_Init)
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

TEST(Sunspec_Init, TestMemoryInitialisation_AfterSetBuffer_1_113)
{
    writer.initAll({1, 113});

    LONGS_EQUAL(0x5375, client.getValueHoldingRegister(0));
    LONGS_EQUAL(0x6E53, client.getValueHoldingRegister(1));

    LONGS_EQUAL(0x0001, client.getValueHoldingRegister(2));
    LONGS_EQUAL(66, client.getValueHoldingRegister(3));
    // LONGS_EQUAL(0x8000, client.getValueHoldingRegister(69));

    LONGS_EQUAL(113, client.getValueHoldingRegister(70));
    LONGS_EQUAL(60, client.getValueHoldingRegister(71));

    LONGS_EQUAL(0xFFFF, client.getValueHoldingRegister(132));
    LONGS_EQUAL(0x0000, client.getValueHoldingRegister(133));

    LONGS_EQUAL(134, client.getNumHoldingRegisters());

    LONGS_EQUAL(2, writer.modelCount());
}

TEST(Sunspec_Init, TestMemoryInitialisation_AfterSetBuffer_1_160)
{
    writer.initTopLevel({1, 160});
    SunspecPointFunction funct{.uint16 = {.function = [](void *param) -> uint16_t
                                          { return 2; }}};

    writer.getModel(160)->getPoint("N")->setPointFunction(funct);

    writer.initSubLevels();
    writer.setAllValueToModbusBuffer();

    LONGS_EQUAL(0x5375, client.getValueHoldingRegister(0));
    LONGS_EQUAL(0x6E53, client.getValueHoldingRegister(1));

    LONGS_EQUAL(0x0001, client.getValueHoldingRegister(2));
    LONGS_EQUAL(66, client.getValueHoldingRegister(3));
    // LONGS_EQUAL(0x8000, client.getValueHoldingRegister(69));

    LONGS_EQUAL(160, client.getValueHoldingRegister(70));
    LONGS_EQUAL(48, client.getValueHoldingRegister(71));
    LONGS_EQUAL(2, client.getValueHoldingRegister(78));

    LONGS_EQUAL(0xFFFF, client.getValueHoldingRegister(120));
    LONGS_EQUAL(0x0000, client.getValueHoldingRegister(121));

    LONGS_EQUAL(122, client.getNumHoldingRegisters());

    LONGS_EQUAL(2, writer.modelCount());
}

TEST(Sunspec_Init, TestMemoryInitialisation_AfterSetBuffer_1_160_No_Count)
{
    writer.initTopLevel({1, 160});

    writer.initSubLevels();
    writer.setAllValueToModbusBuffer();

    LONGS_EQUAL(0x5375, client.getValueHoldingRegister(0));
    LONGS_EQUAL(0x6E53, client.getValueHoldingRegister(1));

    LONGS_EQUAL(0x0001, client.getValueHoldingRegister(2));
    LONGS_EQUAL(66, client.getValueHoldingRegister(3));
    // LONGS_EQUAL(0x8000, client.getValueHoldingRegister(69));

    LONGS_EQUAL(160, client.getValueHoldingRegister(70));
    LONGS_EQUAL(8, client.getValueHoldingRegister(71));
    // LONGS_EQUAL(0xFFFF, client.getValueHoldingRegister(78));

    LONGS_EQUAL(0xFFFF, client.getValueHoldingRegister(80));
    LONGS_EQUAL(0x0000, client.getValueHoldingRegister(81));

    LONGS_EQUAL(82, client.getNumHoldingRegisters());

    LONGS_EQUAL(2, writer.modelCount());
}
