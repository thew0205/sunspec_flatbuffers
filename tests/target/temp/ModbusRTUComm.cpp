#include "ModbusRTUComm.h"
#include "Stream.h"
ModbusRTUComm::ModbusRTUComm(Stream& serial, int8_t dePin, int8_t rePin) : _serial(serial) {
  _dePin = dePin;
  _rePin = rePin;
}

void ModbusRTUComm::begin(unsigned long baud, uint32_t config) {
 


  if (_dePin >= 0) {
    pinMode(_dePin, OUTPUT);
    digitalWrite(_dePin, LOW);
  }
  if (_rePin >= 0) {
    pinMode(_rePin, OUTPUT);
    digitalWrite(_rePin, LOW);
  }
  unsigned long startMicros = micros();
  do {
    if (_serial.available() > 0) {
      startMicros = micros();
      _serial.read();
    }
  } while (micros() - startMicros < _frameTimeout);
}

void ModbusRTUComm::setTimeout(unsigned long timeout) {
  _readTimeout = timeout;
}

ModbusRTUCommError ModbusRTUComm::readAdu(ModbusADU& adu) {
  adu.setRtuLen(0);
  unsigned long startMillis = millis();
  while (!_serial.available()) {
    if (millis() - startMillis >= _readTimeout) return MODBUS_RTU_COMM_TIMEOUT;
  }
  uint16_t len = 0;
  unsigned long startMicros = micros();
  do {
    if (_serial.available()) {
      startMicros = micros();
      adu.rtu[len] = _serial.read();
      len++;
    }
  } while (micros() - startMicros <= _charTimeout && len < 256);
  adu.setRtuLen(len);
  while (micros() - startMicros < _frameTimeout);
  if (_serial.available()) {
    adu.setRtuLen(0);
    return MODBUS_RTU_COMM_FRAME_ERROR;
  }
  if (!adu.crcGood()) {
    adu.setRtuLen(0);
    return MODBUS_RTU_COMM_CRC_ERROR;
  }
  return MODBUS_RTU_COMM_SUCCESS;
}

bool ModbusRTUComm::writeAdu(ModbusADU& adu) {
  uint16_t i = 0;
  uint16_t j = 0;
  bool transmitting = true;
  bool verified = false;
  adu.updateCrc();
  uint16_t len = adu.getRtuLen();
  if (_dePin >= 0) digitalWrite(_dePin, HIGH);
  unsigned long microsNow= micros();
  unsigned long txStartMicros = microsNow;
  unsigned long rxStartMicros = microsNow;
  while (true) {
    microsNow = micros();
    if (transmitting) {
      if (i == 0 || (i < len && microsNow - txStartMicros >= _bytePeriod)) {
        txStartMicros = microsNow;
        _serial.write(adu.rtu[i]);
        _serial.flush();
        i++;
      }
      if (i == len && microsNow - txStartMicros >= _postDelay) {
        if (_dePin >= 0) digitalWrite(_dePin, LOW);
        transmitting = false;
      }
    }
    if (_serial.available()) {
      rxStartMicros = microsNow;
      uint8_t value = _serial.read();
      if (j == 0) verified = true;
      if (j < len && value != adu.rtu[j]) verified = false;
      j++;
    }
    if (!transmitting && (microsNow - rxStartMicros) > _charTimeout) {
      if (j != len) verified = false;
      break;
    }
  }
  return verified;
}