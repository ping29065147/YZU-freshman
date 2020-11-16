#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <string.h>
#include <string>
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
	char reservationNumber[12]; // used to identify a reservation
	char trainNumber[8];  // used to identify a train
	char idNumber[12];    // the id number of the contact person
	char phone[12];       // the (local or mobile) phone number of the contact person
	char date[12];        // outbound date
	int originStation;      // the origin station code
	int destinationStation; // the destination station code
	int carClass;           // the car class code; 1:standard car, 2:business car
	int adultTickets;       // the number of adult tickets
	int concessionTickets;  // the number of concession tickets
};

struct Train
{
	char trainNumber[8];          // used to identify a train
	char departureTimes[13][8]; // the departure time of a train for each station,
};                                 // departureTimes[0] is not used

// input an integer in the range [ begin, end ]
int inputAnInteger(int begin, int end);

void makingReservation(Train southboundTimetable[100], Train northboundTimetable[100]);

// inputs originStation, destinationStation, carClass,
// date, departureTime, adultTickets and concessionTickets
void inputReservationDetails(Reservation& reservation, int& departureTime);

// loads the southbound timetable from the file "Southbound timetable.dat"
void loadSouthboundTimetable(Train southboundTimetable[100], int& numSouthboundTrains);

// loads the northbound timetable from the file "Northbound timetable.dat"
void loadNorthboundTimetable(Train northboundTimetable[100], int& numNorthboundTrains);

// displays timetables for 10 coming southbound trains, then let user select one
void selectSouthboundTrain(Train southboundTimetable[100], int numSouthboundTrains,
	Reservation& reservation, int departureTime);

// displays timetables for 10 coming northbound trains, then let user select one
void selectNorthboundTrain(Train northboundTimetable[100], int numNorthboundTrains,
	Reservation& reservation, int departureTime);

// inputs idNumber and phone, and randomly generate reservationNumber
void inputContactInfo(Reservation& reservation);

// save reservation to the end of the file Reservation details.dat
void saveReservation(Reservation reservation);

void reservationHistory(Train southboundTimetable[100],
	Train northboundTimetable[100]);

// inputs idNumber and reservationNumber, and
// checks if the corresponding reservation exists
bool existReservation(fstream& ioFile, Reservation& reservation);


void displayReservations(Train southboundTimetable[100],
	Train northboundTimetable[100], Reservation reservation);

// displays date, originStation, destinationStation, departureTime, arrival time,
// fare for adultTickets, fare for concessionTickets and total fare
void display(Reservation reservation, Train trainTimetable[100],
	char stations[13][12], char carClass[12]);

// reduces adultTickets and/or concessionTickets in reservation
void reduceSeats(fstream& ioFile, Train southboundTimetable[100],
	Train northboundTimetable[100], Reservation& reservation);

int main()
{
	cout << "Taiwan High Speed Rail Booking System\n";
	srand(static_cast<unsigned int>(time(0)));

	Train southboundTimetable[100];
	Train northboundTimetable[100];
	int choice; // store user choice

	// enable user to specify action
	while (true)
	{
		cout << "\nEnter Your Choice\n"
			<< "1. Booking\n"
			<< "2. Booking History\n"
			<< "3. End Program";

		do cout << "\n? ";
		while ((choice = inputAnInteger(1, 3)) == -1);
		cout << endl;

		switch (choice)
		{
		case 1:
			makingReservation(southboundTimetable, northboundTimetable);
			break;
		case 2:
			reservationHistory(southboundTimetable, northboundTimetable);
			break;
		case 3:
			cout << "Thank you! Goodbye!\n\n";
			system("pause");
			return 0;
		default: // display error if user does not select valid choice
			cerr << "Incorrect Choice!\n";
			break;
		}
	}

	system("pause");
} // end main

// input an integer in the range [ begin, end ]
int inputAnInteger(int begin, int end)
{
	string input;
	int re;

	cin >> input;

	if (input.size() == 2)
		re = (input[0] - '0') * 10 + input[1] - '0';
	else if (input.size() == 1)
		re = input[0] - '0';
	else
		return -1;

	if (re >= begin && re <= end)
		return re;
	else
		return -1;
}

void makingReservation(Train southboundTimetable[100], Train northboundTimetable[100])
{
	Reservation reservation;
	int departureTime, numSouthboundTrains, numNorthboundTrains;

	inputReservationDetails(reservation, departureTime);

	loadSouthboundTimetable(southboundTimetable, numSouthboundTrains);
	loadNorthboundTimetable(northboundTimetable, numNorthboundTrains);

	if (reservation.originStation < reservation.destinationStation)
		selectSouthboundTrain(southboundTimetable, numSouthboundTrains, reservation, departureTime);
	else
		selectNorthboundTrain(northboundTimetable, numNorthboundTrains, reservation, departureTime);


	inputContactInfo(reservation);
}

// inputs originStation, destinationStation, carClass,
// date, departureTime, adultTickets and concessionTickets
void inputReservationDetails(Reservation& reservation, int& departureTime)
{

choose_again:
	cout << "Origin Station\n";
	cout << "1. Nangang\n2. Taipei\n3. Banqiao\n4. Taoyuan\n5. Hsinchu\n6. Miaoli\n7. Taichung\n8. Changhua\n9. Yunlin\n10. Chiayi\n11. Tainan\n12. Zuoying";
	do cout << "\n? ";
	while ((reservation.originStation = inputAnInteger(1, 12)) == -1);
	cout << endl;

	cout << "Destination Station\n";
	cout << "1. Nangang\n2. Taipei\n3. Banqiao\n4. Taoyuan\n5. Hsinchu\n6. Miaoli\n7. Taichung\n8. Changhua\n9. Yunlin\n10. Chiayi\n11. Tainan\n12. Zuoying";
	do cout << "\n? ";
	while ((reservation.destinationStation = inputAnInteger(1, 12)) == -1);
	cout << endl;

	if (reservation.originStation == reservation.destinationStation) {
		cout << "Can not choose the same station!!!\nplease choose again.\n\n";
		goto choose_again;
	}

	cout << "Car Class\n";
	cout << "1. Standard Car\n2. Business Car";
	do cout << "\n? ";
	while ((reservation.carClass = inputAnInteger(1, 2)) == -1);
	cout << endl;

	cout << "Departure Date: ";
	cin >> reservation.date;
	cout << endl;

	cout << "Departure Time\n";
	for (int a = 1; a < 35; a++) {
		cout << a << ". " << departureTimes[a];
		if (a < 34)
			cout << endl;
	}
	do cout << "\n? ";
	while ((departureTime = inputAnInteger(1, 34)) == -1);
	cout << endl;

choose_again2:
	cout << "How many adult tickets";
	while (1) {
		cout << "? ";
		cin >> reservation.adultTickets;
		cout << endl;
		if (reservation.adultTickets >= 0)
			break;
	}

	cout << "How many concession tickets";
	while (1) {
		cout << "? ";
		cin >> reservation.concessionTickets;
		cout << endl;
		if (reservation.concessionTickets >= 0)
			break;
	}

	if (reservation.adultTickets + reservation.concessionTickets == 0) {
		cout << "Can not choose both 0 ticket!!!\nplease choose again.\n\n";
		goto choose_again2;
	}
}

// loads the southbound timetable from the file "Southbound timetable.txt"
void loadSouthboundTimetable(Train southboundTimetable[100], int& numSouthboundTrains)
{
	numSouthboundTrains = 0;
	int count = 0;
	char input[8];
	ifstream inFile("Southbound timetable.txt", ios::in);

	while (inFile >> input) {

		if (count == 0)
			strcpy_s(southboundTimetable[numSouthboundTrains].trainNumber, input);
		else if (count < 13)
			strcpy_s(southboundTimetable[numSouthboundTrains].departureTimes[count], input);
		else {
			count = 0;
			numSouthboundTrains++;
			strcpy_s(southboundTimetable[numSouthboundTrains].trainNumber, input);
		}

		count++;
	}

	inFile.close();
}

// loads the northbound timetable from the file "Northbound timetable.txt"
void loadNorthboundTimetable(Train northboundTimetable[100], int& numNorthboundTrains)
{
	numNorthboundTrains = 0;
	int count = 0;
	char input[8];
	ifstream inFile("Northbound timetable.txt", ios::in);

	while (inFile >> input) {

		if (count == 0)
			strcpy_s(northboundTimetable[numNorthboundTrains].trainNumber, input);
		else if (count < 13)
			strcpy_s(northboundTimetable[numNorthboundTrains].departureTimes[count], input);
		else {
			count = 0;
			numNorthboundTrains++;
			strcpy_s(northboundTimetable[numNorthboundTrains].trainNumber, input);
		}

		count++;
	}

	inFile.close();
}

// displays timetables for 10 coming southbound trains, then let user select one
void selectSouthboundTrain(Train southboundTimetable[100], int numSouthboundTrains,
	Reservation& reservation, int departureTime)
{
	char stations[13][12] = { "", "Nangang", "Taipei", "Banqiao", "Taoyuan", "Hsinchu", "Miaoli", "Taichung", "Changhua", "Yunlin", "Chiayi", "Tainan", "Zuoying" };
	char carClass[12];
	if (reservation.carClass == 1)
		strcpy_s(carClass, "Standard");
	else
		strcpy_s(carClass, "Business");

	int a, control, count = 0;
	char num[10][8];
	cout << "Train No.  Departure  Arrival\n";

	for (a = 0; a < numSouthboundTrains; a++) {
		if (strlen(southboundTimetable[a].departureTimes[reservation.originStation]) == 1 || strlen(southboundTimetable[a].departureTimes[reservation.destinationStation]) == 1)
			continue;
		control = strcmp(southboundTimetable[a].departureTimes[reservation.originStation], departureTimes[departureTime]);

		if (control > 0) {
			cout << setw(9) << right << southboundTimetable[a].trainNumber;
			strcpy_s(num[count], southboundTimetable[a].trainNumber);
			cout << setw(11) << southboundTimetable[a].departureTimes[reservation.originStation];
			cout << setw(9) << southboundTimetable[a].departureTimes[reservation.destinationStation];
			cout << endl;
			count++;
		}

		if (count == 10)
			break;
	}

	while (1) {
		cout << "\nEnter Train Number: ";
		cin >> reservation.trainNumber;

		for (a = 0; a < 10; a++) {
			if (!strcmp(reservation.trainNumber, num[a]))
				goto out;
		}
	}
out:
	cout << "\nTrip Details\n\n";

	display(reservation, southboundTimetable, stations, carClass);
}

// displays timetables for 10 coming northbound trains, then let user select one
void selectNorthboundTrain(Train northboundTimetable[100], int numNorthboundTrains,
	Reservation& reservation, int departureTime)
{
	char stations[13][12] = { "", "Zuoying", "Tainan", "Chiayi", "Yunlin", "Changhua", "Taichung", "Miaoli", "Hsinchu", "Taoyuan", "Banqiao", "Taipei", "Nangang" };
	char carClass[12];
	if (reservation.carClass == 1)
		strcpy_s(carClass, "Standard");
	else
		strcpy_s(carClass, "Business");
	reservation.originStation = 13 - reservation.originStation;
	reservation.destinationStation = 13 - reservation.destinationStation;

	int a, control, count = 0;
	char num[10][8];
	cout << "Train No.  Departure  Arrival\n";

	for (a = 0; a < numNorthboundTrains; a++) {
		if (strlen(northboundTimetable[a].departureTimes[reservation.originStation]) == 1 || strlen(northboundTimetable[a].departureTimes[reservation.destinationStation]) == 1)
			continue;
		control = strcmp(northboundTimetable[a].departureTimes[reservation.originStation], departureTimes[departureTime]);

		if (control > 0) {
			cout << setw(9) << right << northboundTimetable[a].trainNumber;
			strcpy_s(num[count], northboundTimetable[a].trainNumber);
			cout << setw(11) << northboundTimetable[a].departureTimes[reservation.originStation];
			cout << setw(9) << northboundTimetable[a].departureTimes[reservation.destinationStation];
			cout << endl;
			count++;
		}

		if (count == 10)
			break;
	}

	while (1) {
		cout << "\nEnter Train Number: ";
		cin >> reservation.trainNumber;

		for (a = 0; a < 10; a++) {
			if (!strcmp(reservation.trainNumber, num[a]))
				goto out;
		}
	}
out:
	cout << "\nTrip Details\n\n";

	display(reservation, northboundTimetable, stations, carClass);
}

// inputs idNumber and phone, and randomly generate reservationNumber
void inputContactInfo(Reservation& reservation)
{
	cout << "\nEnter Contact Person Information\n";
	cout << "\nID Number: ";
	cin >> reservation.idNumber;
	cout << "\nPhone: ";
	cin >> reservation.phone;
	cout << endl;

	srand(time(NULL));
	cout << "Reservation Number: ";
	for (int a = 0; a < 8; a++) {
		reservation.reservationNumber[a] = (rand() % 10) + '0';
		cout << reservation.reservationNumber[a];
	}
	reservation.reservationNumber[8] = '\0';
	saveReservation(reservation);
	cout << "\n\nReservation Completed!\n\n";

}

// save reservation to the end of the file Reservation details.dat
void saveReservation(Reservation reservation)
{
	ofstream outFile("Reservation details.dat", ios::app | ios::binary);
	outFile.seekp(0, ios::end);

	outFile.write(reinterpret_cast<const char*>(&reservation), sizeof(Reservation));

	outFile.close();
}

void reservationHistory(Train southboundTimetable[100],
	Train northboundTimetable[100])
{
	int choice, now;
	Reservation reservation;

	fstream ioFile("Reservation details.dat", ios::in | ios::app | ios::binary);
	while (existReservation(ioFile, reservation) == false)
		cout << "\nReservation record not found.\n\n";



	displayReservations(southboundTimetable, northboundTimetable, reservation);

	while (true)
	{
		cout << "\nEnter Your Choice\n"
			<< "1. Cancellation\n"
			<< "2. Reduce\n"
			<< "3. End";

		do cout << "\n? ";
		while ((choice = inputAnInteger(1, 3)) == -1);
		cout << endl;

		switch (choice)
		{
		case 1:
			reservation.adultTickets = 0;
			reservation.carClass = 0;
			reservation.concessionTickets = 0;
			reservation.destinationStation = 0;
			reservation.originStation = 0;
			reservation.date[0] = '\0';
			reservation.idNumber[0] = '\0';
			reservation.phone[0] = '\0';
			reservation.reservationNumber[0] = '\0';
			reservation.trainNumber[0] = '\0';
			now = ioFile.tellp();
			now -= sizeof(Reservation);
			ioFile.seekp(now, ios::beg);
			ioFile.write(reinterpret_cast<const char*>(&reservation), sizeof(Reservation));
			cout << "\nReservation Cancelled!\n\n";
			return;
		case 2:
			reduceSeats(ioFile, southboundTimetable, northboundTimetable, reservation);
			return;
		case 3:
			return;
		default:
			cerr << "Incorrect Choice!\n";
			return;
		}
	}
	ioFile.close();
}

// inputs idNumber and reservationNumber, and
// checks if the corresponding reservation exists
bool existReservation(fstream& ioFile, Reservation& reservation)
{

	char IDNumber[12], ReservationNumber[12];
	cout << "Enter ID Number: ";
	cin >> IDNumber;
	cout << "\nEnter Reservation Number: ";
	cin >> ReservationNumber;

	Reservation input;

	ioFile.clear();
	ioFile.seekg(0, ios::beg);
	while (ioFile.read((char*)& input, sizeof(Reservation))) {
		cout << input.idNumber << endl;
		cout << IDNumber << endl;
		cout << input.reservationNumber << endl;
		cout << ReservationNumber << endl;
		if (!strcmp(input.idNumber, IDNumber) && !strcmp(input.reservationNumber, ReservationNumber)) {
			reservation = input;
			return true;
		}
	}
	return false;


}


void displayReservations(Train southboundTimetable[100],
	Train northboundTimetable[100], Reservation reservation)
{
	int numSouthboundTrains, numNorthboundTrains;
	char stations[13][12] = { "", "Nangang", "Taipei", "Banqiao", "Taoyuan", "Hsinchu", "Miaoli", "Taichung", "Changhua", "Yunlin", "Chiayi", "Tainan", "Zuoying" };
	char carClass[12];

	if (reservation.carClass == 1)
		strcpy_s(carClass, "Standard");
	else
		strcpy_s(carClass, "Business");

	loadSouthboundTimetable(southboundTimetable, numSouthboundTrains);
	loadNorthboundTimetable(northboundTimetable, numNorthboundTrains);

	cout << "\nReservation Details\n\n";

	if (reservation.originStation < reservation.destinationStation)
		display(reservation, southboundTimetable, stations, carClass);
	else
		display(reservation, northboundTimetable, stations, carClass);
}

// displays date, originStation, destinationStation, departureTime, arrival time,
// fare for adultTickets, fare for concessionTickets and total fare
void display(Reservation reservation, Train trainTimetable[100],
	char stations[13][12], char carClass[12])
{
	int s, t, fare = 0;

	cout << "      Date  Train No.    From        To  Departure  Arrival   Adult  Concession  Fare     Class\n";
	cout << setw(10) << right << reservation.date;
	cout << setw(11) << reservation.trainNumber;
	cout << setw(8) << stations[reservation.originStation];
	cout << setw(10) << stations[reservation.destinationStation];
	for (int a = 0; a < 100; a++) {
		if (!strcmp(reservation.trainNumber, trainTimetable[a].trainNumber)) {
			cout << setw(11) << trainTimetable[a].departureTimes[reservation.originStation];
			cout << setw(9) << trainTimetable[a].departureTimes[reservation.destinationStation];
			break;
		}
	}
	if (reservation.originStation > reservation.destinationStation) {
		s = reservation.originStation;
		t = reservation.destinationStation;
	}
	else {
		t = reservation.originStation;
		s = reservation.destinationStation;
	}

	fare = adultTicketPrice[s][t] * reservation.adultTickets + (adultTicketPrice[s][t] / 2) * reservation.concessionTickets;
	cout << setw(6) << adultTicketPrice[s][t] << "*" << reservation.adultTickets;
	cout << setw(10) << adultTicketPrice[s][t] / 2 << "*" << reservation.concessionTickets;

	cout << setw(6) << fare;
	cout << setw(10) << carClass << endl << endl;
}

// reduces adultTickets and/or concessionTickets in reservation
void reduceSeats(fstream& ioFile, Train southboundTimetable[100],
	Train northboundTimetable[100], Reservation& reservation)
{
	int cancel_adult, cancel_concession, now;
	cout << "How many adult tickets to cancel?";
	cin >> cancel_adult;
	cout << "How many concession tickets to cancel?";
	cin >> cancel_concession;

	reservation.adultTickets -= cancel_adult;
	reservation.concessionTickets -= cancel_concession;

	if (reservation.adultTickets==0 && reservation.concessionTickets==0) {
		reservation.adultTickets = 0;
		reservation.carClass = 0;
		reservation.concessionTickets = 0;
		reservation.destinationStation = 0;
		reservation.originStation = 0;
		reservation.date[0] = '\0';
		reservation.idNumber[0] = '\0';
		reservation.phone[0] = '\0';
		reservation.reservationNumber[0] = '\0';
		reservation.trainNumber[0] = '\0';
		now = ioFile.tellp();
		now -= sizeof(Reservation);
		ioFile.seekp(now, ios::beg);
		ioFile.write(reinterpret_cast<const char*>(&reservation), sizeof(Reservation));
	}

	displayReservations(southboundTimetable, northboundTimetable, reservation);

	cout << "\nYou have successfully reduced the number of tickets!\n\n";
}


<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head><meta http-equiv="Content-Type" content="text/html; charset=utf-8" /><title>

</title></head>
<body>
    <form method="post" action="./File_DownLoad_Wk_zip.aspx?File_name=1083321_final.cpp&amp;type=3&amp;id=2848559" id="form1">
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
