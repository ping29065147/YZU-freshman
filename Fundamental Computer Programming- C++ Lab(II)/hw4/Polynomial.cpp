// The implenment of Class Polynomial
#include "Polynomial.h"


Polynomial::Polynomial(int expNum)
{
   size = expNum;
   terms = new int[expNum]();
}

Polynomial::Polynomial(const Polynomial& rightPoint) //copy constructor
{
   size = rightPoint.size;
   terms = new int[size]();

   for (int a = 0; a < size; a++)
      terms[a] = rightPoint.terms[a];
}

Polynomial::~Polynomial()
{
   delete[] terms;
}


Polynomial Polynomial::operator+(Polynomial & rightPoint) //+
{
   int maxsize;
   if (size > rightPoint.size)
      maxsize = size;
   else
      maxsize = rightPoint.size;

   Polynomial x(maxsize);

   for (int a = 0; a < size; a++)
      x.terms[a] = terms[a];
   for (int a = 0; a < rightPoint.size; a++)
      x.terms[a] += rightPoint.terms[a];

   return x;
}


Polynomial Polynomial::operator-(Polynomial &rightPoint) //-
{
   int maxsize;
   if (size > rightPoint.size)
      maxsize = size;
   else
      maxsize = rightPoint.size;

   Polynomial x(maxsize);

   for (int a = 0; a < size; a++)
      x.terms[a] = terms[a];
   for (int a = 0; a < rightPoint.size; a++)
      x.terms[a] -= rightPoint.terms[a];

   return x;
}

Polynomial& Polynomial::operator=(const Polynomial &rightPoint) //=
{
   size = rightPoint.size;
   terms = new int[size]();

   for (int a = 0; a < size; a++)
      terms[a] = rightPoint.terms[a];

   return *this;
}

ostream& operator<<(ostream &out, const Polynomial& outPoint) //output
{

   for (int a=0; a<outPoint.size; a++) {

      if (outPoint.terms[a] != 0)
         out << outPoint.terms[a] << " * X^" << a;
      else
         continue;
      if (a+1 != outPoint.size)
         out << " + ";
    }
   out << endl;

    return out;
} 

istream& operator>>(istream &in, Polynomial& outPoint) //input
{
   for (int a = 0; a < outPoint.size; a++)
      in >> outPoint.terms[a];

    return in;
}
