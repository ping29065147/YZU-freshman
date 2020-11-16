#ifndef CHINESEYEAR_H
#define CHINESEYEAR_H

#include <string>
using namespace std;

string animal_data[12] = { "Rat", "Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat", "Monkey", "Rooster", "Dog", "Pig" };

class ChineseYear
{
	public:
		class WrongGregorianYear : public exception {  //例外year<1900
			public:
				const char* what() const noexcept override {
					return "Invalid Gregorian Year(must be >= 1900)";
				}
		};
		class WrongChineseYear : public exception {  //例外wrong animal
			public:
				const char* what() const noexcept override {
					return "Invalid Chinese Year";
				}
		};
	
		//constructor 多載
		ChineseYear(string a) {
			int i;
			for (i=11, year = 2019; i>=0; i--, year--)
				if (animal_data[i] == a)
					break;
			if (i == -1)
				throw ChineseYear::WrongChineseYear();  //例外
			else
				animal = a;
			
		}
		ChineseYear(int y) {
			if (y < 1900)
				throw ChineseYear::WrongGregorianYear();  //例外
			year = y;
			animal = animal_data[(year - 1900) % 12];
		}
		ChineseYear() {
			year = 2020;
			animal = animal_data[0];
		}

		friend ostream& operator<<(ostream& os, ChineseYear right);  //display
		friend ChineseYear operator+(int a, ChineseYear right);

		ChineseYear operator+=(int a) {
			year += 1;
			animal = animal_data[(year - 1900) % 12];
			return *this;
		}
		
		ChineseYear operator+(int a) {
			ChineseYear temp;
			temp.year = year + a;
			temp.animal = animal_data[(temp.year - 1900) % 12];
			return temp;
		}
		

	private:
		int year;
		string animal;
};

ostream& operator<<(ostream& os, ChineseYear right) {
	os << right.animal << " " << right.year << "-" << right.year + 1;
	return os;
}

ChineseYear operator+(int a, ChineseYear right) {
	ChineseYear temp;
	temp.year = right.year + a;
	temp.animal = animal_data[(temp.year - 1900) % 12];
	return temp;
}


#endif // CHINESEYEAR_H
