#include "sortedarray.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char *argv[])
{
    SortedArray<int> intArray(5);
    intArray.addValue(3);
    intArray.addValue(1);
    intArray.addValue(2);
    intArray.addValue(5);
    intArray.addValue(4);
    for(int i=0; i<5; i++){
        cout << intArray.getValue(i) << " ";
    }

    cout << endl;

    SortedArray<float> floatArray(5);
    floatArray.addValue(0.21);
    floatArray.addValue(0.53);
    floatArray.addValue(0.44);
    floatArray.addValue(0.71);
    floatArray.addValue(0.13);
    for(int i=0; i<5; i++){
        cout << floatArray.getValue(i) << " ";
    }

    cout << endl;

    SortedArray<string> stringArray(5);
    stringArray.addValue("test");
    stringArray.addValue("configuration");
    stringArray.addValue("number");
    stringArray.addValue("template");
    stringArray.addValue("get");
    for(int i=0; i<5; i++){
        cout << stringArray.getValue(i) << " ";
    }

    cout << endl;

    return 0;
}
