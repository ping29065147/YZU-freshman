#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>

using namespace std;
#define MAXWORDLENGTH 255

struct dictionary {
    char word[MAXWORDLENGTH];
    unsigned int count;
};

bool change(dictionary a, dictionary b)
{
    return a.count>b.count;
}

int main()
{
    ofstream outFile("dict.dat", ios::binary | ios::app);
    outFile.close();

    ifstream inFile("dict.dat", ios::binary | ios::in);
    ifstream test1("test2.txt", ios::in);
    if (!inFile) cout << "no dict.dat";
    else if (!test1) cout << "no test1.txt";

    dictionary input_test1;
    input_test1.count = 1;
    vector<dictionary> test1_data;
    int a, b, c;

    while(test1 >> input_test1.word)        //讀檔
        test1_data.push_back(input_test1);
    test1.close();

    for(a=0; a<test1_data.size(); a++){
        for(b=0; b<strlen(test1_data[a].word) ;b++){
            if (test1_data[a].word[b]>='A' && test1_data[a].word[b]<='Z')   //將大寫轉小寫
                test1_data[a].word[b] += 32;

            if (isdigit(test1_data[a].word[b]) || !(isalpha(test1_data[a].word[b]))){   //將非字母去除
                if(b == strlen(test1_data[a].word)-1)
                    test1_data[a].word[b] = '\0';
                else{
                    for(c=b; c<strlen(test1_data[a].word); c++)
                        test1_data[a].word[c] = test1_data[a].word[c+1];
                    test1_data[a].word[c-1] = '\0';
                }
                b--;
            }
        }
    }

    dictionary read;
    while(inFile.read((char*)(&read), sizeof(dictionary)))
        test1_data.push_back(read);

   inFile.close();
   ofstream outFile2("dict.dat", ios::binary | ios::out);

    for(a=0; a<test1_data.size()-1; a++){
        for(b=a+1; b<test1_data.size(); b++){
            if (!strcmp(test1_data[a].word, test1_data[b].word)){   //將重複字串刪除
                test1_data[a].count += test1_data[b].count;
                test1_data.erase(test1_data.begin()+b);
            }
        }
    }

    sort(test1_data.begin(), test1_data.end(), change);

    for(a=0; a<test1_data.size(); a++){
        outFile2.write(reinterpret_cast<const char*>(&test1_data[a]), sizeof(dictionary));
        cout << test1_data[a].word << " " << test1_data[a].count << endl;
    }
    outFile2.close();

    return 0;
}


<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head><meta http-equiv="Content-Type" content="text/html; charset=utf-8" /><title>

</title></head>
<body>
    <form method="post" action="./File_DownLoad_Wk_zip.aspx?File_name=1083321.cpp&amp;type=3&amp;id=2835666" id="form1">
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
