#include "ability.h"
#include "rlutil.h"
base_pokemon::base_pokemon(pokemon now_pok)
	:HP(now_pok.hp), MaxHP(now_pok.hp), Attack(now_pok.atk), Defense(now_pok.def), Speed(now_pok.speed), NO(now_pok.no), Name(now_pok.name)
{
}

void base_pokemon::setHP(int hp)
{
	HP = hp; 
}

void base_pokemon::setSpeed(int spd)
{
	Speed = spd;
}

void base_pokemon::setSpecial(int spcial)
{
	Special = spcial;
}

void base_pokemon::setDefense(int def)
{
	Defense = def;
}

void base_pokemon::setAttack(int atk)
{
	Attack = atk;
}

void base_pokemon::set_player_last(int hp, int atk, int def, int spd, int spcl)
{
	HP = hp;
	Attack = atk;
	Defense = def;
	Speed = spd;
	Special = spcl;	
}

void base_pokemon::set_npc_last(int hp, int atk, int def, int spd, int spcl)
{
	HP = hp;
	Attack = atk;
	Defense = def;
	Speed = spd;
	Special = spcl;
}

int base_pokemon::getNO() const
{
	return NO;
}

int base_pokemon::getHP() const
{
	return HP; 
}

int base_pokemon::getMaxHP() const
{ 
	return MaxHP; 
}

int base_pokemon::getAttack() const
{ 
	return Attack;
}

int base_pokemon::getDefense() const
{ 
	return Defense; 
}

int base_pokemon::getSpeed() const
{
	return Speed;
}

int base_pokemon::getSpecial() const
{
	return Special;
}

void base_pokemon::p_show()
{
	rlutil::locate(22, 29);
	if (HP < 10)
		cout << " ";
	if (HP < 0)
		cout << "0";
	else
		cout << HP;
	rlutil::locate(21, 30);
	cout << Attack << " ";
	rlutil::locate(21, 31);
	cout << Defense << " ";
	rlutil::locate(21, 32);
	cout << Speed << " ";
}

void base_pokemon::n_show()
{
	rlutil::locate(102, 29);
	if (HP < 10)
		cout << " ";
	if (HP < 0)
		cout << "0";
	else
		cout << HP;
	rlutil::locate(101, 30);
	cout << Attack << " ";
	rlutil::locate(101, 31);
	cout << Defense << " ";
	rlutil::locate(101, 32);
	cout << Speed << " ";
}

void base_pokemon::attack(base_pokemon& m, double rate)
{
	oldHP = m.getHP();
	m.setHP(m.getHP() - (getAttack() - m.getDefense()) * rate);
	setHP(getHP() - m.getCounterAttack(oldHP));
}

int base_pokemon::getCounterAttack(int oldHP)
{
	return 0; 
}

void base_pokemon::special_ability(int w)
{
}

void base_pokemon::located(int a, int b)
{
	rlutil::locate(a, b);
}

void base_pokemon::space_()
{
	char y;
	while (1) {
		y = _getch();
		if (y == ' ')
			break;
	}
}