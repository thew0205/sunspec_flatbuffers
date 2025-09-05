#include <stdio.h>

#include <iostream>
#include <string>
#include <stdint.h>
#include <iostream>

#include "sunspec_model_definition_generated.h"
#include "sunspec.h"
#include "model_definitions.h"

#include "modbus_master.h"
#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"
#include "reader/sunspec_device_reader.h"

#define lowByte(w) ((uint8_t)((w) & 0xff))
#define highByte(w) ((uint8_t)((w) >> 8))
using std::cout;
using std::endl;
using std::string;
static const uint16_t buffer[314] = {0x5375, 0x6e53, 0x1, 0x41, 0x4672, 0x6f6e, 0x6975, 0x7300, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4652, 0x4f4e, 0x4955, 0x5320, 0x4563, 0x6f20, 0x3237, 0x2e30, 0x2d33, 0x2d53, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x332e, 0x3237, 0x2e31, 0x2d33, 0x0, 0x0, 0x0, 0x0, 0x302e, 0x332e, 0x3238, 0x2e30, 0x0, 0x0, 0x0, 0x0, 0x3332, 0x3039, 0x3137, 0x3937, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x71, 0x3c, 0x42be, 0x7ae1, 0x41fe, 0x6666, 0x41fd, 0x5c29, 0x41fe, 0x28f5, 0x43cb, 0xe667, 0x43cc, 0x0, 0x43cb, 0x4ccd, 0x436b, 0xb333, 0x436c, 0x199a, 0x436a, 0x0, 0x46af, 0xf000, 0x4247, 0xe147, 0x46af, 0xf10a, 0x4319, 0x0, 0xc2c7, 0xfed2, 0x4c15, 0x6cbc, 0x7fc0, 0x0, 0x7fc0, 0x0, 0x46b8, 0x27ef, 0x7fc0, 0x0, 0x7fc0, 0x0, 0x7fc0, 0x0, 0x7fc0, 0x0, 0x4, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x78, 0x1a, 0x4, 0xa8c, 0x1, 0xa8c, 0x1, 0xa8c, 0x8000, 0x8000, 0xf574, 0x1, 0xea6, 0xfffe, 0xfce0, 0x8000, 0x8000, 0x320, 0xfffd, 0xffff, 0x8000, 0xffff, 0x8000, 0xffff, 0x8000, 0xffff, 0x8000, 0x8000, 0x79, 0x1e, 0xa8c, 0xf0, 0x0, 0xffff, 0xffff, 0xa8c, 0xa8c, 0x8000, 0x8000, 0xf574, 0xffff, 0xfce0, 0x8000, 0x8000, 0x320, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x1, 0x0, 0x0, 0x8000, 0x1, 0x1, 0x8000, 0xfffd, 0x8000, 0x8000, 0x7a, 0x2c, 0x7, 0x0, 0x1, 0x0, 0x0, 0x255, 0xb2f0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8000, 0x8000, 0xffff, 0x8000, 0xffff, 0xffff, 0x0, 0x0, 0x5254, 0x4300, 0x0, 0x0, 0x3001, 0x3574, 0xffff, 0xffff, 0x8000, 0x7b, 0x18, 0x0, 0x0, 0x1, 0x2710, 0x0, 0x0, 0x0, 0x0, 0x3e8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8000, 0x0, 0x0, 0x0, 0x2, 0x0, 0xfffe, 0xfffd, 0x0, 0xa0, 0x30, 0xfffe, 0xfffe, 0x0, 0x0, 0x0, 0x0, 0x2, 0xffff, 0x1, 0x5374, 0x7269, 0x6e67, 0x2031, 0x0, 0x0, 0x0, 0x0, 0x981, 0xf17c, 0x3ac0, 0x179, 0xbf84, 0x3001, 0x3575, 0x8000, 0x4, 0xffff, 0xffff, 0x2, 0x5374, 0x7269, 0x6e67, 0x2032, 0x0, 0x0, 0x0, 0x0, 0x564, 0xf17c, 0x2153, 0xdb, 0xf339, 0x3001, 0x3575, 0x8000, 0x4, 0xffff, 0xffff, 0xffff};
static uint16_t gBufferBaseAddress;
static const uint16_t gBufferSize = sizeof(buffer) / sizeof(buffer[0]);
static const uint16_t *gModbusBuffer = buffer;

TEST_GROUP(Sunspec_Device_Reader_Fronius)
{

    class FakeModbusMaster : public ModbusMaster
    {

        // VIRTUAL_TEST uint8_t readHoldingRegisters(uint8_t slaveId, uint16_t, uint16_t){

        // }
        VIRTUAL_TEST uint8_t readHoldingRegisters(uint16_t u16ReadAddress, uint16_t u16ReadQty)
        {
            _u16ReadAddress = u16ReadAddress;
            _u16ReadQty = u16ReadQty;

            if ((u16ReadAddress > gBufferSize + gBufferBaseAddress) || (u16ReadAddress < gBufferBaseAddress) || (u16ReadQty > gBufferSize))

            {
                return ku8MBIllegalDataAddress;
            }

            int addressOffset = u16ReadAddress - gBufferBaseAddress;
            for (int i = 0; i < u16ReadQty; i++)
            {
                _u16ResponseBuffer[i] = gModbusBuffer[i + addressOffset];
            }
            return ModbusMaster::ku8MBSuccess;
        }
    };

    FakeModbusMaster client{};

    void setup()
    {
        // modelDef = GetSunspecModelDef(modelDefinition1);
    }

    void teardown()
    {
    }

    void setBaseAddress(uint16_t baseAddress)
    {
        gBufferBaseAddress = baseAddress;
    }
};

TEST(Sunspec_Device_Reader_Fronius, Device_ScanAddress_Init_Buffer_Read)
{
    setBaseAddress(40000);
    uint16_t baseAddress = SunspecDeviceReader::kInvalidBaseAddress;
    SunspecDeviceReader device{1, client};
    device.initAllModels({SunspecModelList_kModel1, SunspecModelList_kModel113});
    auto &model1 = device.models()[0];
    LONGS_EQUAL(40002, model1.address());
    LONGS_EQUAL(67, model1.registerLength());
    LONGS_EQUAL(1, model1.getPoint("ID")->valueAsUint16());
    LONGS_EQUAL(65, model1.getPoint("L")->valueAsUint16());

    auto &model113 = device.models()[1];
    LONGS_EQUAL(40069, model113.address());
    LONGS_EQUAL(62, model113.registerLength());

    LONGS_EQUAL(113, model113.getPoint("ID")->valueAsUint16());
    LONGS_EQUAL(60, model113.getPoint("L")->valueAsUint16());
    DOUBLES_EQUAL(240, model113.getPoint("PhVphA")->valueAsFloat32(), 10);
}

TEST(Sunspec_Device_Reader_Fronius, Device_ScanAddress_Read_Buffer)
{
    setBaseAddress(40000);
    uint16_t baseAddress = SunspecDeviceReader::kInvalidBaseAddress;
    SunspecDeviceReader device{1, client};
    device.initAllModels({SunspecModelList_kModel1, SunspecModelList_kModel113});
    device.readBufferFromDevice();
    auto &model1 = device.models()[0];
    LONGS_EQUAL(40002, model1.address());
    LONGS_EQUAL(67, model1.registerLength());
    LONGS_EQUAL(1, model1.getPoint("ID")->valueAsUint16());
    LONGS_EQUAL(65, model1.getPoint("L")->valueAsUint16());

    auto &model113 = device.models()[1];
    LONGS_EQUAL(40069, model113.address());
    LONGS_EQUAL(62, model113.registerLength());

    LONGS_EQUAL(113, model113.getPoint("ID")->valueAsUint16());
    LONGS_EQUAL(60, model113.getPoint("L")->valueAsUint16());
    DOUBLES_EQUAL(240, model113.getPoint("PhVphA")->valueAsFloat32(), 10);
}

TEST(Sunspec_Device_Reader_Fronius, Device_ScanAddress_1_113_160_Init_Buffer_Read)
{
    setBaseAddress(40000);
    uint16_t baseAddress = SunspecDeviceReader::kInvalidBaseAddress;
    SunspecDeviceReader device{1, client};
    device.initAllModels({SunspecModelList_kModel1, SunspecModelList_kModel113, SunspecModelList_kModel160});
    auto &model1 = device.models()[0];
    LONGS_EQUAL(40002, model1.address());
    LONGS_EQUAL(67, model1.registerLength());
    LONGS_EQUAL(1, model1.getPoint("ID")->valueAsUint16());
    LONGS_EQUAL(65, model1.getPoint("L")->valueAsUint16());

    auto &model113 = device.models()[1];
    LONGS_EQUAL(40069, model113.address());
    LONGS_EQUAL(62, model113.registerLength());

    LONGS_EQUAL(113, model113.getPoint("ID")->valueAsUint16());
    LONGS_EQUAL(60, model113.getPoint("L")->valueAsUint16());
    DOUBLES_EQUAL(240, model113.getPoint("PhVphA")->valueAsFloat32(), 10);

    auto &model160 = *device.getModel(SunspecModelList_kModel160);
    LONGS_EQUAL(40263, model160.address());
    LONGS_EQUAL(50, model160.registerLength());

    LONGS_EQUAL(160, model160.getPoint("ID")->valueAsUint16());
    LONGS_EQUAL(48, model160.getPoint("L")->valueAsUint16());
    LONGS_EQUAL(2, model160.getPoint("N")->valueAsUint16());

    auto &groupModule =  *model160.getGroup("module");
    LONGS_EQUAL(1, groupModule.getPoint("ID")->valueAsUint16());

}

