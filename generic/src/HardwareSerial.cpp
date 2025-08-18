#include "HardwareSerial.h"

HardwareSerial::HardwareSerial(uart_inst_t *uart) : uart(uart), rx_buffer({{0}, 0, 0}) {}

void HardwareSerial::begin(unsigned long baud, uint8_t txPin, uint8_t rxPin) {
    uart_init(uart, baud);
    gpio_set_function(txPin, GPIO_FUNC_UART);
    gpio_set_function(rxPin, GPIO_FUNC_UART);
    uart_set_hw_flow(uart, false, false); // Disable hardware flow control
    uart_set_format(uart, UART_DATA_BITS, UART_STOP_BITS, UART_PARITY_NONE);
    uart_set_fifo_enabled(uart, true);
}

void HardwareSerial::end() {
    uart_deinit(uart);
}

void HardwareSerial::poll() {
    while (uart_is_readable(uart)) {
        uint8_t c = uart_getc(uart);
        uint16_t i = (rx_buffer.head + 1) % UART_BUFFER_SIZE;

        // Only store data if the buffer is not full
        if (i != rx_buffer.tail) {
            rx_buffer.buffer[rx_buffer.head] = c;
            rx_buffer.head = i;
        }
    }
}

int HardwareSerial::available() {
    poll(); // Ensure buffer is updated
    return (UART_BUFFER_SIZE + rx_buffer.head - rx_buffer.tail) % UART_BUFFER_SIZE;
}

int HardwareSerial::peek() {
    poll(); // Ensure buffer is updated
    if (rx_buffer.head == rx_buffer.tail) {
        return -1; // No data available
    } else {
        return rx_buffer.buffer[rx_buffer.tail];
    }
}

int HardwareSerial::read() {
    poll(); // Ensure buffer is updated
    if (rx_buffer.head == rx_buffer.tail) {
        return -1; // No data available
    } else {
        uint8_t c = rx_buffer.buffer[rx_buffer.tail];
        rx_buffer.tail = (rx_buffer.tail + 1) % UART_BUFFER_SIZE;
        return c;
    }
}

int HardwareSerial::availableForWrite() {
    return uart_is_writable(uart);
}

void HardwareSerial::flush() {
    uart_tx_wait_blocking(uart);
}

size_t HardwareSerial::write(uint8_t c) {
    uart_putc(uart, c);
    return 1;
}

// HardwareSerial Serial(uart0);
HardwareSerial Serial1(uart1);





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
