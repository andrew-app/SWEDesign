#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

#define strSize 256
using namespace std;

int OUSBcommand(char* command);//function prototype



int OUSBcommand(char* command)
{
    FILE* fpipe;
    char line[strSize] = {};

    fpipe = (FILE*)_popen(command, "r");
    if (fpipe != NULL)
    {
        while (fgets(line, sizeof(line), fpipe))
        {   // do nothing here, or print out debug data
            //cout << line; // print out OUSB data for debug purposes
        }
        _pclose(fpipe);   // close pipe

        // caller can see whole ousb string in str so any errors can be detected
        strcpy_s(command, strSize, line);
    }
    else strcpy_s(command, strSize, "Error, problems with pipe!\n");

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


int main() {
    string argline;
    ifstream myfile("test.txt");
    int temp = 0;
    int val = 0;
    int retvalue = 0;
     //write output from reading to LED
    char myArray[strSize];//as 1 char space for null is also required


    
    if (myfile.is_open())
    {
        while (getline(myfile, argline))
        {
            bool isnum = true;
            memset(myArray, 0, 256);
            strcpy_s(myArray, strSize, argline.c_str());
            for (int i = 0; myArray[i] != '\0'; i++)
            {
                if (isdigit(myArray[i]))
                    temp = 1;
                else
                {
                    cout << "Y" << endl;
                    isnum = false;
                    break;
                }
            }
            if (isnum == 1)
            {
                
                val = stoi(argline);

                if (val > 15)
                    cout << "Y" << endl;

                else
                {
                    char writeportb[strSize] = "ousb -r io PORTB ";
                    strcat_s(writeportb, myArray);
                    retvalue = OUSBcommand(writeportb);
                    cout << val << endl;
                    Sleep(100);
                }
            }
        }
        myfile.close();
    }

    else cout << "F" << endl;

    return 0;
}
