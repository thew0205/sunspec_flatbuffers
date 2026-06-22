/**
 * @file sunspec_device_writer.h
 * @brief This file defines the SunspecDevice class, which is a sunspec device that can hold a variety of SunspecModelWriter within it.
 * It represent a Sunspec Device that can set modbus register map for reading by other sunspec compliant devices.
 *
 * @author Tolulope Matthew Busoye PowerLabs
 */

#pragma once

#include <stdint.h>

#include <initializer_list>
#include <string>

#include "writer/sunspec_model_writer.h"

class ModbusRTUSlave;

/**
 * @class SunspecDevice
 * @brief Represents a physical device that supports the Sunspec protocol over Modbus.
 *
 * This class manages the connection to a Modbus device, scans for its Sunspec base address,
 * initializes supported models, and provides methods to read data and convert it to JSON.
 */
class SunspecDeviceWriter
{
    template <typename T>
    using vector = std::vector<T>;

public:
    /**
     * @brief Class constructor.
     * @param [in] slaveId The Modbus slave ID of the device.
     * @param [in] _client A reference to the ModbusRTUSlave client.
     */
    SunspecDeviceWriter(ModbusRTUSlave &_client);

    /**
     * @brief Copy constructor.
     */
    SunspecDeviceWriter(const SunspecDeviceWriter &device) = delete;

    /**
     * @brief Move constructor.
     */
    SunspecDeviceWriter(SunspecDeviceWriter &&device) noexcept = delete;

    ~SunspecDeviceWriter();

    uint16_t registerLength() const
    {
        return registerLength_;
    }

    /**
     * @brief Returns the number of models initialized on this device.
     * @return The size of the models list.
     */
    const vector<SunspecModelWriter> &models() const
    {
        return models_;
    }

    /**
     * @brief Returns the number of models initialized on this device.
     * @return The size of the models list.
     */
    size_t modelCount() const
    {
        return models_.size();
    }

    /**
     * @brief Retrieves a pointer to an initialized model by its ID.
     * @param [in] id The ID of the model to retrieve.
     * @return A pointer to the SunspecModel object, or nullptr if not found.
     */
    SunspecModelWriter *getModel(SunspecModelList id);

    /**
     * @brief Initializes the supported Sunspec models on the device.
     *
     * @param [in] supportedModel An initializer list of model IDs that should be initialized.
     * @return The number of models successfully initialized.
     */
    // For device with only fixed value models, we can use this function to get the model definition.
    uint16_t initAll(const std::initializer_list<SunspecModelList> &supportedModel);

    /**
     * @brief Initializes the supported Sunspec models on the device.
     *It adds supported models to the device based on the provided list of model IDs and those supported as defined in getModelDefinition function. Supported models are initialized and their top-level points are set up.
     * @param [in] supportedModel An initializer list of model IDs that should be initialized.
     * @return The number of models successfully initialized.
     */
    // For device with either fixed or variable models with variable length groups, we need to call this function after setting any dynamic group lengths.
    uint16_t initTopLevel(const std::initializer_list<SunspecModelList> &supportedModel);

    /**
     * @brief Initializes all sub-level groups of SunspecPointWriter in all models of the device.
     * This method recursively sets up all nested groups and their points according to the model definitions. This must be called after initTopLevel.
     * @return The total register length of the device after initialization.
     */
    uint16_t initSubLevels();

    /**
     * @brief Sets the values of modbus buffer by calling all the setValueToModbusBuffer function for toplevel SunspecModelWriter for the device.
     * This should be called after assignBuffer to ensure all models and their points are initialized, as it relies on the registerLength_ for all containing sunspec elements being set.
     */
    void setAllValueToModbusBuffer();

    /**
     * @brief Polls the Modbus client to read the latest data from the device as well as calling setAllValueToModbusBuffer.
     * This method updates the modbus buffer with the latest data from the device. It should be called periodically to ensure the data remains current either in a loop or a timer interrupt callback.
     */
    void poll();

    /**
     * @brief Generates a JSON representation of all initialized models and their data.
     * @param [in] includeSf Whether to include scale factors in the JSON output.
     * @param [in] includeUnits Whether to include units in the JSON output.
     * @return A string containing the JSON representation.
     */
    std::string toJson(bool includeSf = false, bool includeUnits = false) const;

    /** Maximum length for a single Modbus read operation in registers. */
    static constexpr int kMaxModbusReadLength = 120;
    /** The number of standard base addresses to check during a scan. */
    static constexpr uint8_t kSunspecBaseAddressListLength = 3;
    /** An array of standard Sunspec base addresses. */
    static constexpr uint16_t kSunspecBaseAddressList[kSunspecBaseAddressListLength] = {40000, 0, 50000};
    /** A special value used to indicate an invalid or un-found base address. */
    static constexpr uint16_t kInvalidBaseAddress = 0XFFFF;
    /** The maximum number of retries for a Modbus operation. */
    static constexpr uint8_t kModbusMaxRetries = 10;
    /** The 32-bit "SunS" magic number identifier for Sunspec. */
    static constexpr uint16_t kSunspecIdentifier[2] = {0x5375, 0x6E53};

private:


    /**
     * @brief Set the constant identifiers (Sunspec identifier, model ID, and model length) in the modbus buffer.
     */
    void setConstantIdentifiersInBuffer();

    /**
     * @brief Allocates and assigns the modbus buffer based on the total register length required.
     * This should after calling initSubLevels to ensure all models and their points are initialized.
     * @return The size of the allocated buffer in registers, or 0 if allocation fails.
     */
    uint16_t assignBuffer();

    /**
     * @brief Sets the values of modbus buffer by calling all the setValueToModbusBuffer function for toplevel SunspecModelWriter for the device.
     * This should be called after assignBuffer to ensure all models and their points are initialized, as it relies on the registerLength_ for all containing sunspec elements being set.
     */
    void setAllModbusBuffer();

    vector<SunspecModelWriter> models_; /**< A list of models in the device. */
    ModbusRTUSlave &client_;            /**< A reference to the ModbusRTUSlave client used for communication. */
    uint16_t *modbusBuffer_;            /**< A pointer to the inplace modbus buffer where the device's data is to be stored. */
    uint16_t registerLength_;           /**< The total length of the modbus register map for all models, including 2 registers for the Sunspec identifier and the end model identifier */
};