// Demonstrate the copy constructor and assignment operator

#include <iostream>
#include "person.h"

int main(int argc, const char *argv[])
{
    person noname;
    cout << "name: " << noname.getName() << " age: " << noname.getAge() << endl;

    person tom("Tom", 20 );
    person sameName = tom;
    noname = tom;

    cout << "name: " << noname.getName() << " age: " << noname.getAge() << endl;
    cout << "name: " << tom.getName() << " age: " << tom.getAge() << endl;
    cout << "name: " << sameName.getName() << " age: " << sameName.getAge() << endl;

    sameName.setName("Bruce");
    sameName.setAge(55);

    cout << "name: " << noname.getName() << " age: " << noname.getAge() << endl;
    cout << "name: " << tom.getName() << " age: " << tom.getAge() << endl;
    cout << "name: " << sameName.getName() << " age: " << sameName.getAge() << endl;

    noname = tom = sameName;

    cout << "name: " << noname.getName() << " age: " << noname.getAge() << endl;
    cout << "name: " << tom.getName() << " age: " << tom.getAge() << endl;
    cout << "name: " << sameName.getName() << " age: " << sameName.getAge() << endl;

    return 0;
}
