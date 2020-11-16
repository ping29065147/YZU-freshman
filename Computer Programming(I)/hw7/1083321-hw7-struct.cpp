// Huge integer addition, subtraction, multiplication and division
#include <stdlib.h>
#include <string.h>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

const int numTestCases = 22;
const int arraySize = 200;

// HugeInt struct definition
struct HugeInt
{
   int size = 1;       // the number of digits of the integer; it can never be zero
   int *elems = new int[ 1 ](); // used to store a nonnegative integer, one digit per element
};

// enable user to input a positive huge integer
void input( istream &inFile, HugeInt &hugeInt );

// perform addition, subtraction, multiplication and division
void perform( ostream &outFile, HugeInt &hugeInt1, HugeInt &hugeInt2,
              HugeInt &hugeInt3, HugeInt &hugeInt4 );

// outputs hugeInt.elems[ hugeInt.size - 1 .. 0 ]
void output( ostream &outFile, HugeInt &hugeInt );

// a recursive function that outputs hugeInt.elems[ last .. 0 ]
void recursiveOutput( ostream &outFile, HugeInt &hugeInt, int last );

// returns true if and only if the specified huge integer is zero
bool isZero( HugeInt &hugeInt );

// return true if and only if hugeInt1 == hugeInt2
bool equal( HugeInt &hugeInt1, HugeInt &hugeInt2 );

// a recursive function that returns true if and only if
// hugeInt1.elems[ 0 .. last ] == hugeInt2.elems[ 0 .. last ]
// provided that hugeInt1.size == hugeInt2.size
bool recursiveEqual( HugeInt &hugeInt1, HugeInt &hugeInt2, int last );

// return true if and only if hugeInt1 < hugeInt2
bool less( HugeInt &hugeInt1, HugeInt &hugeInt2 );

// a recursive function that returns true if and only if hugeInt1 < hugeInt2
// provided that hugeInt1.size == hugeInt2.size
bool recursiveLess( HugeInt &hugeInt1, HugeInt &hugeInt2, int last );

// sum = addend + adder
void addition( HugeInt &addend, HugeInt &adder, HugeInt &sum );

// difference = minuend - subtrahend
// provided that the minuend is greater than or equal to the subtrahend
void subtraction( HugeInt &minuend,
                  HugeInt &subtrahend, HugeInt &difference );

// product = multiplicand * multiplier
void multiplication( HugeInt &multiplicand,
                     HugeInt &multiplier, HugeInt &product );

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that the divisor is not equal to 0
void division( HugeInt &dividend, HugeInt &divisor,
               HugeInt &quotient, HugeInt &remainder );

// hugeInt2 = hugeInt1; assignment
void assign( HugeInt &hugeInt1, HugeInt &hugeInt2 );

// hugeInt /= 10
void divideByTen( HugeInt &hugeInt );

void reset( HugeInt &hugeInt );

int main()
{
   system( "mode con cols=122" );

   ifstream inFile( "Test cases.txt", ios::in );

   // exit program if ifstream could not open file
   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   ofstream outFile( "Result.txt", ios::out );

   // exit program if ofstream could not open file
   if( !outFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   HugeInt hugeInt1;
   HugeInt hugeInt2;
   HugeInt hugeInt3;
   HugeInt hugeInt4;

   for( int i = 0; i < numTestCases; i++ )
   {
      input( inFile, hugeInt1 );
      input( inFile, hugeInt2 );
      perform( cout, hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
      perform( outFile, hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
      reset( hugeInt1 );
      reset( hugeInt2 );
   }

   delete[] hugeInt1.elems;
   delete[] hugeInt2.elems;
   delete[] hugeInt3.elems;
   delete[] hugeInt4.elems;

   inFile.close();
   outFile.close();

   system( "pause" );
}

// enable user to input a positive huge integer
void input( istream &inFile, HugeInt &hugeInt )
{
   char numericString[ arraySize ];

   inFile >> numericString;

   hugeInt.size = strlen( numericString );
   delete[] hugeInt.elems;
   hugeInt.elems = new int[ hugeInt.size ];
   for( int i = 0; i < hugeInt.size; i++ )
      hugeInt.elems[ i ] = numericString[ hugeInt.size - i - 1 ] - '0';
}

// perform addition, subtraction, multiplication and division
void perform( ostream &outFile, HugeInt &hugeInt1, HugeInt &hugeInt2,
                                HugeInt &hugeInt3, HugeInt &hugeInt4 )
{
   output( outFile, hugeInt1 );
   output( outFile, hugeInt2 );

   addition( hugeInt1, hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 + hugeInt2
   output( outFile, hugeInt3 );
   reset( hugeInt3 );

   if( less( hugeInt1, hugeInt2 ) )
   {
      outFile << '-';
      subtraction( hugeInt2, hugeInt1, hugeInt3 ); // hugeInt3 = hugeInt2 - hugeInt1
      output( outFile, hugeInt3 );
   }
   else
   {
      subtraction( hugeInt1, hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 - hugeInt2
      output( outFile, hugeInt3 );
   }
   reset( hugeInt3 );

   multiplication( hugeInt1, hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 * hugeInt2
   output( outFile, hugeInt3 );
   reset( hugeInt3 );

   if( isZero( hugeInt2 ) )
   {
      outFile << "DivideByZero!\n";
      outFile << "DivideByZero!\n";
   }
   else
   {
      // hugeInt3 = hugeInt1 / hugeInt2;   hugeInt4 = hugeInt1 % hugeInt2
      division( hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
      output( outFile, hugeInt3 );
      output( outFile, hugeInt4 );
      reset( hugeInt3 );
      reset( hugeInt4 );
   }

   outFile << endl;
}

// outputs hugeInt.elems[ hugeInt.size - 1 .. 0 ]
void output( ostream &outFile, HugeInt &hugeInt )
{
    if( isZero( hugeInt ) )
        outFile << 0;
    else
        recursiveOutput( outFile, hugeInt, hugeInt.size - 1 );

    outFile << endl;
}

// a recursive function that outputs hugeInt.elems[ last .. 0 ]
void recursiveOutput( ostream &outFile, HugeInt &hugeInt, int last )
{
    if(last>=0){
        outFile << hugeInt.elems[last];
        return recursiveOutput(outFile, hugeInt, last-1);
    }
}

// returns true if and only if the specified huge integer is zero
bool isZero( HugeInt &hugeInt )
{
   if( hugeInt.size == 1 && hugeInt.elems[ 0 ] == 0 )
      return true;
   return false;
}

// return true if and only if hugeInt1 == hugeInt2
bool equal( HugeInt &hugeInt1, HugeInt &hugeInt2 )
{
   if( hugeInt1.size != hugeInt2.size )
      return false;

   return recursiveEqual( hugeInt1, hugeInt2, hugeInt1.size - 1 );
}

// a recursive function that returns true if and only if
// hugeInt1.elems[ 0 .. last ] == hugeInt2.elems[ 0 .. last ]
// provided that hugeInt1.size == hugeInt2.size
bool recursiveEqual( HugeInt &hugeInt1, HugeInt &hugeInt2, int last )
{
    if (last>=0){
        if (hugeInt1.elems[last] != hugeInt2.elems[last])
            return false;
    }
    else
        return true;

    return recursiveEqual(hugeInt1, hugeInt2, last-1);
}

// returns true if and only if hugeInt1 < hugeInt2
bool less( HugeInt &hugeInt1, HugeInt &hugeInt2 )
{
   if( hugeInt1.size < hugeInt2.size )
      return true;
   if( hugeInt1.size > hugeInt2.size )
      return false;

   return recursiveLess( hugeInt1, hugeInt2, hugeInt1.size - 1 );
}

// a recursive function that returns true if and only if
// hugeInt1.elems[ 0 .. last ] < hugeInt2.elems[ 0 .. last ]
// provided that hugeInt1.size == hugeInt2.size
bool recursiveLess( HugeInt &hugeInt1, HugeInt &hugeInt2, int last )
{
    if (hugeInt1.elems[last] < hugeInt2.elems[last])
        return true;
    else if (hugeInt1.elems[last] > hugeInt2.elems[last])
        return false;

    if (last>0)
        recursiveLess(hugeInt1, hugeInt2, last-1);
    else
        return false;
}

// sum = addend + adder
void addition( HugeInt &addend, HugeInt &adder, HugeInt &sum )
{
   sum.size = ( addend.size >= adder.size ) ? addend.size + 1 : adder.size + 1;

   delete [] sum.elems;
   sum.elems = new int[ sum.size ]();

   for( int i = 0; i < addend.size; i++ )
      sum.elems[ i ] = addend.elems[ i ];

   for( int i = 0; i < adder.size; i++ )
      sum.elems[ i ] += adder.elems[ i ];

   for( int i = 0; i < sum.size - 1; i++ )
      if( sum.elems[ i ] > 9 ) // determine whether to carry a 1
      {
         sum.elems[ i ] -= 10; // reduce to 0-9
         sum.elems[ i + 1 ]++;
      }

   if( sum.elems[ sum.size - 1 ] == 0 )
      sum.size--;
}

// difference = minuend - subtrahend
// provided that the minuend is greater than or equal to the subtrahend
void subtraction( HugeInt &minuend,
                  HugeInt &subtrahend, HugeInt &difference )
{

    int i;
    if (equal(minuend, subtrahend)){
        difference.size=1;
        delete[] difference.elems;
        difference.elems = new int[difference.size];
        difference.elems[0] = 0;
    }
    else{
        difference.size = minuend.size;
        delete[] difference.elems;
        difference.elems = new int[difference.size]();

        for(i=0; i<minuend.size; i++)
            difference.elems[i] = minuend.elems[i];

        for(i=0; i<subtrahend.size; i++)
            difference.elems[i] -= subtrahend.elems[i];

        for(i=0; i<difference.size-1; i++){
            if (difference.elems[i] < 0){
                difference.elems[i] += 10;
                difference.elems[i+1]--;
            }
        }

        for(i=difference.size; difference.elems[i-1]==0; i--)
            difference.size--;
        }

}

// product = multiplicand * multiplier
void multiplication( HugeInt &multiplicand,
                     HugeInt &multiplier, HugeInt &product )
{
    int i, j, cpy;

    if (isZero(multiplicand)==1 || isZero(multiplier)==1){
        product.size=1;
        delete[] product.elems;
        product.elems = new int[product.size]();
        product.elems[0] = 0;
    }
    else{
        product.size = multiplicand.size + multiplier.size;
        delete[] product.elems;
        product.elems = new int[product.size]();


        for(int i=0; i < product.size; i++)
            product.elems[i] = 0;

        for(i=0; i < multiplier.size; i++){
            for(j=0; j < multiplicand.size; j++)
                product.elems[j+i] += multiplicand.elems[j]*multiplier.elems[i];
        }

        for(i=0; i < product.size; i++){
            if (product.elems[i] > 9){
                cpy = product.elems[i]%10;
                product.elems[i+1] += product.elems[i]/10;
                product.elems[i] = cpy;
            }
        }

        for(i=product.size; product.elems[product.size-1] == 0; i--)
                product.size--;
        }
}

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that the divisor is not equal to 0
void division( HugeInt &dividend, HugeInt &divisor,
               HugeInt &quotient, HugeInt &remainder )
{
   if( isZero( dividend ) )
    {
        reset( quotient);
        reset( remainder );
        quotient.elems[0] = 0;
        remainder.elems[0] = 0;
        quotient.size = 1;
        remainder.size = 1;
        return;
    }
    else if (equal(dividend, divisor)){
        reset( quotient);
        reset( remainder );
        quotient.elems[0] = 1;
        remainder.elems[0] = 0;
        quotient.size = 1;
        remainder.size = 1;
        return;
    }
    else if (less(dividend, divisor)){
        quotient.size=1;
        remainder.size=dividend.size;
        delete[] quotient.elems;
        delete[] remainder.elems;
        quotient.elems = new int[quotient.size]();
        remainder.elems = new int[remainder.size]();
        quotient.elems[0] = 0;
        for(int i=0; i<remainder.size; i++)
            remainder.elems[i]=dividend.elems[i];
        return;
    }

    int n = dividend.size - divisor.size;
    HugeInt buffer;
    buffer.size= dividend.size;
    buffer.elems = new int[buffer.size]();

    remainder.size = dividend.size;
    delete[] remainder.elems;
    remainder.elems = new int[remainder.size]();

    for(int i=0; i<dividend.size; i++)
        remainder.elems[i] = dividend.elems[i];

    if (less(dividend, divisor)){
        reset( quotient );
        quotient.elems[0] = 0;
        quotient.size = 1;
    }
    else{

        for(int i=0; i<n; i++)
            buffer.elems[i] = 0;
        for(int i=n; i<dividend.size; i++)
            buffer.elems[i] = divisor.elems[i-n];

        quotient.size = dividend.size - divisor.size;

        if (less(dividend, buffer))
            divideByTen(buffer);
        else
            quotient.size++;


        HugeInt temp;
        temp.elems = new int[1]();
        temp.size=remainder.size;
        quotient.elems = new int[quotient.size]();

        for(int k = quotient.size-1; k>=0; k--){

            while(less(buffer, remainder) || equal(buffer, remainder)){

                delete[] temp.elems;
                temp.elems = new int[temp.size]();


                subtraction(remainder, buffer, temp);


                delete[] remainder.elems;
                remainder.elems = new int[temp.size]();
                remainder.size=temp.size;
                for(int l=temp.size-1; l>=0; l--)
                    remainder.elems[l] = temp.elems[l];

                if (remainder.size==0)
                    reset(remainder);

                quotient.elems[k]++;
                if (isZero(remainder))
                    return;


            }
            divideByTen(buffer);
        }

    }

    delete[] buffer.elems;

    return;

}

// hugeInt2 = hugeInt1; assignment
void assign( HugeInt &hugeInt1, HugeInt &hugeInt2 )
{
   hugeInt2.size = hugeInt1.size;
   delete[] hugeInt2.elems;
   hugeInt2.elems = new int[ hugeInt2.size ];
   for( int i = 0; i < hugeInt2.size; i++ )
      hugeInt2.elems[ i ] = hugeInt1.elems[ i ];
}

// hugeInt /= 10
void divideByTen( HugeInt &hugeInt )
{
   if( hugeInt.size == 1 )
      hugeInt.elems[ 0 ] = 0;
   else
   {
      for( int i = 1; i < hugeInt.size; i++ )
         hugeInt.elems[ i - 1 ] = hugeInt.elems[ i ];

      hugeInt.size--;
      hugeInt.elems[ hugeInt.size ] = 0;
   }
}

void reset( HugeInt &hugeInt )
{
   hugeInt.size = 1;
   delete[] hugeInt.elems;
   hugeInt.elems = new int[ 1 ]();
}
