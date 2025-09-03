#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/stdio.h"
#include <iostream>

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"

IMPORT_TEST_GROUP(Flatbuffer_Model1);
IMPORT_TEST_GROUP(Flatbuffer_Model160);

int main(int ac, char **av)
{

    stdio_init_all();
    sleep_ms(5000);

    printf("\nRunning tests with CppUTest\n\n");

    const char *fav[] = {"sunspec", "-c"};

    CommandLineTestRunner::RunAllTests(sizeof(fav) / sizeof(fav[0]), fav);

    while (1)
        ;
}
