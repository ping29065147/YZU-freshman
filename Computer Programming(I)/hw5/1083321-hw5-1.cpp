#include <iostream>

using namespace std;

int oddSum(int a, int b)
{
    if (a<b)
        return a + oddSum(a+2, b);
    else if (a==b)
        return a;
    else
        return 0;

}

int main()
{
    int T, a, b, i, change;
    cin >> T;

    for(i=1; i<=T; i++){
        cin >> a >> b;

        if (a>b){
            change = a;
            a = b;
            b = change;
        }
        if (a%2==0)
            a++;

        cout << "Case " << i << ": " << oddSum(a, b) << endl;
    }

    return 0;
}
