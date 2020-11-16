// Demonstrate how to rewrite c++ struct to c++ class

#include <iostream>
#include "person.h"

int main(int argc, const char *argv[])
{
    Rectangle rec;
    Rectangle rec2(5, 10);

    cout << "rec length:" << rec.getLength() << " width:" << rec.getWidth() << endl;
    cout << "rec2 length:" << rec2.getLength() << " width:" << rec2.getWidth() << endl << endl;

    int reclen, recwid;
    cout << "set rec length:";
    cin >> reclen;
    cout << "set rec width:";
    cin >> recwid;

    rec.setLength(reclen);
    rec.setWidth(recwid);
    cout << "rec length:" << rec.getLength() << " width:" << rec.getWidth() << endl << endl;

    cout << "rec perimeter:" << rec.calculatePerimeter() << endl;
    cout << "rec calculatearea" << rec.calculateArea() << endl;
    cout << "rec2 perimeter:" << rec2.calculatePerimeter() << endl;
    cout << "rec2 calculatearea" << rec2.calculateArea() << endl << endl;

    char recchar;
    cout << "set rec fillCharacter:";
    cin >> recchar;
    rec.setFillCharacter(recchar);
    rec2.setFillCharacter('*');

    rec.draw();
    rec2.draw();

    return 0;
}
