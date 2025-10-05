#include "polynomial.h"
#include <iostream>
#include <map>
#include <sstream>
#include <string>
using namespace std;

class Node {
public:
    int coeff;
    int power;
    Node* next;

    Node(int c, int p) {
        coeff = c;
        power = p;
        next = NULL;
    }
};

class test {
public:
    Node* head;

    test() {
        head = NULL;
    }
};

// i used global storage for each Polynomial object
static map<const Polynomial*, test> data;

// insert term in polynomial
void Polynomial::insertTerm(int coeff, int power) {
    if (coeff == 0) {
        return;
    }

    Node*& head = data[this].head;
    Node* new_node = new Node(coeff, power);

    if (head == NULL) {
        head = new_node;
        return;
    }

    Node* temp = head;
    Node* pre = NULL;

    while (temp != NULL && temp->power > power) {
        pre = temp;
        temp = temp->next;
    }

    if (temp != NULL && temp->power == power) {
        temp->coeff += coeff;
        if (temp->coeff == 0) {
            if (pre != NULL) {
                pre->next = temp->next;
            }
            else {
                head = temp->next;
            }
            delete temp;
        }
        delete new_node;
        return;
    }

    if (pre == NULL) {
        new_node->next = head;
        head = new_node;
    }
    else {
        new_node->next = temp;
        pre->next = new_node;
    }
}

// toString
string Polynomial::toString() const {
    Node* temp = data.at(this).head;
    if (temp == NULL) {
        return "0";
    }

    ostringstream out;
    bool first = true;

    while (temp != NULL) {
        if (!first && temp->coeff > 0) {
            out << "+";
        }

        if (temp->power == 0) {
            out << temp->coeff;
        }
        else if (temp->power == 1) {
            if (temp->coeff == 1) {
                out << "x";
            }
            else if (temp->coeff == -1) {
                out << "-x";
            }
            else {
                out << temp->coeff << "x";
            }
        }
        else {
            if (temp->coeff == 1) {
                out << "x^" << temp->power;
            }
            else if (temp->coeff == -1) {
                out << "-x^" << temp->power;
            }
            else {
                out << temp->coeff << "x^" << temp->power;
            }
        }

        first = false;
        temp = temp->next;
    }

    return out.str();
}

// add
Polynomial Polynomial::add(const Polynomial& other) const {
    Polynomial result;

    Node* temp_1 = data.at(this).head;
    Node* temp_2 = data.at(&other).head;

    while (temp_1 != NULL && temp_2 != NULL) {
        if (temp_1->power == temp_2->power) {
            result.insertTerm(temp_1->coeff + temp_2->coeff, temp_1->power);
            temp_1 = temp_1->next;
            temp_2 = temp_2->next;
        }
        else if (temp_1->power > temp_2->power) {
            result.insertTerm(temp_1->coeff, temp_1->power);
            temp_1 = temp_1->next;
        }
        else {
            result.insertTerm(temp_2->coeff, temp_2->power);
            temp_2 = temp_2->next;
        }
    }

    while (temp_1 != NULL) {
        result.insertTerm(temp_1->coeff, temp_1->power);
        temp_1 = temp_1->next;
    }

    while (temp_2 != NULL) {
        result.insertTerm(temp_2->coeff, temp_2->power);
        temp_2 = temp_2->next;
    }

    return result;
}

// multiply
Polynomial Polynomial::multiply(const Polynomial& other) const {
    Polynomial result;

    Node* temp_1 = data.at(this).head;

    while (temp_1 != NULL) {
        Node* temp_2 = data.at(&other).head;
        while (temp_2 != NULL) {
            result.insertTerm(temp_1->coeff * temp_2->coeff, temp_1->power + temp_2->power);
            temp_2 = temp_2->next;
        }
        temp_1 = temp_1->next;
    }

    return result;
}

// derivative
Polynomial Polynomial::derivative() const {
    Polynomial result;
    Node* t = data.at(this).head;

    while (t != NULL) {
        if (t->power > 0) {
            result.insertTerm(t->coeff * t->power, t->power - 1);
        }
        t = t->next;
    }

    return result;
}
