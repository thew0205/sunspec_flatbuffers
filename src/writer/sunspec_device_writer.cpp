#include "writer/sunspec_device_writer.h"

#include <algorithm>

#include "ModbusRTUSlave.h"
#include "writer/sunspec_point_writer.h"
#include "writer/sunspec_group_writer.h"
#include "sunspec.h"

using namespace Sunspec;

SunspecDeviceWriter::SunspecDeviceWriter(ModbusRTUSlave &client) : client_{client}, registerLength_{0}, modbusBuffer_{nullptr}
{
}

SunspecDeviceWriter::~SunspecDeviceWriter()
{
    if (modbusBuffer_)
    {
        delete[] modbusBuffer_;
        modbusBuffer_ = nullptr;
    }
    models_.clear();
}

SunspecModelWriter *SunspecDeviceWriter::getModel(SunspecModelList id)
{
    for (auto &model : models_)
    {
        if (model.def().id() == id)
            return &model;
    }

    return nullptr;
}

uint16_t SunspecDeviceWriter::initTopLevel(const std::initializer_list<SunspecModelList> &supportedModels)
{

    registerLength_ = 0;
    models_.clear(); // Clear any previously initialized models.
    int modelCount = 0;

    std::vector<const SunspecModelDef *> modelDefList;
    for (const auto &modelId : supportedModels)
    {
        const SunspecModelDef *const modelDef = SunspecDeviceWriter::getModelDefinition(modelId);
        // The models not supported will return nullptr.
        if (nullptr != modelDef)
        {
            modelDefList.push_back(modelDef);
            modelCount++;
        }
    }
    models_.reserve(modelCount);
    for (size_t i = 0; i < modelCount; i++)
    {
        registerLength_ += models_.emplace_back(*modelDefList[i], *this).initTopLevel();
    }
    return modelCount;
}

uint16_t SunspecDeviceWriter::initSubLevels()
{
    registerLength_ = 2; // Start with 2 for the base address and model end marker.

    for (auto &model : models_)
    {
        registerLength_ += model.initSubLevels();
    }
    registerLength_ += 2; // Start with 2 for the base address and model end marker.
    assignBuffer();
    setAllModbusBuffer();
    return registerLength_;
}

void SunspecDeviceWriter::setAllValueToModbusBuffer()
{

    for (auto &model : models_)
    {
        model.setAllValueToModbusBuffer();
    }
    setConstantIdentifiersInBuffer();
}

void SunspecDeviceWriter::poll()
{
    setAllValueToModbusBuffer();
    client_.poll();
}


std::string SunspecDeviceWriter::toJson(bool includeSf, bool includeUnits) const
{
    std::string ret;
    ret += "{ ";
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

void SunspecDeviceWriter::setConstantIdentifiersInBuffer()
{
    uint16_t currentOffset = 0;
    memcpy(&modbusBuffer_[currentOffset], &kSunspecIdentifier, 2 * sizeof(uint16_t));

    const uint16_t modelEndBuffer[2] = {SunspecModelList_kModelEnd, 0};
    currentOffset += 2;

    memcpy(&modbusBuffer_[registerLength_ - 2], modelEndBuffer, sizeof(uint16_t) * 2);
}

uint16_t SunspecDeviceWriter::assignBuffer()
{
    if (modbusBuffer_)
    {
        delete[] modbusBuffer_;
        modbusBuffer_ = nullptr;
    }
    modbusBuffer_ = new uint16_t[registerLength_];
    assert(modbusBuffer_ != nullptr && "Failed to allocate buffer for Sunspec device writer");
    if (nullptr == modbusBuffer_)
    {
        models_.clear(); // Clear the models if buffer allocation fails.
        return 0;        // Allocation failed, return 0 to indicate no models initialized.
    }
    setConstantIdentifiersInBuffer();

    client_.configureHoldingRegisters(modbusBuffer_, registerLength_);
    return registerLength_;
}

void SunspecDeviceWriter::setAllModbusBuffer()
{

    uint16_t offset = 2;
    for (auto &model : models_)
    {
        model.setAllModbusBuffer(&modbusBuffer_[offset]);
        offset += model.registerLength();
    }
}


uint16_t SunspecDeviceWriter::initAll(const std::initializer_list<SunspecModelList> &supportedModel)
{

    uint16_t count = initTopLevel(supportedModel);
    if (count == 0)
    {
        return 0; // No models initialized, return 0.
    }

    registerLength_ = initSubLevels();
    if (registerLength_ == 0)
    {
        return 0; // No valid register length, return 0.
    }

    if (assignBuffer() == 0)
    {
        return 0; // Buffer allocation failed, return 0.
    }

    setAllValueToModbusBuffer();
    return count;
}








extern const unsigned char modelDefinition1[];
extern const unsigned char modelDefinition112[];
extern const unsigned char modelDefinition113[];
extern const unsigned char modelDefinition160[];
const SunspecModelDef *SunspecDeviceWriter::getModelDefinition(SunspecModelList id)
{

    switch (id)
    {
    case SunspecModelList_kModel1:
        return GetSunspecModelDef(modelDefinition1);

    case SunspecModelList_kModel112:

        return GetSunspecModelDef(modelDefinition112);
    case SunspecModelList_kModel113:

        return GetSunspecModelDef(modelDefinition113);
    case SunspecModelList_kModel160:
        return GetSunspecModelDef(modelDefinition160);
    default:
        return nullptr;
        break;
    }
    // TODO
    //  auto modelDefIte = std::find_if(modelDefList.cbegin(), modelDefList.cend(), [id](const SunspecModelDef *pModelDef)
    //                                  { return pModelDef->id() == id; });
    //  return modelDefIte == modelDefList.cend() ? nullptr : *modelDefIte;
}

