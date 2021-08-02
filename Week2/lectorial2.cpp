#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
  // outputing to a text file

  ofstream myStream;

  myStream.open("test.txt", ios::out | ios::app);

  myStream << "Hello World!" << endl;

  myStream.close();

  return 0;
}
