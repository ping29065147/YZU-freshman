// MakeReservation.cpp
// AvailSeats-function definitions for class MakeReservation.
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "MakeReservation.h"

extern int inputAnInteger( int begin, int end );

MakeReservation::MakeReservation( ReservationDatabase &theReservationDatabase,
   AvailSeatsDatabase &theSeatsDatabase )
   : reservationDatabase( theReservationDatabase ),
     availSeatsDatabase( theSeatsDatabase )
{
}

void MakeReservation::execute()
{
   cout << "\nEnter the party size (1~6): ";

   int partySize;
   do cout << "? ";
   while( ( partySize = inputAnInteger( 1, 6 ) ) == -1 );

   Date currentDate;
   computeCurrentDate( currentDate );

   Date date;
   inputDate( date, currentDate, partySize );

   int timeCode;
   inputTimeCode( timeCode, date, partySize );

   string name;
   cout << "\nEnter name: ";
   cin >> name;

   string phoneNumber;
   cout << "\nEnter phone Number: ";
   cin >> phoneNumber;
   cin.ignore();

   cout << "\nChoose a menu:\n";
   cout << "1. NT$ 1080\n";
   cout << "2. NT$ 1680\n";
   cout << "3. NT$ 2280\n";

   int menuCode;
   do cout << "? ";
   while( ( menuCode = inputAnInteger( 1, 3 ) ) == -1 );

   Reservation newReservation( phoneNumber, name, date, timeCode, partySize, menuCode );

   cout << endl;
   newReservation.displayReservationInfo();

   cout << "\nReservation Completed\n";

   reservationDatabase.pushBack( newReservation );

   availSeatsDatabase.decreaseAvailSeats( date, timeCode, partySize );
}

void MakeReservation::inputDate( Date &date, Date currentDate, int partySize )
{
	int count = 0;
	int d;

	cout << "\nChoose a date\n";
	for (size_t a = 1; a <= 30; a++) {
		if (availSeatsDatabase.availableTimes((currentDate + a), partySize)) {

			cout << setw(2) << a << ". " << (currentDate + a).getYear() << "/";
			if ((currentDate + a).getMonth() < 10)
				cout << "0";
			cout << (currentDate + a).getMonth() << "/";
			if ((currentDate + a).getDay() < 10)
				cout << "0";
			cout << (currentDate + a).getDay() << "  ";

			count++;
			if (count % 4 == 0)
				cout << endl;
		}
	}
	if (count % 4 != 0)
		cout << endl;

	do cout << "? ";
	while ((d = inputAnInteger(1, 30)) == -1 || !availSeatsDatabase.availableTimes((currentDate + d), partySize));

	date = (currentDate + d);
}

void MakeReservation::inputTimeCode( int &timeCode, Date date, int partySize )
{
	string t[4] = { "11:30", "13:30", "17:45", "19:45" };
	int tc;

	cout << "\nChoose a time:\n";
	for (size_t a = 1; a <= 4; a++) {
		if (availSeatsDatabase.availableTimes(date, a, partySize))
			cout << a << ". " << t[a - 1] << endl;
	}

	do cout << "? ";
	while ((tc = inputAnInteger(1, 4)) == -1 || !availSeatsDatabase.availableTimes(date, tc, partySize));

	timeCode = tc;
}