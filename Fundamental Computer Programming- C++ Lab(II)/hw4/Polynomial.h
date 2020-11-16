// The definition of Class Polynomial
#ifndef Polynomial_H
#define Polynomial_H
#include <iostream>

using namespace std;

class Polynomial {
    friend ostream& operator<<(ostream &out, const Polynomial &outPoint);
    friend istream& operator>>(istream &in, Polynomial &outPoint);

    private:
       int* terms;
       int size;
    public:
       Polynomial(int expNum);
       Polynomial(const Polynomial& rightPoint);
       
       ~Polynomial();
       Polynomial operator+(Polynomial &rightPoint);
       Polynomial operator-(Polynomial &rightPoint);
       Polynomial& operator=(const Polynomial &rightPoint);
};

#endif /* Polynomial_H */
