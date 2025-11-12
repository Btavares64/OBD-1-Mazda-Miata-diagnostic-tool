// ########## INCLUDE STANDARD LIBRARIES #############
#include <iostream>                    
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 1024

// ########## DICTIONARY TO HANDLE CODES ###############
class Dictionary
{
    public:
        int key;
        int fileID;
        char value[MAX_SIZE];
};

void codeTranslationTask(int* codeValues, int count, int fileId);

int main()
{
    int array[] = {101, 10 , 4};

    codeTranslationTask(array, 3, 100);

    std::cout << "\nLets see if we will return back to main\n";

    return 0;
}

void codeTranslationTask(int* codeValues, int count, int fileId)
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
    while (index < count)
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
            }
        }
        // increment to the next element in the array if it exists
        index ++;
    }
}
