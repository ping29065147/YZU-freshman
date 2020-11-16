#include <iostream>
#include "ReservationHistory.h" // ReservationHistory class definition

extern int inputAnInteger( int begin, int end );

// ReservationHistory default constructor
ReservationHistory::ReservationHistory( ReservationDatabase &theReservationDatabase,
                                        SouthboundTimetable &theSouthboundTimetable,
                                        NorthboundTimetable &theNorthboundTimetable )
   : idNumber(),
     reservationNumber(),
     reservationDatabase( theReservationDatabase ),
     southboundTimetable( theSouthboundTimetable ),
     northboundTimetable( theNorthboundTimetable )
{
} // end ReservationHistory default constructor

void ReservationHistory::execute()
{
    cout << "Enter ID Number: ";
    cin >> idNumber;
    cout << "\nEnter Reservation Number: ";
    cin >> reservationNumber;
    if (reservationDatabase.exist(idNumber, reservationNumber)) {
        cout << "\nReservation Details\n";
        reservationDatabase.displayReservation(idNumber, reservationNumber);
    }
    else {
        cout << "\nReservation record not found.\n\n";
        return;
    }

    int choice;
    cout << "\nEnter Your Choice"
        << "\n1. Cancellation"
        << "\n2. Reduce"
        << "\n3. End";
    while (1) {
        cout << "\n? ";
        cin >> choice;
        if (choice >= 1 && choice <= 3)
            break;
    }

    switch (choice) 
    {
    case 1:
        reservationDatabase.cancelReservation(idNumber, reservationNumber);
        break;
    case 2:
        reservationDatabase.reduceSeats(idNumber, reservationNumber);
        break;
    case 3:
        cout << endl;
        return;
    }
}