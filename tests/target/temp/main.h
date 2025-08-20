#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "HardwareSerial.h"
#include "stdint.h"

#define BAUD_9600       9600
#define BAUD_115200     115200
#define MAX485_CTRL     0
#define MAX485_RE_NEG   15
#define HIGH            true
#define LOW             false
 
#define PHASE_A_VOLTAGE         0x01
#define PHASE_B_VOLTAGE         0x08
#define PHASE_C_VOLTAGE         0x0A
#define LINE_A_B_VOLTAGE        0x0C
#define LINE_B_C_VOLTAGE        0x0E
#define LINE_C_A_VOLTAGE        0x10
#define FREQ                    0x12
#define CCT_1_PHASE_A_CURRENT   0x14
#define CCT_1_PHASE_B_CURRENT   0x16
#define CCT_1_PHASE_C_CURRENT   0x18
#define CCT_1_NEUTRAL_CURRENT   0x1A
#define CCT_1_PHASE_A_PWR       0x1C
#define CCT_1_PHASE_B_PWR       0x1E
#define CCT_1_PHASE_C_PWR       0x20
#define CCT_1_TOTAL_PWR         0x22

namespace Pin
{
    const uint8_t rxPin = 8;
    const uint8_t txPin = 9;
}


#endif