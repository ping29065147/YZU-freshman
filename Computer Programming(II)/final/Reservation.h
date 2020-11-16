#ifndef RESERVATION_H
#define RESERVATION_H

#include "Date.h"

class Reservation
{
public:
   Reservation();

   Reservation( string thePhoneNumber, string theName, Date theDate,
                int theTime, int thePartySize, int theMenu );

   void setPhoneNumber( string thePhoneNumber );
   void setName( string theName );
   void setDate( Date theDate );
   void setTime( int theTime );
   void setPartySize( int thePartySize );
   void setMenu( int theMenu );

   string getPhoneNumber();
   string getName();
   Date getDate();
   int getTime();
   int getPartySize();

   // displays 1: partySize
   //          2: date
   //          3: time
   void displayReservationInfo();

private:
   char phoneNumber[ 12 ]; // �q�ܸ��X
   char name[ 8 ];         // �m�W
   Date date;              // �w�����
   int time;               // �w���ɶ��G1 for 11:30, 2 for 13:30, 3 for 17:45, 4 for 19:45
   int partySize;          // ���O�H��
   int menu;               // 1 for NT$ 1080, 2 for NT$ 1680, 3 for NT$ 2280
};

#endif