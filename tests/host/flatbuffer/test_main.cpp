#include <stdio.h>

#include <iostream>

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"

IMPORT_TEST_GROUP(Flatbuffer_Model1);
IMPORT_TEST_GROUP(Flatbuffer_Model160);

int main(int ac, char **av)
{

    printf("\nRunning tests with CppUTest\n\n");

    const char *fav[3] = {"sunspec", "-c", "-v"};

    return CommandLineTestRunner::RunAllTests(3, fav);
}
