#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Node{
public:
    int coeff;
    int power;
    Node* next;
    Node(int c, int p){
        coeff = c;
        power = p;
        next = NULL;
    }
};

class Polynomial{
private:
    Node* head;
public:
    Polynomial(){
        head = NULL;
    }

    bool is_empty() const{
        return head == NULL;
    }

    // insertTerm
    void insertTerm(int coeff, int power){
        if (coeff == 0){
            return;
        }
        Node* new_node = new Node(coeff, power);
        if (is_empty()){
            head = new_node;
            return;
        }
        Node* temp = head;
        Node* pre = NULL;
        while(temp != NULL && temp->power > power){
            pre = temp;
            temp = temp->next;
        }
        if(temp != NULL && temp->power == power){
            temp->coeff += coeff;
            if(temp->coeff == 0) { // remove zero terms
                if(pre){
                    pre->next = temp->next;
                } 
                else{
                    head = temp->next;
                } 
                delete temp;
            }
            delete new_node;
            return;
        }
        if(pre == NULL){
            new_node->next = head;
            head = new_node;
        }else{
            new_node->next = temp;
            pre->next = new_node;
        }
    }

    // toString
    string toString() const{
        if(is_empty()){
            return "0";
        } 
        ostringstream out;
        Node* temp = head;
        bool first = true;
        while(temp != NULL){
            if(!first && temp->coeff > 0){
                out << "+";
            } 
            if(temp->power == 0){
                out << temp->coeff;
            } 
            else if(temp->power == 1){
                if(temp->coeff == 1){
                    out << "x";
                } 
                else if(temp->coeff == -1){
                    out << "-x";
                } 
                else{
                    out << temp->coeff << "x";
                } 
            }else{
                if(temp->coeff == 1){
                    out << "x^" << temp->power;
                } 
                else if(temp->coeff == -1){
                    out << "-x^" << temp->power;
                } 
                else{
                    out << temp->coeff << "x^" << temp->power;
                } 
            }
            first = false;
            temp = temp->next;
        }
        return out.str();
    }

    // add
    Polynomial add(const Polynomial& other) const{
        Polynomial result;
        Node* temp_1 = head;
        Node* temp_2 = other.head;
        while(temp_1 != NULL && temp_2 != NULL){
            if(temp_1->power == temp_2->power){
                result.insertTerm(temp_1->coeff + temp_2->coeff, temp_1->power);
                temp_1 = temp_1->next;
                temp_2 = temp_2->next;
            }else if(temp_1->power > temp_2->power) {
                result.insertTerm(temp_1->coeff, temp_1->power);
                temp_1 = temp_1->next;
            }else{
                result.insertTerm(temp_2->coeff, temp_2->power);
                temp_2 = temp_2->next;
            }
        }
        while(temp_1 != NULL){
            result.insertTerm(temp_1->coeff, temp_1->power);
            temp_1 = temp_1->next;
        }
        while(temp_2 != NULL){
            result.insertTerm(temp_2->coeff, temp_2->power);
            temp_2 = temp_2->next;
        }
        return result;
    }

    // multiply
    Polynomial multiply(const Polynomial& other) const{
        Polynomial result;
        Node* temp_1 = head;
        while(temp_1 != NULL){
            Node* temp_2 = other.head;
            while(temp_2 != NULL){
                result.insertTerm(temp_1->coeff * temp_2->coeff, temp_1->power + temp_2->power);
                temp_2 = temp_2->next;
            }
            temp_1 = temp_1->next;
        }
        return result;
    }

    // derivative
    Polynomial derivative() const{
        Polynomial result;
        Node* temp = head;
        while(temp != NULL){
            if(temp->power > 0){
                result.insertTerm(temp->coeff * temp->power, temp->power - 1);
            }
            temp = temp->next;
        }
        return result;
    }
};

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

