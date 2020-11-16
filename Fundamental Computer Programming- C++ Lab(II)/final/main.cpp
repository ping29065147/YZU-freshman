#include "account.h"
#include "map.h"
#include "pokemon database.h"
#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

#define battle 1
#define catch 2
#define exit_game 4
#define open_backpack 8
#define check_attribute 9

// =Sleep, delay time/1000 second(s)
void Delay(int time)
{
	clock_t now = clock();
	while (clock() - now < time);
}

int main()
{
	//control = false if login or create a new account
	bool control = true;

	account Account;
	map Map;

	while (control) {
		
		switch (Account.print_menu())
		{
		case 1:
			Map.show_cursor();
			Account.create_account();
			control = false;
			break;
		case 2:
			Map.show_cursor();
			if (Account.login())
				control = false;
			break;
		case 3:
			cout << "\n\n\t\t\t\t\tGoodbye!\n\n";
			return 0;
		}
		Delay(1000);
		system("cls");
	}

	//set the data in account to player
	Account.load_player(Account.get_account());
	//set the reference of player in map
	Map.set_player(Account.get_player());

	cout << "\n" << setw(40) << " " << "¡¹ Game explanation. ¡¹\n\n";
	for (size_t a = 0; a < 120; a++)
		cout << "=";
	cout << "\n\n" << setw(35) << " " << "¡» Use WASD to control your player\n"
		<< setw(35) << " " << "   W : go up 1 step\n"
		<< setw(35) << " " << "   S : go down 1 step\n"
		<< setw(35) << " " << "   A : go left 1 step\n"
		<< setw(35) << " " << "   D : go right 1 step\n\n"
		<< setw(35) << " " << "¡» ESC to save and leave the game.\n"
		<< setw(35) << " " << "   B to check your backpack.\n"
		<< setw(35) << " " << "   N to check attribute.\n\n"
		<< setw(35) << " " << "¡» You can pass the grasses and the lake,\n"
		<< setw(35) << " " << "   but not the walls, the buildings or the trees.\n\n"
		<< setw(35) << " " << "¡» When you move, you will randomly run into a pokemon.\n"
		<< setw(35) << " " << "   You can decide if you want to catch it or not.\n\n"
		<< setw(35) << " " << "¡» When you go into the buildings (step on #).\n"
		<< setw(35) << " " << "   You will fight with the NPC.\n"
		<< setw(35) << " " << "   After you win 7 battles, you win the game.\n\n"
		<< setw(35) << " " << "¡» Enjoy it! Wish you have a good time.\n\n";
	for (size_t a = 0; a < 120; a++)
		cout << "=";
	cout << "\n\n" << setw(35) << " ";
	system("pause");
	system("cls");

	while (1) {

		Map.print_map();
		switch (Map.move())
		{
		case battle:
			Account.battled();
			break;
		case catch:
			Account.catch_pok();
			break;
		case exit_game:
			if (Account._exit()) {
				cout << "\n\n" << setw(35) << " " << "Goodbye!\n\n";
				return 0;
			}
			break;
		case open_backpack:
			Account.backpack();
			break;
		case check_attribute:
			Account.attribute();
			break;
		}
		system("cls");
	}


	return 0;
}