#include <iostream>
#include <string>
#include <Windows.h>
#include <map>


using namespace std;

//task 2: read from the analogue ports on the OUSB board.

string str;
string cmd;

map<int, string> ADC_Port{ {5,"trim-pot"},{6,"LDR"},{7,"USB"} };//hash table for each analogue port

map<string, string> Param{ {"A","ADC pin"}, {"P","Duty Cycle"}, {"L","Target Value"} }; // Available Parameters

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

void ReadUADC(int val) {
	if (ADC_Port[val] == "")
	{
		cout << "Invalid port number." << endl;

	}

	if (val > 7)
	{
		cout << "Port Does not Exist" << endl;
	}

	else
	{
		str = "ousb -r adc ";
		string* port = &ADC_Port[val];
		printf("Selected ADC PIN: %d[%s]\n", val, port->c_str());
		cmd = str + to_string(val);
		cout << cpp_do_ousb_command(&cmd) << endl;
	}
}

void shutdown()
{
	cmd = "ousb pwm 1 0";
	cpp_do_ousb_command(&cmd);
	cmd.clear();
}

void SetPWM(int duty_cycle) {
	if (duty_cycle > 100 || duty_cycle < 0)
	{
		cout << "Duty cycle out of range." << endl;
		shutdown();
		exit(0);

	}
	
	str = "ousb pwm 1 ";
	cmd = str + to_string(duty_cycle);
	cpp_do_ousb_command(&cmd);
	cmd.clear();

}



int ReadADC0() {
	str = "ousb -r adc 0";
	int val = cpp_do_ousb_command(&str);
	str.clear();
	return val;
}

void TargetADC(int val)
{
	

	if (val > 1024)
	{
		cout << "Target ADC value out of range." << endl;
		return;
	}

	int DC = 50; //initial duty cycle 50%

	SetPWM(DC);

	int CurrentADC0 = 0;
	int i = 1;

	while (val != CurrentADC0)
	{
		CurrentADC0 = ReadADC0();

		

		

		if (CurrentADC0 > val)
		{
			SetPWM(DC);
			DC++;
		}


		else if (CurrentADC0 < val)
		{

			SetPWM(DC);
			DC--;
		}

		else
			cout << "Target Reached." << endl;

		cout << "Loop# " << i << " ADC target = " << val << " ADC read: " << CurrentADC0 << " Next PWM " << DC << endl;

		if (i == 60)
		{
			cout << "Calibration exhausted. Target not met." << endl;
			break;
		}
		i++;
		Sleep(1000);
	}
	

}

int errorcheck(char* temp,string arg) {
	for (int i = 0; temp[i] != '\0'; i++)
	{
		if (isdigit(temp[i]))
			(void)0;
		else
		{
			cout << "Invalid " << arg << endl;
			exit(0);
		}
	}
	return atoi(temp);
	
}

int main(int argc, char* argv[])
{
	str = "ousb pwm-freq 1 46";
	cpp_do_ousb_command(&str);
	str.clear();

	for (int k = 0; k <= 4; k++)
	{
		ADC_Port[k] = "GPIO"; //PA0-PA4 are available for any use(general purpose).
	}

	if (argc != 3)
	{
		cout << "Incorrect number of commandline arguments" << endl;

		return 0;

	}
	
	string arg1 = argv[1];
	
	char* arg2 = argv[2];

	

	if (arg1 == "A") //ADC
	{
		
		ReadUADC(errorcheck(arg2, Param[arg1]));
	}

	else if (arg1 == "P") // PWM
	{
		
		SetPWM(errorcheck(arg2, Param[arg1]));
	}

	else if (arg1 == "L") //Target ADC
	{
		TargetADC(errorcheck(arg2, Param[arg1]));
	}


	else {
		cout << "Error: Invalid Command" << endl;

	}
	

	return 0;
}