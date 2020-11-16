#include <iostream>
#include <fstream>
using namespace::std;

#include "AvailSeatsDatabase.h"

AvailSeatsDatabase::AvailSeatsDatabase()
{
	loadAvailSeats();

	Date currentDate;
	computeCurrentDate(currentDate);
	AvailSeats temp;
	int x = 1;

	if (availSeats.size() > 0) {
		while (availSeats[0].getDate() < currentDate + 1) {
			availSeats.erase(availSeats.begin());

			temp.setDate(availSeats.end()->getDate() + 1);
			temp.setNumAvailSeats(1, 20);
			temp.setNumAvailSeats(2, 20);
			temp.setNumAvailSeats(3, 20);
			temp.setNumAvailSeats(4, 20);
			availSeats.push_back(temp);
		}
	}

	while (availSeats.size() != 30) {
		temp.setDate(currentDate + x++);
		temp.setNumAvailSeats(1, 20);
		temp.setNumAvailSeats(2, 20);
		temp.setNumAvailSeats(3, 20);
		temp.setNumAvailSeats(4, 20);
		availSeats.push_back(temp);
	}
}

AvailSeatsDatabase::~AvailSeatsDatabase()
{
   storeAvailSeats();
}

void AvailSeatsDatabase::decreaseAvailSeats( Date date, int timeCode, int requiredSeats )
{
	for (size_t a = 0; a < availSeats.size(); a++) {
		if (availSeats[a].getDate() == date) {
			availSeats[a].setNumAvailSeats(timeCode, availSeats[a].getNumAvailSeats(timeCode) - requiredSeats);
			break;
		}
	}
}

bool AvailSeatsDatabase::availableTimes( Date date, int requiredSeats )
{
	if (searchAvailSeats(date)->getDate() == date) {
		for (size_t b = 1; b <= 4; b++) {
			if (searchAvailSeats(date)->getNumAvailSeats(b) >= requiredSeats)
				return true;
		}
	}

	return false;
}

bool AvailSeatsDatabase::availableTimes( Date date, int timeCode, int requiredSeats )
{
	if (searchAvailSeats(date)->getDate() == date) {
		if (searchAvailSeats(date)->getNumAvailSeats(timeCode) >= requiredSeats)
			return true;
	}

	return false;
}

vector< AvailSeats >::iterator AvailSeatsDatabase::searchAvailSeats( Date date )
{
	auto it = availSeats.begin();

	for (; it != availSeats.end(); it++) {
		if ((*it).getDate() == date)
			return it;
	}
}

void AvailSeatsDatabase::loadAvailSeats()
{
	AvailSeats temp;
	ifstream inFile("AvailSeats.dat", ios::in | ios::binary);
	while (inFile.read((char*)& temp, sizeof(AvailSeats)))
		availSeats.push_back(temp);
	inFile.close();
}

void AvailSeatsDatabase::storeAvailSeats()
{
	ofstream outFile("AvailSeats.dat", ios::out | ios::binary);
	for (size_t a = 0; a < availSeats.size(); a++)
		outFile.write((char*)& availSeats[a], sizeof(AvailSeats));
	outFile.close();
}