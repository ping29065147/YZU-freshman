#include <iostream>
#include <iomanip>

using namespace std;

double calculateCharges(float charge)
{
    float total=0;
    if (charge <= 2)    //未滿2小時以2小時計
        total=3;
    else if (charge >= 24)  //total不會多餘15
        total=15;
    else{
        for(total=3, charge-=2; charge>0; charge-=1) //charge大於3的情況下，charge每多1，則total多0.6
            total+=0.6;
    }

    cout << setw(10) << setprecision(2) << fixed << total << endl;
    return total;
}

int main()
{
    int i, j;
    float input[3], totalhour=0, totalcharge=0;
    for(i=0; i<3; i++){
        cin >> input[i];
        totalhour += input[i];  //計算總hour
    }

    cout << left << setw(6) << "Car" << right << setw(6) << "Hours" << setw(10) << "Charge" << endl;
    for(i=1; i<4; i++){
        cout << left << setw(6) << i << right << setw(6) << setprecision(1) << fixed << input[i-1];
        totalcharge += calculateCharges(input[i-1]);    //計算總charge
    }

    cout << left << setw(6) << "TOTAL" << right << setw(6) << setprecision(1) << fixed << totalhour << setw(10) << setprecision(2) << fixed << totalcharge << endl;

    return 0;
}
