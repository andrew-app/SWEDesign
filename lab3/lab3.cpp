
#include <iostream>
#include <string>

using namespace std;



class OUSB
{
private:
	unsigned int portA;
	unsigned int portB;
	unsigned int portC;
	unsigned int portD;
	string command(string* str);

public:
	OUSB() {
		portA = 0;
		portB = 0;
		portC = 0;
		portD = 0;
	};

	unsigned int getPORTA();

	unsigned int getPORTB();

	void setPORTB(unsigned int val);

	unsigned int getPORTC();

	unsigned int getPORTD();

	void setPORTD(unsigned int val);
};

unsigned int OUSB::getPORTA() {
	string commandPORTA = "ousb -r io porta";
	portA = (unsigned int)stoi(command(&commandPORTA));
	return portA;
}

unsigned int OUSB::getPORTB() {
	string commandPORTB = "ousb -r io portb";
	portB = (unsigned int)stoi(command(&commandPORTB));
	return portB;
}

void OUSB::setPORTB(unsigned int val) {
	string commandPORTB = "ousb -r io portb " + to_string(val);
	portB = stoi(command(&commandPORTB));
}

unsigned int OUSB::getPORTC() {
	string commandPORTC = "ousb -r io portc";
	portC = (unsigned int)stoi(command(&commandPORTC));
	return portC;
}

unsigned int OUSB::getPORTD() {
	string commandPORTD = "ousb -r io portd";
	portD = (unsigned int)stoi(command(&commandPORTD));
	return portD;
}

void OUSB::setPORTD(unsigned int val) {
	string commandPORTD = "ousb -r io portd " + to_string(val);
	portD = stoi(command(&commandPORTD));
}

string OUSB::command(string* str)
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
	else cout << "Z" << endl;

	string output(line);

	string errorCheck("Device not found");

	if (output.find(errorCheck) != string::npos) {

		cout << "Z" << endl;
	}


	return output;

}

class trafficLight : public OUSB
{
private:
	bool redLight;
	bool yellowLight;
	bool greenLight;

public:
	trafficLight() {
		redLight = false;
		yellowLight = false;
		greenLight = false;
	}
	
	void setRed();

	bool isRed() { return redLight ? true : false; };

	void setYellow();

	bool isYellow() { return yellowLight ? true : false; };

	void setGreen();

	bool isGreen() { return greenLight ? true : false; };

	void initState(string &colour);

	void setState();
};

void trafficLight::setRed() {
	setPORTB(1);
	redLight = true;
	yellowLight = false;
	greenLight = false;
}

void trafficLight::setYellow() {
	setPORTB(6);
	redLight = false;
	yellowLight = true;
	greenLight = false;
};

void trafficLight::setGreen() {
	setPORTB(8);
	redLight = false;
	yellowLight = false;
	greenLight = true;
};

void trafficLight::initState(string &colour) {
	if (colour == "R") setRed();
	else if (colour == "Y") setYellow();
	else if (colour == "G") setGreen();
};

void trafficLight::setState() {
	if (isRed()) setGreen();
	else if (isYellow()) setRed();
	else if (isGreen()) setYellow();
};


int main(int argc, char* argv[])
{
	if (argc != 3) {
		cout << "Incorrect # of args" << endl;
		return 0;
	}

	trafficLight light;

	string colour = argv[1];

	cout << colour << endl;

	if (colour == "R" || colour == "r") {
		colour = "R";
	}

	else if (colour == "Y" || colour == "y") {
		colour = "Y";
	}

	else if (colour == "G" || colour == "g") {
		colour = "G";
	}

	else {
		cout << "invalid first arg" << endl;
		return 0;
	}

	int transitions = atoi(argv[2]);

	if (transitions > 50 || transitions < 0)
	{
		cout << "invalid # of state transitions" << endl;

		return 0;
	}

	light.initState(colour);

	for (int i = 0; i <= transitions; i++) {

		light.setState();
	}
	
	return 0;
	
}
