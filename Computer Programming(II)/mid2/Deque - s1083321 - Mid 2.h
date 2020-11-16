#ifndef DEQUE_H
#define DEQUE_H

//#include "XUtility.h" // include definition of class template ReverseIterator

// CLASS TEMPLATE DequeConstIterator
template< typename MyDeque >
class DequeConstIterator // iterator for nonmutable deque
{
private:
   using size_type = typename MyDeque::size_type;

public:
   using value_type      = typename MyDeque::value_type;
   using difference_type = typename MyDeque::difference_type;
   using pointer         = typename MyDeque::const_pointer;
   using reference       = const value_type &;

   // construct with null pointer
   DequeConstIterator()
      : myOff( 0 ),
        myCont( nullptr )
   {
   }

   // construct with offset off in *pDeque
   DequeConstIterator( size_type off, const MyDeque *pDeque )
      : myOff( off ),
        myCont( pDeque )
   {
   }

   DequeConstIterator( const DequeConstIterator &right ) // copy constructor
      : myOff( right.myOff ),
        myCont( right.myCont )
   {
   }

   ~DequeConstIterator() // destructor
   {
   }

   // const return avoids: ( a1 = a2 ) = a3
   const DequeConstIterator& operator=( const DequeConstIterator &right )
   {
      if( &right != this ) // avoid self-assignment
      {
         myCont = right.myCont;
         myOff = right.myOff;
      }
      return *this; // enables x = y = z, for example
   }

   reference operator*() const
   {
//      size_type block = myOff % ( 4 * myCont->mapSize ) / 4;
      size_type block = myCont->getBlock( myOff );
      size_type off = myOff % 4;
      return myCont->map[ block ][ off ];
   }

   pointer operator->() const
   {
      return &( operator*() );
   }

   DequeConstIterator& operator++() // preincrement
   {
      ++myOff;
      return *this;
   }

   DequeConstIterator operator++( int ) // postincrement
   {
      DequeConstIterator tmp = *this;
      ++*this;
      return tmp;
   }

   DequeConstIterator& operator--() // predecrement
   {
      --myOff;
      return *this;
   }

   DequeConstIterator operator--( int ) // postdecrement
   {
      DequeConstIterator tmp = *this;
      --*this;
      return tmp;
   }

   // increment by integer
   DequeConstIterator& operator+=( const difference_type off )
   {
      myOff += off;
      return *this;
   }

   // return this + integer
   DequeConstIterator operator+( const difference_type off ) const
   {
      DequeConstIterator tmp = *this;
      return tmp += off;
   }

   // decrement by integer
   DequeConstIterator& operator-=( const difference_type off )
   {
      return *this += -off;
   }

   // return this - integer
   DequeConstIterator operator-( const difference_type off ) const
   {
      DequeConstIterator tmp = *this;
      return tmp -= off;
   }

   // return difference of iterators
   difference_type operator-( const DequeConstIterator &right ) const
   {
      return ( static_cast< difference_type >( this->myOff - right.myOff ) );
   }

   reference operator[]( const difference_type off ) const // subscript
   {
      return *( *this + off );
   }

   // test for iterator equality
   bool operator==( const DequeConstIterator &right ) const
   {
      return this->myCont == right.myCont && this->myOff == right.myOff;
   }

   // test for iterator inequality
   bool operator!=( const DequeConstIterator &right ) const
   {
      return !( *this == right );
   }

   // test if this < right
   bool operator<( const DequeConstIterator &right ) const
   {
      return this->myOff < right.myOff;
   }

   // test if this > right
   bool operator>( const DequeConstIterator &right ) const
   {
      return right < *this;
   }

   // test if this <= right
   bool operator<=( const DequeConstIterator &right ) const
   {
      return !( right < *this );
   }

   // test if this >= right
   bool operator>=( const DequeConstIterator &right ) const
   {
      return !( *this < right );
   }

   const MyDeque *myCont; // keep a pointer to deque
   size_type myOff;       // offset of element in deque
};


// CLASS TEMPLATE DequeIterator
template< typename MyDeque >
class DequeIterator : public DequeConstIterator< MyDeque >
{ // iterator for mutable deque
private:
   using size_type = typename MyDeque::size_type;
   using MyBase = DequeConstIterator< MyDeque >;

public:
   using value_type      = typename MyDeque::value_type;
   using difference_type = typename MyDeque::difference_type;
   using pointer         = typename MyDeque::pointer;
   using reference       = value_type &;

   DequeIterator() // construct with null deque pointer
   {
   }

   DequeIterator( size_type off, const MyDeque *pDeque )
      : MyBase( off, pDeque ) // construct with offset off in *pDeque
   {
   }

   reference operator*() const // return designated object
   {
      return const_cast< reference >( MyBase::operator*() );
   }

   pointer operator->() const // return pointer to class object
   {
      return const_cast< pointer >( MyBase::operator->() );
//      return &( operator*() );
   }

   DequeIterator& operator++() // preincrement
   {
      MyBase::operator++();
      return *this;
   }

   DequeIterator operator++( int ) // postincrement
   {
      DequeIterator tmp = *this;
      MyBase::operator++();
      return tmp;
   }

   DequeIterator& operator--() // predecrement
   {
      MyBase::operator--();
      return *this;
   }

   DequeIterator operator--( int ) // postdecrement
   {
      DequeIterator tmp = *this;
      MyBase::operator--();
      return tmp;
   }

   // increment by integer
   DequeIterator& operator+=( const difference_type off )
   {
      MyBase::operator+=( off );
      return *this;
   }

   // return this + integer
   DequeIterator operator+( const difference_type off ) const
   {
      DequeIterator tmp = *this;
      return tmp += off;
   }

   // decrement by integer
   DequeIterator& operator-=( const difference_type off )
   {
      MyBase::operator-=( off );
      return *this;
   }

   using MyBase::operator-; // return difference of iterators

   // return this - integer
   DequeIterator operator-( const difference_type off ) const
   {
      DequeIterator tmp = *this;
      return tmp -= off;
   }

   reference operator[]( const difference_type off ) const // subscript
   {
      return const_cast< reference >( MyBase::operator[]( off ) );
   }
};

// CLASS TEMPLATE DequeVal
template< typename Ty >
class DequeVal // base class for deque to hold data
{
public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference       = value_type &;
   using const_reference = const value_type &;
   using MapPtr = Ty **;

   DequeVal() // initialize values
      : map(),
        mapSize( 0 ),
        myOff( 0 ),
        mySize( 0 )
   {
   }

   // determine block from offset
   size_type getBlock( size_type off ) const
   {
      return off % ( 4 * mapSize ) / 4;
//      return ( off / 4 ) & ( mapSize - 1 );
   }

   MapPtr map;        // pointer to array of pointers to blocks
   size_type mapSize; // size of map array, zero or 2^N
   size_type myOff;   // offset of initial element
   size_type mySize;  // current length of sequence
};


// CLASS TEMPLATE deque
template< typename Ty >
class deque // circular queue of pointers to blocks
{
private:
   using MapPtr = Ty **;
   using ScaryVal = DequeVal< Ty >;

public:
   using value_type      = Ty;
   using size_type       = size_t;
   using difference_type = ptrdiff_t;
   using pointer         = value_type *;
   using const_pointer   = const value_type *;
   using reference       = value_type &;
   using const_reference = const value_type &;

   using iterator               = DequeIterator< ScaryVal >;
   using const_iterator         = DequeConstIterator< ScaryVal >;

   // construct empty deque
   deque()
      : myData()
   {
   }

   // construct from count * val
   deque( size_type count, const value_type &val )
      : myData()
   {
      myData.map = new value_type *[ 8 ]();
      myData.map[ 0 ] = new value_type[ 4 ];
      myData.map[ 0 ][ 0 ] = val;
      myData.mapSize = 8;
      myData.mySize = count;
   }

   // construct by copying right
   deque( const deque &right )
      : myData()
   {
	   myData.mapSize = right.myData.mapSize;
	   myData.myOff = right.myData.myOff;
	   myData.mySize = right.myData.mySize;

	   myData.map = new Ty * [myData.mapSize]();

	   for (int a = 0; a < myData.mapSize; a++) {
		   if (right.myData.map[a] != nullptr) {
			   myData.map[a] = new Ty[4]();

			   for (int b = 0; b < 4; b++)
				   myData.map[a][b] = right.myData.map[a][b];
		   }
	   }
   }

   // destroy the deque
   ~deque()
   {
      clear();
   }

   // return iterator for beginning of mutable sequence
   iterator begin()
   {
      return iterator( myData.myOff, &myData );
   }

   // return iterator for beginning of nonmutable sequence
   const_iterator begin() const
   {
      return const_iterator( myData.myOff, &myData );
   }

   // return iterator for end of mutable sequence
   iterator end()
   {
      return iterator( myData.myOff + myData.mySize, &myData );
   }

   // return iterator for end of nonmutable sequence
   const_iterator end() const
   {
      return const_iterator( myData.myOff + myData.mySize, &myData );
   }

   // return length of sequence
   size_type size() const
   {
      return myData.mySize;
   }

   // test if sequence is empty
   bool empty() const
   {
      return myData.mySize == 0;
   }

   // insert val at where
   void insert( const_iterator where, const value_type &val )
   {
	   unsigned int inserted = myData.myOff;
	   while (inserted != where.myOff)
		   inserted++;

	   if (myData.mySize == 0){
		   if (myData.mapSize == 0) {
			   myData.mapSize = 8;
			   myData.map = new Ty*[myData.mapSize]();
		   }
           // /*modify
		   if (myData.map[myData.mapSize - 1] == nullptr)
			   myData.map[myData.mapSize - 1] = new Ty[4]();
           myData.map[myData.mapSize - 1][3] = val;
           myData.myOff = myData.mapSize * 4 - 1;
           // */
	   }
	   else{
		   inserted %= (myData.mapSize * 4);
		   if (begin() <= where && where <= end()){
			   if (where <= begin() + myData.mySize / 2){
				   auto newfront = (myData.myOff - 1) % (myData.mapSize * 4);
				   
				   if (newfront % 4 == 3 && (myData.mySize + 1) > (myData.mapSize - 1) * 4) {
					   doubleMapSize();
					   newfront = (myData.myOff - 1) % (myData.mapSize * 4);
				   }

				   for (int a = newfront, b = newfront+1; a != where.myOff; a++, b++) {  //modify
					   if (a == myData.mapSize * 4)
                           a = 0;
					   if (b == myData.mapSize * 4) 
                           b = 0;
					   if (a == inserted) 
                           break;

					   if (myData.map[a / 4] == nullptr)
						   myData.map[a / 4] = new Ty[4]();
					   if (myData.map[b / 4] == nullptr)
						   myData.map[b / 4] = new Ty[4]();
					   myData.map[a / 4][a % 4] = myData.map[b / 4][b % 4];
				   }

				   if (myData.map[inserted / 4] == nullptr)
					   myData.map[inserted / 4] = new Ty[4]();
                   inserted = (where.myOff - 1) % (myData.mapSize * 4);  //add
				   myData.map[inserted / 4][inserted % 4] = val;
				   myData.myOff = newfront;
			   }
			   else  {
				   auto newback = (myData.myOff + myData.mySize) % (myData.mapSize * 4);
				   if (newback % 4 == 0 && (myData.mySize + 1) > (myData.mapSize - 1) * 4) {
					   doubleMapSize();
					   newback = (myData.myOff + myData.mySize) % (myData.mapSize * 4);
				   }

				   for (int a = newback, b = newback - 1; a != where.myOff-1; a--, b--) { //modify
					   if (a == -1)
						   a = (myData.mapSize * 4) - 1;
					   if (b == -1)
						   b = (myData.mapSize * 4) - 1;

					   if (myData.map[a / 4] == nullptr)
						   myData.map[a / 4] = new Ty[4]();
					   if (myData.map[b / 4] == nullptr)
						   myData.map[b / 4] = new Ty[4]();
					   myData.map[a / 4][a % 4] = myData.map[b / 4][b % 4];

					   if (a == inserted)
						   break;
				   }

				   if (myData.map[inserted / 4] == nullptr)
					   myData.map[inserted / 4] = new Ty[4]();
                   inserted = where.myOff % (myData.mapSize * 4); //add
				   myData.map[inserted / 4][inserted % 4] = val;
                   myData.myOff = myData.myOff % (4 * myData.mapSize); //add
			   }
		   }
	   }
	   ++myData.mySize;
   }

   // erase element at where
   void erase( const_iterator where )
   {
	   if (myData.mySize > 0 && begin() <= where && where < end()){
		   if (myData.mySize == 1 && begin() == where){
			   myData.myOff = 0;
			   myData.mySize = 0;
		   }
		   else{
               int size_m = myData.mapSize * 4;  //add
			   if (where < begin() + myData.mySize / 2){
                   // /*add
                   for (int a = where.myOff % size_m, b = (where.myOff-1) % size_m; a != myData.myOff % size_m; a--, b--) {
                       if (a == -1) a = size_m - 1;
                       if (b == -1) b = size_m - 1;
                       myData.map[a / 4][a % 4] = myData.map[b / 4][b % 4];
                       if (a == myData.myOff % size_m) break;
                   }
                   myData.myOff++;
                   // */
			   }
			   else{
                   // /*add
                   for (int a = where.myOff % size_m, b = (where.myOff+1) % size_m; a != (myData.myOff + myData.mySize - 1) % size_m; a++, b++) {
                       if (a == size_m) a = 0;
                       if (b == size_m) b = 0;
                       myData.map[a / 4][a % 4] = myData.map[b / 4][b % 4];
                       if (a == (myData.myOff + myData.mySize - 1) % size_m) break;
                   }
                   // */
			   }
			   --myData.mySize;
		   }
	   }
   }

   // erase all
   void clear()
   {
      if( myData.mapSize > 0 )
      {
         for( size_type i = 0; i < myData.mapSize; i++ )
            if( myData.map[ i ] != nullptr )
               delete[] myData.map[ i ];
         delete[] myData.map;

         myData.mapSize = 0;
         myData.mySize = 0;
         myData.myOff = 0;
         myData.map = MapPtr();
      }
   }

private:

   // determine block from offset
   size_type getBlock( size_type off ) const
   {
      return myData.getBlock( off );
//      return ( ( myData.off / 4 ) & ( myData.mapSize - 1 ) );
   }

   void doubleMapSize()
   {
	   auto newmap = new Ty*[myData.mapSize * 2]();

	   int i = (myData.myOff / 4) % (myData.mapSize * 4);
	   for (; i < (myData.myOff + myData.mySize) / 4; i++) {
		   if (newmap[i] == nullptr)
			   newmap[i] = new Ty[4]();
	   }
	   if ((myData.myOff + myData.mySize) % 4 != 0)
		   newmap[(myData.myOff + myData.mySize) / 4] = new Ty[4]();

	   i = myData.myOff;
	   auto j = myData.myOff;
	   for (; i < (myData.myOff + myData.mySize); i++, j++) {
		   if (j == myData.mapSize * 4)
			   j = 0;
		   newmap[i / 4][i % 4] = myData.map[j / 4][j % 4];
	   }
		   
	   for (int a = 0; a < myData.mapSize; a++) {
		   if (myData.map[a] != nullptr)
			   delete[] myData.map[a];
	   }
	   delete[] myData.map;

	   myData.map = newmap;
	   myData.mapSize *= 2;
   }

   ScaryVal myData;
};

#endif