// count.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"

// TODO: This is an example of a library function
#include "count.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <iomanip>

using namespace std;
#define MAXWORDLENGTH 255

struct dictionary {
	char word[MAXWORDLENGTH];
	unsigned int count;
};

bool change(dictionary a, dictionary b)
{
	return a.count > b.count;
}

void getresult()
{

	ifstream test1("IHaveADream.txt", ios::in);
	if (!test1) cout << "no test1.txt";

	dictionary input_test1;
	input_test1.count = 1;
	vector<dictionary> test1_data;
	int a, b, c;

	while (test1 >> input_test1.word)        //讀檔
		test1_data.push_back(input_test1);
	test1.close();

	for (a = 0; a < test1_data.size(); a++) {
		for (b = 0; b < strlen(test1_data[a].word); b++) {
			if (test1_data[a].word[b] >= 'A' && test1_data[a].word[b] <= 'Z')   //將大寫轉小寫
				test1_data[a].word[b] += 32;

			if ((test1_data[a].word[b]>='0' && test1_data[a].word[b] <= '9') || (!(test1_data[a].word[b]>='a' && test1_data[a].word[b] <= 'z') )) {   //將非字母去除
				if (b == strlen(test1_data[a].word) - 1)
					test1_data[a].word[b] = '\0';
				else {
					for (c = b; c < strlen(test1_data[a].word); c++)
						test1_data[a].word[c] = test1_data[a].word[c + 1];
					test1_data[a].word[c - 1] = '\0';
				}
				b--;
			}
		}
	}





	for (a = 0; a < test1_data.size() - 1; a++) {
		for (b = a + 1; b < test1_data.size(); b++) {
			if (!strcmp(test1_data[a].word, test1_data[b].word)) {   //將重複字串刪除
				test1_data[a].count += test1_data[b].count;
				test1_data.erase(test1_data.begin() + b);
				b--;
			}
			
		}
	}

	sort(test1_data.begin(), test1_data.end(), change);

	for (a = 0; a < test1_data.size(); a++)	//印出結果
		cout << setw(7) << test1_data[a].count << " " << test1_data[a].word << endl;
}

