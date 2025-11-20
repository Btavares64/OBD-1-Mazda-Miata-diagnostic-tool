#include <iostream>
#include <stdbool.h>
#include <string.h>
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

int parsingTask(int* codeValues, int &numOfValidCodes, int fileId);

void codeTranslationTask(int* codeValues, int numOfValidCodes, int fileId);

int codeReadAirBag();

bool codeExists(int* codeValues, int codeReadCount, int tempVal);

int main()
{

    char userInput; // user input
    int blinkCount = 0;
    int numOfValidCodes = 0;    // track valid code reads for parsing function
    
    // allocate mem for array of codes if it exists
    int* codeValues = new int[MAX_SIZE]; 
                              
    
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
                parsingTask(codeValues, numOfValidCodes, 100);
                codeTranslationTask(codeValues, numOfValidCodes, 100);
                break;
            case '2':
                parsingTask(codeValues, numOfValidCodes, 200);
                codeTranslationTask(codeValues, numOfValidCodes, 200);
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                std::cout << "\nProgram End\n\n";
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

int parsingTask(int* codeValues, int &numOfValidCodes, int fileId)
{
 
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
        if (fileId == 100)
        {
            //tempVal = codeReadECU();
        }
        else if (fileId == 200)
        {
            tempVal = codeReadAirBag();
        }

        // check if the code already exists
        if (codeExists(codeValues, codeReadCount, tempVal))
        {
            std::cout << "\nCode " << tempVal << " already exists. Stopping input.\n";
            control = false;
        }
        else
        {
            // append to array
            codeValues[codeReadCount] = tempVal;
            codeReadCount++;
        }
    }

    // add corrected value 
    numOfValidCodes = codeReadCount;

        // check vals in array
    std::cout << "\nCodes stored in array:\n";
    for (int i = 0; i < numOfValidCodes; i++)
    {
        std::cout << "array[" << i << "]: " << codeValues[i] << std::endl;
    }
    // return sucess
    return 0;
}

int codeReadAirBag()
{
    int value1 = 0;

    std::cout << "\nEnter value 1: ";
    std::cin >> value1;

    return value1; 

}

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

void codeTranslationTask(int* codeValues, int numOfValidCodes, int fileId)
{
    // for my reference count is just th enumber of members

    // track the number of iterations
    int index = 0;

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

    // This is to it iterate the amount of engine codes exist in codeValues array
    while (index < numOfValidCodes)
    {
        // this is for translating any code inside of the ecu code dictionary
        if (fileId == 100)
        {
            // increment through entire size of the dictionary
            for (int i = 0; i < sizeof(ecuDiagnostics) / sizeof(ecuDiagnostics[0]); i++)
            {
                // check if the current key is equal to the value inside the array
                // and if the the current fileID is equal to the desired module
                if (ecuDiagnostics[i].key == codeValues[index] && ecuDiagnostics[i].fileID == fileId)
                {
                    // output engine code
                    std::cout << ecuDiagnostics[i].value << std::endl << std::endl;
                }
            }
        }
        // this is for translating any code inside of the airbag code dictionary
        else if (fileId == 200)
        {
            // increment through entire size of the dictionary
            for (int i = 0; i < sizeof(airbagDiagnostics) / sizeof(airbagDiagnostics[0]); i++)
            {
                // check if the current key is equal to the value inside the array
                // and if the the current fileID is equal to the desired module
                if (airbagDiagnostics[i].key == codeValues[index] && airbagDiagnostics[i].fileID == fileId)
                {
                    // output error code
                    std::cout << airbagDiagnostics[i].value << std::endl << std::endl;
                }
                else
                {
                    continue;
                }
            }
        }
        // increment to the next element in the array if it exists
        index++;
    }
}