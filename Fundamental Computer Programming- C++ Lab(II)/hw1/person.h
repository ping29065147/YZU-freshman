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
        void setLength( int ); //設定長
        int getLength(); //return長
        void setWidth( int ); //設定寬
        int getWidth(); //return 寬

        int calculatePerimeter(); //計算周長
        int calculateArea(); //計算面積

        void setFillCharacter(char ); //設定符號
        void draw(); //劃出圖形
};

#endif // RECTANGLE_H
