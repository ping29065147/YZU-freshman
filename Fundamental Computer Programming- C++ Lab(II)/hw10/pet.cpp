
#include "pet.h"
#include <string>
using namespace std;

class pet::hide 
{
	public:
		string name;
		string sound;

};

pet::pet(string n)
{
	ptr = new hide;
	ptr->name = n;
}
pet::~pet()
{
	delete ptr;
}
string pet::Name()
{
	return ptr->name;
}
string pet::makeSound()
{
	return ptr->sound;
}


cat::cat(string n)
	:pet(n)
{
	ptr->sound = "miau";
}


dog::dog(string n)
	:pet(n)
{
	ptr->sound = "won";
}
