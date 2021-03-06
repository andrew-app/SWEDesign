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
        strcpy_s(command, stdSize,line);
    }
    else strcpy_s(command, stdSize,"Error, problems with pipe!\n");

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
    int val = 0; //value from text file
    int portb = 0; //value sent to port b
    int retvalue = 0;// value returned from ousb command function
    int upperbits = 240;//11110000 bitwise AND when val > 15
    int largenum = 0; //variable to hold value from pb7-pb4
  

    //write output from reading to LED
    char myArray[stdSize];//as 1 char space for null is also required
    char number[stdSize];


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

            if (isnum == 1)
            {

                val = stoi(argline);


                if (val > 15)
                {
                    // for first iteration
                    largenum = upperbits & val;

                    portb = largenum | val;
                }

                else
                {
                    portb = largenum | val;
                }





                char writeportb[stdSize] = "ousb io portb ";

            
                _itoa_s(portb, number, stdSize, 10);


                cout << number << endl;

                strcat_s(writeportb, number);

                retvalue = OUSBcommand(writeportb);

                memset(number, 0, stdSize);

                Sleep(100);

            }
        }
        myfile.close();
    }

    else cout << "File specified not found." << endl;

    return 0;
}
