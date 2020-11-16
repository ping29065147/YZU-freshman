#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
   int year, determine=0;
   cout << "Enter a year ( 1583-3000 ): ";
   cin >> year;

   cout << "Year " << year << " is a ";

   if (year%4 == 0){
      determine = 1;
      if (year%100 == 0)
         determine = 0;
         if (year%400 == 0)
            determine = 1;
   }

   if (determine)
      cout << "leap year.";
   else
      cout << "common year.";

   system( "pause" );
   return 0;
}
