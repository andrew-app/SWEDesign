#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
//#include <windows.h>

using namespace std;



int main() {
    int val1 = 240;
    int val2 = 123;
    int val3 = 2;
    int portb = 0;


    portb = val1&val2;
    cout << portb << endl;

    portb = portb|val3;
    cout << portb << endl;
    return 0;
}
