#ifndef BOOK_H
#define BOOH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

int adultTicketPrice[13][13] = {
   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   0,    0,    0,    0,  500,  700,  920, 1330, 1510, 1660, 1880, 2290, 2500,
   0,   40,    0,    0,  440,  640,  850, 1250, 1430, 1600, 1820, 2230, 2440,
   0,   70,   40,    0,  400,  590,  800, 1210, 1390, 1550, 1780, 2180, 2390,
   0,  200,  160,  130,    0,  400,  620, 1010, 1210, 1370, 1580, 1990, 2200,
   0,  330,  290,  260,  130,    0,  410,  820, 1010, 1160, 1390, 1790, 2000,
   0,  480,  430,  400,  280,  140,    0,  610,  790,  950, 1160, 1580, 1790,
   0,  750,  700,  670,  540,  410,  270,    0,  400,  550,  770, 1180, 1390,
   0,  870,  820,  790,  670,  540,  390,  130,    0,  370,  580, 1000, 1210,
   0,  970,  930,  900,  780,  640,  500,  230,  110,    0,  430,  830, 1040,
   0, 1120, 1080, 1050,  920,  790,  640,  380,  250,  150,    0,  620,  820,
   0, 1390, 1350, 1320, 1190, 1060,  920,  650,  530,  420,  280,    0,  410,
   0, 1530, 1490, 1460, 1330, 1200, 1060,  790,  670,  560,  410,  140,    0 };

char departureTimes[37][8] = { "",
   "06:00", "06:30", "07:00", "07:30", "08:00", "08:30", "09:00", "09:30",
   "10:00", "10:30", "11:00", "11:30", "12:00", "12:30", "13:00", "13:30",
   "14:00", "14:30", "15:00", "15:30", "16:00", "16:30", "17:00", "17:30",
   "18:00", "18:30", "19:00", "19:30", "20:00", "20:30", "21:00", "21:30",
   "22:00", "22:30", "23:00", "23:30" };

struct Reservation
{
    char reservationNumber[12]; // used to identify a reservation  訂位代號
    char trainNumber[8]; // used to identify a train  車次號碼
    char idNumber[12]; // the id number of the contact person  取票人的身分證字號
    char phone[12]; // the (local or mobile) phone number of the contact person  取票人的聯絡電話
    char date[12]; // outbound date  搭乘日期
    char departure[8];
    char arrival[8];
    int originStation; // the origin station code  起程站代碼
    int destinationStation; // the destination station code  到達站代碼
    int carClass; // the car class code; 1:standard car, 2:business car  車廂種類; 1:標準車廂, 2:商務車廂
    int adultTickets; // the number of adult tickets  全票張數
    int concessionTickets; // the number of concession tickets  優待票張數
};

struct Train
{
    char trainNumber[8]; // used to identify a train  車次號碼
    char departureTimes[13][8]; // the departure time of a train for each station  火車在各站的離站時間
};

string station_name[13] = { "", "Nangang", "Taipei", "Banqiao", "Taoyuan", "Hsinchu", "Miaoli"
                              , "Taichung", "Changhua", "Yunlin", "Chiayi", "Tainan", "Zuoying" };

class book
{
    public:
        book();
        ~book();
        void display(Reservation* object);
        int input_num(int from, int to);
        void booking();
        bool login();
        void cancellation();
        void reduce();
    protected:
        vector<Reservation> redetails;
        vector<Train> nbtimetable;
        vector<Train> sbtimetable;
        Reservation* now;
};

book::book()
{
    ifstream inFile1("Reservation details.dat", ios::binary | ios::in);
    if (!inFile1) {
        ofstream outFile1("Reservation details.dat", ios::binary | ios::out);
        outFile1.close();
    }
    while (inFile1) {
        Reservation temp;
        inFile1.read((char*)&temp, sizeof(Reservation));
        redetails.push_back(temp);
    }
    inFile1.close();

    ifstream inFile2("Northbound timetable.dat", ios::binary | ios::in);
    while (inFile2) {
        Train temp;
        inFile2.read((char*)&temp, sizeof(Train));
        nbtimetable.push_back(temp);
    }
    inFile2.close();

    ifstream inFile3("Southbound timetable.dat", ios::binary | ios::in);
    while (inFile3) {
        Train temp;
        inFile3.read((char*)&temp, sizeof(Train));
        sbtimetable.push_back(temp);
    }
    inFile3.close();

}

book::~book()
{
    ofstream outFile("Reservation details.dat", ios::binary | ios::out);
    for (int a = 0; a < redetails.size(); a++) {
        outFile.write((char*)&redetails[a], sizeof(Reservation));
    }
    outFile.close();
}

void book::display(Reservation* object)
{
    cout << setw(10) << "Date" << setw(11) << "Train No." << setw(10) << "From" << setw(10) << "To" << setw(11) << "Departure"
        << setw(10) << "Arrival" << setw(10) << "Adult" << setw(12) << "Concession" << setw(6) << "Fare" << setw(10) << "Class" << endl;
    cout << setw(10) << object->date << setw(11) << object->trainNumber << setw(10) << station_name[object->originStation] << setw(10)
        << station_name[object->destinationStation] << setw(11) << object->departure << setw(10) << object->arrival;
    if (object->carClass == 1) {
        if (object->originStation < object->destinationStation) {
            cout << setw(7) << adultTicketPrice[object->destinationStation][object->originStation] << "*" << setw(2) << object->adultTickets;
            cout << setw(9) << adultTicketPrice[object->destinationStation][object->originStation] / 2 << "*" << setw(2) << object->concessionTickets;
            cout << setw(6) << adultTicketPrice[object->destinationStation][object->originStation] * object->adultTickets + adultTicketPrice[object->destinationStation][object->originStation] / 2 * object->concessionTickets;
        }
        else {
            cout << setw(7) << adultTicketPrice[object->originStation][object->destinationStation] << "*" << setw(2) << object->adultTickets;
            cout << setw(9) << adultTicketPrice[object->originStation][object->destinationStation] / 2 << "*" << setw(2) << object->concessionTickets;
            cout << setw(6) << adultTicketPrice[object->originStation][object->destinationStation] * object->adultTickets + adultTicketPrice[object->originStation][object->destinationStation] / 2 * object->concessionTickets;
        }
        cout << setw(10) << "Standard" << endl;
    }
    else {
        if (object->originStation < object->destinationStation) {
            cout << setw(7) << adultTicketPrice[object->originStation][object->destinationStation] << "*" << setw(2) << object->adultTickets;
            cout << setw(9) << adultTicketPrice[object->originStation][object->destinationStation] / 2 << "*" << setw(2) << object->concessionTickets;
            cout << setw(6) << adultTicketPrice[object->originStation][object->destinationStation] * object->adultTickets + adultTicketPrice[object->originStation][object->destinationStation] / 2 * object->concessionTickets;
        }
        else {
            cout << setw(7) << adultTicketPrice[object->destinationStation][object->originStation] << "*" << setw(2) << object->adultTickets;
            cout << setw(9) << adultTicketPrice[object->destinationStation][object->originStation] / 2 << "*" << setw(2) << object->concessionTickets;
            cout << setw(6) << adultTicketPrice[object->destinationStation][object->originStation] * object->adultTickets + adultTicketPrice[object->destinationStation][object->originStation] / 2 * object->concessionTickets;
        }
        cout << setw(10) << "Business" << endl;
    }
}

int book::input_num(int from, int to) {
    string a;
    int result = 0;
    while (1) {
        getline(cin, a);
        if (a.size() == 0)
            getline(cin, a);
        if (isalnum) {
            stringstream turn(a);
            turn >> result;
            if (result >= from && result <= to)
                return result;
        }

        cout << "wrong input!\n? ";
    }
}

void book::booking()
{
    Reservation temp;
    int timenum;

    cout << "\nOrigin Station\n";
    for (int a = 1; a <= 12; a++)
        cout << a << ". " << station_name[a] << endl;
    cout << "? ";
    temp.originStation = input_num(1, 12);

  rechoose:
    cout << "\nDestination Station\n";
    for (int a = 1; a <= 12; a++)
        cout << a << ". " << station_name[a] << endl;
    cout << "? ";
    temp.destinationStation = input_num(1, 12);
    if (temp.originStation == temp.destinationStation)
        goto rechoose;

    cout << "\nCar Class\n1. Standard Car\n2. Business Car\n? ";
    temp.carClass = input_num(1, 2);
    cout << "\nDeparture Date: ";
    cin >> temp.date;

    cout << "\nDeparture Time\n";
    for (int a = 1; a < 37; a++)
        cout << a << ". " << departureTimes[a] << endl;
    cout << "? ";
    timenum = input_num(1, 36);

    cout << "\nHow many adult tickets? ";
    temp.adultTickets = input_num(0, 1000);
    cout << "\nHow many concession tickets? ";
    temp.concessionTickets = input_num(0, 1000);

    cout << endl << setw(11) << "Train No." << setw(11) << "Departure" << setw(11) << "Arrival" << endl;
    char train_time[10][3][8];
    int n = 0;
    if (temp.originStation < temp.destinationStation) { //南下
        for (int a = 0; a < sbtimetable.size(); a++) {
            if (strcmp(sbtimetable[a].departureTimes[temp.originStation], departureTimes[timenum]) >= 0 && strlen(sbtimetable[a].departureTimes[temp.destinationStation]) != 1) {
                strcpy_s(train_time[n][0], sbtimetable[a].trainNumber);
                strcpy_s(train_time[n][1], sbtimetable[a].departureTimes[temp.originStation]);
                strcpy_s(train_time[n][2], sbtimetable[a].departureTimes[temp.destinationStation]);
                n++;
            }
            if (n == 10)
                break;
        }
    }
    else { //北上
        for (int a = 0; a < nbtimetable.size(); a++) {
            if (strcmp(nbtimetable[a].departureTimes[13-temp.originStation], departureTimes[timenum]) >= 0 && strlen(nbtimetable[a].departureTimes[13-temp.destinationStation]) != 1) {
                strcpy_s(train_time[n][0], nbtimetable[a].trainNumber);
                strcpy_s(train_time[n][1], nbtimetable[a].departureTimes[13-temp.originStation]);
                strcpy_s(train_time[n][2], nbtimetable[a].departureTimes[13-temp.destinationStation]);
                n++;
            }
            if (n == 10)
                break;
        }
    }
    if (n == 0) {
        cout << "\nNo car class.\n\n\n";
        return;
    }

    for (int a = 0; a < n; a++)
        cout << setw(11) << train_time[a][0] << setw(11) << train_time[a][1] << setw(11) << train_time[a][2] << endl;
    cout << "\nEnter Train Number";
    while (1) {
        cout << ": ";
        cin >> temp.trainNumber;
        for (int a = 0; a < n; a++)
            if (!strcmp(temp.trainNumber, train_time[a][0])) {
                strcpy_s(temp.departure, train_time[a][1]);
                strcpy_s(temp.arrival, train_time[a][2]);
                goto out;
            }
    }
out:
    cout << "\nTrip Details\n\n";
    display(&temp);

    cout << "\nEnter Contact Person Information\n\n";
    cout << "ID Number: ";
    cin >> temp.idNumber;
    cout << "\nPhone: ";
    cin >> temp.phone;
    cout << "\nReservation Number: ";
    srand((unsigned)time(NULL));
    for (int a = 0; a < 8; a++)
        temp.reservationNumber[a] = rand() % 10 + '0';
    temp.reservationNumber[8] = '\0';
    cout << temp.reservationNumber << endl;
    cout << "\nReservation Completed!\n\n\n";

    redetails.push_back(temp);
}

bool book::login()
{
    char id[12], rnum[12];
    while (1) {
        cout << "\n(Enter 0, 0 to quit.)\n";
        cout << "Enter ID Number: ";
        cin >> id;
        cout << "\nEnter Reservation Number: ";
        cin >> rnum;
        if (id[0] == '0' && rnum[0] == '0')
            return false;

        for (int a = 0; a < redetails.size(); a++)
            if (!strcmp(id, redetails[a].idNumber) && !strcmp(rnum, redetails[a].reservationNumber)) {
                cout << "\nReservation Details\n\n";
                display(&redetails[a]);
                now = &redetails[a];
                return true;
            }
    }
}

void book::cancellation()
{
    for (int a = 0; a < redetails.size(); a++)
        if (!strcmp(now->reservationNumber, redetails[a].reservationNumber)) 
            redetails.erase(redetails.begin() + a);
    cout << "\nReservation Cancelled.\n\n\n";
}

void book::reduce()
{
    int cancel_a, cancel_c;
    while (1) {
        cout << "\nHow many adult tickets to cancel？ ";
        cancel_a = input_num(0, now->adultTickets);
        cout << "How many concession tickets to cancel？ ";
        cancel_c = input_num(0, now->concessionTickets);
        cout << endl;
        if (cancel_a + cancel_c > 0)
            break;       
    }
    for (int a = 0; a < redetails.size(); a++) {
        if (!strcmp(now->reservationNumber, redetails[a].reservationNumber)) {
            redetails[a].adultTickets -= cancel_a;
            redetails[a].concessionTickets -= cancel_c;
        }
    }
    display(now);
    cout << "\nYou have successfully reduced the number of tickets!\n\n\n";
}

#endif // !BOOK_H
