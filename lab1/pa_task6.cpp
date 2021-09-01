#include <iostream>
#include <windows.h>

using namespace std;

int ReadPORTB();
int ReadPINC();
int ReadADC();
void WritePORTB(int val);


int ReadPORTB()
{
	int portb = 0;

	const char* command = "ousb -r io PORTB";  // must be const
	FILE* fpipe;
	char line[256] = {};

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

	memset(line, 0, 256);

	return portb;
}


int ReadPINC()
{
	int pinc = 0;

	const char* command = "ousb -r io pinc";  // must be const
	FILE* fpipe;
	char line[256] = {};

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
	pinc = (int)atoi(line);

	return pinc;
}

int ReadADC()
{
	int adc = 0;

	const char* command = "ousb -r io adc";  // must be const
	FILE* fpipe;
	char line[256] = {};

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
	adc = (int)atoi(line);

	return adc;
}

void WritePORTB(int val)
{

	char command[256] = { "ousb -r io PORTB " };
	char val_string[4] = {};

	// Convert portb integer to character array (in base 10)
	
	_itoa_s(val, val_string, 10);
	// append the value to write to portb to the Command string
	strcat_s(command, val_string);

	FILE* fpipe;
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

	memset(val_string, 0, 4); //clear 

}

int main()
{


	


	cout << "Current PINC value: " << ReadPINC() << endl;
	cout << "Writing PINC value to PORTB..." << endl;

	WritePORTB(ReadPINC());
	cout << "Current PORTB value: " << ReadPORTB() << endl;
	Sleep(1000);

	cout << "Current ADC value: " << ReadADC() << endl;
	cout << "Writing ADC value to PORTB..." << endl;
	WritePORTB(ReadADC());
	cout << "Current PORTB value: " << ReadPORTB() << endl;


	return 0;
}