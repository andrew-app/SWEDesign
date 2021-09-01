#include <iostream>
#include <string>
#include <unistd.h>
  // for Sleep()

using namespace std;

double gain = 0.01;  // Gain from ADC error to PWM % change.  Higher
					 // values give faster response to mechanical load
					 // changes but may cause cycling and overshoot.
					 // Lower values cause slower response.
double pwm = 0;      // starting PWM %.

string str;
string cmd;


//============== cpp_do_ousb_comand ================================
//
// PURPOSE - send a command to the OUSB Board using the ousb
//           command.  Return any integer reply.

int cpp_do_ousb_command(string* str)
{
	FILE* fpipe;
	char line[256] = {};

	fpipe = (FILE*)popen(str->c_str(), "r");    // attempt to open pipe and execute a command
	if (fpipe != NULL)					   // check that the pipe opened correctly
	{
		while (fgets(line, sizeof(line), fpipe))
		{   // do nothing here, or print out debug data
			// cout << line; // print out OUSB data for debug purposes
		}
		pclose(fpipe);   // close pipe
	}
	else cout << "Error, problems with pipe!\n";
	*str = line;					// Caller can see whole returned string.
	return(atoi(str->c_str()));	// try returning string as integer.
}

//==================== main ======================================

void shutdown()
{
	int arr[4] = {75,50,25,0};
	for(int j = 0; j < 4; j++)
	{

		cmd.clear();
		cmd = str + to_string(arr[j]);
		cpp_do_ousb_command(&cmd);
		if(j == 2)
		{
			cout << "Turning motor off..." << endl;
			usleep(10000000);
		}
		else
			usleep(100000*6);
	}
}
int main(int argc, char* argv[])
{

	//--- set PWM frequency.
	cout << "Starting Motor..." << endl;
	str = "sudo ousb pwm-freq 1 45";
	cpp_do_ousb_command(&str);

	str = "sudo ousb pwm 1 ";
	int gear = 1;

for(gear; gear < 7; gear++)
{
	for(int i = 25; i <= 100; i = i+25)
	{
		cmd = str + to_string(i);
		cout << gear << endl;
		cpp_do_ousb_command(&cmd);
		cmd.clear();

		if ((gear == 6) && (i == 100))
		{
			usleep(10000000);
			shutdown();

		}
		else
			usleep(100000*gear);

	}
}

	//--- calculate supply voltage using pwm of zero.

	str = "sudo ousb pwm 1 0";
	cpp_do_ousb_command(&str);

	usleep(100); // allow motor to stop if going.
	str = "sudo ousb -r adc 0";
	cpp_do_ousb_command(&str);



	return 0;
}
