#pragma once

#include "pico/stdlib.h"
#include "hardware/uart.h"

#define OUTPUT 1u
#define INPUT 0u
#define LOW 0u
#define HIGH 1u

#define millis() (time_us_32() / 1000)
#define micros() (time_us_32())
#define delay(x) (sleep_ms(x))
#define yield()
constexpr uint32_t NAN_32 = 0x7FC00000; // NaN


#define isnan(x) ((float)(x) == NAN)

inline void pinMode(uint16_t pin, bool out)
{
    gpio_init(pin);
    gpio_set_dir(pin, out);
}

inline void digitalWrite(uint16_t pin, bool high)
{
    gpio_put(pin, high);
}