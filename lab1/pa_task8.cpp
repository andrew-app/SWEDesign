#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

#define stdSize 256
using namespace std;

int OUSBcommand(char* command);//function prototype



int OUSBcommand(char* command)
{
    FILE* fpipe;
    char line[stdSize] = {};

    fpipe = (FILE*)_popen(command, "r");
    if (fpipe != NULL)
    {
        while (fgets(line, sizeof(line), fpipe))
        {   // do nothing here, or print out debug data
            //cout << line; // print out OUSB data for debug purposes
        }
        _pclose(fpipe);   // close pipe

        // caller can see whole ousb string in str so any errors can be detected
        strcpy_s(command, stdSize, line);
    }
    else strcpy_s(command, stdSize, "Error, problems with pipe!\n");

    char checktxt[50] = "Device not found";

    char invalid[50] = "Invalid Register";

    string debug = line; //copy char array of ousb.exe output to a string

    int value = 0;

    value = (int)atoi(line);



    if (debug.find(checktxt) != string::npos) {
        cout << "OUSB is not connected." << endl;

        return -1;

    }

    else if(debug.find(invalid) != string::npos) {
        cout << "Invalid command/register" << endl;

        return -2;
    }




   
    return value;
}


int main(int argc, char* argv[]) {
    bool isnum = true;
    
    int val = 0;
    

    if (argc > 2)
    {
        cout << "Too many cmd line arguments." << endl; 

        return 0;
    }
    else if(argc == 2)
    {
        char command[stdSize] = "ousb io portb ";

        for (int i = 0; argv[1][i] != '\0'; i++)
        {
            if (isdigit(argv[1][i]))
                (void)0;

            else
            {
                cout << "Invalid Command Argument (numerical only)" << endl;
                isnum = false;
                break;
            }
        }

        if (isnum == true)
        {
            
            

            strcat_s(command, argv[1]);

            val = OUSBcommand(command);

            if(val != -1)
                cout << "Current PORTB value: " << val << endl;
            else cout << "Invalid command." << endl;
        }
    }

    else
    {

        char command[stdSize] = "ousb -r io portb";

        
        val = OUSBcommand(command);

        if (val != -1 && val != -2) // check if ousb connected or invalid command given
            cout << val << endl;

    }

    return 0;
}
