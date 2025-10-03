# include <iostream>
# include <string>
using namespace std;

class Node{
    public:
    char ch;
    Node* next;
    Node* previous;

    Node(char c){
        ch = c;
        next = previous = NULL;
    }
};

class texteditor{
    private:
    Node* head;
    Node* tail;
    Node* current;
    public:
    texteditor(){
        head = tail = NULL;
    }
    bool is_empty(){
        return head == NULL;
    }
    void insert_char(char c){
        Node* new_node = new Node(c);
        if(is_empty()){
            head = tail = new_node;
            current = new_node->next;
        }else if(current == head){
            new_node->next = head;
            head->previous = new_node;
            head = new_node;
        }else if(current == NULL){
            tail->next = new_node;
            new_node->previous = tail;
            tail = new_node;
        }else{
            new_node->next = current;
            new_node->previous = current->previous;
            if (current->previous != NULL){
                current->previous->next = new_node;
            } 
            current->previous = new_node;
            if (current == head){
                head = new_node;
            } 
            
        }
        cout<<"After insert '"<<c<<" ': "<<tostring()<<endl;

    }

    void deleteChar() {
        if (current == head) {
            cout << "After delete: " << tostring() << endl;
            return; // nothing to delete
        }
        Node* to_delete;
        if (current == NULL) { // delete last node
            to_delete = tail;
            tail = tail->previous;
            if(tail != NULL){
                tail->next = NULL;
            } 
            else{
                head = NULL;
            } 
        } else{
            to_delete = current->previous;
            if(to_delete->previous != NULL){
                to_delete->previous->next = current;
            } 
            current->previous = to_delete->previous;
            if(to_delete == head){
                head = current;
            } 
        }
        delete to_delete;
        cout << "After delete: " << tostring() << endl;
    }

    void move_left(){
        if(current == head){
            cout<<"after moving left :"<<tostring()<<endl;
            return;
        }
        if(current == NULL){
            current = tail;
        }else{
            current = current->previous;
        }
        cout<<"after moving left :"<<tostring()<<endl;
    }
    void move_right(){
        if(current == NULL){
            cout<<"after moving right :"<<tostring()<<endl;
            return;
        }else{
            current = current->next;
            cout<<"after moving right :"<<tostring()<<endl;
        }
    }
    string tostring(){
        string result;
        
        Node* temp = head;
        while(temp != NULL){
            if(temp == current){
                result += '|';
            }
            result += temp->ch;
            temp = temp->next;
        }
        if(current == NULL){
            result += '|';
        }
        return result;
    }
};

int main(){

    texteditor ed;
    ed.insert_char('a');
    ed.insert_char('b');
    ed.deleteChar();
    ed.insert_char('c');
    ed.move_left();
    ed.insert_char('x');
    ed.deleteChar();
    ed.move_right();
    ed.insert_char('e');
    ed.deleteChar();

    return 0;
}