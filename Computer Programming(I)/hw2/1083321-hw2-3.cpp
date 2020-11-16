#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
    double a, b, c;

    cout << "all Armstrong numbers of three digits:" << endl;

    for(a=1;a<9;a++){
        for(b=0;b<9;b++){
            for(c=0;c<9;c++){
                if (a*100+b*10+c == a*a*a+b*b*b+c*c*c)  //determine if a 3 digits number is a Armstrong number
                    cout << a*100+b*10+c << "\t";
            }
        }
    }

    cout << endl;

    system("pause");
    return 0;
}
