#include <stdio.h>

#include <iostream>

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"

IMPORT_TEST_GROUP(Sunspec_Init);

int main(int ac, char **av)
{

    printf("\nRunning tests with CppUTest\n\n");

    const char *fav[] = {"sunspec", "-c"};

    return CommandLineTestRunner::RunAllTests(sizeof(fav) / sizeof(fav[0]), fav);
}
