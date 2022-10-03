// lab3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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

		unsigned int getPORTB(){
			return portB;
		};

		unsigned int getPORTA();

		void setPORTB(unsigned int val);

		unsigned int getPORTD() {
			return portD;
		}

		unsigned int getPORTC();

		void setPORTD(unsigned int val);
};



class trafficLight: public OUSB
{
	private:
		bool redLight;
		bool yellowLight;
		bool greenLight;
		
	public:
		trafficLight(){
			redLight = false;
			yellowLight = false;
			greenLight = false;
		}

		void setredLight() {
			OUSB temp;
			temp.setPORTB(1);
			redLight = true;
			yellowLight = false;
			greenLight = false;
		}
		bool isRed() { return redLight ? true : false; };

		void setyellowLight() {
			OUSB temp;
			temp.setPORTB(6);
			redLight = false;
			yellowLight = true;
			greenLight = false;
		};

		bool isYellow() { return yellowLight ? true : false; };

		void setgreenLight() {
			OUSB temp;
			temp.setPORTB(8);
			redLight = false;
			yellowLight = false;
			greenLight = true;
		};
		bool isGreen() { return greenLight ? true : false; };
};

void sequence(trafficLight* l) {
	l->setgreenLight();
	l->setyellowLight();
	l->setredLight();
};


string OUSB::command(string *str)
{
	FILE* fpipe;
	char line[256] = {};

	fpipe = (FILE*)popen(str->c_str(), "r");
	if (fpipe != NULL)
	{
		while (fgets(line, sizeof(line), fpipe))
		{   // do nothing here, or print out debug data
			// cout << line; // print out OUSB data for debug purposes
		}
		pclose(fpipe);   // close pipe
	}
	else cout << "Z" << endl;

	string output(line);

	string errorCheck("Device not found");

	if (output.find(errorCheck) != string::npos) {

		cout << "Z" << endl;
	}

	
	return output;
	
}

unsigned int OUSB::getPORTA() {
	string commandPORTA = "sudo ./ousb -r io porta";
	portA = (unsigned int)stoi(command(&commandPORTA));
	return portA;
}

void OUSB::setPORTB(unsigned int val) {
	string commandPORTB = "sudo ./ousb -r io portb " + to_string(val);
	portB = stoi(command(&commandPORTB));
}

unsigned int OUSB::getPORTC() {
	string commandPORTA = "sudo ./ousb -r io portc";
	portC = (unsigned int)stoi(command(&commandPORTA));
	return portC;
}

void OUSB::setPORTD(unsigned int val) {
	string commandPORTD = "sudo ./ousb -r io portd " + to_string(val);
	portD = stoi(command(&commandPORTD));
}



int main()
{
	OUSB obj;
	obj.setPORTB(0);
	// obj.setPORTD(0);

	cout << "portA: " << obj.getPORTA() << endl;
	cout << "portB: " << obj.getPORTB() << endl;
	cout << "portC: " << obj.getPORTC() << endl;
	cout << "portD: " << obj.getPORTD() << endl;

	trafficLight light;

	sequence(&light);

	if (light.isGreen()) {
		cout << "GOOOO!!!" << endl;
	}

	else if (light.isYellow()) {
		cout << "SLOW.." << endl;
	}

	else {
		cout << "STOP!!!" << endl;
	}
}
