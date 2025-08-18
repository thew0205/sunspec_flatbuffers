#include "writer/sunspec_device_writer.h"

#include <algorithm>

#include "ModbusRTUSlave.h"
#include "writer/sunspec_point_writer.h"
#include "writer/sunspec_group_writer.h"
#include "sunspec_utils.h"

using namespace Sunspec;

// bool SunspecDeviceWriter::setBaseAddress(uint16_t baseAddr)
// {
//     baseAddress_ = baseAddr;
// }
SunspecModelWriter *SunspecDeviceWriter::getModel(SunspecModelList id)
{
    for (auto &model : models_)
    {
        if (model.def().id() == id)
            return &model;
    }

    return nullptr;
}

uint16_t SunspecDeviceWriter::initAllModels(const std::initializer_list<SunspecModelList> &supportedModels)
{
    int count = 0;

    registerLength_ += 2;

    for (auto &modelId : supportedModels)
    {
        const SunspecModelDef *const modelDef = SunspecDeviceWriter::getModelDefinition(modelId);

        if (nullptr != modelDef && std::find(supportedModels.begin(), supportedModels.end(), modelId) != supportedModels.end())
        {
            models_.emplace_back(*modelDef, baseAddress_ + registerLength_, *this);
            registerLength_ += models_.back().init(baseAddress_ + registerLength_);
            count++;
        }
    }
    registerLength_ += 2;
    buffer_ = new uint16_t[registerLength_];
    if (buffer_ == nullptr)
    {
        models_.clear();
        return 0;
    }
    client_.configureHoldingRegisters(buffer_, registerLength_);
    setConstantIdentifiersInBuffer();
    return count;
}

void SunspecDeviceWriter::poll()
{
    setAllBuffer();
    client_.poll();
}
void SunspecDeviceWriter::setConstantIdentifiersInBuffer()
{

    memcpy(buffer_, &kSunspecIdentifier, 4);
    const uint16_t modelEndBuffer[2] = {SunspecModelList_kModelEnd, 0};

    memcpy(buffer_ + registerLength_ - 2, modelEndBuffer, sizeof(uint16_t) * 2);

    for (auto &model : models_)
    {
        model.setConstantIdentifiersInBuffer(buffer_ + 2);
    }
}
void SunspecDeviceWriter::setAllBuffer()
{

    uint16_t *modelBuffer = buffer_ + 2;

    for (auto &model : models_)
    {
        model.setToDeviceBuffer(modelBuffer);
        modelBuffer += model.registerLength();
    }
}

std::string SunspecDeviceWriter::toJson(bool includeSf, bool includeUnits) const
{
    std::string ret;
    ret += "{ \"baseAddress\":" + std::to_string(baseAddress_) + ",";
    ret += "\"deviceId\" : " + std::to_string(slaveId_) + ",";
    if (!models_.empty())
    {
        ret += "\"models\":[";
        for (auto &model : models_)
        {
            ret += model.toJson(includeSf, includeUnits);
            ret += ",";
        }
        if (!ret.empty() && ret.back() == ',')
        {
            ret.pop_back(); // Remove the last comma
        }
        ret += "]";
    }

    ret += "}";
    return ret;
}

SunspecDeviceWriter::SunspecDeviceWriter(uint8_t slaveId, ModbusRTUSlave &client, uint16_t baseAddress) : slaveId_(slaveId), client_{client}, baseAddress_{baseAddress}, registerLength_{0}, buffer_{nullptr}
{
}

extern const unsigned char modelDef112[];
extern const unsigned char modelDef113[];
const SunspecModelDef *SunspecDeviceWriter::getModelDefinition(SunspecModelList id)
{

    switch (id)
    {
    case SunspecModelList_kModel112:

        return GetSunspecModelDef(modelDef112);
    case SunspecModelList_kModel113:

        return GetSunspecModelDef(modelDef113);

    default:
        return nullptr;
        break;
    }
    // TODO
    //  auto modelDefIte = std::find_if(modelDefList.cbegin(), modelDefList.cend(), [id](const SunspecModelDef *pModelDef)
    //                                  { return pModelDef->id() == id; });
    //  return modelDefIte == modelDefList.cend() ? nullptr : *modelDefIte;
}
