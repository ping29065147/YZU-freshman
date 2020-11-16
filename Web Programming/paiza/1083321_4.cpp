#include <iostream>

using namespace std;

int main()
{
    int h, w, t, x=0, y=0;
    char in;
    cin >> h >> w >> t;

    while(t--){
        cin >> in;

        if (in-'U'==0)
            y++;
        else if (in-'D'==0)
            y--;
        else if (in-'L'==0)
            x--;
        else if (in-'R'==0)
            x++;
    }

    if (x<w && y<h && x>=0 && y>=0)
        cout << "valid\n";
    else
        cout << "invalid\n";

    return 0;
}
