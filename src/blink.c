// INCLUDE C STANDARD LIBRARIES
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>

// INCLUDE .H FILES
#include "pico/stdlib.h"
#include "FreeRTOSConfig.h"
#include "task.h"

#define ON 17
#define READ_CODE 16
#define ENGINE_RESET 18
#define ECU_TEST 19
#define MAX_SIZE 50

// ########## DICTIONARY TO HANDLE CODES ###############

typedef struct Dictionary 
{
    int key;
    int fileID; 
    char value[MAX_SIZE]; 
} dict;

// ######### FUNCTION PROTOTYPES #######################

int codeReadTask();

void loadSoftwareInstructions();

void resetCodeTask();

void clearTerminalTask();

int codeTranslationTask(int count, int fileId);

int main()
{
    // ######### INTILIZE PINS ##############
    stdio_init_all();

    gpio_init(ON);	            
    gpio_set_dir(ON, GPIO_OUT); // CONFIRM IF THE DEVICE IS ON

    gpio_init(READ_CODE);             
    gpio_set_dir(READ_CODE, GPIO_IN); // START DIAGNOSTICS 

    gpio_init(ECU_TEST);             
    gpio_set_dir(ECU_TEST, GPIO_IN); // COUNT BLINKS

    gpio_init(ENGINE_RESET);             
    gpio_set_dir(ENGINE_RESET, GPIO_IN); // RESET ENGINE

    // ######### INTRODUCTION AND USER SELECTION ##############
    
    gpio_put(ON, 1);

    // start program when minicom is open
    while(!stdio_usb_connected())
    {
        sleep_ms(100);
    }

    // clear previous terminal commands to make it easier to read
    clearTerminal();

    char userInput; // user input

    int blinkCount = 0;
    
    printf("1. Scan Engine\n");
    printf("2. Scan Airbags\n");
    printf("3. About the Diagnostics Tool\n");
    printf("4. Reset Engine Code\n");
    printf("5. Quit\n");

    printf("\nPick: ");

    while (userInput != '5')
    {
        scanf(" %c", &userInput);

        // This switch case will handle user selection
        switch (userInput)
        {
            case '1':
                blinkCount = codeRead();
                codeTranslation(blinkCount, 100);
                break;
            case '2':
                blinkCount = codeRead();
                codeTranslation(blinkCount, 200);
                break;
            case '3':
                loadSoftwareInstructions();
                break;
            case '4':
                resetCode();
                break;
            case '5':
                printf("\nProgram End\n\n");
                gpio_put(ON, 0);
                return 0;
            default:
                printf("\nInvalid Entry\n\n");
        }
        
        printf("1. Scan Engine\n");
        printf("2. Scan Airbags\n");
        printf("3. About the Diagnostics Tool\n");
        printf("4. Reset Engine Code\n");
        printf("5. Quit\n");

	    printf("\nPick: ");
    
    }
     
    return 0;
}

int codeReadTask()
{
    clearTerminal();
    
    puts("\nReading in progress.... Dont not unplug device\n");

    // I need to intilize a pin in order to start reading
    bool reading = gpio_get(ECU_TEST);

    int timeKeep = 5;
    int tens = 0;
    int ones = 0;

    while(timeKeep != 0)
    {
        if (!gpio_get(ECU_TEST))
        {
            sleep_ms(1000);
	        timeKeep--;

            if (timeKeep == 4)
            {
                tens += 10;
            }
            else if (timeKeep == 1)
            {
                ones += 1;
            }
        }
        else 
        {
            timeKeep = 5;
        }
    }
    // need to return the count
    return tens + ones;
}

/*
loadSoftwareInstructions - function will assist users on the process of utilizing this
diagnostics tool.
*/
void loadSoftwareInstructions()
{
    // instruction manual
    printf("\n##############################\n"
       "# How To Use Diagnostic Tool #\n"
       "##############################\n\n"
       "~~ This isn't final instruction guide ~~\n\n"
       "Getting Started:\n\n"
       "- In order to get started you plug in your device, once plugged in, turn 
       your\n"
       "  key into accessory mode\n\n"
       "- Open your terminal and interact with the interface to get to the 
       appropriate setting\n\n"
       "Code Reset:\n\n"
       "- Allow the system 10 minutes in order to reset the engine code\n\n");

    

    char input;
    // return back to menu
    printf("\nEnter 1 to Return Back to Main Menu\n\n");

    // return to the menu
    while(input != '1')
    {
        scanf (" %c", &input);
 
        if (input != '1')
        {
            printf("\nInvalid Entry, Enter 1 to Return Back to Main Menu\n\n");
        }
    }

    clearTerminal();
}

void resetCodeTask()
{

//################# USER NOTICE WHILE RESETING CODE ############################
   
    // clear previous terminal commands to make it easier to read
    clearTerminal();

    printf("\n IMPORTANT NOTICE\n");
    printf("###################\n");
    
    printf("Keep termimal running while reseting code. Process may take up to 10
         minutes.\n"); 

    gpio_put(ENGINE_RESET, 1);


//####################### TIMER ################################################
    // update user every 30 seconds on the current wait time
    
    int timeKeep = 600;
    
    while(timeKeep != 0)
    {
        sleep_ms(1000);
	    timeKeep--;

        if (timeKeep % 30 == 0)
        {
            int minutes = timeKeep / 60;
            int seconds = timeKeep % 60;

            printf("\n%d:%02d remaining....\n\n", minutes, seconds);
        }
 	
    }

    gpio_put(ENGINE_RESET, 0);  //stop signal

    clearTerminal();

    printf("\nEngine Codes Cleared.\n\n");
}

void clearTerminalTask()
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n
        \n\n\n\n\n\n\n\n\n\n\n\n\n");

    printf("#########################################\n");
    printf("# NA Miata Diagnostics Tool Version 1.0 #\n");
    printf("#########################################\n\n");
}


int codeTranslationTask(int count, int fileId)
{
    // ENGINE = 100 AIRBAG = 200

    // ################## ERROR CODES ##########################################

    dict ecuDiagnostics[] = {
        {1, 100, "Ignition pulse (No Igf signal)"},
        {2, 100, "No Ne signal"},
        {3, 100, "No G signal"},
        {8, 100, "Airflow meter open or short circuit"},
        {9, 100, "Water thermistor open or short circuit"},
        {10, 100, "Intake air thermistor in airflow meter open or short circuit"},
        {12, 100, "Throttle position sensor open or short circuit"},
        {14, 100, "Atmospheric pressure sensor open or short circuit"},
        {15, 100, "Oxygen sensor <0.55 V 180 sec after 1500 rpm"},
        {17, 100, "Oxygen sensor unchanged after 1500 rpm"},
        {26, 100, "Solenoid valve (Evaporative canister purge)"},
        {34, 100, "ISC Valve"}
    };

    dict airbagDiagnostics[] = {
        {101, 200, "*Faulty Diagnostic Module\n*Poor Connection Of Diagnostic 
            Module Connector"},
        {3,   200, "*Open Circuit\n*Poor Connection of Power Source Circuit"},
        {5,   200, "*Faulty Front Impact Sensor"},
        {10,  200, "*Faulty Diagnostic Module"},
        {4,   200, "*Faulty Rear safing Sensor"},
        {6,   200, "*Faulty Air Bag Module\n*Poor Connection Of Clockspring 
            Connector"},
        {7,   200, "*Poor Wiring Harness Ground"},
        {8,   200, "*Poor Ground Of Front Impact Sensor"},
        {9,   200, "*Open Circuit Between Diagnostic Module and Front Impact 
            Sensor"},
        {2,   200, "*Poor Ground Of All Front Impact Sensors"}
    };

    // ############# OUTPUT CODE ###############################################
    if (fileId == 100)
    {
        for (int i = 0; i < sizeof(ecuDiagnostics) / sizeof(ecuDiagnostics[0]); i++)
        {
            if (ecuDiagnostics[i].key == count && ecuDiagnostics[i].fileID == fileId)
            {
                printf("%s ", ecuDiagnostics[i].value);

                return 0;
            }
            // CREATE ERROR CASE IF READING DOESNT WORK. GOOD FOR DEBUGGING :)
            else
            {
                printf("\nERROR OCCOURS WHILE PROCESSING ENGINE CODE...\n
                        PLEASE TRY AGAIN.\n");
            }
        }
    }
    else if (fileId == 200)
    {
        for (int i = 0; i < sizeof(airbagDiagnostics) / sizeof(airbagDiagnostics[0]); i++)
        {
            if (airbagDiagnostics[i].key == count && airbagDiagnostics[i].fileID == fileId)
            {
                printf("%s ", airbagDiagnostics[i].value);

                return 0;
            }
            // CREATE ERROR CASE IF READING DOESNT WORK. GOOD FOR DEBUGGING :)
            else
            {
                printf("\nERROR OCCOURS WHILE PROCESSING AIRBAG CODE...\n
                        PLEASE TRY AGAIN.\n");
            }
        }
    }
}

