#include <iostream>
#include <vector>
#include "matrix.h"

using namespace std;

int main()
{
    vector< vector<int> > data1, data2, data3;

    load(data1, data2); //Åª

    if (data1[0].size() == data2.size())
        compute(data1, data2, data3);   //­¼

    print(data3);   //¦L

    return 0;
}
