/**
 * @file sunspec_device.h
 * @brief This file defines the SunspecDevice class, which is a sunspec device that can hold a variety of SunspecModel within it.
 *
 * @author Tolulope Matthew Busoye PowerLabs
 */

#pragma once

#include <stdint.h>

#include <initializer_list>
#include <list>
#include <string>

#include "reader/sunspec_model_reader.h"

class ModbusMaster;

/**
 * @class SunspecDevice
 * @brief Represents a physical device that supports the Sunspec protocol over Modbus.
 *
 * This class manages the connection to a Modbus device, scans for its Sunspec base address,
 * initializes supported models, and provides methods to read data and convert it to JSON.
 */
class SunspecDeviceReader
{
    template <typename T>
    using list = std::list<T>;

public:
    /**
     * @brief Returns the number of models initialized on this device.
     * @return The size of the models list.
     */
    size_t modelLength() const
    {
        return models_.size();
    }

    /**
     * @brief Returns the slave Id of this device.
     * @return The slave Id of this device.
     */
    uint8_t slaveId() const
    {
        return slaveId_;
    }

    /**
     * @brief Returns the number of models initialized on this device.
     * @return The size of the models list.
     */
    const list<SunspecModelReader> &models() const
    {
        return models_;
    }

    /**
     * @brief Scans for the Sunspec base address on a device.
     *
     * This method attempts to find the "SunS" identifier at predefined base addresses.
     * @param [in] slaveId The Modbus slave ID of the device.
     * @param [in] client The ModbusMaster client to use for communication.
     * @param [out] baseAddr A pointer to a uint16_t to store the found base address.
     * @return true if the base address is found, false otherwise.
     */
    static bool scanforBaseAddress(uint8_t slaveId, ModbusMaster &client, uint16_t *baseAddr = nullptr);

    /**
     * @brief Initializes the supported Sunspec models on the device.
     *
     * This method reads the model information from the device starting at the base address
     * and initializes the corresponding SunspecModel objects.
     * @param [in] supportedModel An initializer list of model IDs that should be initialized.
     * @return The number of models successfully initialized.
     */
    uint16_t initAllModels(const std::initializer_list<SunspecModelList> &supportedModel);

    /**
     * @brief Reads all data from the device for all initialized models.
     */
    void readBufferFromDevice();

    /**
     * @brief Generates a JSON representation of all initialized models and their data.
     * @param [in] includeSf Whether to include scale factors in the JSON output.
     * @param [in] includeUnits Whether to include units in the JSON output.
     * @return A string containing the JSON representation.
     */
    std::string toJson(bool includeSf = false, bool includeUnits = false) const;

    /**
     * @brief Retrieves a pointer to an initialized model by its ID.
     * @param [in] id The ID of the model to retrieve.
     * @return A pointer to the SunspecModel object, or nullptr if not found.
     */
    SunspecModelReader *getModel(SunspecModelList id);

    /**
     * @brief Reads a block of registers from the device.
     * @param [in] addr The starting address of the registers to read.
     * @param [out] buf A buffer to store the read data.
     * @param [in] len The number of registers to read.
     * @return true if the read operation was successful, false otherwise.
     */
    bool read(uint16_t addr, uint16_t *buf, size_t len);

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
    static constexpr uint32_t kSunspecIdentifier = 0x53756E53;

    /**
     * @brief Class constructor.
     * @param [in] slaveId The Modbus slave ID of the device.
     * @param [in] _client A reference to the ModbusMaster client.
     * @param [in] _baseAddr The known base address of the device. If kInvalidBaseAddress, a scan will be performed.
     */
    SunspecDeviceReader(uint8_t slaveId, ModbusMaster &_client, uint16_t _baseAddr = kInvalidBaseAddress);

    /**
     * @brief Retrieves a static model definition by its ID.
     * @param [in] id The ID of the Sunspec model to retrieve.
     * @return A pointer to the requested SunspecModelDef, or nullptr if not found.
     */
    static const SunspecModelDef *getModelDefinition(SunspecModelList id);

private:
    uint8_t slaveId_{0};
    uint16_t baseAddress_{kInvalidBaseAddress};
    list<SunspecModelReader> models_;
    ModbusMaster &client_;

    /**
     * @brief Reads a single 16-bit field from a device.
     * @param [in] addr The address to read from.
     * @param [in] slaveId The device's slave ID.
     * @param [in] client The Modbus client.
     * @return The 16-bit value read from the device.
     */
    static uint16_t readUint16Field(uint16_t addr, uint16_t slaveId, ModbusMaster &client);

    /**
     * @brief Reads a single 32-bit field from a device.
     * @param [in] addr The address to read from.
     * @param [in] slaveId The device's slave ID.
     * @param [in] client The Modbus client.
     * @return The 32-bit value read from the device.
     */
    static uint32_t readUint32Field(uint16_t addr, uint16_t slaveId, ModbusMaster &client);

    /**
     * @brief Reads a single 32-bit floating-point field from a device.
     * @param [in] addr The address to read from.
     * @param [in] slaveId The device's slave ID.
     * @param [in] client The Modbus client.
     * @return The 32-bit float value read from the device.
     */
    static float readFloatField(uint16_t addr, uint16_t slaveId, ModbusMaster &client);
};