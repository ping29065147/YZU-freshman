#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int gender, age, mass, activity, s, bmr, tdee;
    float bmi, height;

    cout << "Input Gender(Male:1/Female:2): ";
    cin >> gender;

    cout << "Input Age(year): ";
    cin >> age;

    cout << "Input mass(kg): ";
    cin >> mass;

    cout << "Input height(cm): ";
    cin >> height;

    cout << "Activity List\n1. Sedentary(office job)\n2. Light Exercise(1-2 days/week)\n3. Moderate Exercise(3-5 days/week)\n4. Heavy Exercise(6-7 days/week)\n5. Athlete(2x per day)\nInput Activity: ";
    cin >> activity;


    cout << endl;
    if (gender == 1){
        cout << "Gender: Male";
        s = 5;
    }
    else{
        cout << "Gender: Female";
        s = -161;
    }

    cout << "\nAge(year): " << age << endl;
    cout << "Mass(kg): " << mass << endl;
    cout << "Height(cm): " << height << endl;

    bmi = mass/((height/100)*(height/100));
    cout << "BMI: " << setprecision(3) << fixed << bmi << endl;
    if (bmi < 18.5)
        cout << "You are Underweight\n";
    else if (bmi < 24)
        cout << "You are Normal\n";
    else if (bmi < 27)
        cout << "You are Overweight\n";
    else if (bmi < 30)
        cout << "You are Moderately obese\n";
    else if (bmi < 35)
        cout << "You are Severely obese\n";
    else
        cout << "You are Very severely obese\n";

    bmr = 10*mass+6.25*height-5*age+s;
    cout << "BMR: " << bmr << endl;

    if (activity == 1){
        tdee = bmr*1.2;
        cout << "You are Sedentary\n";
    }
    else if (activity == 2){
        tdee = bmr*1.375;
        cout << "You are Light Exercise\n";
    }
    else if (activity == 3){
        tdee = bmr*1.55;
        cout << "You are Moderate Exercise\n";
    }
    else if (activity == 4){
        tdee = bmr*1.725;
        cout << "You are Heavy Exercise\n";
    }
    else {
        tdee = bmr*1.9;
        cout << "You are Athlete\n";
    }
    cout << "TDEE: " << tdee;

    return 0;
}
