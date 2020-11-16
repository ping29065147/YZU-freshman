#include "account.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <conio.h>
#include <iomanip>

using namespace std;
#define normal 7

account::account()
{
    load_data();
}

account::~account()
{
    store_data();
}

void account::load_data()
{
    mydata temp;
    ifstream inFile("account data.dat", ios::in | ios::binary);
    if (!inFile) {
        ofstream outFile("account data.dat", ios::out | ios::binary);
        outFile.close();
    }
    while (inFile.read((char*)&temp, sizeof(mydata)))
        account_data.push_back(temp);
    inFile.close();
    
}

void account::store_data()
{
    if (now != nullptr) {
        now->x = myplayer.getx();
        now->y = myplayer.gety();
        now->topography = myplayer.get_topography();
        for (size_t a = 0; a < myplayer.get_mypokemons_size(); a++)
            now->mypokemons[a] = myplayer.get_mypokemons()[a];
        for (size_t a = 0; a < 12; a++)
            now->victory[a] = myplayer.get_victory()[a];
    }

    ofstream outFile("account data.dat", ios::out | ios::binary);
    for (const auto& a : account_data)
        outFile.write((char*)&a, sizeof(mydata));
    outFile.close();
}

player& account::get_player()
{
    return myplayer;
}

int account::print_menu()
{
    char left[3] = {'[', ' ', ' '};
    char right[3] = { '[', ' ', ' ' };
    char ch, c;
    int control = 0;

    while (1) {
        left[control] = '[';
        right[control] = ']';

        cout << "\n" << setw(40) << " " << "¡¹ Welcome to pokemon's world! ¡¹\n\n\n";
        for (size_t a = 0; a < 120; a++)
            cout << "=";
        cout << "\n\n" << setw(40) << " " << left[0] << "1" << right[0] << " Create a new acount\n"
            << setw(40) << " " << left[1] << "2" << right[1] << " Login\n"
            << setw(40) << " " << left[2] << "3" << right[2] << " Quit\n\n";
        for (size_t a = 0; a < 120; a++)
            cout << "=";

        //enter by up and down
        ch = _getch();
        if (ch == -32) {
            c = _getch();
            left[control] = ' ';
            right[control] = ' ';
            if (c == 72)
                control = (control + 2) % 3;
            else if (c == 80)
                control = (control + 1) % 3;
        }
        else if (ch == '\r')
            break;
        system("cls");
    }
    return control + 1;
}

void account::input_range(size_t begin, size_t end, char* temp, bool check)
{
    string in;
    size_t a;
    char ch;

    while (1) {
        if (check) { // if check = true, enter password
            in.clear();
            while (1) {
                ch = _getch();
                if (ch == '\r')
                    break;
                else if (ch == '\b') {
                    if (in.size() > 0) {
                        cout << '\b' << " " << '\b';
                        in.pop_back();
                    }
                }
                else {
                    cout << "*";
                    in += ch;
                }
            }
            cout << endl;
        }
        else
            cin >> in;
        if (in.size() >= begin && in.size() <= end) {
            for (a = 0; a < in.size(); a++)
                temp[a] = in[a];
            temp[a] = '\0';
            return;
        }
        else
            cout << "wrong input. please input again: ";
    }
}

void account::create_account()
{
    mydata temp;
    cout << "\n\ninput your name (1-20 letters): ";
    input_range(1, 20, temp.name);
    while (1) {
        cout << "\ninput your account number (5-20 letters): ";
        input_range(5, 20, temp.account_number);
        if (!exist(temp.account_number))
            break;
        cout << "account exist.\n\n";
    }
    cout << "\ninput your passward (5-20 letters): ";
    input_range(5, 20, temp.passward, true);   

    temp.x = 20;
    temp.y = 29;
    temp.topography = normal;
    for (auto& a : temp.mypokemons)
        a = 0;
    for (auto& a : temp.victory)
        a = false;

    account_data.push_back(temp);
    now = &account_data[account_data.size() - 1];
    cout << "\n\naccount create success.\n\n";
}

bool account::exist(char* account_number)
{
    for (const auto& i : account_data)
        if (!strcmp(i.account_number, account_number))
            return true;

    return false;
}

bool account::login()
{
    mydata temp;
    string in;
    char ch;
    cout << "\n\ninput your account number: ";
    cin >> temp.account_number;
    cout << "\ninput your passward: ";
    in.clear();
    while (1) {
        ch = _getch();
        if (ch == '\r')
            break;
        else if (ch == '\b') {
            if (in.size() > 0) {
                cout << '\b' << " " << '\b';
                in.pop_back();
            }
        }
        else {
            cout << "*";
            in += ch;
        }
    }
    for (size_t a = 0; a < in.size(); a++)
        temp.passward[a] = in[a];
    temp.passward[in.size()] = '\0';

    for (auto& a : account_data) {
        if (!strcmp(temp.account_number, a.account_number) && !strcmp(temp.passward, a.passward)) {
            now = &a;
            cout << "\n\nlogin successed.\n";
            return true;
        }
    }
    
    cout << "\n\nlogin failed.\n";
    return false;
}

void account::catch_pok()
{
    myplayer.catch_pokemon();
}

void account::battled()
{
    myplayer.battle();
}

bool account::_exit()
{
    string yesno[2] = { " Yes  / [No]", "[Yes] /  No " };
    int control = 0;
    char ch, c;

    while (1) {
        system("cls");
        cout << "\n" << setw(35) << " " << "¡» Do you sure to exit game? ";
        cout << yesno[control];
        ch = _getch();
        if (ch == -32) {
            c = _getch();
            if (c == 75 || c == 77)
                control++;
            if (control == 2)
                control = 0;
        }
        else if (ch == '\r')
            return control;
    }
}

mydata* account::get_account()
{
    return now;
}

void account::load_player(mydata* my_acc)
{
    myplayer.setxy(my_acc->x, my_acc->y);
    myplayer.set_topography(my_acc->topography);
    myplayer.set_my_pok(my_acc->mypokemons);
    myplayer.set_victory(my_acc->victory);
}

void account::backpack()
{
    myplayer.print_backpack();
}

void account::attribute()
{
    myplayer.print_atb();
}