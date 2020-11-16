#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <vector>

using namespace std;

int main()
{
    int random1, random2;
    int i, j, k, add=0;
    int dice[6][6] = {0};
    double probability[11];
    vector<double> decimal;

    srand(time(NULL));
    for(i=0; i<11; i++)
        probability[i]=0;


    for(i=0; i<36000; i++){
        random1 = (rand()%6);
        random2 = (rand()%6);

        dice[random1][random2]++;   //存取rand資料
    }

    cout << setw(6) << " ";
    for(i=1; i<=6; i++)
        cout << setw(6) << i;
    cout << "\n\n";

    for(i=0; i<6; i++){
        cout << setw(6) << i+1;
        for(j=0; j<6; j++)
            cout << setw(6) << dice[i][j];  //將表格印出
        cout << "\n\n";
    }
    cout << "\n\n";


    for(i=0; i<11; i++){
        cout << "P(" << i+2 << ") = ";
        add=0;
        decimal.clear();

        for(j=0; j<6; j++){
            for(k=0; k<6; k++){
                if (j+k == i){
                    probability[i] += dice[j][k];   //將骰子總和次數存入probability
                    decimal.push_back((double)dice[j][k]/36000);    ////將骰子總和機率存入decimal

                    if (add)
                        cout << "+";    //如果為第一項 則不印出+
                    cout << "P(" << j+1 << "+" << k+1 << ")";   //骰子組合
                    add++;
                }
            }
        }
        if (i!=0 && i!=10){
            add=0;
            cout << " = ";
            for(j=0; j<decimal.size(); j++){
                if (add)
                    cout << "+";
                cout << decimal[j]; //印出骰子個別機率
                add++;
            }
        }


        cout << " = " << probability[i]/36000;  //印出骰子總和機率

        cout << "\n\n";
    }

    return 0;
}
