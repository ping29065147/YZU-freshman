// NorthboundTimetable.cpp
// Member-function definitions for class NorthboundTimetable.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "NorthboundTimetable.h"

extern string departureTimes[ 37 ];

// NorthboundTimetable default constructor
// loads northbound timetable from the file "Northbound timetable.dat"
NorthboundTimetable::NorthboundTimetable()
{
   loadNorthboundTimetable();
}

void NorthboundTimetable::loadNorthboundTimetable()
{
    ifstream inFile2("Northbound timetable.dat", ios::binary | ios::in);
    Train temp;
    while (inFile2.read((char*)&temp, sizeof(Train)))
        northboundTimetable.push_back(temp);
    inFile2.close();
}

// returns departureTimes[ station ]
string NorthboundTimetable::getDepartureTimes( string trainNumber, int station )
{
   vector< Train >::iterator it = searchTrain( trainNumber );
   return it->getDepartureTimes( station );
}

bool NorthboundTimetable::trainsAvailable( int departureTime,
     int originStation, int destinationStation )
{
    for (int a = northboundTimetable.size() - 1; a >= 0; a--) {
        if (departureTimes[departureTime] <= northboundTimetable[a].getDepartureTimes(originStation) && northboundTimetable[a].getDepartureTimes(destinationStation) != "-")
            return true;
    }

    return false;
}

void NorthboundTimetable::displayComingTrains( int departureTime,
     int originStation, int destinationStation )
{
    int count = 0;
    for (int a = 0; a < northboundTimetable.size() && count < 10; a++) {
        if (departureTimes[departureTime] <= northboundTimetable[a].getDepartureTimes(originStation) && northboundTimetable[a].getDepartureTimes(destinationStation) != "-") {
            cout << setw(11) << northboundTimetable[a].getTrainNumber() << setw(11) <<northboundTimetable[a].getDepartureTimes(originStation) << setw(11) << northboundTimetable[a].getDepartureTimes(destinationStation) << endl;
            count++;
        }
    }
}

vector< Train >::iterator NorthboundTimetable::searchTrain( string trainNumber )
{
   vector< Train >::iterator it = northboundTimetable.begin();
   for( ; it != northboundTimetable.end(); ++it )
      if( it->getTrainNumber() == trainNumber )
         return it;

   return northboundTimetable.end();
}