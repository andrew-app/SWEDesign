#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
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

    string debug = line; //copy char array of ousb.exe output to a string

    int value = 0;

    value = (int)atoi(line);

    if (debug.find(checktxt) != string::npos) {
        cout << "OUSB is not connected." << endl;

        value = -1; // if ousb not connected set portb to -1 same as npos(not positive)

    }

    // convert value from char array to int

    return value;
}


int main(int argc, char* argv[]) {
    string argline;
    ifstream myfile(argv[1]);
    int val = 0;
    int temp = 0;
    char myArray[stdSize] = {};
    if (argc > 2) {
        cout << "Incorrect number of command line arguments" << endl;
        return 0;
    }
    
    if (myfile.is_open())
    {
        while (getline(myfile, argline))
        {
            bool isnum = true;

            
            memset(myArray, 0, stdSize);
            strcpy_s(myArray, stdSize, argline.c_str());



            for (int i = 0; myArray[i] != '\0'; i++)
            {
                if (isdigit(myArray[i]))
                    (void)0;
                else
                {
                    cout << "Invalid Value" << endl;
                    isnum = false;
                    break;
                }
            }

            if (isnum == true)
            {
                val = stoi(argline);

                if (val > 15)
                {
                    cout << "Out of Range Value" << endl;
                }

                else
                {

                   

                    char writeportb[stdSize] = "ousb io portb ";

                    char number[stdSize] = {};


                    strcpy_s(number, stdSize, argline.c_str());

                    strcat_s(writeportb, number);

                    temp = OUSBcommand(writeportb);

                    if (temp != -1)
                    {
                        cout << val << endl;
                    }
                    
                    Sleep(500);
                }

            }
        }
        myfile.close();
    }

    else cout << "File specified not found." << endl;

    return 0;
}
