#include <iostream>
#include <iomanip>

using namespace std;

void ConvertToCelsius(double lower, double upper)
{
    double i, j, lenth=upper-lower+1;
    int mid=(upper+lower)/2;  //start at the middle

    cout << endl;
    for(i=0; i<2; i++)
        cout << setw(15) << "Fahrenheit" << setw(10) << "Celsius";
    cout << endl << "   ";
    for(i=0; i<47; i++)
        cout << "-";
    cout << endl;

    for(i=lower, j=mid+1; i<=mid; i++, j++){
        //i=Fahrenheit i*1.8+32=Celsius (start at lower)
        cout << setw(15) << setprecision(1) << fixed << i << setw(10) << setprecision(1) << fixed << (i-32)*5/9;
        if (j==lenth+lower)  ////jump out the loop if lenth is a odd number
            break;
        //j=Fahrenheit j*1.8+32=Celsius (start at mid+1)
        cout << setw(15) << setprecision(1) << fixed << j << setw(10) << setprecision(1) << fixed << (j-32)*5/9;
        cout << endl;
    }
}

void ConvertToFahrenheit(double lower, double upper)
{
    double i, j, lenth=upper-lower+1;
    int mid=(upper+lower)/2;  //start at the middle

    cout << endl;
    for(i=0; i<2; i++)
        cout << setw(10) << "Celsius" << setw(15) << "Fahrenheit";
    cout << endl << "   ";
    for(i=0; i<47; i++)
        cout << "-";
    cout << endl;

    for(i=lower, j=mid+1; i<=mid; i++, j++){
        //i=Celsius i*1.8+32=Fahrenheit (start at lower)
        cout << setw(10) << setprecision(1) << fixed << i << setw(15) << setprecision(1) << fixed << i*1.8+32;
        if (j==lenth+lower)  //jump out the loop if lenth is a odd number
            break;
        //j=Celsius j*1.8+32=Fahrenheit (start at mid+1)
        cout << setw(10) << setprecision(1) << fixed << j << setw(15) << setprecision(1) << fixed << j*1.8+32;
        cout << endl;
    }
}

int main()
{
    int choose, i;
    double lower, upper;
    cout << "Please choose which conversion you want to use:\n1. Celsius to Fahrenheit\n2. Fahrenheit to Celsius\n";
    cin >> choose;

    cout << "Please input the lower bond and upper bond of the temperature you want to convert:\nlower bond: ";
    cin >> lower;
    cout << "upper bond: ";
    cin >> upper;

    if (choose==1)
        ConvertToFahrenheit(lower, upper);  //Celsius to Fahrenheit
    else if (choose==2)
        ConvertToCelsius(lower, upper);  //Fahrenheit to Celsius

    return 0;
}
