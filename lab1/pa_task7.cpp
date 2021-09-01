#include <iostream>
#include <windows.h>

using namespace std;

int ReadPORTB();
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


void WritePORTB(int val)
{

	char command[256] = { "ousb -r io PORTB " };
	char val_string[50] = {};

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

	memset(val_string, 0, 4); //clear memory 

}

int main(int argc, char* argv[])
{
	bool isnum = true; //boolean for valid number
	int portb = 0;
	if (argc == 2)
		for (int i = 0; argv[1][i] != '\0'; i++)
		{
			if (isdigit(argv[1][i]))
				(void)0; // do nothing if valid char
			else
			{
				cout << "Invalid Value" << endl;
				isnum = false;
				break;
			}
		}
	else
		cout << "Invalid number of arguments" << endl;

	if (isnum == true)
	{
		portb = atoi(argv[1]);

		WritePORTB(portb);

		cout << "Current Value of PORTB: " << ReadPORTB() << endl;

	}

	return 0;
}