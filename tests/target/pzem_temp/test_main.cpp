

#include <stdio.h>
#include "main.h"
#include "pico/stdlib.h"
#include "modbus_master.h"
#include <ModbusRTUSlave.h>
#include "writer/sunspec_device_writer.h"

#include <stdio.h>

#include <iostream>
#include <string>
#include <stdint.h>
#include <iostream>
#include "PZEM004Tv30.h"
#include "pico_includes.h"
using std::cout;
using std::endl;
using std::string;
ModbusRTUSlave modbus(Serial0, MAX485_CTRL);

PZEM004Tv30 pzem;

int main()
{

    stdio_init_all();
    pzem = PZEM004Tv30(Serial1, 9, 8, 1);
    while (1)
    {
        /* code */
        printf("%f\n", pzem.voltage());
    }

    Serial0.begin(BAUD_9600, Pin::txPin, Pin::rxPin);

    modbus.begin(1, BAUD_9600, SERIAL_8N1);

    SunspecDeviceWriter writer{modbus};
    writer.initAll({1, 113});
    SunspecPointFunction functMn{.str = {.function = [](void *param) -> string
                                         { return "Matthew"; }}};

    writer.getModel(1)->getPoint("Mn")->setPointFunction(functMn);

    writer.getModel(1)->getPoint("Opt")->setPointFunction({.str = {.function = [](void *param) -> string
                                                                                          { return "Busoye Tolulope Matthew"; }}});
    writer.getModel(1)->getPoint("DA")->setPointFunction({.uint16 = {.function = [](void *param) -> uint16_t
                                                                                            { return 1; }}});
    writer.getModel(1)->getPoint("Opt")->setPointFunction({.str = {.function = [](void *param) -> string
                                                                                          { return "Busoye Tolulope Matthew"; }}});
    writer.getModel(1)->getPoint("DA")->setPointFunction({.uint16 = {.function = [](void *param) -> uint16_t
                                                                                            { return 1; }}});

    writer.getModel(113)->getPoint("A")->setPointFunction({.float32 = {.function = [](void *param)
                                                                                              { return pzem.current(); }}});
    writer.getModel(113)->getPoint("PhVphA")->setPointFunction({.float32 = {.function = [](void *param)
                                                                                                   { return pzem.voltage(); }}});

    writer.getModel(113)->getPoint("AphA")->setPointFunction({.float32 = {.function = [](void *param)
                                                                                                 { return pzem.current(); }}});
    writer.getModel(113)->getPoint("W")->setPointFunction({.float32 = {.function = [](void *param)
                                                                                              { return pzem.power(); }}});
    writer.getModel(113)->getPoint("Hz")->setPointFunction({.float32 = {.function = [](void *param)
                                                                                               { return pzem.frequency(); }}});
    writer.getModel(113)->getPoint("PF")->setPointFunction({.float32 = {.function = [](void *param)
                                                                                               { return pzem.pf(); }}});
    writer.getModel(113)->getPoint("WH")->setPointFunction({.float32 = {.function = [](void *param)
                                                                                               { return pzem.energy(); }}});

    while (1)
    {
        writer.poll();
        // Print the values to the Serial console
        printf("Voltage: ");
        printf("%f", pzem.voltage());
        printf("V\n");
        printf("Current: ");
        printf("%f", pzem.current());
        printf("A\n");
        printf("Power: ");
        printf("%f", pzem.power());
        printf("W\n");
        printf("Energy: ");
        printf("%f", pzem.energy());
        printf("kWh\n");
        printf("Frequency: ");
        printf("%f", pzem.frequency());
        printf("Hz\n");
        printf("PF: ");
        printf("%f", pzem.pf());
    }
}
