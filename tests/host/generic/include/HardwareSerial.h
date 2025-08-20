#ifndef HARDWARESERIAL_H
#define HARDWARESERIAL_H

#include <inttypes.h>
#include "Stream.h"

#define UART_BUFFER_SIZE 1024
#define UART_DATA_BITS 8
#define UART_STOP_BITS 1

struct RingBuffer
{
    uint8_t buffer[UART_BUFFER_SIZE];
    volatile uint16_t head;
    volatile uint16_t tail;
};

class HardwareSerial : public Stream
{
public:
    HardwareSerial();
    void begin(const char *portname);
    void end();
    int available();
    int peek();
    int read();
    int availableForWrite();
    void flush();
    size_t write(uint8_t c);

    int fd{0};

private:
    void poll();
    RingBuffer rx_buffer;
};

extern HardwareSerial Serial;
extern HardwareSerial Serial1;
#define millis() (time_ms_32() / 1000)

#endif // HARDWARESERIAL_H

// #ifndef HARDWARESERIAL_H
// #define HARDWARESERIAL_H

// #include <inttypes.h>
// #include "Stream.h"
// #include "hardware/uart.h"

// class HardwareSerial : public Stream
// {
//     protected:
//         uart_inst_t *uart;

//     public:
//         HardwareSerial(uart_inst_t *uart);
//         void begin(unsigned long baud, uint8_t txPin, uint8_t rxPin);
//         void end();
//         virtual int available();
//         virtual int peek();
//         virtual int read();
//         virtual int availableForWrite();
//         virtual void flush();
//         virtual size_t write(uint8_t);
// };

// extern HardwareSerial Serial;
// extern HardwareSerial Serial1;

// #endif // HARDWARESERIAL_H