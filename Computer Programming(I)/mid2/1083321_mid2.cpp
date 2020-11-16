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

#include <string.h>
#include <stdlib.h>

const int numTestCases = 20;
const int arraySize = 200;

// HugeInt class definition
class HugeInt
{
public:
   // enable user to input a positive huge integer
   void input( istream &inFile );

   // output the specified huge integer
   void output( ostream &outFile );

   // returns true if and only if the specified huge integer is zero
   bool isZero();

   // return true if and only if current object == hugeInt2
   bool equal( HugeInt &hugeInt2 );

   // a recursive function that returns true if and only if
   // elems[ 0 .. last ] == hugeInt2.elems[ 0 .. last ]
   // provided that size == hugeInt2.size
   bool recursiveEqual( HugeInt &hugeInt2, int last );

   // return true if and only if current object < hugeInt2
   bool less( HugeInt &hugeInt2 );

   // a recursive function that returns true if and only if
   // elems[ 0 .. last ] < hugeInt2.elems[ 0 .. last ]
   // provided that size == hugeInt2.size
   bool recursiveLess( HugeInt &hugeInt2, int last );

   // request the current object to reduce its array to fit its size
   void shrink_to_fit();

   // sum = current object + adder
   void addition( HugeInt &adder, HugeInt &sum );

   // a recursive function that perform the carry operation
   // used in addition and multiplication
   int carrying( int last );

   // difference = current object - subtrahend
   // provided that the current object is greater than or equal to the subtrahend
   void subtraction( HugeInt &subtrahend, HugeInt &difference );

   // a recursive function that perform the borrow operation used in subtraction
   int borrowing( int last );

   // product = current object * multiplier
   void multiplication( HugeInt &multiplier, HugeInt &product );

   // quotient = current object / divisor; remainder = current object % divisor
   // provided that the divisor is not equal to 0
   void division( HugeInt &divisor, HugeInt &quotient, HugeInt &remainder );

   // left = current object; assignment
   void assign( HugeInt &left );

   // current object /= 10
   void divideByTen();

   void reset();

   int size = 1; // the number of digits of the integer; it can never be zero
   int *elems = new int[ 1 ]();  // used to store a nonnegative integer, one digit per element
}; // end class HugeInt


// enable user to input a positive huge integer
void HugeInt::input( istream &inFile )
{
   char numericString[ arraySize ];

   inFile >> numericString;

   size = strlen( numericString );
   delete[] elems;
   elems = new int[ size ];
   for( int i = 0; i < size; i++ )
      elems[ i ] = numericString[ size - i - 1 ] - '0';
} // end function input

// output the specified huge integer
void HugeInt::output( ostream &outFile )
{
   for( int i = size - 1; i >= 0; i-- )
      if( elems[ i ] < 10 )
         outFile << elems[ i ];
   outFile << endl;
} // end function output

// returns true if and only if the specified huge integer is zero
bool HugeInt::isZero()
{
   if( size == 1 && elems[ 0 ] == 0 )
      return true;
   return false;
}

// return true if and only if current object == hugeInt2
bool HugeInt::equal( HugeInt &hugeInt2 )
{
   if( size != hugeInt2.size )
      return false;

   return recursiveEqual( hugeInt2, size - 1 );
}

// a recursive function that returns true if and only if
// elems[ 0 .. last ] == hugeInt2.elems[ 0 .. last ]
// provided that size == hugeInt2.size
bool HugeInt::recursiveEqual( HugeInt &hugeInt2, int last )
{
    if (last==-1)
        return true;

    if (elems[last] == hugeInt2.elems[last])
        return recursiveEqual( hugeInt2, last - 1 );
    else
        return false;
}

// returns true if and only if current object < hugeInt2
bool HugeInt::less( HugeInt &hugeInt2 )
{
   if( size < hugeInt2.size )
      return true;
   if( size > hugeInt2.size )
      return false;

   return recursiveLess( hugeInt2, size - 1 );
}

// a recursive function that returns true if and only if
// elems[ 0 .. last ] < hugeInt2.elems[ 0 .. last ]
// provided that size == hugeInt2.size
bool HugeInt::recursiveLess( HugeInt &hugeInt2, int last )
{
    if (last==-1)
        return false;

    if (elems[last] < hugeInt2.elems[last])
        return true;
    else if (elems[last] > hugeInt2.elems[last])
        return false;
    else
        return recursiveLess( hugeInt2, last - 1 );


}

// request the current object to reduce its array to fit its size
void HugeInt::shrink_to_fit()
{
   int *buffer = new int[ size ];
   for( int i = 0; i < size; i++ )
      buffer[ i ] = elems[ i ];
   delete [] elems;
   elems = buffer;
}

// sum = current object + adder
void HugeInt::addition( HugeInt &adder, HugeInt &sum )
{
   sum.size = ( size >= adder.size ) ? size + 1 : adder.size + 1;

   delete[] sum.elems;
   sum.elems = new int[ sum.size ]();

   for( int i = 0; i < size; i++ )
      sum.elems[ i ] = elems[ i ];

   for( int i = 0; i < adder.size; i++ )
      sum.elems[ i ] += adder.elems[ i ];

   // a recursive function that perform the carry operation
   sum.carrying( sum.size - 1 );

   if( sum.elems[ sum.size - 1 ] == 0 )
   {
      sum.size--;
      sum.shrink_to_fit();
   }
}

int HugeInt::carrying( int last )
{

    if (last==-1)
        return 0;

    carrying(last-1);

    if(elems[last] >= 10){
        elems[last+1] += elems[last]/10;
        elems[last] %= 10;
    }


}

// difference = current object - subtrahend
// provided that the current object is greater than or equal to the subtrahend
void HugeInt::subtraction( HugeInt &subtrahend, HugeInt &difference )
{
   if( equal( subtrahend ) )
      difference.reset();
   else
   {
        int i;
        if (size > subtrahend.size)
            difference.size = size;
        else
            difference.size = subtrahend.size;
        delete[] difference.elems;
        difference.elems = new int[difference.size]();

        for(i=0; i<size; i++)
            difference.elems[i] = elems[i];
        for(i=0; i<subtrahend.size; i++)
            difference.elems[i] -= subtrahend.elems[i];

        // a recursive function that perform the borrow operation
        difference.borrowing( difference.size - 1 );

        for(i=difference.size-1; difference.elems[i]==0; i--){
            difference.size--;
            difference.shrink_to_fit();
        }
   }
}

int HugeInt::borrowing( int last )
{
    if (last==-1)
        return 0;

    borrowing(last-1);

    if (elems[last] < 0){
        elems[last] += 10;
        elems[last+1]--;
    }


}

// product = current object * multiplier
void HugeInt::multiplication( HugeInt &multiplier, HugeInt &product )
{
   if( isZero() || multiplier.isZero() )
      product.reset();
   else
   {
        int i, j;
        product.size = size + multiplier.size;
        delete[] product.elems;
        product.elems = new int[product.size]();

        for(i=0; i<size; i++){
            for(j=0; j<multiplier.size; j++){
                product.elems[i+j] += elems[i] * multiplier.elems[j];
            }
        }

        // a recursive function that perform the carry operation
        product.carrying( product.size - 1 );

        for(i=product.size-1; product.elems[i]==0; i--){
            product.size--;
            product.shrink_to_fit();
        }
   }
}

// quotient = current object / divisor; remainder = current object % divisor
// provided that the divisor is not equal to 0
void HugeInt::division( HugeInt &divisor, HugeInt &quotient, HugeInt &remainder )
{
   if( isZero() )        // current object == 0
   {
      quotient.reset();  // quotient == 0
      remainder.reset(); // remainder == 0
   }
   else if( less( divisor ) ) // current object < divisor
   {
      quotient.reset();       // quotient == 0
      assign( remainder );    // remainder = dividend
   }
   else if( equal( divisor ) ) // current object == divisor
   {
      quotient.reset();        // quotient == 0
      quotient.elems[ 0 ] = 1; // quotient == 1
      remainder.reset();       // remainder == 0
   }
   else
   {
        int i, j, k;
        int n = size - divisor.size;
        HugeInt buffer;
        buffer.elems = new int[size]();

        for(i=0; i<n; i++)
            buffer.elems[i] = 0;
        for(j=0; j<divisor.size; j++)
            buffer.elems[i+j] = divisor.elems[j];

        if (less(buffer))
            quotient.size = size - divisor.size;
        else
            quotient.size = size - divisor.size + 1;

        delete[] quotient.elems;
        quotient.elems = new int[quotient.size]();

        for (k=quotient.size-1; k>=0; k--){
            quotient.elems[k] = 10;
            do{
                quotient.elems[k]--;
                divisor.multiplication(quotient, buffer);
            }
            while(less(buffer));

            if (equal(buffer))
                break;
        }

        for(i=quotient.size-1; quotient.elems[i]==0; i--){
            quotient.size--;
            quotient.shrink_to_fit();
        }

        subtraction(buffer, remainder);

        delete[] buffer.elems;
   }
}

// left = current object; assignment
void HugeInt::assign( HugeInt &left )
{
   left.size = size;
   delete[] left.elems;
   left.elems = new int[ left.size ];
   for( int i = 0; i < left.size; i++ )
      left.elems[ i ] = elems[ i ];
}

// current object /= 10
void HugeInt::divideByTen()
{
   if( size == 1 )
      elems[ 0 ] = 0;
   else
   {
      for( int i = 1; i < size; i++ )
         elems[ i - 1 ] = elems[ i ];

      size--;
      elems[ size ] = 0;
      shrink_to_fit();
   }
}

void HugeInt::reset()
{
   size = 1;
   delete[] elems;
   elems = new int[ 1 ]();
}

void inputAll( HugeInt hugeInt1[], HugeInt hugeInt2[] )
{
    ifstream inFile("Test cases.txt", ios::in);

    for( int i = 0; i < numTestCases; i++ ){
      hugeInt1[ i ].input( inFile );
      hugeInt2[ i ].input( inFile );
    }
}

// output the specified huge integer
void outputScreen( HugeInt hugeInt1[], HugeInt hugeInt2[],
                   HugeInt hugeInt3[], HugeInt hugeInt4[] )
{
   for( int i = 0; i < numTestCases; i++ )
   {
      hugeInt1[ i ].output( cout );
      hugeInt2[ i ].output( cout );
      hugeInt3[ i ].output( cout );
      hugeInt4[ i ].output( cout );
      cout << endl;
   }
}

// output the specified huge integer
void outputFile( HugeInt hugeInt1[], HugeInt hugeInt2[],
                 HugeInt hugeInt3[], HugeInt hugeInt4[] )
{
    ofstream outFile("result.txt", ios::out);

    for( int i = 0; i < numTestCases; i++ ){
      hugeInt1[ i ].output( outFile );
      hugeInt2[ i ].output( outFile );
      hugeInt3[ i ].output( outFile );
      hugeInt4[ i ].output( outFile );
      outFile << endl;
    }

}

int main()
{
   system( "mode con cols=80" );

   HugeInt hugeInt1[ numTestCases ];
   HugeInt hugeInt2[ numTestCases ];
   HugeInt hugeInt3[ numTestCases ];
   HugeInt hugeInt4[ numTestCases ];

   inputAll( hugeInt1, hugeInt2 );

   for( int i = 0; i < numTestCases; i++ )
      hugeInt1[ i ].division( hugeInt2[ i ], hugeInt3[ i ], hugeInt4[ i ] );
      // hugeInt3 = hugeInt1 / hugeInt2; hugeInt4 = hugeInt1 % hugeInt2

   outputScreen( hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
   outputFile( hugeInt1, hugeInt2, hugeInt3, hugeInt4 );

   for( int i = 0; i < numTestCases; i++ )
   {
      delete[] hugeInt1[ i ].elems;
      delete[] hugeInt2[ i ].elems;
      delete[] hugeInt3[ i ].elems;
      delete[] hugeInt4[ i ].elems;
   }

   system( "pause" );
}


<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head><meta http-equiv="Content-Type" content="text/html; charset=utf-8" /><title>

</title></head>
<body>
    <form method="post" action="./File_DownLoad_Wk_zip.aspx?File_name=1083321_mid2.cpp&amp;type=3&amp;id=2813777" id="form1">
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
