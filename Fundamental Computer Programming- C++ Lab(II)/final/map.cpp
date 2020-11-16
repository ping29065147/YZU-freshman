#include "map.h"
#include "player.h"
#include "rlutil.h"
#include <fstream>
#include <iostream>
#include <time.h>
using namespace std;

#define obstacle 0
#define battle 1
#define catch 2
#define available 3
#define exit_game 4
#define grass 5
#define water 6
#define normal 7
#define open_backpack 8
#define check_attribute 9

map::map()
{
	load();
	rlutil::hidecursor();
}

void map::set_player(player& Mp)
{
	myplayer = &Mp;
	x = myplayer->getx();
	y = myplayer->gety();
}

void map::load()
{
	map_type temp;
	ifstream inFile("termproj\\assets\\yzumap.txt", ios::in);
	while (getline(inFile, temp.map_data))
		yzumap.push_back(temp);
	for (size_t a = 0; a < yzumap.size(); a++) {
		for (size_t b = 0; b < yzumap[a].map_data.size(); b++) {
			if (yzumap[a].map_data[b] == ';')
				yzumap[a].map_color.push_back(10);
			else if (yzumap[a].map_data[b] == '!')
				yzumap[a].map_color.push_back(6);
			else if (yzumap[a].map_data[b] == '~')
				yzumap[a].map_color.push_back(11);
			else if (yzumap[a].map_data[b] == '#')
				yzumap[a].map_color.push_back(14);
			else if (yzumap[a].map_data[b] == '*')
				yzumap[a].map_color.push_back(12);
			else
				yzumap[a].map_color.push_back(7);
		}
	}
	inFile.close();
}

void map::print_map()
{
	int temp = 0;

	system("mode con:lines=35 cols=120");
	system("color 0F");

	rlutil::hidecursor();
	for (size_t a = 0; a < yzumap.size(); a++){
		for (size_t b = 0; b < yzumap[a].map_data.size(); b++){
			if (temp != yzumap[a].map_color[b]){
				rlutil::setColor(yzumap[a].map_color[b]);
				temp = yzumap[a].map_color[b];
			}
			cout << yzumap[a].map_data[b];
		}
		cout << endl;
	}
	origin._ch = yzumap[y - 1].map_data[x - 1];
	origin._color = yzumap[y - 1].map_color[x - 1];
	rlutil::locate(x, y);
	rlutil::setColor(13);
	cout << "@";
	rlutil::setColor(7);
}

int map::move()
{
	char ch;
	int choice;
	srand((unsigned)time(NULL));

	while (1) {
		ch = _getch();
		rlutil::setColor(origin._color);
		rlutil::locate(x, y);
		cout << origin._ch;
		rlutil::setColor(7);

		choice = determine(ch);
		if (choice == battle || choice == catch || choice == exit_game || choice == open_backpack || choice == check_attribute)
			return choice;
	}
}

int map::determine(char ch)
{
	int temp = 3;

	if (ch == 'w' || ch == 'W') {
		y--;
		if ((temp = encounter()) == 0)
			y++;
	}
	else if (ch == 'a' || ch == 'A') {
		x--;
		if ((temp = encounter()) == 0)
			x++;
	}
	else if (ch == 's' || ch == 'S') {
		y++;
		if ((temp = encounter()) == 0)
			y--;
	}
	else if (ch == 'd' || ch == 'D') {
		x++;
		if ((temp = encounter()) == 0)
			x--;
	}
	else if (ch == 27) {
		myplayer->setxy(x, y);
		return exit_game;
	}
	else if (ch == 'b' || ch == 'B')
		return open_backpack;
	else if (ch == 'n' || ch == 'N')
		return check_attribute;

	origin._ch = yzumap[y - 1].map_data[x - 1];
	origin._color = yzumap[y - 1].map_color[x - 1];
	rlutil::locate(x, y);
	rlutil::setColor(13);
	cout << "@";
	rlutil::setColor(7);

	return temp;
}

int map::encounter()
{
	if (yzumap[y - 1].map_data[x - 1] == ' ' || yzumap[y - 1].map_data[x - 1] == ';' || yzumap[y - 1].map_data[x - 1] == '~') {
		if (rand() % 10 == 1) {
			if (yzumap[y - 1].map_data[x - 1] == ';')
				myplayer->set_topography(grass);
			else if (yzumap[y - 1].map_data[x - 1] == '~')
				myplayer->set_topography(water);
			else
				myplayer->set_topography(normal);
			return catch;
		}	
		return available;
	}
	else if (yzumap[y - 1].map_data[x - 1] == '#') {
		myplayer->setxy(x, y);
		return battle;
	}
	else
		return obstacle;

}

void map::show_cursor()
{
	rlutil::showcursor();
}