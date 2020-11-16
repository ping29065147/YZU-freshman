#include "player.h"
#include "rlutil.h"
#include "Windows.h"
#include <iostream>
#include <iomanip>
using namespace std;
#define grass 5
#define water 6
#define normal 7
#define heal_ 1

extern string pokemon_types[19];

//to change background color
void FlashConsoleBackgroundColor(int cntFlashes, int flashInterval_ms, COLORREF color)
{

	CONSOLE_SCREEN_BUFFER_INFOEX sbInfoEx;
	sbInfoEx.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	
	HANDLE consoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(consoleOut, &sbInfoEx);

	COLORREF storedBG = sbInfoEx.ColorTable[0];

	for (int i = 0; i < cntFlashes; ++i)
	{
		//-- set BG color
		Sleep(flashInterval_ms);
		sbInfoEx.ColorTable[0] = color;
		SetConsoleScreenBufferInfoEx(consoleOut, &sbInfoEx);

		//-- restore previous color
		Sleep(flashInterval_ms);
		sbInfoEx.ColorTable[0] = storedBG;
		SetConsoleScreenBufferInfoEx(consoleOut, &sbInfoEx);
	}
}

void space_()
{
	char y;
	while (1) {
		y = _getch();
		if (y == ' ')
			break;
	}
}

player::player()
	:x(20), y(29), topography(normal)
{
	set_NPC(3, 6, 9, 10, 11);
	set_NPC(24, 25, 26, 18, 7);
	set_NPC(29, 31, 32, 14, 18);
	set_NPC(1, 4, 7, 31, 15);
	set_NPC(2, 11, 14, 35, 7);
	set_NPC(5, 8, 10, 41, 14);
	set_NPC(11, 13, 12, 75, 4);
	set_NPC(30, 27, 28, 76, 7);
	set_NPC(18, 20, 22, 76, 9);
	set_NPC(15, 16, 24, 77, 12);
	set_NPC(23, 19, 14, 84, 7);
	set_NPC(21, 15, 17, 86, 10);
}

int player::getx()
{
	return x;
}

int player::gety()
{
	return y;
}

int player::get_topography()
{
	return topography;
}

vector<int> player::get_mypokemons()
{
	return mypokemons;
}

size_t player::get_mypokemons_size()
{
	return mypokemons.size();
}

int player::get_npc_n()
{
	for (size_t a = 0; a < NPC.size(); a++) {
		if (NPC[a]._x == getx() && NPC[a]._y == gety())
			return a;
	}
}

bool* player::get_victory()
{
	return victory;
}

int player::get_victory_times()
{
	int times = 0;

	for (size_t a = 0; a < 12; a++)
		if (victory[a] == true)
			times++;

	return times;
}

void player::setxy(int X, int Y)
{
	x = X;
	y = Y;
}

void player::set_topography(int topo)
{
	topography = topo;
}

void player::set_my_pok(int* my_pok)
{
	for (size_t a = 0; a < 3; a++) // make the size right
		if (my_pok[a] != 0)
			mypokemons.push_back(my_pok[a]);
		else
			break;
}

void player::set_victory(bool* vic)
{
	for (size_t a = 0; a < 12; a++)
		victory[a] = vic[a];
}

void player::catch_pokemon()
{
	int target = 0;

	//determine target pokemon
	switch (topography)
	{
	case normal:
		target = rand() % 32 + 1;
		break;
	case grass:
		if (rand() % 10 < 4)
			target = rand() % 3 + 1;
		else
			target = rand() % 29 + 4;
		break;
	case water:
		if (rand() % 10 < 4)
			target = rand() % 3 + 7;
		else {
			target = rand() % 29 + 1;
			if (target >= 7)
				target += 3;
		}
		break;
	}

	system("cls");
	Pokemon_database.print_catch(target);

	rlutil::locate(1, 25);
	for (size_t a = 0; a < 120; a++)
		cout << "=";
	rlutil::locate(15, 27);
	cout << "My pokemons:";
	size_t MaxPok = (mypokemons.size() > 3) ? 3 : mypokemons.size();
	if (MaxPok == 0)
		cout << "\tNone\n";
	for (size_t a = 0; a < MaxPok; a++) {
		if (mypokemons[a] != 0) {
			rlutil::locate(35, 27+a);
			cout << "No." << setw(2) << Pokemon_database.get_no(mypokemons[a])
				<< "   Name: " << setw(12) << Pokemon_database.get_name(mypokemons[a])
				<< "   Type: " << setw(10) << Pokemon_database.get_type(mypokemons[a]);
		}
	}
	cout << "\n\n";
	for (size_t a = 0; a < 120; a++)
		cout << "=";

	string yesno[2] = { " Yes  / [No]", "[Yes] /  No " };
	int control = 0;
	char ch, c;
	while (1) {
		cout << "\r";
		cout.flush();
		rlutil::locate(25, 33);
		cout << "It's " << Pokemon_database.get_name(target) << " !!!\tDo you want to catch it or not? ";
		cout << yesno[control];
		ch = _getch();
		if (ch == -32) {
			c = _getch();
			if (c == 75 || c == 77)
				control++;
			if (control == 2)
				control = 0;
		}
		else if (ch == '\r')
			break;
	}

	if (control == 0)
		return;

	FlashConsoleBackgroundColor(10, 50, RGB(0, 60, 160));
	FlashConsoleBackgroundColor(12, 50, RGB(0, 160, 60));
	if (rand() % 2) { // failed
		FlashConsoleBackgroundColor(14, 50, RGB(255, 0, 0));
		FlashConsoleBackgroundColor(1, 1, RGB(10, 10, 10));
		system("cls");
		cout << "\n" << setw(40) << " " << "Pokemon had escaped!!!\n\n";
		Sleep(1000);
		return;
	}
	else { // successed
		FlashConsoleBackgroundColor(14, 50, RGB(255, 255, 255));
		system("cls");
		system("mode con:lines=35");
		system("color 0F");
		FlashConsoleBackgroundColor(1, 1, RGB(10, 10, 10));

		if (mypokemons.size() < 3) {
			cout << "\n\n" << setw(40) << " " << "You have caught " << Pokemon_database.get_name(target) << "!!!\n\n";
			mypokemons.push_back(target);
		}
		else {
			for (size_t a = 0; a < 120; a++)
				cout << "=";
			cout << "\n\n";
			cout << setw(15) << " " << "My pokemons:\n\n";
			for (size_t a = 0; a < MaxPok; a++) {
				if (mypokemons[a] != 0) {
					cout << setw(25) << " " << "No." << setw(2) << Pokemon_database.get_no(mypokemons[a])
						<< " " << "   Name: " << setw(12) << Pokemon_database.get_name(mypokemons[a])
						<< " " << "   Type: " << setw(10) << Pokemon_database.get_type(mypokemons[a]) << endl;
				}
			}
			cout << setw(25) << " " << "x" << endl;
			cout << endl;
			for (size_t a = 0; a < 120; a++)
				cout << "=";
			cout << "\n\n" << setw(40) << " " << "You have caught " << Pokemon_database.get_name(target) << "!!!\n\n";
		
			int located = 5;
			if (mypokemons.size() >= 3) { // edit pok code
				cout << setw(25) << " " << "But your pokemon bag is full. Choose one pokemon to exchange";
				while (1) {
					rlutil::locate(22, located);
					cout << "->";
					ch = _getch();
					cout << "\b\b" << "  ";
					if (ch == -32) {
						c = _getch();
						if (c == 72)
							located--;
						else if (c == 80)
							located++;
						if (located == 4)
							located = 8;
						else if (located == 9)
							located = 5;
					}
					else if (ch == '\r')
						break;
				}
				if (located != 8) {
					auto it = mypokemons.begin() + (located - 5);
					*it = target;
				}
			}
		}	
	}

	Sleep(1000);

	print_backpack();
}

void player::print_backpack()
{
	system("cls");

	cout << "\n" << setw(40) << " " << "My backpack\n\n";
	for (size_t a = 0; a < 120; a++)
		cout << "=";

	cout << "\n\n" << setw(25) << " " << "My pokemon\n\n";
	size_t MaxPok = (mypokemons.size() > 3) ? 3 : mypokemons.size();
	if (MaxPok == 0)
		cout << "\tNone\n";
	for (size_t a = 0; a < MaxPok; a++) {
		if (mypokemons[a] != 0) {
			cout << setw(40) << " " << "No." << setw(2) << Pokemon_database.get_no(mypokemons[a])
				<< "   Name: " << setw(12) << Pokemon_database.get_name(mypokemons[a])
				<< "   Type: " << setw(10) << Pokemon_database.get_type(mypokemons[a]) << endl;
		}
	}
	
	cout << "\n\n";
	for (size_t a = 0; a < 120; a++)
		cout << "=";

	cout << "\n\n" << setw(25) << " " << "My items\n\n";

	cout << setw(40) << " " << "Gym Badge * ";
	int n = 0;
	for (size_t a = 0; a < 12; a++)
		if (victory[a] == true)
			n++;
	cout << n << "\n\n";

	cout << "\n\n";
	for (size_t a = 0; a < 120; a++)
		cout << "=";

	cout << "\n\n" << setw(40) << " ";
	system("pause");
}

void player::print_atb()
{
	Pokemon_database.print_attribute();
}

void player::set_NPC(int p1, int p2, int p3, int x, int y)
{
	NPC_data temp;

	temp.poks.push_back(p1);
	temp.poks.push_back(p2);
	temp.poks.push_back(p3);
	temp._x = x;
	temp._y = y;
	NPC.push_back(temp);
}

void player::battle()
{
	system("cls");

	//return if pokemons < 3 or you had already win the battle
	size_t MaxPok = (mypokemons.size() > 3) ? 3 : mypokemons.size();
	if (MaxPok != 3) {
		cout << "\n" << setw(40) << " " << "You need 3 pokemons to participate in battle!!!\n\n";
		Sleep(1000);
		return;
	}
	else if (victory[get_npc_n()] == true) {
		cout << "\n" << setw(40) << " " << "You had already win the battle!!!\n\n";
		Sleep(1000);
		return;
	}

	int npc_count = 0;  //npc current pokemon
	bool alive[3] = { true, true, true }; //if player's pokemon alive or not
	lists.clear();

	while (1) {

		// return if all nps's pokemon were dead, you win
		if (npc_count == 3) {
			system("cls");
			cout << "\n" << setw(40) << " " << "々 You win the battle! 々\n\n";
			cout << setw(40) << " ";
			victory[get_npc_n()] = true;
			system("pause");
			if (get_victory_times() >= 7) {
				system("cls");
				cout << "\n" << setw(40) << " " << "々 Congratulation! You have dominate yzu! 々\n\n";
				cout << setw(40) << " ";
				system("pause");
			}
			return;
		}
		// return if all your pokemon were dead, you lose
		if (alive[0] == false && alive[1] == false && alive[2] == false) {
			system("cls");
			cout << "\n" << setw(40) << " " << "You lose the battle!\n\n";
			cout << setw(40) << " ";
			system("pause");
			return;
		}

		int alive_num = 0, located = 8, top = 8;
		char ch, c;

		//set battle data
		if (lists.size() == 0)
			set_battle_data();

		//print out pokemon that you have
		cout << "\n" << setw(40) << " " << "Choose one pokemon to play\n\n";
		for (size_t a = 0; a < 120; a++)
			cout << "=";
		cout << "\n\n" << setw(25) << " " << "My pokemons\n\n";
		for (size_t a = 0; a < MaxPok; a++) {
			if (mypokemons[a] != 0 && alive[a] == true) {
				cout << setw(40) << " " << "No." << setw(2) << Pokemon_database.get_no(mypokemons[a])
					<< "   Name: " << setw(12) << Pokemon_database.get_name(mypokemons[a])
					<< "   Type: " << setw(10) << Pokemon_database.get_type(mypokemons[a]) << endl;
			}
		}
		cout << "\n\n";
		for (size_t a = 0; a < 120; a++)
			cout << "=";

		//set the alive number
		for (size_t a = 0; a < 3; a++)
			if (alive[a])
				alive_num++;
		
		// choose a pokemon using -> by up and down
		while (1) {
			rlutil::locate(37, located);
			cout << "->";
			ch = _getch();
			cout << "\b\b" << "  ";
			if (ch == -32) {
				c = _getch();
				if (c == 72)
					located--;
				else if (c == 80)
					located++;
				if (located == top-1)
					located += alive_num;
				else if (located == top + alive_num)
					located = top;
			}
			else if (ch == '\r')
				break;
		}
		for (size_t a = 0; a <= located - 8 && a < 3; a++) {
			if (alive[a] == false)
				located++;
		}

		//set player's current pokemon
		heal pok_heal(Pokemon_database.get_pokemon(mypokemons[located - 8]));
		burning pok_burning(Pokemon_database.get_pokemon(mypokemons[located - 8]));
		counter_attack pok_counter_attack(Pokemon_database.get_pokemon(mypokemons[located - 8]));
		immunology pok_immunology(Pokemon_database.get_pokemon(mypokemons[located - 8]));
		leech_life pok_leech_life(Pokemon_database.get_pokemon(mypokemons[located - 8]));
		avoid pok_avoid(Pokemon_database.get_pokemon(mypokemons[located - 8]));
		normal_p pok_normal(Pokemon_database.get_pokemon(mypokemons[located - 8]));
		double_attack pok_double_attack(Pokemon_database.get_pokemon(mypokemons[located - 8]));
		poison pok_poison(Pokemon_database.get_pokemon(mypokemons[located - 8]));
		lower_speed pok_lower_speed(Pokemon_database.get_pokemon(mypokemons[located - 8]));
		rock_skin pok_rock_skin(Pokemon_database.get_pokemon(mypokemons[located - 8]));
		lower_defence pok_lower_defence(Pokemon_database.get_pokemon(mypokemons[located - 8]));
		lower_attack pok_lower_attack(Pokemon_database.get_pokemon(mypokemons[located - 8]));
		if (mypokemons[located - 8] <= 3)
			current_pok = &pok_heal;
		else if (mypokemons[located - 8] <= 6)
			current_pok = &pok_burning;
		else if (mypokemons[located - 8] <= 9)
			current_pok = &pok_counter_attack;
		else if (mypokemons[located - 8] <= 12)
			current_pok = &pok_immunology;
		else if (mypokemons[located - 8] <= 15)
			current_pok = &pok_leech_life;
		else if (mypokemons[located - 8] <= 18)
			current_pok = &pok_avoid;
		else if (mypokemons[located - 8] <= 20)
			current_pok = &pok_normal;
		else if (mypokemons[located - 8] <= 22)
			current_pok = &pok_double_attack;
		else if (mypokemons[located - 8] <= 24)
			current_pok = &pok_poison;
		else if (mypokemons[located - 8] <= 26)
			current_pok = &pok_lower_speed;
		else if (mypokemons[located - 8] <= 28)
			current_pok = &pok_rock_skin;
		else if (mypokemons[located - 8] <= 31)
			current_pok = &pok_lower_defence;
		else if (mypokemons[located - 8] <= 32)
			current_pok = &pok_lower_attack;

		//set npc's current pokemon
		current_npc = NPC[get_npc_n()];
		heal npc_heal(Pokemon_database.get_pokemon(current_npc.poks[npc_count]));
		burning npc_burning(Pokemon_database.get_pokemon(current_npc.poks[npc_count]));
		counter_attack npc_counter_attack(Pokemon_database.get_pokemon(current_npc.poks[npc_count]));
		immunology npc_immunology(Pokemon_database.get_pokemon(current_npc.poks[npc_count]));
		leech_life npc_leech_life(Pokemon_database.get_pokemon(current_npc.poks[npc_count]));
		avoid npc_avoid(Pokemon_database.get_pokemon(current_npc.poks[npc_count]));
		normal_p npc_normal(Pokemon_database.get_pokemon(current_npc.poks[npc_count]));
		double_attack npc_double_attack(Pokemon_database.get_pokemon(current_npc.poks[npc_count]));
		poison npc_poison(Pokemon_database.get_pokemon(current_npc.poks[npc_count]));
		lower_speed npc_lower_speed(Pokemon_database.get_pokemon(current_npc.poks[npc_count]));
		rock_skin npc_rock_skin(Pokemon_database.get_pokemon(current_npc.poks[npc_count]));
		lower_defence npc_lower_defence(Pokemon_database.get_pokemon(current_npc.poks[npc_count]));
		lower_attack npc_lower_attack(Pokemon_database.get_pokemon(current_npc.poks[npc_count]));
		if (current_npc.poks[npc_count] <= 3)
			npc_pok = &npc_heal;
		else if (current_npc.poks[npc_count] <= 6)
			npc_pok = &npc_burning;
		else if (current_npc.poks[npc_count] <= 9)
			npc_pok = &npc_counter_attack;
		else if (current_npc.poks[npc_count] <= 12)
			npc_pok = &npc_immunology;
		else if (current_npc.poks[npc_count] <= 15)
			npc_pok = &npc_leech_life;
		else if (current_npc.poks[npc_count] <= 18)
			npc_pok = &npc_avoid;
		else if (current_npc.poks[npc_count] <= 20)
			npc_pok = &npc_normal;
		else if (current_npc.poks[npc_count] <= 22)
			npc_pok = &npc_double_attack;
		else if (current_npc.poks[npc_count] <= 24)
			npc_pok = &npc_poison;
		else if (current_npc.poks[npc_count] <= 26)
			npc_pok = &npc_lower_speed;
		else if (current_npc.poks[npc_count] <= 28)
			npc_pok = &npc_rock_skin;
		else if (current_npc.poks[npc_count] <= 31)
			npc_pok = &npc_lower_defence;
		else if (current_npc.poks[npc_count] <= 32)
			npc_pok = &npc_lower_attack;

		set_damage_rate(mypokemons[located - 8], current_npc.poks[npc_count]);
		Pokemon_database.print_battle(mypokemons[located - 8], current_npc.poks[npc_count], mypokemons, current_npc.poks, alive, npc_count);
		
		if (lists[located - 8].hp != -1)
			 current_pok->set_player_last(lists[located - 8].hp, lists[located - 8].atk, lists[located - 8].def, lists[located - 8].spd, lists[located - 8].special);
		if (lists[npc_count + 3].hp != -1)
			npc_pok->set_npc_last(lists[npc_count + 3].hp, lists[npc_count + 3].atk, lists[npc_count + 3].def, lists[npc_count + 3].spd, lists[npc_count + 3].special);
		current_pok->p_show();
		npc_pok->n_show();

		rlutil::locate(50, 45);
		cout << "Battle start!!\n!";
		space_();

		//break if one pokemon died
		while (1) {
			if (current_pok->getSpeed() >= npc_pok->getSpeed()) {  //player attack first

				clean_line(45);
				old_hp = npc_pok->getHP();
				current_pok->attack(*npc_pok, damage_rate_player);
				rlutil::locate(1, 45);
				cout << "Damage rate: " << damage_rate_player;
				rlutil::locate(25, 45);
				cout << "Your " << Pokemon_database.get_name(mypokemons[located - 8]) << " attack " << Pokemon_database.get_name(current_npc.poks[npc_count])
					<< ". " << "Cause " << setw(2) << old_hp - npc_pok->getHP() << " damages.";
				current_pok->p_show();
				npc_pok->n_show();
				if(check_hp(alive, located, npc_count, get_player_battle_data(), get_npc_battle_data()))
					break;
				space_();


				clean_line(45);
				old_hp = current_pok->getHP();
				npc_pok->attack(*current_pok, damage_rate_npc);
				rlutil::locate(1, 45);
				cout << "Damage rate: " << damage_rate_npc;
				rlutil::locate(25, 45);
				cout << Pokemon_database.get_name(current_npc.poks[npc_count]) << " attack your " << Pokemon_database.get_name(mypokemons[located - 8])
					<< ". " << "Cause " << setw(2) << old_hp - current_pok->getHP() << " damages.";
				current_pok->p_show();
				npc_pok->n_show();
				if (check_hp(alive, located, npc_count, get_player_battle_data(), get_npc_battle_data()))
					break;
				space_();


				clean_line(45);
				current_pok->special_ability(1);
				npc_pok->special_ability(2);
			}
			else {  //npc attack first

				clean_line(45);
				old_hp = current_pok->getHP();
				npc_pok->attack(*current_pok, damage_rate_npc);
				rlutil::locate(1, 45);
				cout << "Damage rate: " << damage_rate_npc;
				rlutil::locate(25, 45);
				cout <<  Pokemon_database.get_name(current_npc.poks[npc_count]) << " attack your " << Pokemon_database.get_name(mypokemons[located - 8])
					<< ". " << "Cause " << setw(2) << old_hp - current_pok->getHP() << " damages.";
				current_pok->p_show();
				npc_pok->n_show();
				if (check_hp(alive, located, npc_count, get_player_battle_data(), get_npc_battle_data()))
					break;
				space_();

			
				clean_line(45);
				old_hp = npc_pok->getHP();
				current_pok->attack(*npc_pok, damage_rate_player);
				rlutil::locate(1, 45);
				cout << "Damage rate: " << damage_rate_player;
				rlutil::locate(25, 45);
				cout << "Your " << Pokemon_database.get_name(mypokemons[located - 8]) << " attack " << Pokemon_database.get_name(current_npc.poks[npc_count])
					<< ". " << "Cause " << setw(2) << old_hp - npc_pok->getHP() << " damages.";
				current_pok->p_show();
				npc_pok->n_show();
				if (check_hp(alive, located, npc_count, get_player_battle_data(), get_npc_battle_data()))
					break;
				space_();


				npc_pok->special_ability(2);
				current_pok->special_ability(1);
			}
		}

		rlutil::locate(45, 47);
		system("pause");
		system("cls");
	}
}

void player::set_battle_data()
{
	battle_data temp;
	temp.hp = -1;
	temp.atk = -1;
	temp.def = -1;
	temp.spd = -1;
	temp.special = -1;

	for (size_t a = 0; a < 6; a++)
		lists.push_back(temp);
}

battle_data player::get_player_battle_data()
{
	battle_data temp;
	temp.hp = current_pok->getHP();
	temp.atk = current_pok->getAttack();
	temp.def = current_pok->getDefense();
	temp.spd = current_pok->getSpeed();
	temp.special = current_pok->getSpecial();

	return temp;
}

battle_data player::get_npc_battle_data()
{
	battle_data temp;
	temp.hp = npc_pok->getHP();
	temp.atk = npc_pok->getAttack();
	temp.def = npc_pok->getDefense();
	temp.spd = npc_pok->getSpeed();
	temp.special = npc_pok->getSpecial();

	return temp;
}

bool player::check_hp(bool* alive, int& located, int& npc_count, battle_data c1, battle_data c2)
{
	if (current_pok->getHP() <= 0) {
		clean_line(45);
		rlutil::locate(45, 45);
		cout << "!!!!!!!!!!" << Pokemon_database.get_name(mypokemons[located - 8]) << " died!!!!!!!!!!";
		while (!alive[located - 8])
			located++;
		alive[located - 8] = false;

		lists[npc_count + 3].hp = c2.hp;
		lists[npc_count + 3].atk = c2.atk;
		lists[npc_count + 3].def = c2.def;
		lists[npc_count + 3].spd = c2.spd;
		lists[npc_count + 3].special = c2.special;
		
		FlashConsoleBackgroundColor(20, 20, RGB(255, 0, 0));
		FlashConsoleBackgroundColor(10, 10, RGB(10, 10, 10));
		return true;
	}
	else if (npc_pok->getHP() <= 0) {
		clean_line(45);
		rlutil::locate(45, 45);
		cout << "!!!!!!!!!!" << Pokemon_database.get_name(current_npc.poks[npc_count]) << " died!!!!!!!!!!";
		npc_count++;

		lists[located - 8].hp = c1.hp;
		lists[located - 8].atk = c1.atk;
		lists[located - 8].def = c1.def;
		lists[located - 8].spd = c1.spd;
		lists[located - 8].special = c1.special;

		FlashConsoleBackgroundColor(20, 20, RGB(0, 120, 120));
		FlashConsoleBackgroundColor(10, 10, RGB(10, 10, 10));
		return true;
	}

	return false;
}

void player::clean_line(int line)
{
	rlutil::locate(1, line);
	cout << setw(120) << " ";
	rlutil::locate(1, 46);
	cout << setw(120) << " ";
}

void player::set_damage_rate(int p, int n)
{
	size_t x=1, y=1;
	for (; x <= 18; x++) {
		if (Pokemon_database.get_type(p) == pokemon_types[x])
			break;
	}
	for (; y <= 18; y++) {
		if (Pokemon_database.get_type(n) == pokemon_types[y])
			break;
	}
	
	damage_rate_player = Pokemon_database.get_attribute(x, y);
	damage_rate_npc = Pokemon_database.get_attribute(y, x);
}
