#include <iostream>
#include <vector>
#include "matrix.h"

using namespace std;

int main()
{
    vector< vector<int> > data1, data2, data3;

    load(data1, data2); //Ū

    if (data1[0].size() == data2.size())
        compute(data1, data2, data3);   //��

    print(data3);   //�L

    return 0;
}
