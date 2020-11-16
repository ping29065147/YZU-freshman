#ifndef SORTEDARRAY_H
#define SORTEDARRAY_H

#include <iostream>

using namespace std;

template <typename T>
class Array
{
   public:
      Array(int s) { //��l
         Size = s;
         ArrayPtr = new T[Size]();
      }
      ~Array() { delete[] ArrayPtr; }
      void setValue(int index, T value) { *(ArrayPtr + index) = value; } //�]��
      T getValue(int index) { return *(ArrayPtr + index); }
   protected:
      int Size;
      T* ArrayPtr;
};

template <typename T>
class SortedArray : public Array<T> //sortedarray�~��array
{
   public:
      SortedArray(int size) : now(0), Array<T>(size) {}
      void addValue(T t);
      bool isgreater(T left, T right);
   private:
      int now;
};

#endif // SORTEDARRAY_H
