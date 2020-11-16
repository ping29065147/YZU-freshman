#include "array.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char *argv[])
{
    Array<int> intArray(5);
    intArray.setValue(0,1);
    intArray.setValue(1,2);
    intArray.setValue(2,3);
    intArray.setValue(3,4);
    intArray.setValue(4,5);
    for(int i=0; i<5; i++){
        cout << intArray.getValue(i) << " ";
    }

    cout << endl;

    Array<double> doubleArray(5);
    doubleArray.setValue(0,0.1);
    doubleArray.setValue(1,0.2);
    doubleArray.setValue(2,0.3);
    doubleArray.setValue(3,0.4);
    doubleArray.setValue(4,0.5);
    for(int i=0; i<5; i++){
        cout << doubleArray.getValue(i) << " ";
    }

    cout << endl;

    Array<string> stringArray(5);
    stringArray.setValue(0,"test1");
    stringArray.setValue(1,"test2");
    stringArray.setValue(2,"test3");
    stringArray.setValue(3,"test4");
    stringArray.setValue(4,"test5");
    for(int i=0; i<5; i++){
        cout << stringArray.getValue(i) << " ";
    }

    return 0;
}
