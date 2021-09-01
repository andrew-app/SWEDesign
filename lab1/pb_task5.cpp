#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>


using namespace std;



int main(int argc, char* argv[]) {
    ofstream myStream;

    myStream.open(argv[1], ios::out | ios::app);

    

    int A = 3680;

    int B = 442;
    

   
   if (myStream)
   {
     A = A ^ B;
     myStream << A << endl;
     B = A ^ B;
     myStream << B << endl;
     A = A ^ B;
     myStream << A << endl;
            

   }

   else cout << "File specified not found." << endl;

   myStream.close();

    

    return 0;
}
