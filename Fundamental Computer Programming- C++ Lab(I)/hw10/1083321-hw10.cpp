#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <vector>

using namespace std;

int main()
{
    ifstream inFile("records.csv", ios::in);        //開檔
    if (!inFile)
        cout << "can't open file";

    stringstream change;
    string input, output;
    vector<string> data, split;
    vector<int> intdata;
    int a, in, maxheight, outputtimes=0;
    float weight=0, height=0;

    while(inFile >> input){
        data.push_back(input);      //完整資料傳存入data

        change.str("");
        change.clear();
        change << input;

        while(getline(change, output, ','))     //分割資料存入split
            split.push_back(output);
    }

    for(a=0; a<split.size(); a++){      //將string轉為int
        if (a%4 != 1){
            change.str("");
            change.clear();
            change << split[a];
            change >> in;
            intdata.push_back(in);
        }
    }

    for(a=0; a<intdata.size(); a++){        //計算平均體重及身高
        if (a%3 == 1)
            weight += intdata[a];
        else if (a%3 == 2)
            height += intdata[a];
    }
    weight /= (intdata.size()/3);
    height /= (intdata.size()/3);
    cout << "average weight: " << weight << endl;
    cout << "average height: " << height << endl << endl;

    while(outputtimes != data.size()){      //從最大身高開始輸出
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
