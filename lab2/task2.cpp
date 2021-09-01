#include <iostream>
#include <string>
#include <Windows.h>
#include <map>


using namespace std;

//task 2: read from the analogue ports on the OUSB board.

string str;
string cmd;



int cpp_do_ousb_command(string* str)
{
	FILE* fpipe;
	char line[256] = {};

	fpipe = (FILE*)_popen(str->c_str(), "r");
	if (fpipe != NULL)
	{
		while (fgets(line, sizeof(line), fpipe))
		{   // do nothing here, or print out debug data
			// cout << line; // print out OUSB data for debug purposes
		}
		_pclose(fpipe);   // close pipe
	}
	else cout << "Error, problems with pipe!\n";
	*str = line;					// Caller can see whole returned string.
	return(atoi(str->c_str()));	// try returning string as integer.
}

//==================== main ======================================


int main(int argc, char* argv[])
{
	
	map<int, string> ADC_Port{ {5,"trim-pot"},{6,"LDR"},{7,"USB"} };//hash table for each analogue port

	 

	for (int k = 0; k <= 4; k++)
	{
		ADC_Port[k] = "GPIO"; //PA0-PA4 are available for any use(general purpose).
	}

	
	if (argc > 2)
	{
		cout << "Incorrect number of commandline arguments" << endl;

		return 0;

	}


	for (int i = 0; argv[1][i] != '\0'; i++)
	{
		if (isdigit(argv[1][i]))
			(void)0;
		else
		{
			cout << "Invalid ADC pin" << endl;

			return 0;
		}
	}
	int ADC_pin = atoi(argv[1]);

	if (ADC_Port[ADC_pin] == "")
	{
		cout << "Invalid port number." << endl;
		return 0;
	}

	str = "ousb -r adc ";
	string* port = &ADC_Port[ADC_pin];
	printf("Selected ADC PIN: %d[%s]\n", ADC_pin, port->c_str());
	cmd = str + to_string(ADC_pin);
	cout << cpp_do_ousb_command(&cmd) << endl;
	

	return 0;
}