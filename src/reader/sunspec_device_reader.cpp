#include "reader/sunspec_device_reader.h"

#include <algorithm>

#include "modbus_master.h"
#include "reader/sunspec_point_reader.h"
#include "reader/sunspec_group_reader.h"
#include "sunspec.h"
#include <model_definitions.h>

using namespace Sunspec;

SunspecDeviceReader::SunspecDeviceReader(uint8_t slaveId, ModbusMaster &client, uint16_t baseAddress) : slaveId_(slaveId), client_{client}, baseAddress_{baseAddress}, registerLength_{0} {}

bool SunspecDeviceReader::scanforBaseAddress(uint8_t slaveId, ModbusMaster &client, uint16_t *baseAddress)
{
    for (uint8_t i = 0; i < kSunspecBaseAddressListLength; i++)
    {
        uint32_t sunsIden = readUint32Field(kSunspecBaseAddressList[i], slaveId, client);
        if (kSunspecIdentifier == sunsIden)
        {
            if (baseAddress != nullptr)
            {
                *baseAddress = kSunspecBaseAddressList[i];
            }
            return true;
        }
    }
    return false;
}

SunspecDeviceReader::~SunspecDeviceReader()
{
    if (modbusBuffer_)
    {
        delete[] modbusBuffer_;
        modbusBuffer_ = nullptr;
    }
    models_.clear();
}

SunspecModelReader *SunspecDeviceReader::getModel(SunspecModelList id)
{
    for (auto &model : models_)
    {
        if (model.def().id() == id)
            return &model;
    }

    return nullptr;
}
uint16_t SunspecDeviceReader::initAllModels(const std::initializer_list<SunspecModelList> &supportedModels)
{
    int count = 0;
    if (kInvalidBaseAddress == baseAddress_ && !(scanforBaseAddress(slaveId_, client_, &baseAddress_)))
    {

        models_.clear();
        return 0;
    }
    else
    {
        uint16_t address = baseAddress_ + 2;
        std::vector<uint16_t> availableModelsAddr{};
        registerLength_ = 2;
        std::vector<uint16_t> modelLengths{};
        std::vector<const SunspecModelDef *> availableModelsDef{};
        while (true)
        {
            SunspecModelList modelId = static_cast<SunspecModelList>(readUint16Field(address, slaveId_, client_));
            uint16_t len = readUint16Field(address + 1, slaveId_, client_);

            if (SunspecModelList_kModelEnd == modelId)
            {
                break;
            }

            const SunspecModelDef *const modelDef = Sunspec::getModelDefinition(modelId);

            if (nullptr != modelDef && std::find(supportedModels.begin(), supportedModels.end(), modelId) != supportedModels.end())
            {
                modelLengths.emplace_back(len + 2);
                registerLength_ += len + 2;

                availableModelsAddr.emplace_back(address);
                availableModelsDef.emplace_back(modelDef);
                count++;
            }
            address += len + 2;
        }
        registerLength_ += 2;
        assert(modelLengths.size() == availableModelsAddr.size());
        assignBuffer();
        models_.reserve(count);
        size_t offset = 2;
        for (size_t i = 0; i < count; i++)
        {
            models_.emplace_back(*availableModelsDef[i], &modbusBuffer_[offset], availableModelsAddr[i], *this).initPoints();

            offset += modelLengths[i];
        }

        offset = 2;
        for (size_t i = 0; i < count; i++)
        {
            read(models_[i].address(), &modbusBuffer_[offset], modelLengths[i]);
            offset += modelLengths[i];

            models_[i].initGroups(modelLengths[i]);
        }
    }
    return count;
}

void SunspecDeviceReader::assignBuffer()
{
    if (modbusBuffer_)
    {
        delete[] modbusBuffer_;
        modbusBuffer_ = nullptr;
    }
    modbusBuffer_ = new uint16_t[registerLength_];
    return;
}

void SunspecDeviceReader::readBufferFromDevice()
{

    uint16_t offset = 2;
    for (auto &model : models_)
    {
        read(model.address(), &modbusBuffer_[offset], model.registerLength());
        offset += model.registerLength();
    }
}

bool SunspecDeviceReader::read(uint16_t address, uint16_t *buf, size_t len)
{
    uint16_t retries = 0;
    if (buf != nullptr && address >= this->baseAddress_)
    {
        uint16_t readLen = 0;
        uint16_t dataRead = 0;
        while (len > 0 && retries < kModbusMaxRetries)
        {
            readLen = (len > kMaxModbusReadLength) ? kMaxModbusReadLength : len;
            uint8_t result = client_.readHoldingRegisters(slaveId_, address + dataRead, readLen);
            if (ModbusMaster::ku8MBSuccess == result)
            {
                for (int i = 0; i < readLen; i++)
                {
                    buf[i + (dataRead)] = client_.getResponseBuffer(i);
                }
                len -= readLen;
                dataRead += readLen;
            }
            else
            {
                retries++;
            }
        }
        return true;
    }
    return false;
}

// void SunspecDeviceReader::readBufferFromDevice()
// {
//     for (auto &model : models_)
//     {

//         model.readAndSetFromDevice();
//     }
// }

// std::string SunspecDeviceReader::toJson(bool includeSf, bool includeUnits) const
// {
//     std::string ret;
//     ret += "{ \"baseAddress\":" + std::to_string(baseAddress_) + ",";
//     ret += "\"deviceId\" : " + std::to_string(slaveId_) + ",";
//     if (!models_.empty())
//     {
//         ret += "\"models\":[";
//         for (auto &model : models_)
//         {
//             ret += model.toJson(includeSf, includeUnits);
//             ret += ",";
//         }
//         if (!ret.empty() && ret.back() == ',')
//         {
//             ret.pop_back(); // Remove the last comma
//         }
//         ret += "]";
//     }

//     ret += "}";
//     return ret;
// }

float SunspecDeviceReader::readFloatField(uint16_t address, uint16_t slaveId, ModbusMaster &client)
{

    if (ModbusMaster::ku8MBSuccess == client.readHoldingRegisters(slaveId, address, 2))
    {
        return registersToFloat(client.getResponseBuffer(0), client.getResponseBuffer(1));
    }
    return 0;
}

uint16_t SunspecDeviceReader::readUint16Field(uint16_t address, uint16_t slaveId, ModbusMaster &client)
{
    if (ModbusMaster::ku8MBSuccess == client.readHoldingRegisters(slaveId, address, 1))
    {
        return registersToUint16(client.getResponseBuffer(0));
    }
    return 0;
}
uint32_t SunspecDeviceReader::readUint32Field(uint16_t address, uint16_t slaveId, ModbusMaster &client)
{
    uint8_t result = client.readHoldingRegisters(slaveId, address, 2);
    if (ModbusMaster::ku8MBSuccess == result)
    {
        return registersToUint32(client.getResponseBuffer(0), client.getResponseBuffer(1));
    }
    return 0;
}

// extern const unsigned char modelDef112[];
// extern const unsigned char modelDef113[];
// const SunspecModelDef *SunspecDeviceReader::getModelDefinition(SunspecModelList id)
// {

//     switch (id)
//     {
//     case SunspecModelList_kModel112:

//         return GetSunspecModelDef(modelDef112);
//     case SunspecModelList_kModel113:

//         return GetSunspecModelDef(modelDef113);

//     default:
//         return nullptr;
//         break;
//     }
//     // TODO
//     //  auto modelDefIte = std::find_if(modelDefList.cbegin(), modelDefList.cend(), [id](const SunspecModelDef *pModelDef)
//     //                                  { return pModelDef->id() == id; });
//     //  return modelDefIte == modelDefList.cend() ? nullptr : *modelDefIte;
// }
