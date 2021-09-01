#include <string>
#include <stdio.h>
  //  or "stdafx.h" for older versions of VS
#include <iostream>
#include <cstring>
#include <stdlib.h>

using namespace std;

int ReadPortB();
void WritePortB(int val);

int ReadPortB()
{
	int portb = 0;

	const char *command = "ousb -r io PORTB";  // must be const
	FILE *fpipe;
	char line[256];

	fpipe = (FILE*)_popen(command, "r");
	if (fpipe != NULL)
	{
		while (fgets(line, sizeof(line), fpipe))
		{   // do nothing here, or print out debug data
			// cout << line; // print out OUSB data for debug purposes
		}
		_pclose(fpipe);   // close pipe
	}
	else cout << "Error, problems with pipe!\n";

	// convert value from char array to int
	portb = (int)atoi(line);

	return portb;
}


void WritePortB(int val)
{

	char command[255] = { "ousb -r io PORTB " };
	char val_string[4] = {};

	// Convert portb integer to character array (in base 10)
	sprintf(val_string,"%d",val);
	//itoa(val, val_string, 10);
	// append the value to write to portb to the Command string
	strcat(command, val_string);

	FILE *fpipe;
	char line[256];

	fpipe = (FILE*)_popen(command, "r");
	if (fpipe != NULL)
	{
		while (fgets(line, sizeof(line), fpipe))
		{   // do nothing here, or print out debug data
			// cout << line; // print out OUSB data for debug purposes
		}
		_pclose(fpipe);   // close pipe
	}
	else cout << "Error, problems with pipe!\n";
}


int main()
{
	cout << "port B = " << ReadPortB() << endl;

	WritePortB(0x2);

	cout << "port B = " << ReadPortB() << endl;

	return 0;
}
