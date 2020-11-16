#include <iostream>
#include <vector>

using namespace std;

int recursive(int n)
{
    if (n>=16)  //n<16 last time
        recursive(n/16);

    if (n%16 > 9)
        cout << char(n%16+55);  //if n%16>9 output A-E
    else
        cout << n%16;   //if n%16<=9 output 0-9
}

int main()
{

    int n, a;
    int digit=0;
    vector<char> result;

    while(1){
        cin >> n;
        if (n>=0 && n<=32767)   //check if n is between 0 to 32767
            break;
    }

    cout << "recursive:";
    recursive(n);


    for(a=0; n!=0; a++, n/=16){
        if (n%16 > 9)
            result.push_back(n%16+55);  //if n%16>9 output A-E
        else
            result.push_back(n%16+48);  //if n%16<=9 output 0-9
    }
    result.pop_back();
    cout << "\nIterative:";
    for(a=result.size(); a>=0; a--)
        cout << result[a];

    return 0;
}
