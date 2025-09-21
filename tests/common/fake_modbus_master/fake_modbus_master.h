#include "modbus_master.h"

class FakeModbusMaster : public ModbusMaster
{
public:
    VIRTUAL_TEST uint8_t readHoldingRegisters(uint16_t u16ReadAddress, uint16_t u16ReadQty);

    void setBaseAddress(uint16_t baseAddress);
    void setFakeBuffer(const uint16_t *buffer, uint16_t bufferSize);
};
