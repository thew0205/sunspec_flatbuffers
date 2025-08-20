#include <stdio.h>

#include <iostream>

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"
#include <pico/stdio.h>

int main(int ac, char **av)
{

    stdio_init_all();

    printf("\nRunning tests with CppUTest\n\n");

    const char *fav[3] = {"sunspec", "-c", "-v"};

    CommandLineTestRunner::RunAllTests(3, fav);
    while (1)
        ;
}


