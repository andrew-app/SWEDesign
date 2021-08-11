#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
//#include <windows.h>

#define strSize 256
using namespace std;

int OUSBcommand(char* command);//function prototype



int OUSBcommand(char* command)
{
    FILE* fpipe;
    char line[strSize] = {};

    fpipe = (FILE*)popen(command, "r");
    if (fpipe != NULL)
    {
        while (fgets(line, sizeof(line), fpipe))
        {   // do nothing here, or print out debug data
            //cout << line; // print out OUSB data for debug purposes
        }
        pclose(fpipe);   // close pipe

        // caller can see whole ousb string in str so any errors can be detected
        strcpy(command, line);
    }
    else strcpy(command, "Error, problems with pipe!\n");

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
    int portb = 0;
    int retvalue = 0;
    int upperbits = 240;//11110000 bitwise AND when val > 15
    int largenum = 0; //variable to hold value in pb7-pb4
    int counter = 0;

     //write output from reading to LED
    char myArray[strSize];//as 1 char space for null is also required
    char number[1];


    if (myfile.is_open())
    {
        while (getline(myfile, argline))
        {
            bool isnum = true;
            memset(myArray, 0, strSize);
            strcpy(myArray, argline.c_str());

            counter++;
            for (int i = 0; myArray[i] != '\0'; i++)
            {
                if (isdigit(myArray[i]))
                    temp = 1;
                else
                {
                    cout << "Invalid Value" << endl;
                    isnum = false;
                    break;
                }
            }

            if (isnum == 1)
            {

                val = stoi(argline);


                if (val > 15)
                {
                  // for first iteration
                  largenum = upperbits&val;

                  portb = largenum|val;
                }

                else
                {
                  portb = largenum|val;
                }





                char writeportb[strSize] = "sudo ./ousb io portb ";


                sprintf(number, "%d", portb);
                cout << number << endl;
                strcat(writeportb, number);
                retvalue = OUSBcommand(writeportb);
                memset(number, 0, 1);
                    //Sleep(100);

            }
        }
        myfile.close();
    }

    else cout << "F" << endl;

    return 0;
}
