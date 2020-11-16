#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>

using namespace std;

struct record{
    int id;
    unsigned char name[16];
    int weight;
    int height;
    float bmi;
};

int main()
{
    ifstream inFile("records.csv", ios::in);    //讀檔records.csv
    if (!inFile)
        cout << "can't open file";

    stringstream change, convert;
    string input, output;
    vector<record> data, data2;
    record re;
    int point, a;

    while(inFile >> input){

        change.str("");
        change.clear();
        change << input;

        point=1;
        while(getline(change, output, ',')){    //將string分割並存入data

            convert.str("");
            convert.clear();
            convert << output;

            if (point==1)
                convert >> re.id;
            else if (point==2)
                convert >> re.name;
            else if (point==3)
                convert >> re.weight;
            else if (point==4)
                convert >> re.height;

            point++;
        }
        re.bmi = ((float)re.weight)/(((float)re.height/100)*((float)re.height/100));    //計算bmi
        data.push_back(re);

    }
    inFile.close();

    ofstream outFile("records.dat", ios::binary | ios::out);
    for(a=0; a<data.size(); a++)
        outFile.write((char*)&data[a], sizeof(record)); //存檔records.dat
    outFile.close();


    ifstream inFiles("records.dat", ios::binary | ios::in);
    if (!inFiles)
        cout << "can't open file";

    while(!inFiles.eof()){
        inFiles.read((char*)&re, sizeof(record));
        data2.push_back(re);
    }
    inFiles.close();

    for(a=0; a<data2.size()-1; a++){
        cout << data2[a].id << " " << data2[a].name << " " << data2[a].weight << " " << data2[a].height << " " << data2[a].bmi << "\t";
        if (data2[a].bmi < 18.5)        //判斷bmi
            cout << "Underweight";
        else if (data2[a].bmi < 24)
            cout << "Normal";
        else if (data2[a].bmi < 27)
            cout << "Overweight";
        else if (data2[a].bmi < 30)
            cout << "Moderately obese";
        else if (data2[a].bmi < 35)
            cout << "Severely obese";
        else
            cout << "Very severely obese";
        cout << endl;
    }
    cout << endl << endl;
    for(a=0; a<data2.size()-1; a++){
        if (data2[a].bmi < 18.5){
            cout << data2[a].id << " " << data2[a].name << " " << data2[a].weight << " " << data2[a].height << " " << data2[a].bmi << "\t";
            cout << "Underweight" << endl;
        }
    }

    return 0;
}


<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head><meta http-equiv="Content-Type" content="text/html; charset=utf-8" /><title>

</title></head>
<body>
    <form method="post" action="./File_DownLoad_Wk_zip.aspx?File_name=1083321.cpp&amp;type=3&amp;id=2827675" id="form1">
<div class="aspNetHidden">
<input type="hidden" name="__VIEWSTATE" id="__VIEWSTATE" value="/wEPDwUKLTEzNDM3NzkxOWRkwneTr34MFXJYUKyKKda+DU4gQVM=" />
</div>

<div class="aspNetHidden">

	<input type="hidden" name="__VIEWSTATEGENERATOR" id="__VIEWSTATEGENERATOR" value="629601C3" />
</div>
    <div>
    
    </div>
    </form>
</body>
</html>
