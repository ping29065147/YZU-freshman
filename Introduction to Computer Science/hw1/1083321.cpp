#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;
vector<int> data1, data2;   //��J�s�����O�s�Jdata1,2
vector<char> result;    //�@������cycle�����G
vector<bool> check;

int finds(int n)
{
    unsigned int a;

    for(a=0; a<check.size(); a++){
        if (check[a]==false)
            break;
    }
    if (a==check.size())    //��Ҧ���Ƴ��w�ϥ� ���X
        return 0;

    //�N��쪺��Ƥ@�ӭӦs�Jresult
    for(a=0; a<data1.size(); a++){
        if (check[a]==false && data1[a]==n){
            result.push_back(n+'A');
            check[a]=true;  //�N��Ƴ]���w�ϥ�
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
    int node, side; //��J���`�I, �s��
    int a, b, maxs[2], rands, over, k=0, loop1=0, wrong=0;   //max[0]����} max[1]������
    char start;
    char x, y;
    vector<int> count, point[2], other, o, d1, d2, ct;  //other�s��h�󪺳s�����
    //point[0][0]�N��̤j��ƪ���} point[0][1]�N��̤j��ƪ����e
    //point[1][0]�N���j��ƪ���} point[1][1]�N���j��ƪ����e
    vector<char> keep[100];
    srand(time(NULL));

    cin >> node >> side >> start;

    d1.assign(side, -1);
    d2.assign(side, -1);
    ct.assign(node, 0);


    for(a=0; a<side; a++){
        cin >> x >> y;
        d1[a] = x-'A';  //�N��J���j�g�^���ର�Ʀr�s�Jd1,2(data1,2)
        d2[a] = y-'A';  //�j�g�^��H�U��: ���

        ct[x-'A']++;    //�N�C�ظ�ƥX�{�����Ʀs�Jct(count)
        if (ct[x-'A']>2)
            o.push_back(x-'A'); //�N�j���ӳs������Ʀs�Jo(other)

        ct[y-'A']++;
        if (ct[y-'A']>2)
            o.push_back(y-'A');
    }

    restart:    //���s�M��í��m�Ҧ��ܼ�

    over=0;
    count=ct;
    data1=d1;
    data2=d2;
    other = o;

    //�o��while�ΨӧR���h�l���s��
    while(1){
        over++;

        if (other.size()==0)    //��S���h�l���s���ɸ��X
            break;

        point[0].assign(2, 0);
        point[1].assign(2, 0);
        check.assign(node, false);  //check�Ω��ˬd��ƬO�_�Q�ϥιL

        //��X�̤j���
        rands=rand()%node;  //���N�H���@�ո�Ʀs�J
        maxs[0] = rands;    //��}
        maxs[1] = count[rands]; //����
        for(a=0; a<node; a++){
            //��즸�Ƴ̦h����� �s�Jmaxs
            if (count[a]>maxs[1] && check[a]==false && count[a]>2){
                maxs[0] = a;    //�O����}
                maxs[1] = count[a]; //�O������
            }
        }
        check[maxs[0]]=true;    //�N����Ʃw�q���w�ϥ�
        while(1){
            point[0][0] = rand()%other.size();
            point[0][1] = other[point[0][0]];

            if (point[0][1]==maxs[0])   //���maxs��Ʀs��other����}
                break;
        }

        //��X���j���
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

        //�p�G�R�������, �|���J�L�a�j��, ���^��_�I���s�M��
        if (over>5000){
            wrong++;
            result.clear();
            goto restart;
        }
        //�p�G�R���W�L100�� �h�P�_���L��
        if (wrong>100){
            cout << "Not a hamiltonian circuit.\n";
            goto last;
        }

        //�P�_maxs���̤j�P���j��ƬO�_�k�Xdata1,2
        for(a=0; (unsigned)a<data1.size(); a++){
            if ( (point[0][1]==data1[a]&&point[1][1]==data2[a]) || (point[1][1]==data1[a]&&point[0][1]==data2[a]) ){

                //�N�h�l���s���R��
                data1.erase(data1.begin()+a);
                data2.erase(data2.begin()+a);

                //�N�s����-1 (�̲שҦ��s�����Ӭ�2)
                for(b=0; b<node; b++){
                    if (other[point[0][0]]==b || other[point[1][0]]==b){
                        count[b]--;
                    }
                }

                //�N�h�l���s���R��
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

    //���ɸ�Ƥw�ܦ��@�Ӱ��b��cycle
    check.assign(node, false);
    result.push_back(start);

    //�qstart�}�l��M�s����̫�
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

    //�p�Gresult��Ʀ��~ ���s�M��
    if (result.size()!=node+1){
        result.clear();
        goto restart;
    }

    for(a=0; a<k; a++){
        if (loop1>=10){
            loop1=0;
            goto last;
        }
        if (keep[a]==result){   //�P�_��result�O�_�w��X�L
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

    //�N�H���\��X��result�s�Jkeep
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
