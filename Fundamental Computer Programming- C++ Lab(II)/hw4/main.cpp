// Test Class Polynomial
#include "Polynomial.h"

int main(int argc, const char *argv[])
{
    Polynomial p(3);
    Polynomial q(4);
    Polynomial m(4);

    cout << "Please input all coefficients of polynomial p" << endl;
    cin >> p;
    cout << "Please input all coefficients of  polynomial q" << endl;
    cin >> q;

    cout << p + q;
    cout << p - q;

    m = p + q;
    cout << m;

    Polynomial n(p+q);
    cout << n;
    
    return 0;
}
