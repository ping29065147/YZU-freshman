// Demonstrate how to rewrite c++ struct to c++ class

#include <iostream>
#include <sstream>
#include "person.h"
using namespace std;

Rectangle::Rectangle(int new_length, int new_width)
{
    length = new_length;
    width = new_width;
}

void Rectangle::setLength( int new_length)
{
   if (new_length>1 && new_length<=20)
      length = new_length;
}

int Rectangle::getLength()
{
    return length;
}

void Rectangle::setWidth(int new_width)
{
   if (new_width > 1 && new_width <= 20)
      width = new_width;
}

int Rectangle::getWidth()
{
   return width;
}

int Rectangle::calculatePerimeter()
{
   return (width + length) * 2;
}

int Rectangle::calculateArea()
{
   return width * length;
}


void Rectangle::setFillCharacter(char new_character)
{
   FillCharactor = new_character;
}

void Rectangle::draw()
{
   int a, b;
   for (a = 0; a < width; a++) {
      for (b = 0; b < length; b++) {
         if (a == 0 || a == width - 1 || b == 0 || b == length - 1)
            cout << FillCharactor << " ";
         else
            cout << "  ";
      }
      cout << endl;
   }
}