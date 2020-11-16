#include <iostream>

using namespace std;
int row=3, col=3;

int createMatrixFromArray(int** &mat, int* sam)
{
    int a, b, i=0;

    mat = new int*[row];    //�t�m�G���ʺA�}�C
    for(a=0; a<col; a++){
        mat[a] = new int[col];
    }

    for(a=0; a<row; a++){
        for(b=0; b<col; b++){
            mat[a][b] = sam[i]; //�N�@���}�Csam����ƶǤJmat
            i++;
        }
    }
}

int** multiplicateMatrix(int** mat1, int** mat2)
{
    int a, b, c, d;
    int **result = new int*[row];   //�t�m�G���ʺA�}�C
    for(a=0; a<col; a++){
        result[a] = new int[col]();
    }

    for(a=0; a<row; a++){
        for(b=0; b<col; b++){
            for(c=0; c<row; c++)
                result[a][b] += mat1[a][c]*mat2[c][b];  //�Nmat1�Pmat2���x�}���k�A�æs�Jresult
        }
    }

    return result;
}

int destroyMatrix(int** de)
{
    int a;

    for(a=0; a<col; a++)    //����G���ʺA�}�C
        delete[] de[a];
    delete[] de;
}

int printMatrix(int** print)
{
    int a, b;

    for(a=0; a<row; a++){
        for(b=0; b<col; b++)
            cout << print[a][b] << " "; //�L�X�G���ʺA�}�C
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
