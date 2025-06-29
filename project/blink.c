#include <stdio.h>
#include "pico/stdlib.h"
#include "stdbool.h"
#include "instructions.h"	// for the instructions file
#include <string.h>


#define ON 17
#define READ_CODE 16
#define ENGINE_RESET 18
#define ECU_TEST 19


// ######### FUNCTION PROTOTYPES #######################

void codeRead();

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
    gpio_set_dir(AIRBAG_TEST, GPIO_IN); // START DIAGNOSTICS 

    gpio_init(ECU_TEST);             
    gpio_set_dir(ECU_TEST, GPIO_IN); // COUNT BLINKS

    gpio_init(ENGINE_RESET);             
    gpio_set_dir(ENGINE_RESET, GPIO_IN); // RESET ENGINE

    // ######### INTRODUCTION AND USER SELECTION ##############

    
    gpio_get(ON, 1);

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
                gpio_get(ON, 0);
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


void codeRead()
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

}

/*

aboutTool - function will assist users on the process of utilizing this
diagnostics tool.

Dependencies - about.txt file
*/
void aboutTool()
{

    // clear previous terminal commands to make it easier to read
    clearTerminal();

    // array to store the contents of the instructions file
    char buffer[1024];
    char input;
    char ch;

    FILE *document = fopen("instructions.txt", "r");

    fgets(buffer, 1024, document); // store file contents into the buffer

    // output document
    while ((ch = fgetc(document)) != EOF)
    {
        putchar(ch);
    }

    fclose(document); // close file
    
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

    gpio_get(ENGINE_RESET, 1);


//####################### TIMER ######################################################
    // update user every 30 seconds on the current wait time
    
    int timeKeep = 600;
    
    while(timeKeep != 0)
    {
        sleep (1);
	    timeKeep--;

        if (timeKeep % 30 == 0)
        {
            int minutes = timeKeep / 60;
            int seconds = timeKeep % 60;

            printf("\n%d:%02d remaining....\n\n", minutes, seconds);
        }
 	
    }

    gpio_get(ENGINE_RESET, 0);  //stop signal
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
        puts("You are reading from the ECU"):
    }
}
