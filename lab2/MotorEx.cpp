#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
  // for Sleep()


using namespace std;

/*======== OUSB Board DC Motor Speed Control ===================================

File version: 2021_v01.0

PURPOSE - Show how to control the speed of a DC motor using the Open-USB-IO board.
See Linux Gazette for the full article on DC motor control, which utilizes more
complex control formula than this example.
(http://linuxgazette.net/179/radcliffe.html)

USAGE - Add to a Visual Studio project and build. argv[1] should be a number
between 0 and 500

DETAILS - Program sets PWM 1 to 45 Hz and changes the PWM duty cycle to keep the
motor speed constant by measuring the back-emf of the motor and trying to keep
that a constant.
- Motor must be stopped when program starts to ensure calibration works properly.
- On startup there is a calibration phase where the the motor run at full speed
  for two seconds. Then it stops for two seconds and prints out the ADC1 data.
- Calibration takes 2 seconds.

REQUIRMENTS:
If using the simulator, you must use the ousbMotorSim.exe version (v1.07 or above)
and it must be renamed to ousb.exe  This version of the simulator will update
the p_ADC0.txt every time the PWM 1 value is changed in the loop as it simulates
the voltage changes that occur on the motor drive circuitry (virtually).

If using a Physical OUSB Board, you must use the original ousb.exe interface
applications and the circuit below must be constructed on the OUSB Board.
It should also be supplied with a DC plug pack if a small DC motor (optional)
is wired across the 1K load resistor.  Plug pack voltage should be 1.5 times
or less of the rated motor voltage.

- Must add the circuitry below to the OBSB Board to get a smoothed version
of the motor voltage.

Your C++ Program     OUSB      .  Components Soldered onto Prototype Area
on the PC            Board     .
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
							   .
ousb J5 pin 37 ----->----------.->--+------------------+------------ (Ext DC Supply)
							   .    |                  |
							   .    |              .---+---.
							   .   |"| 1kohm       | motor |
							   .   |_|  load       '---+---'
							   .    |                  |
							   .    +------------------+
ousb pwm 1 ...                 .    |      47 kohm
   |"|___|"|___| -->-- J5 -----.->--+---[\\\]---+
						pin 27 .                |
							   .        +-------+----+
							   .        |       |    | +
ousb adc 0 ...    --<-- J5 ----.-<------+      |"|  ===  10 uF
						pin 1  .          22   |_|   |
							   .          kohm  |    |
							   .                +----+-- J5 any even pin, 0v
							   .
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* In this circuit the link to the on board +5v is removed and DC plug
pack is plugged into the board.  A small DC motor is put in parallel
with the load resistor.

* When the PWM on LED3 goes high pin 27 J5 goes low, current flow through
the motor and drives it.


Original code is Copyright Dr. Pj Radcliffe 2010.
*/

//========= types and data.
double gain = 0.01;  // Gain from ADC error to PWM % change.  Higher
					 // values give faster response to mechanical load
					 // changes but may cause cycling and overshoot.
					 // Lower values cause slower response.
double pwm = 0;      // starting PWM %.

string str;
stringstream stst;

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

int main(int argc, char* argv[])
{


	//--- set PWM frequency.
	cout << "setting pwm-freq to 45 Hz" << endl;
	str = "sudo ousb pwm-freq 1 45";
	cpp_do_ousb_command(&str);


	//--- calculate ADC for motor full on,  Vsat
	cout << "setting duty cycle to 100% - wait 1 second" << endl;
	str = "sudo ousb pwm 1 100";
	cpp_do_ousb_command(&str);

	usleep(1000); // allow motor to get up to speed.
	str = "sudo ousb -r adc 0";
	double Vsat = cpp_do_ousb_command(&str);
	cout << "Vsat = " << Vsat << endl;

	//--- calculate supply voltage using pwm of zero.
	cout << "setting duty cycle to 0% - wait 1 second" << endl;
	str = "sudo ousb pwm 1 0";
	cpp_do_ousb_command(&str);

	usleep(1000); // allow motor to stop if going.
	str = "sudo ousb -r adc 0";
	double Vext = cpp_do_ousb_command(&str);
	cout << "Vext = " << Vext << endl;

	cout << "  Calibration:   Vsat= " << Vsat << ",  Vext= " << Vext << endl;

	//--- advanced control loop.
	float Vgoal = atoi(argv[1]);

	if (Vgoal > 500) Vgoal = 500;
	if (Vgoal < 0) Vgoal = 0;

	cout << "Entering Control loop. Vgoal = " << Vgoal << endl;
	usleep(1000);

	double Vavg = 0, Vgen = 0;

	return 0;
}
