#include <iostream>

using namespace std;

int main()
{
    int pencils[4], ballpoint_pens[4], a, check[4] = {}, b;

    cout << "Please input the daily sales of pencils for the first four days( use a space to separate each character )\n";
    for(a=0; a<4; a++){
        while(1){
            cin >> pencils[a];
            if (pencils[a] >= 0 && pencils[a] <= 5)
                break;
            else
                cout << "please input the daily sales of pencils again:";
        }
    }


    cout << "\nPlease input the daily sales of ballpoint pens for the first four days( use a space to separate each character )\n";
    for(a=0; a<4; a++){
        while(1){
            cin >> ballpoint_pens[a];
            if (ballpoint_pens[a] >= 0 && ballpoint_pens[a]+pencils[a] <= 5)
                break;
            else
                cout << "please input the daily sales of ballpoint_pens again:";
        }
        check[a] += pencils[a]+ballpoint_pens[a];
    }


    cout << "\t* daily sales of pencils\n\t+ daily sales of ballpoint pens\n\n";
    for(b=5; b>=0; b--){
        cout << "\t";
        for(a=0; a<4; a++){
            cout << "  ";
            if (b == 0)
                cout << a+1;
            else if (check[a] == b && pencils[a] != 0){
                cout << "*";
                check[a]--;
                pencils[a]--;
            }
            else if (check[a] == b && pencils[a] == 0){
                cout << "+";
                check[a]--;
            }
            else
                cout << " ";
        }
        cout << endl;
    }

    return 0;
}
