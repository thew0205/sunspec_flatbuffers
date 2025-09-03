

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
ModbusRTUSlave modbus(Serial1, MAX485_CTRL);

PZEM004Tv30 pzem;

int main()
{

    stdio_init_all();
    pzem = PZEM004Tv30(Serial0, 1, 0, 1);

    Serial1.begin(BAUD_9600, Pin::txPin, Pin::rxPin);

    modbus.begin(1, BAUD_9600, SERIAL_8N1);

    SunspecDeviceWriter writer{ modbus};
    writer.initAll({SunspecModelList_kModel1, SunspecModelList_kModel113});
    SunspecPointFunction functMn{.str = {.function = [](void *param) -> string
                                         { return "Matthew"; }}};

    writer.getModel(SunspecModelList_kModel1)->getTopLevelPoint("Mn")->setPointFunction(functMn);

    writer.getModel(SunspecModelList_kModel1)->getTopLevelPoint("Opt")->setPointFunction({.str = {.function = [](void *param) -> string
                                                                                                  { return "Busoye Tolulope Matthew"; }}});
    writer.getModel(SunspecModelList_kModel1)->getTopLevelPoint("DA")->setPointFunction({.uint16 = {.function = [](void *param) -> uint16_t
                                                                                                    { return 1; }}});
    writer.getModel(SunspecModelList_kModel1)->getTopLevelPoint("Opt")->setPointFunction({.str = {.function = [](void *param) -> string
                                                                                                  { return "Busoye Tolulope Matthew"; }}});
    writer.getModel(SunspecModelList_kModel1)->getTopLevelPoint("DA")->setPointFunction({.uint16 = {.function = [](void *param) -> uint16_t
                                                                                                    { return 1; }}});

    writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("A")->setPointFunction({.float32 = {.function = [](void *param)
                                                                                                      { return pzem.current(); }}});
    writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("PhVphA")->setPointFunction({.float32 = {.function = [](void *param)
                                                                                                           { return pzem.voltage(); }}});

    writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("AphA")->setPointFunction({.float32 = {.function = [](void *param)
                                                                                                         { return pzem.current(); }}});
    writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("W")->setPointFunction({.float32 = {.function = [](void *param)
                                                                                                      { return pzem.power(); }}});
    writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("Hz")->setPointFunction({.float32 = {.function = [](void *param)
                                                                                                       { return pzem.frequency(); }}});
    writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("PF")->setPointFunction({.float32 = {.function = [](void *param)
                                                                                                       { return pzem.pf(); }}});
    writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("WH")->setPointFunction({.float32 = {.function = [](void *param)
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
