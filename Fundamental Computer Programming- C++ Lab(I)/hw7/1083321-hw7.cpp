#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

float findMedianScore(int *ptrScore, int amounts)
{
    int a, b, change;

    //bubble sort
    for(a=0; a<amounts-1; a++){
        for(b=0; b<amounts-1-a; b++){
            if (*(ptrScore+b) > *(ptrScore+b+1)){
                change=*(ptrScore+b);
                *(ptrScore+b)=*(ptrScore+b+1);
                *(ptrScore+b+1)=change;
            }
        }
    }

    cout << "bubble sort: ";
    for(a=0; a<amounts; a++)
        cout << *(ptrScore+a) << " ";
    cout << endl;

    //return median
    if (amounts%2)
        return *(ptrScore+(amounts-1)/2);
    else
        return ((float)*(ptrScore+amounts/2)+(float)*(ptrScore+amounts/2-1))/2;
}

int main()
{
    srand(time(NULL));
    int studentScores[10] = {0}, a;
    cout << "random data: ";
    //generate students' score
    for(a=0; a<10; a++){
        studentScores[a] = rand()%101;
        cout << studentScores[a] << " ";
    }
    cout << endl;

    //find the size of studentScores
    int size = sizeof(studentScores)/sizeof(studentScores[0]);
    //find the median of studentScores
    float median = findMedianScore(studentScores,size);

    cout << "Median = " << median;

    return 0;
}
