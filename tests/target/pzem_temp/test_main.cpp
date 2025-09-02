

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

    SunspecDeviceWriter writer{
        1, modbus, 0};
    writer.initAll({SunspecModelList_kModel1, SunspecModelList_kModel113});
    writer.getModel(SunspecModelList_kModel1)->getTopLevelPoint("Mn")->setValueFunction({.str = []() -> string
                                                                                         { return "Matthew"; }});
    writer.getModel(SunspecModelList_kModel1)->getTopLevelPoint("Opt")->setValueFunction({.str = []() -> string
                                                                                          { return "Busoye Tolulope Matthew"; }});
    writer.getModel(SunspecModelList_kModel1)->getTopLevelPoint("DA")->setValueFunction({.uint16 = []() -> uint16_t
                                                                                         { return 1; }});

    writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("A")->setValueFunction({.float32 = []()
                                                                                          { return pzem.current(); }});
    writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("PhVphA")->setValueFunction({.float32 = []()
                                                                                               { return pzem.voltage(); }});

    writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("AphA")->setValueFunction({.float32 = []()
                                                                                             { return pzem.current(); }});
    writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("W")->setValueFunction({.float32 = []()
                                                                                          { return pzem.power(); }});
    writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("Hz")->setValueFunction({.float32 = []()
                                                                                           { return pzem.frequency(); }});
    writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("PF")->setValueFunction({.float32 = []()
                                                                                           { return pzem.pf(); }});
    writer.getModel(SunspecModelList_kModel113)->getTopLevelPoint("WH")->setValueFunction({.float32 = []()
                                                                                           { return pzem.energy(); }});

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
