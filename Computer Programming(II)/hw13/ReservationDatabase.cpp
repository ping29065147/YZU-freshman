// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <fstream>
using namespace std;
#include "ReservationDatabase.h"

// ReservationDatabase default constructor loads reservations from the file Reservation details.dat
ReservationDatabase::ReservationDatabase()
{
   loadReservations();
}

// ReservationDatabase destructor stores reservations into the file Reservation details.dat
ReservationDatabase::~ReservationDatabase()
{
   storeReservations();
}

void ReservationDatabase::loadReservations()
{
    ifstream inFile1("Reservation details.dat", ios::binary | ios::in);
    if (!inFile1) {
        ofstream outFile1("Reservation details.dat", ios::binary | ios::out);
        outFile1.close();
    }
    Reservation temp;
    while (inFile1.read((char*)&temp, sizeof(Reservation)))
        reservations.push_back(temp);
    inFile1.close();
}

void ReservationDatabase::storeReservations()
{
    ofstream outFile("Reservation details.dat", ios::binary | ios::out);
    for (int a = 0; a < reservations.size(); a++) {
        outFile.write((char*)&reservations[a], sizeof(Reservation));
    }
    outFile.close();
}

bool ReservationDatabase::exist( string idNumber, string reservationNumber )
{
   // loop through reservations searching for matching idNumber and reservationNumber
   for( vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it )
      if( it->getIdNumber() == idNumber && it->getReservationNumber() == reservationNumber )
         return true; // return true if match found

   return false; // if no matching reservation was found, return false
}

void ReservationDatabase::displayReservation( string idNumber, string reservationNumber )
{
   vector< Reservation >::iterator it = searchReservation( idNumber, reservationNumber );
   it->displayReservationDetails();
}

void ReservationDatabase::cancelReservation( string idNumber, string reservationNumber )
{
   vector< Reservation >::iterator it = searchReservation( idNumber, reservationNumber );
   reservations.erase( it );
   cout << "\nReservation Cancelled.\n\n";
}

void ReservationDatabase::addReservation( Reservation reservation )
{
   reservations.push_back( reservation );
}

void ReservationDatabase::reduceSeats( string idNumber, string reservationNumber )
{
    int adult_t, concession_t;

    for (int a = 0; a < reservations.size(); a++) {
        if (reservations[a].getIdNumber() == idNumber && reservations[a].getReservationNumber() == reservationNumber) {
            while (1) {
                cout << "\nHow many adult tickets to cancel? ";
                cin >> adult_t;
                cout << "How many concession tickets to cancel? ";
                cin >> concession_t;
                cout << endl;
                if (adult_t + concession_t > 0 && adult_t <= reservations[a].getAdultTickets() && concession_t <= reservations[a].getConcessionTickets()) {
                    reservations[a].setAdultTickets(reservations[a].getAdultTickets() - adult_t);
                    reservations[a].setConcessionTickets(reservations[a].getConcessionTickets() - concession_t);
                    displayReservation(idNumber, reservationNumber);
                    cout << "\nYou have successfully reduced the number of tickets!\n\n";
                    return;
                }
            }
        }
    }
}

vector< Reservation >::iterator ReservationDatabase::searchReservation( string idNumber, string reservationNumber )
{
   // loop through reservations searching for matching idNumber and reservationNumber
   for( vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it )
      if( it->getIdNumber() == idNumber && it->getReservationNumber() == reservationNumber )
         return it; // return iterator to thecurrent reservation if match found

   return reservations.end();
}