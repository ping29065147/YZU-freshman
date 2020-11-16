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

        dice[random1][random2]++;   //�s��rand���
    }

    cout << setw(6) << " ";
    for(i=1; i<=6; i++)
        cout << setw(6) << i;
    cout << "\n\n";

    for(i=0; i<6; i++){
        cout << setw(6) << i+1;
        for(j=0; j<6; j++)
            cout << setw(6) << dice[i][j];  //�N���L�X
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
                    probability[i] += dice[j][k];   //�N��l�`�M���Ʀs�Jprobability
                    decimal.push_back((double)dice[j][k]/36000);    ////�N��l�`�M���v�s�Jdecimal

                    if (add)
                        cout << "+";    //�p�G���Ĥ@�� �h���L�X+
                    cout << "P(" << j+1 << "+" << k+1 << ")";   //��l�զX
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
                cout << decimal[j]; //�L�X��l�ӧO���v
                add++;
            }
        }


        cout << " = " << probability[i]/36000;  //�L�X��l�`�M���v

        cout << "\n\n";
    }

    return 0;
}
