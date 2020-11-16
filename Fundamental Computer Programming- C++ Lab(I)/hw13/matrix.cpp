#include <iostream>
#include <vector>
#include "matrix.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void load(vector< vector<int> > &data1, vector< vector<int> > &data2)
{
    ifstream inFile1("A.csv", ios::in);
    ifstream inFile2("B.csv", ios::in);
    string in, out;
    int a, b, rows1=0, cols1=0, rows2=0, cols2=0;
    stringstream ss, dd;
    vector<int> data;

    while(inFile1 >> in){   //讀檔
        ss.str("");
        ss.clear();
        ss << in;

        while(getline(ss, out, ',')){   //以逗號分割
            dd.str("");
            dd.clear();
            dd << out;

            dd >> a;
            if (rows1==0)
                rows1 = a;
            else if (cols1==0)
                cols1 = a;
            else
                data.push_back(a);
        }
        if (data.size()==cols1){
            data1.push_back(data);      //存入data1
            data.clear();
        }
    }
    while(inFile2 >> in){   //讀檔
        ss.str("");
        ss.clear();
        ss << in;

        while(getline(ss, out, ',')){   //以逗號分割
            dd.str("");
            dd.clear();
            dd << out;

            dd >> a;
            if (rows2==0)
                rows2 = a;
            else if (cols2==0)
                cols2 = a;
            else
                data.push_back(a);
        }
        if (data.size()==cols2){
            data2.push_back(data);      //存入data2
            data.clear();
        }
    }

    /*for(a=0; a<rows1; a++){
        for(b=0; b<cols1; b++){
            cout << data1[a][b] << " ";
        }
        cout << endl;
    }
    for(a=0; a<rows2; a++){
        for(b=0; b<cols2; b++){
            cout << data2[a][b] << " ";
        }
        cout << endl;
    }*/




    inFile1.close();
    inFile2.close();
}

void compute(vector< vector<int> > &data1, vector< vector<int> > &data2, vector< vector<int> > &data3)
{
    vector<int> data;
    int a, b ,c, re;

    for(a=0; a<data1.size(); a++){      //矩陣乘法
        for(b=0; b<data2[0].size(); b++){
            re=0;
            for(c=0; c<data1[0].size(); c++)
                re += data1[a][c]*data2[c][b];

            data.push_back(re);
        }
        data3.push_back(data);
        data.clear();
    }

}

void print(vector< vector<int> > &data3)
{
    int a, b;

    for(a=0; a<data3.size(); a++){
        for(b=0; b<data3[0].size(); b++)
            cout << data3[a][b] << " ";
        cout << endl;
    }
}
