#pragma once
#include <sys/types.h>
uint32_t time_ms_32();
uint32_t time_us_32();
void sleep_ms(uint ms);

#define millis() (time_us_32() / 1000)
#define micros() (time_us_32())
#define delay(x) (sleep_ms(x))
