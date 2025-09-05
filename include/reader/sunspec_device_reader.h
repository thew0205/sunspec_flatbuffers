

#pragma once

#include <stdint.h>

#include <initializer_list>
#include <vector>
#include <string>

#include "reader/sunspec_model_reader.h"

class ModbusMaster;

class SunspecDeviceReader
{
    template <typename T>
    using vector = std::vector<T>;

public:
    SunspecDeviceReader(uint8_t slaveId, ModbusMaster &_client, uint16_t _baseAddr = kInvalidBaseAddress);

    ~SunspecDeviceReader();
    size_t modelLength() const
    {
        return models_.size();
    }

    uint8_t slaveId() const
    {
        return slaveId_;
    }

    uint16_t baseAddress() const
    {
        return baseAddress_;
    }

    const vector<SunspecModelReader> &models() const
    {
        return models_;
    }

    static bool scanforBaseAddress(uint8_t slaveId, ModbusMaster &client, uint16_t *baseAddr = nullptr);

    uint16_t initAllModels(const std::initializer_list<SunspecModelList> &supportedModel);

    void assignBuffer();
    void readBufferFromDevice();

    // std::string toJson(bool includeSf = false, bool includeUnits = false) const;

    SunspecModelReader *getModel(SunspecModelList id);

    bool read(uint16_t addr, uint16_t *buf, size_t len);

    static constexpr int kMaxModbusReadLength = 120;

    static constexpr uint8_t kSunspecBaseAddressListLength = 3;

    static constexpr uint16_t kSunspecBaseAddressList[kSunspecBaseAddressListLength] = {40000, 0, 50000};

    static constexpr uint16_t kInvalidBaseAddress = 0XFFFF;

    static constexpr uint8_t kModbusMaxRetries = 10;

    static constexpr uint32_t kSunspecIdentifier = 0x53756E53;

    static const SunspecModelDef *getModelDefinition(SunspecModelList id);

private:
    uint8_t slaveId_;
    uint16_t baseAddress_;
    uint16_t registerLength_;
    uint16_t *modbusBuffer_{nullptr};
    vector<SunspecModelReader> models_;
    ModbusMaster &client_;

    static uint16_t readUint16Field(uint16_t addr, uint16_t slaveId, ModbusMaster &client);

    static uint32_t readUint32Field(uint16_t addr, uint16_t slaveId, ModbusMaster &client);

    static float readFloatField(uint16_t addr, uint16_t slaveId, ModbusMaster &client);
};