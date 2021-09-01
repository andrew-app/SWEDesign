#include <iostream>

using namespace std;

int ReadPortB();

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

int main()
{




	cout << "Current PortB value: " << ReadPortB() <<endl;

	return 0;
}