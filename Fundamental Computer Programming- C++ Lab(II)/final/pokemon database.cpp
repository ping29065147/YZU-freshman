#include "pokemon database.h"
#include "player.h"
#include "rlutil.h"
#include "ability.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string pokemon_types[19] = {"", "Normal", "Fire", "Water", "Electric", "Grass", "Ice", "Fighting", "Poison", "Ground",
							"Flying", "Psychic", "Bug", "Rock", "Ghost", "Dragon", "Dark", "Steel", "Fairy" };

pokemon_database::pokemon_database() 
{
	//Exception
	try {
		load_pokemon();
		load_picture();
		load_attribute();
	}
	catch (string wrong) {
		cout << wrong << endl;
	}
}

void pokemon_database::load_pokemon()
{
	string temp;
	pokemon pok;

	ifstream inFile("termproj\\assets\\pokemons.csv", ios::in);
	if (!inFile)
		throw "wrong_loading_pokemon";

	while (getline(inFile, temp)) {

		stringstream convert(temp);
		stringstream Convert;
		string data;
		int count = 1;

		while (getline(convert, data, ',')) {
			Convert.str("");
			Convert.clear();
			Convert << data;
			switch (count)
			{
			case 1:
				Convert >> pok.no;
				break;
			case 2:
				Convert >> pok.name;
				break;
			case 3:
				Convert >> pok.type;
				break;
			case 4:
				Convert >> pok.hp;
				break;
			case 5:
				Convert >> pok.atk;
				break;
			case 6:
				Convert >> pok.def;
				break;
			case 7:
				Convert >> pok.speed;
				break;
			case 8:
				Convert >> pok.ability;
				break;
			}
			count++;
		}
		pokemons.push_back(pok);
	}
	inFile.close();
	pokemons.pop_back();
	pokemons.pop_back();
}

void pokemon_database::load_picture()
{
	string file;
	string temp;

	for (size_t a = 1; a <= 32; a++) {
		file.clear();
		file += "termproj\\assets\\icons\\color\\0";
		if (a < 10) {
			file += "0";
			file += a + '0';
		}
		else {
			file += (a / 10) + '0';
			file += (a % 10) + '0';
		}
		file += ".txt";
		
		ifstream inFile(file, ios::in);
		if (!inFile)
			throw "wrong_loading_picture";
		while (getline(inFile, temp))
			pokemons[a - 1].picture.push_back(temp);
		inFile.close();
	}
}

void pokemon_database::load_attribute()
{
	string temp;
	double temp_d;
	vector<double> temp_v;

	ifstream inFile("termproj\\assets\\type.csv", ios::in);
	if (!inFile)
		throw "wrong_loading_attribute";

	while (getline(inFile, temp)) {

		stringstream convert(temp);
		stringstream Convert;
		string data;
		while (getline(convert, data, ',')) {
			Convert.str("");
			Convert.clear();
			Convert << data;
			Convert >> temp_d;
			temp_v.push_back(temp_d);
		}
		attribute.push_back(temp_v);
		temp_v.clear();
	}
	inFile.close();
}

void pokemon_database::print_catch(int no)
{
	if (no > 32 || no < 1) {
		cout << "There is no pokemon.\n\n";
		return;
	}
	for (const auto& a : pokemons[no - 1].picture)
		cout << a << endl;

	rlutil::locate(60, 8);
	cout << setw(12) << right << "No. " << setw(12) << left << pokemons[no - 1].no;
	rlutil::locate(60, 9);
	cout << setw(12) << right << "Name: " << setw(12) << left << pokemons[no - 1].name;
	rlutil::locate(60, 10);
	cout << setw(12) << right << "Type: " << setw(12) << left << setw(12) << pokemons[no - 1].type;
	rlutil::locate(60, 11);
	cout << setw(12) << right << "HP: " << setw(12) << left << pokemons[no - 1].hp;
	rlutil::locate(60, 12);
	cout << setw(12) << right << "ATK: " << setw(12) << left << pokemons[no - 1].atk;
	rlutil::locate(60, 13);
	cout << setw(12) << right << "DEF: " << setw(12) << left << pokemons[no - 1].def;
	rlutil::locate(60, 14);
	cout << setw(12) << right << "Speed: " << setw(12) << left << pokemons[no - 1].speed;
	rlutil::locate(60, 15);
	cout << setw(12) << right << "Ability: " << setw(12) << left << pokemons[no - 1].ability;
}

void pokemon_database::print_battle(int no, int no2, vector<int> player, vector<int> npc, bool* p_num, int n_num)
{
	system("cls");
	system("mode con:lines=50");

	for (auto& a : pokemons[no - 1].picture)
		cout << a << endl;
	cout << endl;

	cout << setw(20) << right << "No. " << pokemons[no - 1].no << endl
		<< setw(20) << right << "Name: " << pokemons[no - 1].name << endl
		<< setw(20) << right << "Type: " << pokemons[no - 1].type << endl
		<< setw(20) << right << "HP: " << "(" << pokemons[no - 1].hp << "/" << pokemons[no - 1].hp << ")" << endl
		<< setw(20) << right << "ATK: "<< pokemons[no - 1].atk << endl
		<< setw(20) << right << "DEF: " << pokemons[no - 1].def << endl
		<< setw(20) << right << "Speed: " << pokemons[no - 1].speed << endl
		<< setw(20) << right << "Ability: " << pokemons[no - 1].ability << "\n\n";
	for (size_t a = 0; a < 120; a++)
		cout << "=";

	for (size_t a = 0; a < pokemons[no - 1].picture.size(); a++) {
		rlutil::locate(80, 1 + a);
		cout << pokemons[no2 - 1].picture[a] << endl;
	}
	rlutil::locate(91, 26);
	cout << setw(10) << right << "No. " << pokemons[no2 - 1].no;
	rlutil::locate(91, 27);
	cout << setw(10) << right << "Name: " << pokemons[no2 - 1].name;
	rlutil::locate(91, 28);
	cout << setw(10) << right << "Type: " << pokemons[no2 - 1].type;
	rlutil::locate(91, 29);
	cout << setw(10) << right << "HP: " << "(" << pokemons[no2 - 1].hp << "/" << pokemons[no2 - 1].hp << ")";
	rlutil::locate(91, 30);
	cout << setw(10) << right << "ATK: " << pokemons[no2 - 1].atk;
	rlutil::locate(91, 31);
	cout << setw(10) << right << "DEF: " << pokemons[no2 - 1].def;
	rlutil::locate(91, 32);
	cout << setw(10) << right << "Speed: " << pokemons[no2 - 1].speed;
	rlutil::locate(91, 33);
	cout << setw(10) << right << "Ability: " << pokemons[no2 - 1].ability << "\n\n";

	rlutil::locate(1, 37);
	cout << left << setw(5) << " " << "My pokemons\n\n";
	for (size_t a = 0; a < 3; a++) {
		if (player[a] != 0 && p_num[a] == true) {
			cout << setw(10) << " " << "No." << setw(2) << get_no(player[a])
				<< "   Name: " << setw(12) << get_name(player[a])
				<< "   Type: " << setw(10) << get_type(player[a]) << endl;
		}
		else
			cout << endl;
	}
	cout << endl;
	for (size_t a = 0; a < 120; a++)
		cout << "=";

	rlutil::locate(70, 37);
	cout << " " << "NPC pokemons";
	for (size_t a = 0; a < 3; a++) {
		if (npc[a] != 0 && a >= n_num) {
			rlutil::locate(76, 39 + a);
			cout << " " << "No." << setw(2) << get_no(npc[a])
				<< "   Name: " << setw(12) << get_name(npc[a])
				<< "   Type: " << setw(10) << get_type(npc[a]);
		}
	}
}

void pokemon_database::print_attribute()
{
	system("cls");
	system("mode con:lines=25 cols=200");
	for (size_t a = 0; a <= 18; a++)
		cout << setw(10) << pokemon_types[a];
	cout << endl;
	for (size_t a = 0; a < attribute.size(); a++) {
		cout << setw(10) << pokemon_types[a + 1];
		for (size_t b = 0; b < attribute[a].size(); b++)
			cout << setw(10) << attribute[a][b];
		cout << endl;
	}
	cout << endl;
	system("pause");
}

template <typename T>
int pokemon_database::get_no(T no)
{
	return pokemons[no - 1].no;
}

template <typename T>
string pokemon_database::get_name(T no)
{
	return pokemons[no - 1].name;
}

template <typename T>
string pokemon_database::get_type(T no)
{
	return pokemons[no - 1].type;
}

pokemon pokemon_database::get_pokemon(int no)
{
	return pokemons[no - 1];
}

double pokemon_database::get_attribute(int atk, int def)
{
	return attribute[atk - 1][def - 1];
}