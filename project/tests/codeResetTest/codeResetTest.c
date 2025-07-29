#include <stdio.h>
#include "sleep.h"


void resetCode();


int main()
{
    resetCode();

    printf("\nTest complete.\n");

    return 0;
}

void resetCode()
{

//################# USER NOTICE WHILE RESETING CODE ##############################
   
    // clear previous terminal commands to make it easier to read
    //clearTerminal();

    printf("\n IMPORTANT NOTICE\n");
    printf("###################\n");
    
    printf("Keep termimal running while reseting code. Process may take up to 10 minutes.\n"); 

    //gpio_put(ENGINE_RESET, 1);


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

    //gpio_put(ENGINE_RESET, 0);  //stop signal

    //clearTerminal();

    printf("\nEngine Codes Cleared.\n\n");
}