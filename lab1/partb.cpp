#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;



int main () {
  string line;
  ifstream myfile ("test.txt");
  int temp = 0;
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      bool isnum = true;
      char myArray[line.size()+1];//as 1 char space for null is also required
      strcpy(myArray, line.c_str());
      for (int i = 0; myArray[i] != '\0'; i++)
      {
        if(isdigit(myArray[i]))
          temp = 1;
        else
        {
          cout << "Invalid Number" << endl;
          isnum = false;
          break;
        }
      }
      if (isnum == 1)
      {
        int val = stoi(line);

        if (val > 15)
          cout << "Out of range" << endl;

        else
          cout << val << endl;
      }
    }
    myfile.close();
  }

  else cout << "Unable to open file";

  return 0;
}
