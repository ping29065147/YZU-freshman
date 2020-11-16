#include <iostream>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

struct data{
    int num;
    int point;
    int w;
    int d;
    int l;
};

int main()
{
    int t, a, b, count=1;
    cin >> t;

    vector<data> result;
    string input;
    data in, max;

    for(a=0; a<t; a++){
        cin >> input;

        in.num = count;
        count++;
        in.point=0;
        in.w=0;
        in.d=0;
        in.l=0;

        for(b=0; b<input.size(); b++){
            if (input[b] == 'W'){
                in.point += 2;
                in.w++;
            }
            else if (input[b] == 'D'){
                in.point += 1;
                in.d++;
            }
            else if (input[b] == 'L')
                in.l++;
        }
        result.push_back(in);
    }

    max.point=0;
    for(a=0; a<result.size(); a++){
        if (result[a].point > max.point)
            max = result[a];
    }

    cout << max.num << " " << max.point << " " << max.w << " " << max.d << " " << max.l << endl;

    return 0;
}
