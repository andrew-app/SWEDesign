#include <string>
#include <stdio.h>
#include <iostream>
#include <cstring>

#define strSize 256

using namespace std;

int OUSBcommand(char *command);//function prototype

int OUSBcommand(char *command)
{
	FILE *fpipe;
	char line[strSize] = {};

	fpipe = (FILE*)popen(command,"r");
	if( fpipe != NULL )
	{
		while(fgets(line, sizeof(line), fpipe))
		{   // do nothing here, or print out debug data
			//cout << line; // print out OUSB data for debug purposes
		}
		pclose(fpipe);   // close pipe

		// caller can see whole ousb string in str so any errors can be detected
		strcpy(command,line);
	}
	else strcpy(command,"Error, problems with pipe!\n");

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

int main(int argc, char* argv[])
{



	char writeportb[strSize] = "sudo ousb -r io PORTB "; //write output from reading to LED


	strcat(writeportb,argv[1]);

	cout << writeportb <<endl;

	int retvalue = OUSBcommand(writeportb);


	if (retvalue != string::npos)
	{
		cout << "OUSB return value: " << retvalue << endl;
		/*
		char line[4] = {};

		sprintf(line, "%d", retvalue); // convert returned integer to char array

		strcat(writeportb,line);


		int portb = OUSBcommand(writeportb);
		*/
	}


	return 0;
}
