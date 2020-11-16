// MakingReservation.cpp
// Member-function definitions for class MakingReservation.
#include <iostream>
#include <iomanip>
#include "MakingReservation.h" // MakingReservation class definition

extern int inputAnInteger( int begin, int end );

extern string departureTimes[ 37 ];

string station_name[13] = { "", "Nangang", "Taipei", "Banqiao", "Taoyuan", "Hsinchu", "Miaoli"
                              , "Taichung", "Changhua", "Yunlin", "Chiayi", "Tainan", "Zuoying" };

// MakingReservation constructor
MakingReservation::MakingReservation( ReservationDatabase &theReservationDatabase,
                                      SouthboundTimetable &theSouthboundTimetable,
                                      NorthboundTimetable &theNorthboundTimetable )
   : reservationDatabase( theReservationDatabase ),
     southboundTimetable( theSouthboundTimetable ),
     northboundTimetable( theNorthboundTimetable )
{
}

void MakingReservation::execute()
{
   if( chooseTrain() ) // displays timetables for 10 coming trains, then let user choose a train
   {
      inputReservationDetails();

      inputContactPersonInfo();

      reservationDatabase.addReservation( reservation );

      cout << "\nReservation Completed!\n\n";
   }
   else
      cout << "\nSorry! No train is available!\n\n";
}

bool MakingReservation::chooseTrain()
{
    int input, time_num;

    cout << "\nOrigin Station\n";
    for (int a = 1; a <= 12; a++)
        cout << a << ". " << station_name[a] << endl;
    while (1) {
        cout << "? ";
        cin >> input;
        reservation.setOriginStation(input);
        if (input >= 1 && input <= 12)
            break;
    }

    cout << "\nDestination Station\n";
    for (int a = 1; a <= 12; a++)
        cout << a << ". " << station_name[a] << endl;
    while (1) {
        cout << "? ";
        cin >> input;
        reservation.setDestinationStation(input);
        if (input >= 1 && input <= 12 && input != reservation.getOriginStation())
            break;
    }

    cout << "\nDeparture Time\n";
    for (int a = 1; a < 37; a++)
        cout << a << ". " << departureTimes[a] << endl;
    while (1) {
        cout << "? ";
        cin >> time_num;
        if (time_num >= 1 && time_num < 37)
            break;
    }

    string tn;
    cout << endl << setw(11) << "Train No." << setw(11) << "Departure" << setw(11) << "Arrival" << endl;
    if (reservation.getOriginStation() < reservation.getDestinationStation()) {
        if (southboundTimetable.trainsAvailable(time_num, reservation.getOriginStation(), reservation.getDestinationStation())) {
            southboundTimetable.displayComingTrains(time_num, reservation.getOriginStation(), reservation.getDestinationStation());
            
            cout << "\nEnter Train Number";
            while (1) {
                cout << ": ";
                cin >> tn;
                if (southboundTimetable.getDepartureTimes(tn, reservation.getOriginStation()).size() > 0 && southboundTimetable.getDepartureTimes(tn, reservation.getOriginStation()) >= departureTimes[time_num]) {
                    reservation.setTrainNumber(tn);
                    return true;
                }
            }
        }
        else
            return false;
    }
    else {
        if (northboundTimetable.trainsAvailable(time_num, 13-reservation.getOriginStation(), 13-reservation.getDestinationStation())) {
            northboundTimetable.displayComingTrains(time_num, 13-reservation.getOriginStation(), 13-reservation.getDestinationStation());
            
            cout << "\nEnter Train Number";
            while (1) {
                cout << ": ";
                cin >> tn;
                if (northboundTimetable.getDepartureTimes(tn, 13-reservation.getOriginStation()).size() > 0 && northboundTimetable.getDepartureTimes(tn, 13-reservation.getOriginStation()) >= departureTimes[time_num]) {
                    reservation.setTrainNumber(tn);
                    return true;
                }
            }
        }
        else
            return false;
    }

    return true;
}

void MakingReservation::inputReservationDetails()
{
   cout << "\nCar Class\n" << "1. Standard Car\n" << "2. Business Car";

   int carClass;
   do cout << "\n? ";
   while( ( carClass = inputAnInteger( 1, 2 ) ) == -1 );
   reservation.setCarClass( carClass );

	cout << "\nDeparture Date: ";

   char date[12];
   cin >> date;
   reservation.setDate( date );
   cin.ignore();

	cout << "\nHow many adult tickets? ";

   int adultTickets;
   cin >> adultTickets;
   reservation.setAdultTickets( adultTickets );

	cout << "\nHow many concession tickets? ";

   int concessionTickets;
   cin >> concessionTickets;
   reservation.setConcessionTickets( concessionTickets );

   cout << "\nTrip Details\n";
   reservation.displayReservationDetails();
}

void MakingReservation::inputContactPersonInfo()
{
   cout << "\nEnter Contact Person Information\n\n";

   cout << "ID Number: ";
   string idNumber;
   cin >> idNumber;
   reservation.setIdNumber( idNumber );

   cout << "\nPhone: ";
   string phone;
   cin >> phone;
   cin.ignore();
   reservation.setPhone( phone );

   srand( static_cast< unsigned int >( time( 0 ) ) );
   char reservationNumber[ 12 ];
   for( int i = 0; i < 8; i++ )
      reservationNumber[ i ] = rand() % 10 + '0';
   reservationNumber[ 8 ] = '\0';
   reservation.setReservationNumber( reservationNumber );
   
	cout << "\nReservation Number: " << reservationNumber << endl;
}