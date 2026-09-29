#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/stdio.h"
#include <iostream>

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"

IMPORT_TEST_GROUP(Flatbuffer_Model1);
IMPORT_TEST_GROUP(Flatbuffer_Model160);
extern float he11lp(float a, float b);
float he11lp(float a, float b)
{
    return a + b;
}
int main(int ac, char **av)
{

    float a = 0.5234324352353445464555;
    float b = 1.5;

    stdio_init_all();
    sleep_ms(5000);

    printf("\nRunning tests with CppUTest\n %f\n", he11lp(a, b));

    const char *fav[] = {"sunspec", "-c"};

    CommandLineTestRunner::RunAllTests(sizeof(fav) / sizeof(fav[0]), fav);
    return 0;
    while (1)
        ;
}
