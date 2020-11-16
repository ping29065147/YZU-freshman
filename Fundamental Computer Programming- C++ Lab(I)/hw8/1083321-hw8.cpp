#include <iostream>

using namespace std;
int row=3, col=3;

int createMatrixFromArray(int** &mat, int* sam)
{
    int a, b, i=0;

    mat = new int*[row];    //配置二維動態陣列
    for(a=0; a<col; a++){
        mat[a] = new int[col];
    }

    for(a=0; a<row; a++){
        for(b=0; b<col; b++){
            mat[a][b] = sam[i]; //將一維陣列sam的資料傳入mat
            i++;
        }
    }
}

int** multiplicateMatrix(int** mat1, int** mat2)
{
    int a, b, c, d;
    int **result = new int*[row];   //配置二維動態陣列
    for(a=0; a<col; a++){
        result[a] = new int[col]();
    }

    for(a=0; a<row; a++){
        for(b=0; b<col; b++){
            for(c=0; c<row; c++)
                result[a][b] += mat1[a][c]*mat2[c][b];  //將mat1與mat2做矩陣乘法，並存入result
        }
    }

    return result;
}

int destroyMatrix(int** de)
{
    int a;

    for(a=0; a<col; a++)    //釋放二維動態陣列
        delete[] de[a];
    delete[] de;
}

int printMatrix(int** print)
{
    int a, b;

    for(a=0; a<row; a++){
        for(b=0; b<col; b++)
            cout << print[a][b] << " "; //印出二維動態陣列
        cout << endl;
    }
    cout << "\n\n";
}

int main()
{
    int a, b;
    int sam1[] = {48, 69, 8, 24, 79, 24, 32, 59, 10};
    int sam2[] = {18, 26, 47, 90, 31, 36, 2, 47, 98};
    int **mat1, **mat2;

    createMatrixFromArray(mat1, sam1);
    createMatrixFromArray(mat2, sam2);
    int **result = multiplicateMatrix(mat1, mat2);

    cout << "mat1\n";
    printMatrix(mat1);
    cout << "mat2\n";
    printMatrix(mat2);
    cout << "result\n";
    printMatrix(result);

    destroyMatrix(mat1);
    destroyMatrix(mat2);
    destroyMatrix(result);

    return 0;
}
