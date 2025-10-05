#include "polynomial.h"
#include <iostream>

using namespace std;

int main() {
    Polynomial p1, p2, p3;

    // p1 terms
    p1.insertTerm(3, 4);
    p1.insertTerm(2, 2);
    p1.insertTerm(-1, 1);
    p1.insertTerm(5, 0);

    // p2 terms
    p2.insertTerm(1, 4);
    p2.insertTerm(1, 0);

    // p1 + p2
    Polynomial sum = p1.add(p2);

    // p3 term
    p3.insertTerm(2, 1);

    // (p1 + p2) * p3
    Polynomial prod = sum.multiply(p3);

    // derivative of p1
    Polynomial deriv = p1.derivative();

    // output
    cout << "p1.toString(): " << p1.toString() << endl;
    cout << "sum.toString(): " << sum.toString() << endl;
    cout << "prod.toString(): " << prod.toString() << endl;
    cout << "deriv.toString(): " << deriv.toString() << endl;

    return 0;
}