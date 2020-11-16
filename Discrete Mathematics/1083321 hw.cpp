#include <iostream>
#include <vector>

using namespace std;

vector<bool> result;
int a, b, i1, i2;
int node, edge;
vector< vector<int> > datas;
vector<bool> check;

bool all_check()
{
    for(a=0; a<node; a++){
        if (check[a] == false)
            return false;
    }

    return true;
}

void dfs(int n)
{
    if (all_check())
        return;

    for(int a=0; a<edge; a++){
        for(int b=0; b<2; b++){
            if (check[ datas[a][(b+1)%2] ] == false && n == datas[a][b]){
                check[ datas[a][(b+1)%2] ] = true;
                dfs( datas[a][(b+1)%2] );
            }
        }
    }

}

int main()
{
    int t;
    cin >> t;

    while(t--){
        cin >> node >> edge;
        datas.clear();

        for(a=0; a<edge; a++){
            cin >> i1 >> i2;
            vector<int> temp;
            temp.push_back(i1);
            temp.push_back(i2);
            datas.push_back(temp);
        }

        check.assign(node, false);
        check[ datas[0][0] ] = true;

        dfs(datas[0][0]);

        if (all_check())
            result.push_back(true);
        else
            result.push_back(false);

    }

    for(a=0; a<result.size(); a++){
        if (!result[a])
            cout << "dis";
        cout << "connected\n";
    }

    return 0;
}

/*
3
3
2
0 1
2 0
4
3
0 3
2 3
2 0
4
5
0 3
2 3
2 0
1 3
2 1
*/


<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head><meta http-equiv="Content-Type" content="text/html; charset=utf-8" /><title>

</title></head>
<body>
    <form method="post" action="./File_DownLoad_Wk_zip.aspx?File_name=1083321+hw.cpp&amp;type=3&amp;id=2927801" id="form1">
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
