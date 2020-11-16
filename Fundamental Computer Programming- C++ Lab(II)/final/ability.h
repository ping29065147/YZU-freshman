#ifndef ABILITY
#define ABILITY
#include <iostream>
#include <iomanip>
#include "pokemon database.h"
using namespace std;

#define low_speed_type 1
#define low_defence_type 2
#define low_attack_type 3


class base_pokemon
{

protected:
    string Name;
    int NO;
    int HP;
    int MaxHP;
    int Attack;
    int Defense;
    int Speed;
    int oldHP = 0;  //use in counter attack
    int Special = 0;  //debuff

public:
    base_pokemon(pokemon now_pok);

    virtual void setHP(int hp);
    void setSpeed(int spd);
    void setSpecial(int spcial);
    void setDefense(int def);
    void setAttack(int atk);
    //set the status of pokemon after a battle
    void set_player_last(int hp, int atk, int def, int spd, int spcl);  
    void set_npc_last(int hp, int atk, int def, int spd, int spcl);

    int getNO() const;
    int getHP() const;
    int getMaxHP() const;
    int getAttack() const;
    int getDefense() const;
    int getSpeed() const;
    int getSpecial() const;

    void p_show();  //renew player state (left)
    void n_show();  //renew npc state (right)
    virtual void attack(base_pokemon& m, double rate);
    virtual int getCounterAttack(int oldHP);
    virtual void special_ability(int w);
    //Polymorphism

    void located(int a, int b); //rlutil::locate
    void space_();  //if enter space, break
};

//normal
class normal_p : public base_pokemon
{
public:
    normal_p(pokemon r) : base_pokemon(r) {}
};

//heal
class heal : public base_pokemon
{
public:
    heal(pokemon r) : base_pokemon(r){}

    void special_ability(int w)
    {
        setHP(getHP() + 3);
        located(1, 45);
        if (w == 1) {
            cout << setw(45) << " " << "Your " << Name << " heals 3 hp." << setw(30) << " ";
            p_show();
        }
        else {
            cout << setw(45) << " " << Name << " heals 3 hp." << setw(30) << " ";
            n_show();
        }
        space_();
    }
};

//burning
class burning : public base_pokemon
{
public:
    burning(pokemon r) : base_pokemon(r) {}

    void attack(base_pokemon& m, double rate)
    {
        int damage = (rand() % 3 + 1);
        
        oldHP = m.getHP();
        m.setHP(m.getHP() - (getAttack() - m.getDefense()) * rate - damage);
        setHP(getHP() - m.getCounterAttack(oldHP));
        located(80, 45);
        cout << "(Burning! Cause " << damage << " damages)";
    }

};

//counter attack
class counter_attack : public base_pokemon
{
public:
    counter_attack(pokemon r) : base_pokemon(r) {}

    int getCounterAttack(int oldHP)
    {
        located(45, 46);
        cout << "(Counter attack! Cause " << (oldHP - getHP()) / 5 << " damages)";
        return (oldHP - getHP()) / 5;
    }
};

//immunology
class immunology : public base_pokemon
{
public:
    immunology(pokemon r) : base_pokemon(r) {}

    void special_ability(int w)
    {
        if (Special != 0) {
            located(1, 45);
            cout << setw(45) << " " << "Immunology of debuff!" << setw(30) << " ";
            Special = 0;
            
            space_();
        }
    }
};

//leech life
class leech_life : public base_pokemon
{
public:
    leech_life(pokemon r) : base_pokemon(r) {}

    void attack(base_pokemon& m, double rate)
    {
        int life = (rand() % 2 + 2);

        oldHP = m.getHP();
        m.setHP(m.getHP() - (getAttack() - m.getDefense()) * rate);
        located(80, 45);
        cout << "(Leech life! Recover " << life << " lifes)";
        setHP(getHP() - m.getCounterAttack(oldHP) + life);
    }
};

//avoid
class avoid : public base_pokemon
{
public:
    avoid(pokemon r) : base_pokemon(r) {}

    void setHP(int hp)
    {   
        if (rand() % 5)
            HP = hp;
        else {
            if (hp != HP) {
                located(25, 46);
                cout << "(Avoid attack!)";
            }
        }
    }
};

//double attack
class double_attack : public base_pokemon
{
public:
    double_attack(pokemon r) : base_pokemon(r) {}

    void attack(base_pokemon& m, double rate)
    {
        oldHP = m.getHP();

        if (rand() % 5)
            m.setHP(m.getHP() - (getAttack() - m.getDefense()) * rate);
        else {
            located(80, 45);
            cout << "(Double attack!)";
            m.setHP(m.getHP() - (getAttack() - m.getDefense()) * 2 * rate);
        }
            
        setHP(getHP() - m.getCounterAttack(oldHP));
    }
};

//poison
class poison : public base_pokemon
{
private:
    int round = 1;

public:
    poison(pokemon r) : base_pokemon(r) {}

    void attack(base_pokemon& m, double rate)
    {
        oldHP = m.getHP();

        if (round <= 3) {
            located(80, 45);
            cout << "(Poison!)";

            if (round == 2 || round == 3)
                m.setHP(m.getHP() - (getAttack() - m.getDefense()) * rate - 2);
            else
                m.setHP(m.getHP() - (getAttack() - m.getDefense()) * rate);
        }
        else
            m.setHP(m.getHP() - (getAttack() - m.getDefense()) * rate);

        setHP(getHP() - m.getCounterAttack(oldHP));
        round++;
    }
};

//lower speed
class lower_speed : public base_pokemon
{
private:
    int round = 1;

public:
    lower_speed(pokemon r) : base_pokemon(r) {}

    void attack(base_pokemon& m, double rate)
    {
        if (round <= 3) {
            located(80, 45);
            cout << "(Lower speed!)";

            if (round == 1)
                m.setSpecial(low_speed_type);
            else if (round == 2 && m.getSpecial() == low_attack_type)
                m.setSpeed(m.getSpeed() - 2);
        }
        else if (round == 4 && m.getSpecial() == low_speed_type)
            m.setSpeed(m.getSpeed() + 2);

        oldHP = m.getHP();
        m.setHP(m.getHP() - (getAttack() - m.getDefense()) * rate);
        setHP(getHP() - m.getCounterAttack(oldHP));

        round++;
    }
};

//rock skin
class rock_skin : public base_pokemon
{
public:
    rock_skin(pokemon r) : base_pokemon(r) {}

    void setHP(int hp)
    {
        if (HP - hp > 0) {
            located(25, 46);
            cout << "(Rock skin!)";

            if (HP - hp >= 2)
                HP = hp + 2;
        }
    }
};

//lower defence
class lower_defence : public base_pokemon
{
private:
    int round = 1;

public:
    lower_defence(pokemon r) : base_pokemon(r) {}

    void attack(base_pokemon& m, double rate)
    {
        if (round <= 3) {
            located(80, 45);
            cout << "(Lower defence!)";

            if (round == 1)
                m.setSpecial(low_defence_type);
            else if (round == 2 && m.getSpecial() == low_attack_type)
                m.setDefense(m.getDefense() - 2);
        }
        else if (round == 4 && m.getSpecial() == low_defence_type)
            m.setDefense(m.getDefense() + 2);

        oldHP = m.getHP();
        m.setHP(m.getHP() - (getAttack() - m.getDefense()) * rate);
        setHP(getHP() - m.getCounterAttack(oldHP));

        round++;
    }
};

//lower attack
class lower_attack : public base_pokemon
{
private:
    int round = 1;
    
public:
    lower_attack(pokemon r) : base_pokemon(r) {}

    void attack(base_pokemon& m, double rate)
    {
        if (round <= 3) {
            located(80, 45);
            cout << "(Lower attack!)";

            if (round == 1)
                m.setSpecial(low_attack_type);
            else if (round == 2 && m.getSpecial() == low_attack_type)
                m.setAttack(m.getAttack() - 2);
        }
        else if (round == 4 && m.getSpecial() == low_attack_type)
            m.setAttack(m.getAttack() + 2);

        oldHP = m.getHP();
        m.setHP(m.getHP() - (getAttack() - m.getDefense()) * rate);
        setHP(getHP() - m.getCounterAttack(oldHP));

        round++;
    }
};

#endif //ABILITY