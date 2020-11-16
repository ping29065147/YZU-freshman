#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace::std;

#include "ReservationDatabase.h"

ReservationDatabase::ReservationDatabase()
{
   loadReservations();
}

ReservationDatabase::~ReservationDatabase()
{
   storeReservations();
}

bool ReservationDatabase::empty()
{
   return ( reservations.size() == 0 );
}

bool ReservationDatabase::exist( string phoneNumber )
{
	for (size_t a = 0; a < reservations.size(); a++) {
		if (reservations[a].getPhoneNumber() == phoneNumber)
			return true;
	}

	return false;
}

void ReservationDatabase::displayReservationInfo( string phoneNumber )
{
	int num = 1;

	cout << endl;
	for (size_t a = 0; a < reservations.size(); a++) {
		if (reservations[a].getPhoneNumber() == phoneNumber) {
			cout << setw(2) << num << ". " << reservations[a].getPartySize();
			if (reservations[a].getPartySize() == 1)
				cout << " guest   ";
			else
				cout << " guests  ";

			cout << reservations[a].getDate().getYear() << "/";
			if (reservations[a].getDate().getMonth() < 10)
				cout << "0";
			cout << reservations[a].getDate().getMonth() << "/";
			if (reservations[a].getDate().getDay() < 10)
				cout << "0";
			cout << reservations[a].getDate().getDay() << "  ";

			if (reservations[a].getTime() == 1)
				cout << "11:30\n";
			else if (reservations[a].getTime() == 2)
				cout << "13:30\n";
			else if (reservations[a].getTime() == 3)
				cout << "17:45\n";
			else if (reservations[a].getTime() == 4)
				cout << "19:45\n";

			num++;
		}
	}
}

void ReservationDatabase::pushBack( Reservation newReservation )
{
   reservations.push_back( newReservation );
}

void ReservationDatabase::loadReservations()
{
	Reservation temp;
	ifstream inFile("Reservations.dat", ios::in | ios::binary);
	while (inFile.read((char*)& temp, sizeof(Reservation)))
		reservations.push_back(temp);
	inFile.close();

}

void ReservationDatabase::storeReservations()
{
	ofstream outFile("Reservations.dat", ios::out | ios::binary);
	for (size_t a = 0; a < reservations.size(); a++)
		outFile.write((char*)& reservations[a], sizeof(Reservation));
	outFile.close();
}