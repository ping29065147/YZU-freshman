#include "sortedarray.h"
#include <algorithm>

template <typename T>
bool SortedArray<T>::isgreater(T left, T right)
{
   if (right > left)
      return true;
   return false;
}
template class SortedArray<int>;
template class SortedArray<float>;
template<typename T> bool isgreater(T left, T right) { //特例化
   if (right[0] > left[0])
      return true;
   return false;
}

template <typename T>
void SortedArray<T>::addValue(T t)
{
   this->ArrayPtr[now] = t;
   now++;
   for (int a = 0; a < now-1; a++) {   //bubble sort
      for (int b = 0; b < now - a - 1; b++) {
         if (isgreater(this->ArrayPtr[b], this->ArrayPtr[b+1])) //判斷大小
            swap(this->ArrayPtr[b], this->ArrayPtr[b+1]);
      }
   }
   //sort(this->ArrayPtr, this->ArrayPtr + now, greater<T>());
}
template class SortedArray<int>;
template class SortedArray<float>;
template class SortedArray<string>;

