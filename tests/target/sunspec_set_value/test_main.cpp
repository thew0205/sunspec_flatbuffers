#include <stdio.h>

#include <iostream>
#include <pico/stdlib.h>
#include <pico/stdio.h>
#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"

IMPORT_TEST_GROUP(Sunspec_Set_Value);

int main(int ac, char **av)
{

    stdio_init_all();
    sleep_ms(10000);

    printf("\nRunning tests with CppUTest\n\n");

    const char *fav[3] = {"sunspec", "-c", "-v"};

    CommandLineTestRunner::RunAllTests(3, fav);
    while (1)
    {
        /* code */
    }
}
