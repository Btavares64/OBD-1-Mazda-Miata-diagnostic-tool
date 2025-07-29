#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1024
// ########## DICTIONARY TO HANDLE CODES ###############

typedef struct Dictionary 
{
    int key;
    int fileID; 
    char value[MAX_SIZE]; 
} dict;


int codeTranslation(int count, int fileId);

int main()
{
    codeTranslation(9, 200);

    printf("\nLets see if we will return back to main\n");
    return 0;
}

int codeTranslation(int count, int fileId)
{
    // ENGINE = 100 AIRBAG = 200

    // ################## ERROR CODES #####################################################

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

    // ############# OUTPUT CODE ############################################################
    if (fileId == 100)
    {
        for (int i = 0; i < sizeof(ecuDiagnostics) / sizeof(ecuDiagnostics[0]); i++)
        {
            if (ecuDiagnostics[i].key == count && ecuDiagnostics[i].fileID == fileId)
            {
                printf("%s ", ecuDiagnostics[i].value);

                return 0;
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
        }
    }
}