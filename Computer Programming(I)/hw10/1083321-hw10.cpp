#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <string.h>
using namespace::std;

struct Date
{
   int year;
   int month;
   int day;
   int hour;
};

struct MemberRecord
{
   char IDNumber[ 12 ];   // account number
   char password[ 24 ];   // password
   char name[ 8 ];        // name
};

struct ReservationRecord
{
   char IDNumber[ 12 ]; // account number
   int branchCode;      // branch code
   Date date;           // reservation date
   int numCustomers;    // number of customers
};

char branchNames[ 17 ][ 24 ] = { "", "Taipei Dunhua South", "Taipei SOGO",
                                     "Taipei Songjiang",    "Taipei Nanjing",
                                     "Taipei Linsen",       "Taipei Zhonghua New",
                                     "Banqiao Guanqian",    "Yonghe Lehua",
                                     "Taoyuan Zhonghua",    "Taoyuan Nankan",
                                     "Zhongli Zhongyang",   "Hsinchu Beida",
                                     "Taichung Ziyou",      "Chiayi Ren'ai",
                                     "Tainan Ximen",        "Kaohsiung Zhonghua New" };

// input memberDetails from the file Members.dat
void loadMemberDetails( vector< MemberRecord > &memberDetails );

// input reservations from the file Reservations.dat
void loadReservations( vector< ReservationRecord > &reservations );

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end );

// login and display the submenu
void login( const vector< MemberRecord > &memberDetails,
            vector< ReservationRecord > &reservations );

// there exists a member with specified IDNumber and password
bool valid( char IDNumber[], char password[],
            const vector< MemberRecord > &memberDetails );

// add a new reservation for the member with specified IDnumber
void reservation( char IDNumber[], vector< ReservationRecord > &reservations );

// compute the current date
void compCurrentDate( Date &currentDate );

// compute 7 dates which is starting from the current date
void compAvailableDates( Date currentDate, Date availableDates[] );

// display all fields of reservation
void output( ReservationRecord reservation );

// display all reservations for the member with specified IDnumber,
// then let the member to choose one of them to delete
void queryDelete( char IDNumber[], vector< ReservationRecord > &reservations );

// add a new member
void registration( vector< MemberRecord > &memberDetails );

// return true if IDNumber is a legal ID number
bool legalID( char IDNumber[] );

// return true if IDNumber belongs to memberDetails
bool existingID( char IDNumber[], const vector< MemberRecord > &memberDetails );

// output all memberDetails into the file Members.dat
void saveMemberDetails( const vector< MemberRecord > &memberDetails );

// output all reservations into the file Reservations.dat
void saveReservations( const vector< ReservationRecord > &reservations );

int main()
{
   vector< MemberRecord > memberDetails; // member details for all members
   vector< ReservationRecord > reservations; // all reservations

   loadMemberDetails( memberDetails );
   loadReservations( reservations );

   cout << "Welcome to the Cashbox Party World!\n\n";

   int choice;

   while( true )
   {
      cout << "1 - Login\n";
      cout << "2 - Registration\n";
      cout << "3 - End\n";

      do cout << "\nEnter your choice (1~3): ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );
      cout << endl;

      switch ( choice )
      {
      case 1:
         login( memberDetails, reservations );
         break;

      case 2:
         registration( memberDetails );
         break;

      case 3:
         saveMemberDetails( memberDetails );
         saveReservations( reservations );
         cout << "Thank you! Goodbye!\n\n";
         system( "pause" );
         return 0;

      default:
         cout << "\nIncorrect choice!\n";
         break;
      }
   }

   system( "pause" );
}

void loadMemberDetails( vector< MemberRecord > &memberDetails )
{
    MemberRecord in;
    int a;
    ofstream outFile("Members.dat", ios::app | ios::binary);
    outFile.close();

    ifstream inFile("Members.dat", ios::in | ios::binary);
    inFile.seekg(0, ios::end);
    int x = inFile.tellg()/sizeof(MemberRecord);
    inFile.seekg(0, ios::beg);

    for(a=0; a<x; a++){
        inFile.read((char*)&in, sizeof(MemberRecord));
        memberDetails.push_back(in);
        //cout << in.IDNumber << " " << in.name << " " << in.password << endl;
    }
}

void loadReservations( vector< ReservationRecord > &reservations )
{
    ReservationRecord in;
    int a;
    ofstream outFile("ReservationInfo.dat", ios::app | ios::binary);
    outFile.close();

    ifstream inFile("ReservationInfo.dat", ios::in | ios::binary);
    inFile.seekg(0, ios::end);
    int x = inFile.tellg()/sizeof(ReservationRecord);
    inFile.seekg(0, ios::beg);

    for(a=0; a<x; a++){
        inFile.read((char*)&in, sizeof(ReservationRecord));
        reservations.push_back(in);
        //cout << in.IDNumber << " " << in.name << " " << in.password << endl;
    }
}

int inputAnInteger( int begin, int end )
{
    string input;
    int trans;
    cin >> input;

    if (input.size()==2)
        trans = (input[0]-'0')*10+(input[1]-'0');
    else
        trans = (input[0]-'0');

    if (trans>=begin && trans<=end)
        return trans;
    else
        return -1;
}

void login( const vector< MemberRecord > &memberDetails,
            vector< ReservationRecord > &reservations )
{
    int a, choice;
    char id[12], pass[24];
    bool check=true;

    while(1){
        cout << "Please enter your ID number: ";
        cin >> id;
        cout << "Enter your password: ";
        cin >> pass;
        cout << endl;

        if (valid(id, pass, memberDetails))
            break;
        else
            cout << "Invalid account number or password. Please try again.\n\n";
    }

    while( check )
   {
    cout << "1 - Make Reservation\n";
    cout << "2 - Reservation Enquiry/Canceling\n";
    cout << "3 - End\n";

      do cout << "\nEnter your choice (1~3): ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );
      cout << endl;

      switch ( choice )
      {
      case 1:
         reservation( id, reservations );
         break;

      case 2:
         queryDelete( id, reservations );
         break;

      case 3:
         check=false;
         break;

      default:
         cout << "\nIncorrect choice!\n";
         break;
      }
   }


}

bool valid( char IDNumber[], char password[],
            const vector< MemberRecord > &memberDetails )
{
    int a;

    for(a=0; a<memberDetails.size(); a++){
        if (!(strcmp(IDNumber, memberDetails[a].IDNumber)) && !(strcmp(password, memberDetails[a].password)))
            return true;
    }
    return false;
}

void reservation( char IDNumber[], vector< ReservationRecord > &reservations )
{
    int a, b, size, choice;
    Date nowdate, result[8];
    ReservationRecord putin;

    for(a=1; a<17; a++){
        size = strlen(branchNames[a]);
        cout << a << ". ";
        for(b=0; b<size; b++)
            cout << branchNames[a][b];
        cout << endl;
    }

    do cout << "\nEnter your choice (0 to end): ";
        while( ( choice = inputAnInteger( 0, 16 ) ) == -1 );
    cout << endl;

    if (choice==0)
        return;
    putin.branchCode = choice;

    compCurrentDate(nowdate);
    cout << "The current hour is ";
    cout << nowdate.year << "/" << nowdate.month << "/" << nowdate.day << ":" << nowdate.hour << "\n\n";

    if (nowdate.hour==23){
        nowdate.day++;
        nowdate.hour=0;
    }

    cout << "Available days:\n\n";
    compAvailableDates(nowdate, result);

    do cout << "\nEnter your choice (0 to end): ";
        while( ( choice = inputAnInteger( 0, 7 ) ) == -1 );

    if (choice==0){
        cout << endl;
        return;
    }
    putin.date.year = result[choice].year;
    putin.date.month = result[choice].month;
    putin.date.day = result[choice].day;

    do cout << "\nEnter hour (" << nowdate.hour+1 << "~23): ";
        while( ( choice = inputAnInteger( nowdate.hour, 23 ) ) == -1 );
    putin.date.hour = choice;

    do cout << "\nEnter the number of customers (1~30, 0 to end): ";
        while( ( choice = inputAnInteger( 0, 30 ) ) == -1 );
    cout << endl;

    if (choice==0)
        return;

    strcpy(putin.IDNumber, IDNumber);
    putin.numCustomers = choice;
    reservations.push_back(putin);

    cout << setw(30) << "Branch" << setw(15) << "Date" << setw(8) << "Hour" << setw(20) << "No of Customers\n";
    cout << "  ";
    output(putin);

    cout << "\nReservation Completed!\n\n";
}

void compCurrentDate( Date &currentDate )
{
    tm *stime;
    time_t rawTime = time(0);
    stime = localtime(&rawTime);

    currentDate.year = stime->tm_year+1900;
    currentDate.month = stime->tm_mon+1;
    currentDate.day = stime->tm_mday;
    currentDate.hour = stime->tm_hour;
}

void compAvailableDates( Date currentDate, Date availableDates[] )
{
    int a, days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (currentDate.year%4==0 && (currentDate.year%100!=0 || currentDate.year%400==0))
        days[2] = 29;

    for(a=1; a<=7; a++){
        availableDates[a].year = currentDate.year;
        availableDates[a].month = currentDate.month;
        availableDates[a].day = currentDate.day;

        cout << a << ". " << currentDate.year << "/" << currentDate.month << "/" << currentDate.day++ << endl;

        if (currentDate.day > days[currentDate.month]){
            currentDate.day = 1;
            currentDate.month++;
            if (currentDate.month==13){
                currentDate.month = 1;
                currentDate.year++;
            }
        }
    }
}

void output( ReservationRecord reservation )
{
    int a;
    vector<char> branch;
    for(a=0; a<strlen(branchNames[reservation.branchCode]); a++)
        branch.push_back(branchNames[reservation.branchCode][a]);
    string branchin(branch.begin(), branch.end());

    cout << setw(28) << branchin << setw(9) << reservation.date.year << "-" << setw(2) << reservation.date.month << "-" << setw(2) << reservation.date.day << setw(8) << reservation.date.hour << setw(19) << reservation.numCustomers << endl;
}

void queryDelete( char IDNumber[], vector< ReservationRecord > &reservations )
{
    int a, b=1, choice;
    vector<int> erases;

    cout << setw(30) << "Branch" << setw(15) << "Date" << setw(8) << "Hour" << setw(20) << "No of Customers\n";
    for(a=0; a<reservations.size(); a++){
        if (!strcmp(IDNumber, reservations[a].IDNumber)){
            cout << b << ".";
            output(reservations[a]);
            b++;
            erases.push_back(a);
        }
    }

    do cout << "\nChoose a reservation to cancel (0: keep all reservations): ";
        while( ( choice = inputAnInteger( 0, b ) ) == -1 );
    cout << endl;

    if (choice==0)
        return;

    reservations.erase(reservations.begin()+erases[choice-1]);
}

void registration( vector< MemberRecord > &memberDetails )
{
    MemberRecord re;

    cout << "Input your ID Number: ";
    cin >> re.IDNumber;
    cout << endl;

    if (legalID(re.IDNumber))
        cout << "The ID number " << re.IDNumber << " is illegal.\n\n";
    else if (existingID(re.IDNumber, memberDetails)){
        cout << "You are already a member!\n\n";
    }
    else{
        cout << "Input your Name: ";
        cin >> re.name;
        cout << "\nChoose a password: ";
        cin >> re.password;
        memberDetails.push_back(re);
        cout << "\nRegistration Completed!\n\n";
    }
}

bool legalID( char IDNumber[] )
{
    int a, total=0;
    char cpy=IDNumber[0];

    if (strlen(IDNumber) != 10)
        return true;
    else if (!((IDNumber[0]>='a'&&IDNumber[0]<='z') || (IDNumber[0]>='A'&&IDNumber[0]<='Z')))
        return true;

    for (a=1; a<strlen(IDNumber); a++){
        if (!(IDNumber[a]>='0'&&IDNumber[a]<='9'))
            return true;
    }

    if (IDNumber[0]>='a'&&IDNumber[0]<='h')
        total = IDNumber[0]-'a'+10;
    else if (IDNumber[0]>='A'&&IDNumber[0]<='H')
        total = IDNumber[0]-'A'+10;
    else if (IDNumber[0]-'i'==0)
        total = 34;
    else if (IDNumber[0]-'I'==0)
        total = 34;
    else if (IDNumber[0]>='j'&&IDNumber[0]<='n')
        total = IDNumber[0]-'j'+18;
    else if (IDNumber[0]>='J'&&IDNumber[0]<='N')
        total = IDNumber[0]-'J'+18;
    else if (IDNumber[0]-'o'==0)
        total = 35;
    else if (IDNumber[0]-'O'==0)
        total = 35;
    else if (IDNumber[0]>='p'&&IDNumber[0]<='v')
        total = IDNumber[0]-'p'+23;
    else if (IDNumber[0]>='P'&&IDNumber[0]<='V')
        total = IDNumber[0]-'P'+23;
    else if (IDNumber[0]-'w'==0)
        total = 32;
    else if (IDNumber[0]-'W'==0)
        total = 32;
    else if (IDNumber[0]>='x'&&IDNumber[0]<='y')
        total = IDNumber[0]-'x'+30;
    else if (IDNumber[0]>='X'&&IDNumber[0]<='Y')
        total = IDNumber[0]-'X'+30;
    else if (IDNumber[0]-'z'==0)
        total = 33;
    else if (IDNumber[0]-'Z'==0)
        total = 33;

    IDNumber[0] = (total%10)+'0';
    total/=10;
    total+=IDNumber[9]-'0';
    for(a=0; a<9; a++)
        total += ((IDNumber[a]-'0')*(9-a));

    IDNumber[0] = cpy;
    if (total%10)
        return true;

    return false;
}

bool existingID( char IDNumber[], const vector< MemberRecord > &memberDetails )
{
    int a;
    for(a=0; a<memberDetails.size(); a++){
        if (!(strcmp(IDNumber, memberDetails[a].IDNumber)))
            return true;
    }
    return false;
}

void saveMemberDetails( const vector< MemberRecord > &memberDetails )
{
    int a;
    ofstream outFile("Members.dat", ios::out | ios::binary);

    for(a=0; a<memberDetails.size(); a++){
        outFile.write(reinterpret_cast<const char*> (&(memberDetails[a])), sizeof(MemberRecord));
    }
}

void saveReservations( const vector< ReservationRecord > &reservations )
{
    int a;
    ofstream outFile("ReservationInfo.dat", ios::out | ios::binary);

    for(a=0; a<reservations.size(); a++){
        outFile.write(reinterpret_cast<const char*> (&(reservations[a])), sizeof(ReservationRecord));
    }
}


<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head><meta http-equiv="Content-Type" content="text/html; charset=utf-8" /><title>

</title></head>
<body>
    <form method="post" action="./File_DownLoad_Wk_zip.aspx?File_name=1083321-hw10.cpp&amp;type=3&amp;id=2809123" id="form1">
<div class="aspNetHidden">
<input type="hidden" name="__VIEWSTATE" id="__VIEWSTATE" value="/wEPDwUKLTEzNDM3NzkxOWRkwneTr34MFXJYUKyKKda+DU4gQVM=" />
</div>

<div class="aspNetHidden">

	<input type="hidden" name="__VIEWSTATEGENERATOR" id="__VIEWSTATEGENERATOR" value="629601C3" />
</div>
    <div>
    
    </div>
    </form>
</body>
</html>
