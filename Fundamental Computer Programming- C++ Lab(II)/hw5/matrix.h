#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

using namespace std;

/**
   This class describes a 3 x 3 matrix.
*/
class Matrix
{
public:
   /**
      Constructs a matrix filled with zero elements.
   */
   Matrix();

   /**
      Accesses a matrix element.
      @param i the row index
      @param j the column index
      @return a reference to the element with the given indexes
   */
   double& operator()(int i, int j);

   /**
      Accesses a matrix element.
      @param i the row index
      @param j the column index
      @return the element with the given indexes
   */
   double operator()(int i, int j) const;

   /**
      Computes the matrix sum
      @param right another matrix
      @return the updated matrix
   */
   Matrix& operator+=(const Matrix& right);

   static const int ROWS = 3;
   static const int COLUMNS = 3;
private:
   double elements[ROWS * COLUMNS];
};

/**
   Computes the matrix sum.
   @param right another matrix
   @return the sum of two matricies
*/
Matrix operator+(const Matrix& left, const Matrix& right);

/**
   Computes the matrix product.
   @param right another matrix
   @return the product of two matricies
*/
Matrix operator*(const Matrix& left, const Matrix& right);

/**
   Computes the scalar product of a scalar value and a matrix.
   @param left a scalar value
   @param right a matrix
   @return the product of the given value and the given matrix
*/
Matrix operator*(double left, const Matrix& right);

/**
   Computes the scalar product of a matrix and a scalar value.
   @param right a scalar value
   @return the product of this matrix and the given value
*/
Matrix operator*(const Matrix& left, double right);

/**
   Prints a matrix to an output stream.
   @param left an output stream
   @param right a matrix
   @return the given output stream
*/
ostream& operator<<(ostream& left, const Matrix& right);

#endif // MATRIX_H
