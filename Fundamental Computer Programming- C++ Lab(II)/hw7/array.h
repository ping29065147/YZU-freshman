// The example of C++ Class
#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>

using namespace std;

template <typename T>
class Array 
{
    public:
       Array(int s) { //ªì©l
          Size = s; 
          ArrayPtr = new T[Size]();
       }
       ~Array() { delete[] ArrayPtr; }
       void setValue(int index, T value) { *(ArrayPtr + index) = value; } //³]­È
       T getValue(int index) { return *(ArrayPtr + index); }
    private:
        int Size;
        T *ArrayPtr;
};

#endif // ARRAY_H
