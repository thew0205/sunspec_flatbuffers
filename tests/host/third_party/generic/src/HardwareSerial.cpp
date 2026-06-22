#include "HardwareSerial.h"
// Function to open the serial port

// serial_posix.cpp
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
using namespace std;
// Function to open the serial port

bool isDataAvailable(int fd)
{
    int bytesAvailable;
    if (ioctl(fd, FIONREAD, &bytesAvailable) == -1)
    {
        perror("ioctl FIONREAD failed");
        return false;
    }
    return bytesAvailable > 0;
}
int openSerialPort(const char *portname)
{
    int fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0)
    {
        cerr << "Error opening " << portname << ": "
             << strerror(errno) << endl;
        return -1;
    }
    return fd;
}

// Function to configure the serial port
bool configureSerialPort(int fd, int speed)
{
    struct termios tty;
    if (tcgetattr(fd, &tty) != 0)
    {
        cerr << "Error from tcgetattr: " << strerror(errno)
             << endl;
        return false;
    }

    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8-bit characters
    tty.c_iflag &= ~IGNBRK;                     // disable break processing
    tty.c_lflag = 0;                            // no signaling chars, no echo, no
                                                // canonical processing
    tty.c_oflag = 0;                            // no remapping, no delays
    tty.c_cc[VMIN] = 0;                         // read doesn't block
    tty.c_cc[VTIME] = 5;                        // 0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    tty.c_cflag |= (CLOCAL | CREAD);   // ignore modem controls,
                                       // enable reading
    tty.c_cflag &= ~(PARENB | PARODD); // shut off parity
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(fd, TCSANOW, &tty) != 0)
    {
        cerr << "Error from tcsetattr: " << strerror(errno)
             << endl;
        return false;
    }
    return true;
}

// Function to read data from the serial port
int readFromSerialPort(int fd, uint8_t *buffer, size_t size)
{
    return read(fd, buffer, size);
}

// Function to write data to the serial port
int writeToSerialPort(int fd, const uint8_t *buffer,
                      size_t size)
{
    return write(fd, buffer, size);
}

// Function to close the serial port
void closeSerialPort(int fd) { close(fd); }
void waitForTxDrain(int fd) {
    tcdrain(fd); // blocks until everything in TX FIFO is sent
}
HardwareSerial::HardwareSerial() : rx_buffer({{0}, 0, 0}) {}

void HardwareSerial::begin( const char *portname, unsigned long baud)
{
    // Replace with your serial port name
    fd = openSerialPort(portname);
    if (fd < 0)
        return;

    if (!configureSerialPort(fd, baud))
    {
        closeSerialPort(fd);
    }
}

void HardwareSerial::end()
{
    closeSerialPort(fd);
}

void HardwareSerial::poll()
{
    while (isDataAvailable(fd))
    {
        uint8_t c;
        // uint8_t c = uart_getc(uart);
        readFromSerialPort(fd, &c, sizeof(c));
        uint16_t i = (rx_buffer.head + 1) % UART_BUFFER_SIZE;

        // Only store data if the buffer is not full
        if (i != rx_buffer.tail)
        {
            rx_buffer.buffer[rx_buffer.head] = c;
            rx_buffer.head = i;
        }
    }
}

int HardwareSerial::available()
{
    poll(); // Ensure buffer is updated
    return (UART_BUFFER_SIZE + rx_buffer.head - rx_buffer.tail) % UART_BUFFER_SIZE;
}

int HardwareSerial::peek()
{
    poll(); // Ensure buffer is updated
    if (rx_buffer.head == rx_buffer.tail)
    {
        return -1; // No data available
    }
    else
    {
        return rx_buffer.buffer[rx_buffer.tail];
    }
}

int HardwareSerial::read()
{
    poll(); // Ensure buffer is updated
    if (rx_buffer.head == rx_buffer.tail)
    {
        return -1; // No data available
    }
    else
    {
        uint8_t c = rx_buffer.buffer[rx_buffer.tail];
        rx_buffer.tail = (rx_buffer.tail + 1) % UART_BUFFER_SIZE;
        return c;
    }
}

int HardwareSerial::availableForWrite()
{
    return true;
    // return uart_is_writable(uart);
}

void HardwareSerial::flush()
{
    waitForTxDrain(fd);
    // uart_tx_wait_blocking(uart);
}

size_t HardwareSerial::write(uint8_t c)
{
    // uart_putc(uart, c);
    return writeToSerialPort(fd, &c, sizeof(c));
    
}

HardwareSerial Serial0{};
HardwareSerial Serial1{};

// #include "HardwareSerial.h"

// #define UART_DATA_BITS      8
// #define UART_STOP_BITS      1

// HardwareSerial::HardwareSerial(uart_inst_t *uart) : uart(uart) {}

// void HardwareSerial::begin(unsigned long baud, uint8_t txPin, uint8_t rxPin) {
//     // Configure UART settings here
//     uart_init(uart, baud);
//     gpio_set_function(txPin, GPIO_FUNC_UART);
//     gpio_set_function(rxPin, GPIO_FUNC_UART);
//     uart_set_hw_flow(uart,false,false); //Disable hardware flow control
//     uart_set_format(uart,UART_DATA_BITS,UART_STOP_BITS,UART_PARITY_NONE);
//     uart_set_fifo_enabled(uart,true);
// }

// void HardwareSerial::end() {
//     // Clean up and disable UART here
//     uart_deinit(uart);
// }

// int HardwareSerial::available() {
//     // Implement UART receive buffer checking here
//     return uart_is_readable(uart) ? 1 : 0;
// }

// int HardwareSerial::peek() {
//     // Return the next available character without removing it from the buffer
//     if (uart_is_readable(uart)) {
//         uint8_t c;
//         if (uart_is_readable(uart)) {
//             // Peek the next character by temporarily reading it
//             c = uart_getc(uart);
//             // Put the character back into the buffer
//             uart_putc(uart, c);
//             return c;
//         }
//     }
//     return -1; // No
// }

// int HardwareSerial::read() {
//     // Read and return the next available character from the buffer
//     if (uart_is_readable(uart)) {
//         return uart_getc(uart);
//     }
//     return -1; // No data available
// }

// int HardwareSerial::availableForWrite() {
//     // Implement available transmit buffer space checking here
//     return uart_is_writable(uart);
// }

// void HardwareSerial::flush() {
//     // Wait until all data in the transmit buffer has been sent
//     uart_tx_wait_blocking(uart);
// }

// size_t HardwareSerial::write(uint8_t c) {
//     // Write the given character to the transmit buffer for sending
//     uart_putc(uart, c);
//     return 1; // Return the number of bytes written (always 1)
// }

// // Instantiate the default Serial object using uart0
// HardwareSerial Serial(uart0);
// HardwareSerial Serial1(uart1);
