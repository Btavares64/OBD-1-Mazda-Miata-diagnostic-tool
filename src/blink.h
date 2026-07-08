#ifndef BLINK_H
#define BLINK_H


#include <iostream>                    
#include <string.h>
#include <stdbool.h>

extern "C" {
    #include "pico/stdio.h"
    #include "pico/stdlib.h"
    #include "pico/time.h"
}

#define ON 17
#define AIRBAG_TEST 16
#define ECU_TEST 19
#define MAX_SIZE 1024

class Dictionary
{
    public:
        int key;
        int fileID;
        char value[MAX_SIZE];
};

int parsingTask(int* codeValues, int &numOfValidCodes, int fileId);

bool codeExists(int* array, int codeReadCount, int tempVal);

int codeReadECU();

int codeReadAirBag();

void loadSoftwareInstructions();

void resetCodeTask();

void clearTerminalTask();

void codeTranslationTask(int* codeValues, int numOfValidCodes, int fileId);

#endif 
