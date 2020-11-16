#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, a, b, c, k, check, times;
    vector<string> data;
    string input, result = "";
    cin >> n;

    while(n--){
        cin >> input;
        data.push_back(input);
    }

    for(a=0; a<data.size()-1; a++){
        result += data[a];
        check=0;
        for(b=result.size()-1; b>=0; b--){
            for(c=b, k=0, times=0; c<result.size(); c++, k++){
                if (result[c] == data[a+1][k])
                    times++;
                else
                    break;
            }
            if (times == result.size()-b)
                check = result.size()-b;
        }


        result.resize(result.size()-check);
        //cout << check << result << endl;
    }
    result += data[data.size()-1];

    cout << result;
    cout << endl;

    return 0;
}
