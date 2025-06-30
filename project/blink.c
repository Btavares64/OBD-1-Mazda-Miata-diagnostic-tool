#include <stdio.h>
#include "pico/stdlib.h"
#include "stdbool.h"
#include <string.h>


#define ON 17
#define READ_CODE 16
#define ENGINE_RESET 18
#define ECU_TEST 19


// ######### FUNCTION PROTOTYPES #######################

int codeRead();

void aboutTool();

void resetCode();

void clearTerminal();

void codeTranslation(int count, int fileId);

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
                codeTranslation(blinkCount, 2);
                break;
            case '2':
                blinkCount = codeRead();
                codeTranslation(blinkCount, 2);
                break;
            case '3':
                aboutTool();
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


int codeRead()
{
    // clear previous terminal commands to make it easier to read
    clearTerminal();

    puts("\nReading in progress.... Dont not unplug device\n");


    // I need to intilize a pin in order to start reading
    bool reading = gpio_get(ECU_TEST);

    reading = true;

    int pulseCount = 0;		// track the blinks
    
    int duration = 0;		// find when blinking is done

    while (reading)
    {
        if (!gpio_get(ECU_TEST))
	    {
            // start count
            duration++;
            sleep_ms(1000);

            if (duration > 4)
            {
                codeTranslation(pulseCount, 1);
                reading = false;	// code has been read... stop reading	
            }
        }
        else
        {
            sleep_ms(1000);

            duration = 0;

            pulseCount++;
        }
    }

    // need to return the count
    return pulseCount;
}

/*
aboutTool - function will assist users on the process of utilizing this
diagnostics tool.
*/
void aboutTool()
{
    // instruction manual
    printf("\n##############################\n"
       "# How To Use Diagnostic Tool #\n"
       "##############################\n\n"
       "~~ This isn't final instruction guide ~~\n\n"
       "Getting Started:\n\n"
       "- In order to get started you plug in your device, once plugged in, turn your\n"
       "  key into accessory mode\n\n"
       "- Open your terminal and interact with the interface to get to the appropriate setting\n\n"
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

void resetCode()
{

//################# USER NOTICE WHILE RESETING CODE ##############################
   
    // clear previous terminal commands to make it easier to read
    clearTerminal();

    printf("\n IMPORTANT NOTICE\n");
    printf("###################\n");
    
    printf("Keep termimal running while reseting code. Process may take up to 10 minutes.\n"); 

    gpio_put(ENGINE_RESET, 1);


//####################### TIMER ######################################################
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
    // clear previous terminal commands to make it easier to read
    clearTerminal();

    printf("\nEngine Codes Cleared.\n\n");
}

void clearTerminal()
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

    printf("#########################################\n");
    printf("# NA Miata Diagnostics Tool Version 1.0 #\n");
    printf("#########################################\n\n");
}


void codeTranslation(int count, int fileId)
{
    if (fileId == 1)
    {
        puts("You are reading from the airbag module");
    }
    else if (fileId == 2)
    {
        puts("You are reading from the ECU");
    }
}
