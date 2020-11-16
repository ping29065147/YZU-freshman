// Member-function definitions for class HugeInteger
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor; construct a zero HugeInteger with size 1
HugeInteger::HugeInteger()
   : integer( 1 )
{
}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger( unsigned int n )
   : integer( ( n > 0 ) ? n : 1 )
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
const HugeInteger &HugeInteger::assign( const HugeInteger &right )
{
   if( &right != this ) // avoid self-assignment
      integer.assign( right.integer );

   return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
bool HugeInteger::equal( const HugeInteger &right ) const
{
    if (integer.size() != right.integer.size())
        return false;

    for (unsigned int a = 0; a < integer.size(); a++) {
        if (*(integer.begin() + a) != *(right.integer.begin() + a))
            return false;
    }

    return true;

} // end function equal

// function that tests if one HugeInteger is less than another
bool HugeInteger::less( const HugeInteger &right ) const
{
    if (integer.size() < right.integer.size())
        return true;
    else if (integer.size() > right.integer.size())
        return false;

    for (int a = integer.size()-1; a >= 0; a--) {
        if (*(integer.begin() + a) < *(right.integer.begin() + a))
            return true;
        else if (*(integer.begin() + a) > *(right.integer.begin() + a))
            return false;
    }

    return false;

} // end function less

// function that tests if one HugeInteger is less than or equal to another
bool HugeInteger::lessEqual( const HugeInteger &right ) const
{
   return ( less( right ) || equal( right ) );
} // end function lessEqual

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::add( HugeInteger &op2 )
{
   unsigned int op1Size = integer.size();
   unsigned int op2Size = op2.integer.size();
   unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger sum( sumSize );

   vector::iterator it1 = integer.begin();
   vector::iterator it3 = sum.integer.begin();
   for( ; it1 != integer.end(); ++it1, ++it3 )
      *it3 = *it1;

   vector::iterator it2 = op2.integer.begin();
   for( it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3 )
      *it3 += *it2;

   for( it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3 )
      if( *it3 > 9 )
      {
         ( *it3 ) -= 10;
         ( *( it3 + 1 ) )++;
      }

   if( *it3 == 0 )
      sum.integer.pop_back();

   return sum;
} // end function add

// subtraction operator; HugeInteger - HugeInteger
HugeInteger HugeInteger::subtract( HugeInteger &op2 )
{
   HugeInteger zero;

   if( equal( op2 ) )
      return zero;

   HugeInteger difference( *this );
   vector::iterator it1 = difference.integer.begin();
   vector::iterator it2 = op2.integer.begin();

   for (unsigned int a = 0; a < op2.integer.size(); a++)
       *(it1 + a) -= *(it2 + a);
   
   for (unsigned int a = 0; a < difference.integer.size()-1; a++) {
       if (*(it1 + a) < 0) {
           *(it1 + a) += 10;
           *(it1 + a + 1) -= 1;
       }
   }

   for (int a = difference.integer.size() - 1; *(it1 + a) == 0; a--)
       difference.integer.pop_back();

   return difference;
} // end function subtract

// multiplication operator; HugeInteger * HugeInteger
HugeInteger HugeInteger::multiply( HugeInteger &op2 )
{
   HugeInteger zero;
   if( isZero() || op2.isZero() )
      return zero;

   unsigned int productSize = integer.size() + op2.integer.size();
   HugeInteger product( productSize );
   
   vector::iterator it1 = product.integer.begin();
   vector::iterator it2 = integer.begin();
   vector::iterator it3 = op2.integer.begin();

   for (unsigned int a = 0; a < integer.size(); a++) {
       for (unsigned int b = 0; b < op2.integer.size(); b++) {
           *(it1 + a + b) += *(it2 + a) * *(it3 + b);
       }
   }

   for (unsigned int a = 0; a < product.integer.size(); a++) {
       if (*(it1 + a) > 9) {
           *(it1 + a + 1) += *(it1 + a) / 10;
           *(it1 + a) %= 10;
       }
   }

   for (unsigned int a = product.integer.size() - 1; *(it1 + a) == 0; a--)
       product.integer.pop_back();


   return product;
} // end function multiply

// division operator; HugeInteger / HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::divide( HugeInteger &op2 )
{
   HugeInteger zero;
   HugeInteger quotient;
   vector::iterator it1 = quotient.integer.begin();

   if( less( op2 ) )
      return zero;
   
   HugeInteger buffer(integer.size());
   HugeInteger remainder(*this);
   vector::iterator it_buffer = buffer.integer.begin();
   vector::iterator it_remainder = remainder.integer.begin();
   vector::iterator it2 = op2.integer.begin();
   unsigned int n = integer.size() - op2.integer.size();
   unsigned int quotient_size = integer.size() - op2.integer.size();

   for (int a = n; a < op2.integer.size()+n; a++)
       *(it_buffer + a) = *(it2 + a - n);

   if (less(buffer))
       buffer.divideByTen();
   else 
       quotient_size++;

   quotient.integer.resize(quotient_size);

   for (it1 = quotient.integer.end() - 1; it1 >= quotient.integer.begin(); it1--) {
       while (buffer.lessEqual(remainder)) {
           HugeInteger copy_re(remainder.subtract(buffer));
           remainder.assign(copy_re);
           *(it1) += 1;

           if (remainder.isZero())
               return quotient;
       }
       buffer.divideByTen();
   }
   
   return quotient;

} // end function divide

// modulus operator; HugeInteger % HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::modulus( HugeInteger &op2 )
{
   HugeInteger quotient = divide( op2 );
   HugeInteger product = quotient.multiply( op2 );
   HugeInteger remainder = subtract( product );
   return remainder;
}

// convert a vector of decimal digits into a HugeInteger
void HugeInteger::convert( vector &v )
{
   integer.resize( v.size() );
   vector::iterator it1 = integer.end() - 1;
   vector::iterator it2 = v.begin();
   for( ; it2 != v.end(); --it1, ++it2 )
      *it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero()
{
   for( vector::iterator it = integer.begin(); it != integer.end(); ++it )
      if ( *it != 0 )
         return false;
         
   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
   vector::iterator it = integer.begin();
   vector::iterator it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      *it = *it2;
   integer.pop_back();
}

// overloaded output operator
void HugeInteger::output( ostream &outFile )
{
   vector::iterator it = integer.end() - 1;
   for( ; it != integer.begin() - 1; --it )
      if( *it < 10 )
         outFile << *it;
   outFile << endl;
} // end function output