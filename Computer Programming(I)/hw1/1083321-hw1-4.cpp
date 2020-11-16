// Determine whether three values represent the sides of a right triangle.
#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
   int side1; // length of side 1
   int side2; // length of side 2
   int side3; // length of side 3
   int change;

   // get values of three sides
   cout << "Enter side 1: ";
   cin >> side1;

   cout << "Enter side 2: ";
   cin >> side2;

   cout << "Enter side 3: ";
   cin >> side3;

   if (side1 > side2){
      change = side1;
      side1 = side2;
      side2 = change;
   }
   if (side2 > side3){
      change = side2;
      side2 = side3;
      side3 = change;
   }

   if (side1*side1 + side2*side2 == side3*side3)
      cout << "These are the sides of a right triangle.";
   else
      cout << "These do not form a right triangle.";

   system( "pause" );
   return 0;
} // end main
