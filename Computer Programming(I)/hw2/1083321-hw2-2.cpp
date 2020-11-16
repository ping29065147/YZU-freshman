#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
    int number, total=0;

    cout << "Enter a positive integer of at most 8 digits: ";
    cin >> number;
    cout << "The sum of all digits of " << number << " is ";

    do{
        total += number%10; //save the last number of number to total
    }
    while(number/=10);  //total divide by 10

    cout << total << endl;

    system("pause");
    return 0;
}
