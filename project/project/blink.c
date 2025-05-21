#include <stdio.h>
#include <time.h>
//#include "pico/stdlib.h" // pico sdk library
#include <string.h>
#include <unistd.h>

/*
Author: Brandon Tavares
*/

// ######### GLOABAL VARIABLE DECLARATION ##############



// ######### FUNCTION PROTOTYPES #######################

void checkEngine();

void checkAirbags();

void aboutTool();

void resetCode();

void clearTerminal();

int main()
{
    // ######### INTILIZE PINS ##############


    // ######### INTRODUCTION AND USER SELECTION ##############
    
    // clear previous terminal commands to make it easier to read
    clearTerminal();

    char userInput; // user input
    
    //stdio_init_all();
    
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
                checkEngine();
                break;
            case '2':
                checkAirbags();
                break;
            case '3':
                aboutTool();
                break;
            case '4':
                resetCode();
                break;
            case '5':
                printf("\nProgram End\n\n");
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

// ######### FUNCTION IMPLEMENTATION ##############
void checkEngine()
{
    // clear previous terminal commands to make it easier to read
    clearTerminal();

    puts("\ncheck engine has been successfully reached\n");
}

void checkAirbags()
{
    // clear previous terminal commands to make it easier to read
    clearTerminal();

    puts("\ncheck airbags has been successfully reached\n");
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
