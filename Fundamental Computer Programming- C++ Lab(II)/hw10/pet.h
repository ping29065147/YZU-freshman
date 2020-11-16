// demo hide implementation in C++
#ifndef PET_H
#define PET_H

#include <string>
using namespace std;

class pet
{
	protected:
		class hide;
		hide* ptr;
	public:
		pet(string n);
		~pet();
		string Name();
		string makeSound();
};

class cat : public pet
{
	public:
		cat(string n);  //初始化
};

class dog : public pet
{
	public:
		dog(string n);  //初始化
};

#endif // PET_H
