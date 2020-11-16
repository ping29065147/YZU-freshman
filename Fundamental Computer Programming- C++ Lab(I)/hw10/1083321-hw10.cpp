#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <vector>

using namespace std;

int main()
{
    ifstream inFile("records.csv", ios::in);        //�}��
    if (!inFile)
        cout << "can't open file";

    stringstream change;
    string input, output;
    vector<string> data, split;
    vector<int> intdata;
    int a, in, maxheight, outputtimes=0;
    float weight=0, height=0;

    while(inFile >> input){
        data.push_back(input);      //�����ƶǦs�Jdata

        change.str("");
        change.clear();
        change << input;

        while(getline(change, output, ','))     //���θ�Ʀs�Jsplit
            split.push_back(output);
    }

    for(a=0; a<split.size(); a++){      //�Nstring�ରint
        if (a%4 != 1){
            change.str("");
            change.clear();
            change << split[a];
            change >> in;
            intdata.push_back(in);
        }
    }

    for(a=0; a<intdata.size(); a++){        //�p�⥭���魫�Ψ���
        if (a%3 == 1)
            weight += intdata[a];
        else if (a%3 == 2)
            height += intdata[a];
    }
    weight /= (intdata.size()/3);
    height /= (intdata.size()/3);
    cout << "average weight: " << weight << endl;
    cout << "average height: " << height << endl << endl;

    while(outputtimes != data.size()){      //�q�̤j�����}�l��X
        maxheight=0;
        for(a=2; a<intdata.size(); a+=3){
            if (intdata[a] > maxheight)
                maxheight = intdata[a];
        }
        for(a=2; a<intdata.size(); a+=3){
            if (maxheight == intdata[a]){
                //cout << data[(a-2)/3] << endl;
                cout << outputtimes+1 << "," << split[((a-2)/3)*4+1] << "," << split[((a-2)/3)*4+2] << "," << split[((a-2)/3)*4+3] << endl;
                intdata[a]=0;
                outputtimes++;
                break;
            }
        }
    }

    return 0;
}
