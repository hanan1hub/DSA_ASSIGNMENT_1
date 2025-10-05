#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H
#include <string>
using namespace std;

class TextEditor {
public:
    virtual void insertChar(char c);
    virtual void deleteChar();
    virtual void moveLeft();
    virtual void moveRight();
    virtual string getTextWithCursor() const;
};

#endif
