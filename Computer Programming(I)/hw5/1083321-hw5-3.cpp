#include <iostream>

using namespace std;

int GCD(int i, int j)
{
    int change=0;


    if(j != 0){
        change = i%j;
        i = j;
        j = change;

        return GCD(i, j);
    }

    return i;
}

int main()
{
    int N, i, j, G;

    while(1){
        G=0;
        cin >> N;
        if (N==0)
            break;


        for(i=1; i<N; i++){
            for(j=i+1; j<=N; j++){
                G+=GCD(i, j);
                //cout  << "\ni:" << i << "\tG:" << G;
            }
        }

        cout << G << endl;
    }

    return 0;
}
