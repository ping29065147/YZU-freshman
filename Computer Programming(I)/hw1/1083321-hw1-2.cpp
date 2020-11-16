#include <iostream> // allows program to perform input and output
#include <stdlib.h>
using namespace std; // program uses names from the std namespace

int main()
{
   int number; // integer read from user
   int n[5], a;

   cout << "Enter a five-digit integer: "; // prompt
   cin >> number; // read integer from user

   for(a=4; a>-1; a--, number/=10)
    n[a] = number%10;

   for(a=0; a<5; a++){
      cout << n[a];
      if (a!=4)
        cout << "   ";
   }
   cout << endl;

   system( "pause" );
   return 0;
} // end main
