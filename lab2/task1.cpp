#include <iostream>
#include <string>
#include <Windows.h>


using namespace std;

//task 1: You need to accept an integer parameter from the command line into your program (i.e., using argc and argv) as the duty cycle. Perform an error check to ensure that the duty cycle entered is between 0 and 100 inclusive.

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

	//--- set PWM frequency.
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
			cout << "Invalid duty cycle" << endl;
			
			return 0;
		}
	}
	int duty_cycle = atoi(argv[1]);
	if (duty_cycle > 100)
	{
		cout << "duty cycle out of range." << endl;
		return 0;
	}
	cout << "Starting Motor..." << endl;
	str = "ousb pwm-freq 1 45";
	cpp_do_ousb_command(&str);
	str.clear();

	str = "ousb pwm 1 ";
	cmd = str + to_string(duty_cycle);
	cpp_do_ousb_command(&cmd);
	Sleep(1000);
	cmd.clear();

	//--- calculate supply voltage using pwm of zero.
	cmd = str + to_string(0);
	cpp_do_ousb_command(&cmd);
	cmd.clear();

	cout << "Shuting down..." << endl;
	Sleep(100); // allow motor to stop if going.
	str = "ousb -r adc 0";
	cpp_do_ousb_command(&str);



	return 0;
}