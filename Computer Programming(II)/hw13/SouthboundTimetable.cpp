// FlightSchedule.cpp
// Member-function definitions for class SouthboundTimetable.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "SouthboundTimetable.h"

extern string departureTimes[ 37 ];

// SouthboundTimetable default constructor
// loads southbound timetable from the file "Southbound timetable.dat"
SouthboundTimetable::SouthboundTimetable()
{
   loadSouthboundTimetable();
}

void SouthboundTimetable::loadSouthboundTimetable()
{
    ifstream inFile3("Southbound timetable.dat", ios::binary | ios::in);
    Train temp;
    while (inFile3.read((char*)&temp, sizeof(Train)))
        southboundTimetable.push_back(temp);
    inFile3.close();
}

// returns departureTimes[ station ]
string SouthboundTimetable::getDepartureTimes( string trainNumber, int station )
{
   vector< Train >::iterator it = searchTrain( trainNumber );
   return it->getDepartureTimes( station );
}

bool SouthboundTimetable::trainsAvailable( int departureTime,
     int originStation, int destinationStation )
{
    for (int a = southboundTimetable.size() - 1; a >= 0; a--) {
        if (departureTimes[departureTime] <= southboundTimetable[a].getDepartureTimes(originStation) && southboundTimetable[a].getDepartureTimes(destinationStation) != "-")
            return true;
    }

    return false;
}

void SouthboundTimetable::displayComingTrains( int departureTime,
     int originStation, int destinationStation )
{
    int count = 0;
    for (int a = 0; a < southboundTimetable.size() && count < 10; a++) {
        if (departureTimes[departureTime] <= southboundTimetable[a].getDepartureTimes(originStation) && southboundTimetable[a].getDepartureTimes(destinationStation) != "-") {
            cout << setw(11) << southboundTimetable[a].getTrainNumber() << setw(11) << southboundTimetable[a].getDepartureTimes(originStation) << setw(11) << southboundTimetable[a].getDepartureTimes(destinationStation) << endl;
            count++;
        }
    }
}

vector< Train >::iterator SouthboundTimetable::searchTrain( string trainNumber )
{
   vector< Train >::iterator it = southboundTimetable.begin();
   for( ; it != southboundTimetable.end(); ++it )
      if( it->getTrainNumber() == trainNumber )
         return it;

   return southboundTimetable.end();
}