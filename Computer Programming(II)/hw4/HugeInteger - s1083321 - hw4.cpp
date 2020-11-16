#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor; construct a zero HugeInteger with size 1
HugeInteger::HugeInteger()
   : integer( 1, '0' )
{
}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger( unsigned int n )
   : integer( ( n > 0 ) ? n : 1, '0' )
{
} // end HugeInteger constructor

// copy constructor
// constructs a HugeInteger with a copy of each of the elements in integerToCopy
HugeInteger::HugeInteger( const HugeInteger &integerToCopy )
   : integer( integerToCopy.integer )
{
} // end HugeInteger copy constructor

// destructor; destroys the HugeInteger
HugeInteger::~HugeInteger()
{
} // end HugeInteger destructor

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
const HugeInteger& HugeInteger::operator=( const HugeInteger &right )
{
   if( &right != this ) // avoid self-assignment
      integer = right.integer;

   return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
bool HugeInteger::operator==( const HugeInteger &right ) const
{
//   return operator==( integer, right.integer );
   return ( integer == right.integer );
} // end function equal

// function that tests if one HugeInteger is less than another
bool HugeInteger::operator<( const HugeInteger &right ) const
{
    if (integer.size() < right.integer.size())
        return true;
    else if (integer.size() > right.integer.size())
        return false;

    for (int a = integer.size() - 1; a >= 0; a--) {
        if (*(integer.begin() + a) < *(right.integer.begin() + a))
            return true;
        else if (*(integer.begin() + a) > * (right.integer.begin() + a))
            return false;
    }

    return false;
} // end function less

// function that tests if one HugeInteger is less than or equal to another
bool HugeInteger::operator<=( const HugeInteger &right ) const
{
   return ( *this == right || *this < right );
} // end function lessEqual

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::operator+( HugeInteger &op2 )
{
   unsigned int op1Size = integer.size();
   unsigned int op2Size = op2.integer.size();
   unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger sum( sumSize );

   string::iterator it1 = integer.begin();
   string::iterator it3 = sum.integer.begin();
   for( ; it1 != integer.end(); ++it1, ++it3 )
      *it3 = *it1;

   string::iterator it2 = op2.integer.begin();
   for( it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3 )
      *it3 = ( *it3 - '0' ) + ( *it2 - '0' ) + '0';

   for( it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3 )
      if( *it3 > '9' )
      {
         ( *it3 ) = ( *it3 - '0' ) - 10 + '0';
         ( *( it3 + 1 ) ) = ( *( it3 + 1 ) - '0' ) + 1 + '0';
      }

   if( *it3 == '0' )
      sum.integer.pop_back();

   return sum;
} // end function add

// subtraction operator; HugeInteger - HugeInteger
HugeInteger HugeInteger::operator-( HugeInteger &op2 )
{
   HugeInteger zero;

   if( *this == op2 )
      return zero;

   HugeInteger difference( *this );

   string::iterator it1 = difference.integer.begin();
   string::iterator it2 = op2.integer.begin();

   for (unsigned int a = 0; a < op2.integer.size(); a++)
       *(it1 + a) = (*(it1 + a) - '0') - (*(it2 + a) - '0') + '0';

   for (unsigned int a = 0; a < difference.integer.size() - 1; a++) {
       if (*(it1 + a) < '0') {
           *(it1 + a) = (*(it1 + a) - '0') + 10 + '0';
           *(it1 + a + 1) = (*(it1 + a + 1) - '0') - 1 + '0';
       }
   }

   for (int a = difference.integer.size() - 1; *(it1 + a) == '0'; a--)
       difference.integer.pop_back();

   return difference;
} // end function subtract

// multiplication operator; HugeInteger * HugeInteger
HugeInteger HugeInteger::operator*( HugeInteger &op2 )
{
   HugeInteger zero;
   if( isZero() || op2.isZero() )
      return zero;

   unsigned int productSize = integer.size() + op2.integer.size();
   HugeInteger product( productSize );

   string::iterator it1 = product.integer.begin();
   string::iterator it2 = integer.begin();
   string::iterator it3 = op2.integer.begin();

   for (unsigned int a = 0; a < integer.size(); a++) {
       for (unsigned int b = 0; b < op2.integer.size(); b++) {

           int temp = (*(it1 + a + b) - '0') + (*(it2 + a) - '0') * (*(it3 + b) - '0');

           if (temp > 9) {
               *(it1 + a + b + 1) = (*(it1 + a + b + 1) - '0') + temp / 10 + '0';
               temp %= 10;
           }

           *(it1 + a + b) = temp + '0';

       }
   }


   for (unsigned int a = product.integer.size() - 1; *(it1 + a) == '0'; a--)
       product.integer.pop_back();
   

   return product;
} // end function multiply

// division operator; HugeInteger / HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::operator/( HugeInteger &op2 )
{
   HugeInteger zero;
   HugeInteger quotient;
   string::iterator it1 = quotient.integer.begin();

   if( *this < op2 )
      return zero;

   HugeInteger buffer(integer.size());
   HugeInteger remainder(*this);
   string::iterator it_buffer = buffer.integer.begin();
   string::iterator it_remainder = remainder.integer.begin();
   string::iterator it2 = op2.integer.begin();
   unsigned int n = integer.size() - op2.integer.size();
   unsigned int quotient_size = integer.size() - op2.integer.size();

   for (int a = n; a < op2.integer.size() + n; a++)
       *(it_buffer + a) = *(it2 + a - n);

   if (*this < buffer)
       buffer.divideByTen();
   else
       quotient_size++;

   quotient.integer.resize(quotient_size);
   for (int a = 0; a < quotient_size; a++)
       quotient.integer[a] = '0';

   for (it1 = quotient.integer.end() - 1; it1 >= quotient.integer.begin(); it1--) {
       while (buffer <= remainder) {
           
           /*HugeInteger copy_re(remainder - buffer);
           remainder = copy_re;
           cout << remainder << endl;*/
           remainder = remainder - buffer;
           //cout << remainder << endl;
           *(it1) = (*(it1)-'0') + 1 + '0';

           if (remainder.isZero())
               return quotient;
       }
       buffer.divideByTen();
   }

   return quotient;
} // end function divide

// modulus operator; HugeInteger % HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::operator%( HugeInteger &op2 )
{
   HugeInteger quotient = ( *this ) / op2;
   HugeInteger product = quotient * op2;
   HugeInteger remainder = ( *this ) - product;
   return remainder;
}

// convert a string of decimal digits into a HugeInteger
void HugeInteger::convert( string &str )
{
   integer.resize( str.size() );
   string::iterator it1 = integer.end() - 1;
   string::iterator it2 = str.begin();
   for( ; it2 != str.end(); --it1, ++it2 )
      *it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero()
{
   for( string::iterator it = integer.begin(); it != integer.end(); ++it )
      if( *it != '0' )
         return false;

   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
   string::iterator it = integer.begin();
   string::iterator it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      *it = *it2;
   integer.pop_back();
}

// overloaded output operator
ostream& operator<<( ostream &output, const HugeInteger &hugeInteger )
{
   string::const_iterator it = hugeInteger.integer.end() - 1;

   for( ; it != hugeInteger.integer.begin() - 1; --it )
      if( *it <= '9' )
         output << *it;

   return output; // enables cout << x << y;
} // end function output
