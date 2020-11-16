#include "Vector.h" // include definition of class vector 

// empty container constructor (default constructor)
// Constructs an empty container, with no elements.
vector::vector()
{
   myFirst = myLast = myEnd = nullptr;
}

// fill constructor
// Constructs a container with "count" elements.
// Each element is initialized as 0.
vector::vector( const size_type count )
{
    int *str = new int[count]; //create a new dynamic array

    myFirst = str;
    myLast = str+count;
    myEnd = str+count;

    for (int a = 0; a < count; a++)
        str[a] = 0;
}

// copy constructor
// Constructs a container with a copy of each of the elements in "right",
// in the same order.
vector::vector( const vector &right )
{
    int s = right.myLast - right.myFirst; //get the size of dynamic array in vector right

    int* str = new int[s];

    myFirst = str;
    myLast = str+s;
    myEnd = str+s;

    if (right.myFirst != nullptr) {
        for (int a = 0; a < s; a++) 
            str[a] = *(right.myFirst + a); //copy the element to str
    }
    else {
        myFirst = nullptr;
        myLast = nullptr;
        myEnd = nullptr;
    }
}

// Vector destructor
// Destroys the container object.
// Deallocates all the storage capacity allocated by the vector.
vector::~vector()
{
   if( myFirst != nullptr )
      delete[] myFirst;
}

// Adds a new element at the end of the vector, after its current last element.
// The content of val is copied to the new element.
// This effectively increases the vector size by one,
// which causes an automatic reallocation of the allocated storage space
// if and only if the new vector size surpasses the current vector capacity.
void vector::push_back( const value_type &val )
{
   size_type originalSize = size();
   resize( originalSize + 1 );
   myFirst[ originalSize ] = val;
}

// Assigns new contents to the container, replacing its current contents,
// and modifying its size accordingly.
// Copies all the elements from "right" into the container
// (with "right" preserving its contents).
vector& vector::assign( const vector &right )
{
   if( this != &right ) // avoid self-assignment
   {
       int right_s = right.myLast - right.myFirst; //right size
       int right_c = right.myEnd - right.myFirst; //right capacity

       if (myFirst == nullptr) { //the first time

           int* str = new int[right_s];

           myFirst = str;
           myLast = str + right_s;
           myEnd = str + right_s;

           for (int a = 0; a < right_s; a++)
               str[a] = *(right.myFirst + a);
       }
       else {

           int s = myLast - myFirst; //size
           int c = myEnd - myFirst; // capacity

           if (right_s <= c) { //the capacity is enough

               myLast = myFirst + right_s;

               for (int a = 0; a < right_s; a++)
                   *(myFirst + a) = *(right.myFirst + a); 
           }
           else { //the capacity isn't enough
               int one_point_five = c * 1.5;

               if (one_point_five < right_s) { //the right size is bigger tan capacity*1.5
                   int* str = new int[right_s];

                   myFirst = str;
                   myLast = str + right_s;
                   myEnd = str + right_s;

                   for(int a=0; a<right_s; a++)
                       str[a] = *(right.myFirst + a);
               }
               else { // capacity*1.5 is enough
                   int* str = new int[one_point_five];

                   myFirst = str;
                   myLast = str + right_s;
                   myEnd = str + one_point_five;

                   for (int a = 0; a < right_s; a++)
                       str[a] = *(right.myFirst + a);
               }
           }
       }
   }

   return *this; // enables x = y = z, for example
}

// Resizes the vector so that it contains newSize elements.
// If newSize is smaller than the current vector size,
// the content is reduced to its first newSize elements, removing those beyond.
// If newSize is greater than the current vector size,
// the content is expanded by inserting at the end
// as many elements as needed to reach a size of newSize.
// The new elements are initialized as 0.
// If newSize is also greater than the current vector capacity,
// an automatic reallocation of the allocated storage space takes place.
void vector::resize( const size_type newSize )
{

    int check;
    
    if (newSize <= capacity()) {   //the capacity is enough

        myLast = myFirst + newSize;
        for (int a = newSize; a < capacity(); a++)
            *(myFirst + a) = 0;
    }
    else {
        check = size(); //check = size
        int one_point_five = capacity() * 1.5;
        if (one_point_five <= newSize) { //capacity*1.5 isn't enough
            int *str = new int[newSize];
            for (int a = 0; a < newSize; a++)
                str[a] = 0;

            myEnd = str + newSize;
            for (int a = 0; a < check; a++)
                str[a] = *(myFirst + a);

            clear();
            myFirst = str;
            myLast = str + newSize;
        }
        else {
            int *str = new int[one_point_five];
            for (int a = 0; a < one_point_five; a++)
                str[a] = 0;

            myEnd = str + one_point_five;
            for (int a = 0; a < check; a++)
                str[a] = *(myFirst + a);

            clear();
            myFirst = str;
            myLast = str + newSize;
        }
    }
}

// Removes the last element in the vector,
// effectively reducing the container size by one.
void vector::pop_back()
{
   if( size() > 0 )
      --myLast;
}

// Removes all elements from the vector (which are destroyed),
// leaving the container with a size of 0.
// A reallocation is not guaranteed to happen,
// and the vector capacity is not guaranteed to change due to calling this function.
void vector::clear()
{
   myLast = myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::pointer vector::begin()
{
   return myFirst;
}

// Returns the number of elements in the vector.
// This is the number of actual objects held in the vector,
// which is not necessarily equal to its storage capacity.
vector::size_type vector::size()
{
   return ( myLast - myFirst );
}

// Returns the size of the storage space currently allocated for the vector,
// expressed in terms of elements.
// This capacity is not necessarily equal to the vector size.
// It can be equal or greater, with the extra space allowing to accommodate
// for growth without the need to reallocate on each insertion.
vector::size_type vector::capacity()
{
   return ( myEnd - myFirst );
}

// Returns a reference to the element at position "pos" in the vector container.
vector::value_type& vector::element( const size_type pos )
{
   return myFirst[ pos ];
}