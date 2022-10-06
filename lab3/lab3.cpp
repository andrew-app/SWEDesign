
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;



class OUSB
{
private:
	short int portA;
	short int portB;
	short int portC;
	short int portD;
	short int command(string* str);

public:
	OUSB() {
		portA = 0;
		portB = 0;
		portC = 0;
		portD = 0;
	};

	short int getPORTA();

	short int getPORTB();

	void setPORTB(unsigned short int val);

	short int getPORTC();

	short int getPORTD();

	void setPORTD(unsigned short int val);
};

short int OUSB::command(string* str)
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
		return -1;
	}


	return atoi(line);

}

short int OUSB::getPORTA() {
	string commandPORTA = "ousb -r io porta";
	portA = command(&commandPORTA);
	return portA;
}

short int OUSB::getPORTB() {
	string commandPORTB = "ousb -r io portb";
	portB = command(&commandPORTB);
	return portB;
}

void OUSB::setPORTB(unsigned short int val) {
	string commandPORTB = "ousb -r io portb " + to_string(val);
	portB = command(&commandPORTB);
}

short int OUSB::getPORTC() {
	string commandPORTC = "ousb -r io portc";
	portC = command(&commandPORTC);
	return portC;
}

short int OUSB::getPORTD() {
	string commandPORTD = "ousb -r io portd";
	portD = command(&commandPORTD);
	return portD;
}

void OUSB::setPORTD(unsigned short int val) {
	string commandPORTD = "ousb -r io portd " + to_string(val);
	portD = command(&commandPORTD);
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

	void useState(string &colour);

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

void trafficLight::useState(string &colour) {
	if (colour == "R") setRed();
	else if (colour == "Y") setYellow();
	else if (colour == "G") setGreen();
};

void trafficLight::setState() {
	if (isRed()) setGreen();
	else if (isYellow()) setRed();
	else if (isGreen()) setYellow();
};

int errorcheck(char* temp) {
	for (int i = 0; temp[i] != '\0'; i++)
	{
		if (isdigit(temp[i]))
			(void)0;

		else
		{
			cout << "N" << endl;
			return -1;
		}
	}
	return atoi(temp);

}


int main(int argc, char* argv[])
{


	OUSB ousb;

	trafficLight light;



	string colour = argv[1];

	bool counter = false;


	if (colour == "R" || colour == "Y" || colour == "G") void(0);



	else if (colour == "CR" || colour == "CY" || colour == "CG") {
		counter = true;
		colour.erase(remove(colour.begin(), colour.end(), 'C'), colour.end());
	}
	else {
		cout << "I" << endl;
		return 0;
	}

	if (argc != 3) {
		cout << "P" << endl;
		return 0;
	}

	int transitions = errorcheck(argv[2]);

	if (transitions == -1) return 0;

	if (transitions > 15 || transitions < 0)
	{
		cout << "R" << endl;

		return 0;
	}

	if (ousb.getPORTA() == -1) return 0; // check if ousb connected

	light.useState(colour);


	for (int i = 1; i <= transitions; i++) {

		Sleep(1000);
		light.setState();
		
	}

	cout << ousb.getPORTB() << "," << ousb.getPORTD() << endl;
	
	return 0;
	
}
