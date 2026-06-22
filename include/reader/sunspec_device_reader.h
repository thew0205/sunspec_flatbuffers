

#pragma once // Ensure the header is included only once

#include <stdint.h> // Standard integer types

#include <initializer_list> // For list initialization
#include <vector>           // For std::vector
#include <string>           // For std::string

#include "reader/sunspec_model_reader.h" // Dependency for model reading

class ModbusMaster; // Forward declaration for Modbus communication

/**
 * @brief Class to read and manage SunSpec device models via Modbus.
 */
class SunspecDeviceReader
{
    /**
     * @brief Alias for std::vector for internal use.
     */
    template <typename T>
    using vector = std::vector<T>;

public:
    /**
     * @brief Constructor: initializes with slave ID, Modbus client, and optional base address.
     * @param slaveId Modbus slave ID
     * @param _client Reference to Modbus client
     * @param _baseAddr Optional base address (default: kInvalidBaseAddress)
     */
    SunspecDeviceReader(uint8_t slaveId, ModbusMaster &_client, uint16_t _baseAddr = kInvalidBaseAddress);

    /**
     * @brief Destructor
     */
    ~SunspecDeviceReader();

    /**
     * @brief Returns the number of models detected
     * @return Number of models
     */
    size_t modelLength() const
    {
        return models_.size();
    }

    /**
     * @brief Returns the Modbus slave ID
     * @return Slave ID
     */
    uint8_t slaveId() const
    {
        return slaveId_;
    }

    /**
     * @brief Returns the base address used for SunSpec data
     * @return Base address
     */
    uint16_t baseAddress() const
    {
        return baseAddress_;
    }

    /**
     * @brief Returns a const reference to the vector of SunSpec model readers
     * @return Vector of SunSpecModelReader
     */
    const vector<SunspecModelReader> &models() const
    {
        return models_;
    }

    /**
     * @brief Scans for the SunSpec base address on a device
     * @param slaveId Modbus slave ID
     * @param client Reference to Modbus client
     * @param baseAddr Optional pointer to store found base address
     * @return True if found, false otherwise
     */
    static bool scanforBaseAddress(uint8_t slaveId, ModbusMaster &client, uint16_t *baseAddr = nullptr);

    /**
     * @brief Initializes all supported SunSpec models
     * @param supportedModel List of supported models
     * @return Number of models initialized
     */
    uint16_t initAllModels(const std::initializer_list<SunspecModelList> &supportedModel);

    /**
     * @brief Assigns the buffer for Modbus data
     */
    void assignBuffer();

    /**
     * @brief Reads the buffer from the device
     */
    void readBufferFromDevice();

    /**
     * @brief Converts device data to JSON format
     * @param includeSf Include scale factors
     * @param includeUnits Include units
     * @return JSON string
     */
    std::string toJson(bool includeSf = false, bool includeUnits = false) const;

    /**
     * @brief Gets a pointer to a model by its ID
     * @param id Model ID
     * @return Pointer to SunspecModelReader
     */
    SunspecModelReader *getModel(SunspecModelList id);

    /**
     * @brief Reads data from the device at a given address into a buffer
     * @param addr Address to read from
     * @param buf Buffer to store data
     * @param len Number of registers to read
     * @return True if successful
     */
    bool read(uint16_t addr, uint16_t *buf, size_t len);

    /**
     * @brief Maximum length for a Modbus read operation
     */
    static constexpr int kMaxModbusReadLength = 120;

    /**
     * @brief Number of possible SunSpec base addresses
     */
    static constexpr uint8_t kSunspecBaseAddressListLength = 3;

    /**
     * @brief List of possible SunSpec base addresses
     */
    static constexpr uint16_t kSunspecBaseAddressList[kSunspecBaseAddressListLength] = {40000, 0, 50000};

    /**
     * @brief Value representing an invalid base address
     */
    static constexpr uint16_t kInvalidBaseAddress = 0XFFFF;

    /**
     * @brief Maximum number of retries for Modbus operations
     */
    static constexpr uint8_t kModbusMaxRetries = 10;

    /**
     * @brief SunSpec identifier value
     */
    static constexpr uint32_t kSunspecIdentifier = 0x53756E53;

    /**
     * @brief Gets the model definition for a given model ID
     * @param id Model ID
     * @return Pointer to SunspecModelDef
     */
    static const SunspecModelDef *getModelDefinition(SunspecModelList id);

private:
    uint8_t slaveId_{0};                /**< Modbus slave ID */
    uint16_t baseAddress_;              /**< SunSpec base address */
    uint16_t registerLength_{0};        /**< Length of Modbus register block */
    uint16_t *modbusBuffer_{nullptr};   /**< Buffer for Modbus data */
    vector<SunspecModelReader> models_; /**< List of SunSpec models */
    ModbusMaster &client_;              /**< Reference to Modbus client */

    /**
     * @brief Reads a 16-bit unsigned field from the device
     * @param addr Address to read from
     * @param slaveId Modbus slave ID
     * @param client Reference to Modbus client
     * @return 16-bit unsigned value
     */
    static uint16_t readUint16Field(uint16_t addr, uint16_t slaveId, ModbusMaster &client);

    /**
     * @brief Reads a 32-bit unsigned field from the device
     * @param addr Address to read from
     * @param slaveId Modbus slave ID
     * @param client Reference to Modbus client
     * @return 32-bit unsigned value
     */
    static uint32_t readUint32Field(uint16_t addr, uint16_t slaveId, ModbusMaster &client);

    /**
     * @brief Reads a float field from the device
     * @param addr Address to read from
     * @param slaveId Modbus slave ID
     * @param client Reference to Modbus client
     * @return Float value
     */
    static float readFloatField(uint16_t addr, uint16_t slaveId, ModbusMaster &client);
};