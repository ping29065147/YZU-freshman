#include "String.h" // include definition of class String
#include "iostream"

string::string()
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
}

string::string( const char *const ptr, const size_type count )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
    mySize = count;
    myRes = (mySize / 16) * 16 + 15;

    if (myRes > 15)
        bx.ptr = new char[myRes+1];

    for (int a = 0; a < mySize; a++)
        myPtr()[a] = *(ptr + a);

    myPtr()[mySize] = '\0';
}

string::string( const size_type count, const char ch )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
    mySize = count;
    myRes = (mySize / 16) * 16 + 15;

    if (myRes > 15)
        bx.ptr = new char[myRes + 1];

    for (int a = 0; a < mySize; a++)
        myPtr()[a] = ch;

    myPtr()[mySize] = '\0';
}

string::string( const string &right )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
    mySize = right.mySize;
    myRes = (mySize / 16) * 16 + 15;

    if (myRes > 15)
        bx.ptr = new char[myRes + 1];

    for (int a = 0; a < mySize; a++)
        myPtr()[a] = right.myPtr()[a];

    myPtr()[mySize] = '\0';
}

string::~string()
{
   if( myRes > 15 )
      delete[] bx.ptr;
}

string::value_type* string::myPtr()
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}

const string::value_type* string::myPtr() const
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}

string& string::assign( const string &right )
{
   if( this != &right )
   {
       size_type oldsize = mySize;
       mySize = right.mySize;

       if (myRes >= right.mySize) {
           if (myRes > 15) {
               for (int a = 0; a < right.mySize; a++)
                   bx.ptr[a] = right.myPtr()[a];
           }
       }
       else {

           myRes *= 1.5;
           if (myRes < (mySize / 16) * 16 + 15)
               myRes = (mySize / 16) * 16 + 15;

           pointer str = new char[myRes];

           for (int a = 0; a < right.mySize; a++)
               str[a] = right.myPtr()[a];

           bx.ptr = str;
       }
   }

   return *this;
}

void string::clear()
{
   mySize = 0;
   myPtr()[ 0 ] = value_type();
}

string::iterator string::begin()
{
   return iterator( myPtr() );
}

string::const_iterator string::begin() const
{
   return const_iterator( myPtr() );
}

string::iterator string::end()
{
   return iterator( myPtr() + static_cast< difference_type >( mySize ) );
}

string::const_iterator string::end() const
{
   return const_iterator( myPtr() + static_cast< difference_type >( mySize ) );
}

string::reference string::element( const size_type off )
{
   return myPtr()[ off ];
}

string::const_reference string::element( const size_type off ) const
{
   return myPtr()[ off ];
}

void string::push_back( char ch )
{
   resize( mySize + 1 );
   myPtr()[ mySize - 1 ] = ch;
}

void string::pop_back()
{
   if( mySize > 0 )
      --mySize;
}

string::reference string::front()
{
   return myPtr()[ 0 ];
}

string::const_reference string::front() const
{
   return myPtr()[ 0 ];
}

string::reference string::back()
{
   return myPtr()[ mySize - 1 ];
}

string::const_reference string::back() const
{
   return myPtr()[ mySize - 1 ];
}

const char* string::c_str() const
{
   return myPtr();
}

string::size_type string::size() const
{
   return mySize;
}

void string::resize( const size_type newSize, const char ch )
{

    size_type oldsize = mySize;
    mySize = newSize;
    size_type oldres = myRes;

    if (oldres >= mySize && oldsize < mySize && myRes > 15) {

        for (int a = 0; a < oldsize; a++)
            bx.ptr[a] = myPtr()[a];
        for (int a = oldsize; a < mySize; a++)
            bx.ptr[a] = ch;
    }
    else if (oldsize < mySize){

        myRes *= 1.5;
        if (myRes < (mySize / 16) * 16 + 15)
            myRes = (mySize / 16) * 16 + 15;

        pointer str = new char[myRes];

        for (int a = 0; a < oldsize; a++)
            str[a] = myPtr()[a];
        for (int a = oldsize; a < mySize; a++)
            str[a] = ch;

        bx.ptr = str;
    }

}

string::size_type string::capacity() const
{
   return myRes;
}

bool string::empty() const
{
   return mySize == 0;
}
