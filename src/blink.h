// ######### INCLUSION GUARDS ####################
#ifndef BLINK_H
#define BLINK_H

// ########## INCLUDE STANDARD LIBRARIES #############
#include <iostream>                    
#include <string.h>
#include <stdbool.h>

// ########### INCLUDE PICO RELATED LIBRARIES #########
extern "C" {
    #include "pico/stdio.h"
    #include "pico/stdlib.h"
    #include "pico/time.h"
}


// ######### CONSTANT DEFINITIONS #############
#define ON 17
#define AIRBAG_TEST 16
#define ECU_TEST 19
#define MAX_SIZE 1024


// ########## DICTIONARY TO HANDLE CODES ###############
class Dictionary
{
    public:
        int key;
        int fileID;
        char value[MAX_SIZE];
};

// ######### FUNCTION PROTOTYPES #######################

int parsingTask(int* codeValues, int &numOfValidCodes, int fileId);

bool codeExists(int* array, int codeReadCount, int tempVal);

int codeReadECU();

int codeReadAirBag();

void loadSoftwareInstructions();

void resetCodeTask();

void clearTerminalTask();

void codeTranslationTask(int* codeValues, int numOfValidCodes, int fileId);

#endif 