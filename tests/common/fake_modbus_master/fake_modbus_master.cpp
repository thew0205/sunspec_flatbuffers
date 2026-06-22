#include "fake_modbus_master.h"

static uint16_t gBufferBaseAddress = 0;
static uint16_t gBufferSize = 0;
static const uint16_t *gModbusBuffer = nullptr;

uint8_t FakeModbusMaster::readHoldingRegisters(uint16_t u16ReadAddress, uint16_t u16ReadQty)
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

void FakeModbusMaster::setBaseAddress(uint16_t baseAddress)
{
    gBufferBaseAddress = baseAddress;
}

void FakeModbusMaster::setFakeBuffer(const uint16_t *buffer, uint16_t bufferSize)
{
    gModbusBuffer = buffer;
    gBufferSize = bufferSize;
}