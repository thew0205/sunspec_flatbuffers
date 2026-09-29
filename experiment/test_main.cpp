#include <stdio.h>

#include <iostream>

#include "sunspec.h"



int main(int ac, char **av)
{
    const SunspecModelDef *model1;

    printf("\nRunning tests with CppUTest\n\n");
    model1 = getModelDefinition(1);
    printf("Model ID: %d\n", model1->id());

}


/*
RAM
FLASH
DYNAMIC ALLOCATION

*/