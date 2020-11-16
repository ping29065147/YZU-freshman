#ifndef PERSON_H
#define PERSON_H
// The declaration of Class person

using namespace std;
class person {
    private:
        // member variables
        char* name;
        int age;
    public:
        // constructor
        person( char const* nm = "noname", int ae = 5 );
        // copy constructor
        person( person& m );
        // destructor
        ~person();
        // assignment operator
        person& operator=( person& m );
        // member functions
        void setName( char const* nm );
        void setAge( int ae );
        string getName();
        int getAge();
};

#endif // PERSON_H
