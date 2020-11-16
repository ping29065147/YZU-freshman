// insert val at where
void insert(const_iterator where, const value_type& val)
{
   unsigned int inserted = 0;
   if (myData.mySize == 0)
   {
	   
   }
   else
   {
	   if (begin() <= where && where <= end())
	   {
		   // all elements before where move forward
		   if (where <= begin() + myData.mySize / 2)
		   {
			   
		   }

		   else  // all elements after (and at) where move backward
		   {
			   
		   }
	   }
   }
   ++myData.mySize;
}


// erase element at where
void erase(const_iterator where)
{
   if (myData.mySize > 0 && begin() <= where && where < end())
   {
	   if (myData.mySize == 1 && begin() == where)
	   {
		   myData.myOff = 0;
		   myData.mySize = 0;
	   }
	   else
	   {
		   // all elements before where move backward
		   if (where < begin() + myData.mySize / 2)
		   {
			   
		   }
		   else // all elements after where move forward
		   {
			   
		   }
		   --myData.mySize;
	   }
   }
}