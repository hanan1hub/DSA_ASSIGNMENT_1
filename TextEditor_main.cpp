#include "TextEditor.h"
#include <iostream>
using namespace std;

int main() {
    TextEditor ed;
    ed.insertChar('a');
    ed.insertChar('b');
    ed.moveLeft();
    ed.insertChar('c');
    ed.deleteChar();
    ed.moveLeft();
    ed.moveLeft();
    ed.moveRight();
    ed.moveRight();

    return 0;
}
