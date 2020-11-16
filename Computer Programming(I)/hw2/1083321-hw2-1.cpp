#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
    int number, a, numcpy, acpy, x, change=2;

    cout << "Enter a positive decimal integer of at most 8 digits: ";
    cin >> number;

    for(x=0; x<2; x++, change=8){   //decide to calculate the binary or the octal
        for(numcpy=number, a=0; numcpy!=0; a++) //copy number to numcpy
            numcpy /= change;   //calculate the digits of number and save it into a

        int n[a];
        acpy = a;   //copy a to acpy
        for(numcpy=number; a>0; a--, numcpy/=change)   //copy number to numcpy again
            n[a-1] = numcpy%change;  //save the last number of numcpy to n[]

        if (change == 2)
            cout << "The binary equivalent of " << number << " is ";
        else
            cout << "\nThe octal equivalent of " << number << " is ";

        for(a=0; a<acpy; a++)
            cout << n[a];   //output the binary or octal
    }
    cout << endl;

    system("pause");
    return 0;
}
