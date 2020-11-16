#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include <string>
using namespace std;

class Monster {
    protected:
        int HP;
        int MaxHP;
        int Attack;
        int Defense;
		int Counterattack = 0;
        int oldHP = 0;  //use in counter attack
    public:
        Monster(int hp, int mxhp, int atk, int def):HP(hp),MaxHP(mxhp),Attack(atk),Defense(def){}
        void setHP(int hp){ HP = hp; }
        int getHP() const { return HP; }
        int getMaxHP() const { return MaxHP; }
        int getAttack() const { return Attack; }
        int getDefense() const { return Defense; }
        virtual void showStats(){
            cout << setw(10) << "Monster(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl; 
        }
        virtual void attack(Monster &m){
            oldHP = m.getHP();
            m.setHP(m.getHP() - (getAttack() - m.getDefense()));
            setHP(getHP() - m.getCounterAttack(oldHP));
        }
		virtual int getCounterAttack(int oldHP) const { return Counterattack; }
};

class Dragon : public Monster {
   protected:
      double Rate;
   public:
      Dragon(double rt): Rate(rt), Monster(35, 35, 5, 2){} //set the dragon hp, attack, defend
      
      void showStats() {
         cout << setw(10) << "Dragon(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
      }
      void attack(Monster& m) {
         double damage = (rand() % 10 + 1)*Rate;  //addition damage
         oldHP = m.getHP();
         m.setHP(m.getHP() - (getAttack() - m.getDefense()) - damage);
         setHP(getHP() - m.getCounterAttack(oldHP));
      }
};

class Unicorn : public Monster {
   public:
      Unicorn(): Monster(50, 50, 6, 1) {}  //set the unicorn hp, attack, defend

      void showStats() {
         cout << setw(10) << "Unicorn(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
      }
      void attack(Monster& m) {
         int probability[4] = { 0, 0, 1, 0 };
         int select = rand() % 4;
         if (probability[select] == 1) {//decide double attack or not
             oldHP = m.getHP();
             m.setHP(m.getHP() - (getAttack() - m.getDefense()) * 2);
             setHP(getHP() - m.getCounterAttack(oldHP));
         }
         else {
             oldHP = m.getHP();
             m.setHP(m.getHP() - (getAttack() - m.getDefense()));
             setHP(getHP() - m.getCounterAttack(oldHP));
         }
      }
};

class Hedgehog : public Monster {
	public:
		Hedgehog(): Monster(100, 100, 3, 0) {}  //set the hedgehog hp, attack, defend

		void showStats() {
			cout << setw(10) << "Hedgehog(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
		}
        int getCounterAttack(int oldHP) const {
            return (oldHP-getHP())/4;
        }
};

class Player {
    protected:
		string name;
		Monster* MonsterList[3];
		Dragon d[3] = { 0.6, 0.7, 0.8 };
		Unicorn u[3];
		Hedgehog h[3];
        bool alive[3] = { true, true, true };
	public:
		Player(string n):name(n){

			int temp;
            for (int a = 0; a < 3; a++) {
                temp = rand() % 3;
                if (temp == 0)
                    MonsterList[a] = &d[a];
                else if (temp == 1)
                    MonsterList[a] = &u[a];
                else if (temp == 2)
                    MonsterList[a] = &h[a];
            }

		}
		string getName() { return name; }
		Monster* getCurrentMonster() const {
			for (int a = 0; a < 3; a++) {
				if (alive[a] == true)
					return MonsterList[a];
                
			}
			return nullptr;
		}
		void showAliveMonsters() {
			for (int a = 0; a < 3; a++) {
				if (MonsterList[a]->getHP() > 0)
					MonsterList[a]->showStats();
			}
		}
        void dead() {
            for (int a = 0; a < 3; a++)
                if (alive[a] == true) {
                    alive[a] = false;
                    break;
                }
        }

};

#endif // MONSTER_H
