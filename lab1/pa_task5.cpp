#include <string>
#include <iostream>


using namespace std;



int ReadPortB();


int ReadPortB()
{
	int portb = 0;

	const char* command = "ousb -r io PORTB";  // must be const
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

	string checktxt("Device not found");

	string debug(line); //copy char array of ousb.exe output to a string

	int value = 0;

	value = (int)atoi(line);

	if (debug.find(checktxt) != string::npos) {
		cout << "OUSB is not connected." << endl;

		return -1;

	}
	// convert value from char array to int
	portb = (int)atoi(line);

	return portb;
}


int main()
{
	int val = ReadPortB();

	if(val != string::npos)
		cout << "Current PortB value: " << val << endl;

	return 0;
}