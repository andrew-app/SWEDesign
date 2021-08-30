#include <iostream>
#include <string>
using namespace std;

int ObjNum = 0;  // Global variable to count objects

class MyObject
{
	int val;
public:
	MyObject(int i);             // Normal constructor
	MyObject(const MyObject &o); // Copy constructor
	~MyObject();                 // Destructor
	int  getval() { return val; }
	void setval(int i) { val = i; }

	MyObject twice();            // Return an object
};

MyObject::MyObject(int i)          // Normal constructor
{
	val = i;
	ObjNum++;
	cout << "In Constructor, ObjNum " << ObjNum << "\n";
}

MyObject::MyObject(const MyObject &o) // Copy constructor
{
	val = o.val;
	ObjNum++;
	cout << "In Copy Constructor, ObjNum " << ObjNum << "\n";
}

MyObject::~MyObject()
{
	cout << "Destructing ObjNum " << ObjNum << "\n";
	ObjNum--;
}

MyObject MyObject::twice()
{
	MyObject NewObj(val * 2); // val is current member
	return NewObj;          // returns an object
}


// pass object by reference
void display(MyObject *ob) // no copy made
{
	cout << ob->getval() << '\n';
}

// pass object by value
void change(MyObject ob) // copy made here
{
	ob.setval(100); // no effect
	cout << "val in change(): ";//debug line
	display(&ob); //debug line
}

int main()
{
	MyObject ob1(10);
	cout << "##val in main: ";
	display(&ob1); //pass reference

	change(ob1);   //pass by value
	cout << "##val after change(): ";
	display(&ob1); //pass reference

	ob1 = ob1.twice(); // returns an obj
	cout << "##val after ob1.twice(): ";
	display(&ob1);
}
