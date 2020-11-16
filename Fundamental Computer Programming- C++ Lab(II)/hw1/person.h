// Demonstrates how to rewrite c++ struct to c++ class
#ifndef RECTANGLE_H
#define RECTANGLE_H

using namespace std;
class Rectangle {
    private:
        // member variables
        int length;
        int width;
        char FillCharactor;
    public:
        // constructor function
        Rectangle( int = 1, int = 1 );
        // member functions
        void setLength( int ); //�]�w��
        int getLength(); //return��
        void setWidth( int ); //�]�w�e
        int getWidth(); //return �e

        int calculatePerimeter(); //�p��P��
        int calculateArea(); //�p�⭱�n

        void setFillCharacter(char ); //�]�w�Ÿ�
        void draw(); //���X�ϧ�
};

#endif // RECTANGLE_H
