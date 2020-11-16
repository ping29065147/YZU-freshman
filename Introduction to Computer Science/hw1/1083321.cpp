#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;
vector<int> data1, data2;   //輸入連結分別存入data1,2
vector<char> result;    //一次完整cycle的結果
vector<bool> check;

int finds(int n)
{
    unsigned int a;

    for(a=0; a<check.size(); a++){
        if (check[a]==false)
            break;
    }
    if (a==check.size())    //當所有資料都已使用 跳出
        return 0;

    //將找到的資料一個個存入result
    for(a=0; a<data1.size(); a++){
        if (check[a]==false && data1[a]==n){
            result.push_back(n+'A');
            check[a]=true;  //將資料設為已使用
            return finds(data2[a]);
        }
        else if (check[a]==false && data2[a]==n){
            result.push_back(n+'A');
            check[a]=true;
            return finds(data1[a]);
        }
    }
    return 0;
}

int main()
{
    int node, side; //輸入之節點, 連結
    int a, b, maxs[2], rands, over, k=0, loop1=0, wrong=0;   //max[0]為位址 max[1]為次數
    char start;
    char x, y;
    vector<int> count, point[2], other, o, d1, d2, ct;  //other存放多於的連結資料
    //point[0][0]代表最大資料的位址 point[0][1]代表最大資料的內容
    //point[1][0]代表次大資料的位址 point[1][1]代表次大資料的內容
    vector<char> keep[100];
    srand(time(NULL));

    cin >> node >> side >> start;

    d1.assign(side, -1);
    d2.assign(side, -1);
    ct.assign(node, 0);


    for(a=0; a<side; a++){
        cin >> x >> y;
        d1[a] = x-'A';  //將輸入之大寫英文轉為數字存入d1,2(data1,2)
        d2[a] = y-'A';  //大寫英文以下稱: 資料

        ct[x-'A']++;    //將每種資料出現之次數存入ct(count)
        if (ct[x-'A']>2)
            o.push_back(x-'A'); //將大於兩個連結之資料存入o(other)

        ct[y-'A']++;
        if (ct[y-'A']>2)
            o.push_back(y-'A');
    }

    restart:    //重新尋找並重置所有變數

    over=0;
    count=ct;
    data1=d1;
    data2=d2;
    other = o;

    //這個while用來刪除多餘的連結
    while(1){
        over++;

        if (other.size()==0)    //當沒有多餘的連結時跳出
            break;

        point[0].assign(2, 0);
        point[1].assign(2, 0);
        check.assign(node, false);  //check用於檢查資料是否被使用過

        //找出最大資料
        rands=rand()%node;  //先將隨機一組資料存入
        maxs[0] = rands;    //位址
        maxs[1] = count[rands]; //次數
        for(a=0; a<node; a++){
            //找到次數最多的資料 存入maxs
            if (count[a]>maxs[1] && check[a]==false && count[a]>2){
                maxs[0] = a;    //記錄位址
                maxs[1] = count[a]; //記錄次數
            }
        }
        check[maxs[0]]=true;    //將此資料定義為已使用
        while(1){
            point[0][0] = rand()%other.size();
            point[0][1] = other[point[0][0]];

            if (point[0][1]==maxs[0])   //找到maxs資料存於other的位址
                break;
        }

        //找出次大資料
        rands=rand()%node;
        maxs[0] = rands;
        maxs[1] = count[rands];
        for(a=0; a<node; a++){
            if (count[a]>maxs[1] && check[a]==false && count[a]>2){
                maxs[0] = a;
                maxs[1] = count[a];
            }
        }
        while(1){
            point[1][0] = rand()%other.size();
            point[1][1] = other[point[1][0]];

            if (point[1][1]==maxs[0])
                break;
        }

        //如果刪除錯資料, 會陷入無窮迴圈, 跳回到起點重新尋找
        if (over>5000){
            wrong++;
            result.clear();
            goto restart;
        }
        //如果刪錯超過100次 則判斷為無解
        if (wrong>100){
            cout << "Not a hamiltonian circuit.\n";
            goto last;
        }

        //判斷maxs中最大與次大資料是否吻合data1,2
        for(a=0; (unsigned)a<data1.size(); a++){
            if ( (point[0][1]==data1[a]&&point[1][1]==data2[a]) || (point[1][1]==data1[a]&&point[0][1]==data2[a]) ){

                //將多餘的連結刪除
                data1.erase(data1.begin()+a);
                data2.erase(data2.begin()+a);

                //將連結數-1 (最終所有連結應該為2)
                for(b=0; b<node; b++){
                    if (other[point[0][0]]==b || other[point[1][0]]==b){
                        count[b]--;
                    }
                }

                //將多餘的連結刪除
                if (point[0][0]>point[1][0]){
                    other.erase(other.begin()+point[0][0]);
                    other.erase(other.begin()+point[1][0]);
                }
                else{
                    other.erase(other.begin()+point[1][0]);
                    other.erase(other.begin()+point[0][0]);
                }

                break;
            }
        }
    }

    //此時資料已變成一個乾淨的cycle
    check.assign(node, false);
    result.push_back(start);

    //從start開始找尋連結到最後
    for(a=0; a<node; a++){
        if (start-'A'==data1[a]){
            check[a]=true;
            finds(data2[a]);
            break;
        }
        else if (start-'A'==data2[a]){
            check[a]=true;
            finds(data1[a]);
            break;
        }
    }
    result.push_back(start);

    //如果result資料有誤 重新尋找
    if (result.size()!=node+1){
        result.clear();
        goto restart;
    }

    for(a=0; a<k; a++){
        if (loop1>=10){
            loop1=0;
            goto last;
        }
        if (keep[a]==result){   //判斷此result是否已輸出過
            result.clear();
            loop1++;
            goto restart;
        }
    }

    for(a=0; (unsigned)a<result.size(); a++)
        cout << result[a];
    cout << endl;
    for(a=result.size()-1; a>=0; a--)
        cout << result[a];
    cout << endl;

    //將以成功輸出的result存入keep
    keep[k]=result;
    k++;
    result.clear();
    goto restart;

    last:
    return 0;
}
/*case 6 O
7 9 E
A F
D F
E D
E A
E G
C D
B C
B A
G D
*/

/*case5 O
4 6 A
A B
A C
D A
B D
D C
C B
*/

/*case4 O
7 11 D
B A
D E
D C
B C
F G
G A
E F
A E
F C
G C
F D
*/

/*case3 O
6 9 A
A B
A C
B C
B D
C D
C E
E D
E F
D F
*/

/*case2 O
5 7 A
A B
C B
D C
D E
A D
D B
A E
*/

/*case1 O
4 5 A
A B
D B
A D
A C
D C
*/


<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head><meta http-equiv="Content-Type" content="text/html; charset=utf-8" /><title>

</title></head>
<body>
    <form method="post" action="./File_DownLoad_Wk_zip.aspx?File_name=1083321.cpp&amp;type=3&amp;id=2788176" id="form1">
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
