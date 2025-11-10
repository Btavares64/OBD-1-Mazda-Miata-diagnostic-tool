// ######### INCLUSION GUARDS ####################
#ifndef BLINK_H
#define BLINK_H

// ########## INCLUDE STANDARD LIBRARIES #############
#include <iostream>                    
#include <string.h>
#include <stdbool.h>

// ########### INCLUDE PICO RELATED LIBRARIES #########
extern "C" {
    #include "pico/stdlib.h"
}


// ######### CONSTANT DEFINITIONS #############
#define ON 17
#define READ_CODE 16
#define ENGINE_RESET 18
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

int codeReadTask();

void loadSoftwareInstructions();

void resetCodeTask();

void clearTerminalTask();

void codeTranslationTask(int count, int fileId);

#endif 