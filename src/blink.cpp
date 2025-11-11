// INCLUDE THE H FILE 
#include "blink.h"

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
    clearTerminalTask();

    char userInput; // user input
    int blinkCount = 0;
    int numOfValidCodes = 0;    // track valid code reads for parsing function
    // allocate mem for array of codes if it exists
    int* codeValues = nullptr; 
                              
    
    std::cout << "1. Scan Engine\n";
    std::cout << "2. Scan Airbags\n";
    std::cout << "3. About the Diagnostics Tool\n";
    std::cout << "4. Reset Engine Code\n";
    std::cout << "5. Quit\n";

    std::cout << "\nPick: ";

    while (userInput != '5')
    {
        std::cin >> userInput;

        // This switch case will handle user selection
        switch (userInput)
        {
            case '1':
                parsingTask(codeCount, numOfValidCodes);
                codeTranslationTask(codeValues, numOfValidCodes, 100);
                break;
            case '2':
                parsingTask(codeCount, numOfValidCodes);
                codeTranslationTask(codeValues, numOfValidCodes, 200);
                break;
            case '3':
                loadSoftwareInstructions();
                break;
            case '4':
                resetCodeTask();
                break;
            case '5':
                std::cout << "\nProgram End\n\n";
                gpio_put(ON, 0);
                return 0;
            default:
                std::cout << "\nInvalid Entry\n\n";
        }
        std::cout << "1. Scan Engine\n";
        std::cout << "2. Scan Airbags\n";
        std::cout << "3. About the Diagnostics Tool\n";
        std::cout << "4. Reset Engine Code\n";
        std::cout << "5. Quit\n";

        std::cout << "\nPick: ";
    
    }

    /// deallocate mem
    delete[] codeValues;

    return 0;
}

/*
If the code is a two-digit number, the "tens" digit will be displayed first, 
then for a short 1.6-second period the light will be dark, then the "ones" 
digit will be displayed. This will repeat after a four-second dark pause. 
If there are multiple codes, they will each be separated by a four-second 
pause and may include two-digit codes, so pay attention.
*/
int parsingTask(int* codeValues, int &numOfValidCodes)
{
    clearTerminalTask();
 
    int codeReadCount = 0; // keep track of code read count

    // another contol mechanism to process all the error codes
    bool control = true;
    int tempVal = 0;    // store temp result before appending

    std::cout << "\nReading in progress.... Dont not unplug device\n";

    // WHAT NEEDS TO BE DONE
    while (control)
    {
        // I need to call codereadtask twice
        // I must append value into the array
        tempVal = codeReadTask();

        //append array
        codeValues[codeReadCount] = tempVal;

        // increment the code read count
        codeReadCount++;

        // I must check if the second value is not the same
        if (codeReadCount > 1 && codeExists(codeValues, codeReadCount, tempVal))
        {
            control = false;
        }
    }

    // add corrected value 
    numOfValidCodes = codeReadCount -1;

    // return sucess
    return 0;
}

/*
code exists function is to to deal with the multiple error code possibility
this isa helper function of the codeReadTask(). 
*/
bool codeExists(int* codeValues, int codeReadCount, int tempVal) 
{
    for (int i = 0; i < codeReadCount; i++) 
    {
        if (codeValues[i] == tempVal)
        {
            return true;
        }
    }
    return false;
}

int codeReadTask()
{
    // I need to intilize a pin in order to start reading
    bool reading = gpio_get(ECU_TEST);

    // control loop
    bool control = true;

    float timeKeep = 0.0;
    int tens = 0;
    int ones = 0;
    int total = 0;

    while (control) 
    {
        reading = !gpio_get(ECU_TEST); // update every loop

        if (reading) // signal is low
        {                       
            sleep_ms(100);
            timeKeep += 0.1;                 // increment in seconds

            if (timeKeep >= 1.6 && tens == 0) 
            {
                tens += 10;
            } 
            else if (timeKeep >= 1.0 && tens > 0 && ones == 0) 
            {
                ones += 1;
            } 
            else if (timeKeep >= 4.0) 
            {
                total = tens + ones;
                control = false;    // ends while loop
            }
        } 
        else 
        {
            timeKeep = 0; // reset if signal goes high
        }
    }

    return total;
}


/*
loadSoftwareInstructions - function will assist users on the process of 
utilizing this diagnostics tool.
*/
void loadSoftwareInstructions()
{
    clearTerminalTask();
    // instruction manual
    std::cout << "\n##############################\n";
    std::cout << "# How To Use Diagnostic Tool #\n";
    std::cout << "##############################\n\n";
    std::cout << "~~ This isn't final instruction guide ~~\n\n";
    std::cout << "Getting Started:\n\n";
    std::cout << "- In order to get started you plug in your device, "; 
    std::cout << "once plugged in, turn your\n";
    std::cout << "  key into accessory mode\n\n";
    std::cout << "- Open your terminal and interact with the interface to get ";
    std::cout << "to the appropriate setting\n\n";
    std::cout << "Code Reset:\n\n";
    std::cout << "- Allow the system 10 minutes in order to reset the engine code\n\n";

    

    char input;

    // return back to menu
    std::cout << "\nEnter 1 to Return Back to Main Menu\n\n";

    // return to the menu
    while(input != '1')
    {
        std::cin >> input;
 
        if (input != '1')
        {
            std::cout << "\nInvalid Entry, Enter 1 to Return Back to Main Menu\n\n";
        }
    }

    clearTerminalTask();
}

void resetCodeTask()
{

//################# USER NOTICE WHILE RESETING CODE ############################
   
    // clear previous terminal commands to make it easier to read
    clearTerminalTask();

    std::cout << "\n IMPORTANT NOTICE\n";
    std::cout << "###################\n";
    
    std::cout << "Keep termimal running while reseting code. Process may take up";
    std::cout << "to 10 minutes.\n"; 

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

            std::cout << "\n" << minutes << ":";
            if (seconds < 10)
            {
                std::cout << "0";    // add 0 when seconds is less than 0
            }
            std::cout << seconds << " remaining....\n\n";
        }
 	
    }

    gpio_put(ENGINE_RESET, 0);  //stop signal

    clearTerminalTask();

    std::cout << "\nEngine Codes Cleared.\n\n";
}

void clearTerminalTask()
{
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

    std::cout << "#########################################\n";
    std::cout << "# NA Miata Diagnostics Tool Version 1.0 #\n";
    std::cout << "#########################################\n\n";
}

void codeTranslationTask(int* codeValues, int count, int fileId)
{
    // ENGINE = 100 AIRBAG = 200

    // ################## ERROR CODES ##########################################

    Dictionary ecuDiagnostics[] = {
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

    Dictionary airbagDiagnostics[] = {
        {101, 200, "*Faulty Diagnostic Module\n*Poor Connection Of Diagnostic Module Connector"},
        {3,   200, "*Open Circuit\n*Poor Connection of Power Source Circuit"},
        {5,   200, "*Faulty Front Impact Sensor"},
        {10,  200, "*Faulty Diagnostic Module"},
        {4,   200, "*Faulty Rear safing Sensor"},
        {6,   200, "*Faulty Air Bag Module\n*Poor Connection Of Clockspring Connector"},
        {7,   200, "*Poor Wiring Harness Ground"},
        {8,   200, "*Poor Ground Of Front Impact Sensor"},
        {9,   200, "*Open Circuit Between Diagnostic Module and Front Impact Sensor"},
        {2,   200, "*Poor Ground Of All Front Impact Sensors"}
    };

    // ############# OUTPUT CODE ###############################################
    if (fileId == 100)
    {
        for (int i = 0; i < sizeof(ecuDiagnostics) / sizeof(ecuDiagnostics[0]); i++)
        {
            if (ecuDiagnostics[i].key == count && ecuDiagnostics[i].fileID == fileId)
            {
                std::cout << ecuDiagnostics[i].value;
            }
        }
    }
    else if (fileId == 200)
    {
        for (int i = 0; i < sizeof(airbagDiagnostics) / sizeof(airbagDiagnostics[0]); i++)
        {
            if (airbagDiagnostics[i].key == count && airbagDiagnostics[i].fileID == fileId)
            {
                std::cout << airbagDiagnostics[i].value;
            }
        }
    }
    else
    {
        std::cout << "\nERROR OCCOURS WHILE PROCESSING ENGINE CODE...\n PLEASE TRY AGAIN.\n";
    }
}
