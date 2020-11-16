#include <iostream>
#include <string.h>

using namespace std;

int main()
{
    char num1[11], num2[11];
    int n1[11], n2[11], a, maxlen, result;

    while(1){
        cin >> num1 >> num2;

        if (num1[0]=='0' && num2[0]=='0')
            break;

        result=0;               //初始化
        for(a=0; a<11; a++){
            n1[a]=0;
            n2[a]=0;
        }

        for(a=0; a<strlen(num1); a++)           //將char string資料轉為int
            n1[strlen(num1)-1-a] = num1[a]-'0';
        for(a=0; a<strlen(num2); a++)
            n2[strlen(num2)-1-a] = num2[a]-'0';

        if (strlen(num1) > strlen(num2))        //取得最大長度
            maxlen = strlen(num1);
        else
            maxlen = strlen(num2);

        for(a=0; a<=maxlen+1; a++){     //將兩數相加，如果>10則進位
            n1[a] += n2[a];
            while(n1[a]>=10){
                result++;
                n1[a+1]++;
                n1[a] -= 10;
            }
        }

        if (result==0)          //印出結果
            cout << "No";
        else
            cout << result;
        cout << " carry operation";
        if (result<=1)
            cout << ".\n";
        else
            cout << "s.\n";
    }

    return 0;
}


<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head><meta http-equiv="Content-Type" content="text/html; charset=utf-8" /><title>

</title></head>
<body>
    <form method="post" action="./File_DownLoad_Wk_zip.aspx?File_name=1083321.cpp&amp;type=3&amp;id=2811154" id="form1">
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
