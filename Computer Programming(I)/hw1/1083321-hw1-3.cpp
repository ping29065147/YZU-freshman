// Determine whether a number is a palindrome.
#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
   int number; // user input number
   int n[5], a;

   cout << "Enter a 5-digit number: "; // prompt for a number
   cin >> number; // get number

   cout << number << " is ";

   for(a=4; a>-1; a--, number/=10)
      n[a] = number%10;

   for(a=0;a<2;a++){
      if (!(n[a] == n[4-a]))
         break;
   }

   if (a==2)
      cout << "a palindrome!!!";
   else
      cout << "not a palindrome.";

   system( "pause" );
   return 0;
} // end main
