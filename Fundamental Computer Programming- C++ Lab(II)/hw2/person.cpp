// Demonstrate how to rewrite c++ struct to c++ class

#include <iostream>
#include <sstream>
#include "person.h"
using namespace std;

person::person(char const* nm, int ae) ///ªì©l¤Æ
{
   name = new char[200];

   int a;
   for (a = 0; *(nm + a) != '\0'; a++) 
      *(name + a) = *(nm + a);
   *(name + a) = '\0';

   age = ae;
}

person::person(person& m) //½Æ»s
{
   name = new char;
   name = m.name;
   age = m.age;
}

person::~person() //destroctor
{
   delete[] name;
}

person& person::operator=(person& m) //=
{

   int a;

   name = new char[200];
   for (a = 0; *(m.name + a) != '\0'; a++)
      * (name + a) = *(m.name + a);
   name[a] = '\0';

   age = m.age;

   return *this;
}

void person::setName(char const* nm)
{
   name = new char[200];
   int a;

   for (a = 0; *(nm+a)!='\0'; a++) 
      *(name+a) = *(nm + a);
   name[a] = '\0';
}

void person::setAge(int ae)
{
   age = ae;
}

string person::getName()
{
   return name;
}

int person::getAge()
{
   return age;
}