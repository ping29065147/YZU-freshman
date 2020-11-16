#include "matrix.h"


Matrix::Matrix() //ªì©l
{
   for (int a = 0; a < ROWS * COLUMNS; a++)
      elements[a] = 0;
}

double& Matrix::operator()(int i, int j)  //µ¹­È
{
   return elements[i * COLUMNS + j];
}

double Matrix::operator()(int i, int j) const  //¨ú­È
{
   return elements[i * COLUMNS + j];
}

Matrix& Matrix::operator+=(const Matrix& right)  //+=
{
   for (int a = 0; a < ROWS * COLUMNS; a++)
      elements[a] += right.elements[a];

   return *this;
}



Matrix operator+(const Matrix& left, const Matrix& right)  //Matrix+Matrix
{
   Matrix re;

   re += left;
   re += right;
   return re;
}

Matrix operator*(const Matrix& left, const Matrix& right)  //Matrix*Matrix
{
   Matrix re;

   for (int a = 0; a < 3; a++) {
      for (int b = 0; b < 3; b++)
         for (int c = 0; c < 3; c++) 
            re(a, b) += left(a, c) * right(c, b);
         
         
   }

   return re;
}

Matrix operator*(double left, const Matrix& right)  //number*Matrix
{
   Matrix re;
   
   for (int a = 0; a < 3; a++) {
      for (int b = 0; b < 3; b++)
         re(a, b) = left * right(a, b);
   }

   return re;
}

Matrix operator*(const Matrix& left, double right)  //Matrix*number
{
   Matrix re;

   for (int a = 0; a < 3; a++) {
      for (int b = 0; b < 3; b++)
         re(a, b) = left(a, b) * right;
   }

   return re;
}

ostream& operator<<(ostream& left, const Matrix& right)  //print
{
   for (int a = 0; a < 3; a++) {
      for (int b = 0; b < 3; b++)
         left << right(a, b) << " ";
      left << endl;
   }


   return left;
}