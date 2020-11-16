#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string.h>
using namespace::std;

struct MemberRecord
{
   char IDNumber[ 12 ];   // account number
   char password[ 24 ];   // password
   char name[ 8 ];        // name
};

// input memberDetails from the file Members.dat
void loadMemberDetails( vector< MemberRecord > &memberDetails );

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end );

// login
void login( const vector< MemberRecord > &memberDetails );

// there exists a member with specified IDNumber and password
bool valid( char IDNumber[], char password[],
            const vector< MemberRecord > &memberDetails );

// add a new member
void registration( vector< MemberRecord > &memberDetails );

// return true if IDNumber is a legal ID number
bool legalID( char IDNumber[] );

// return true if IDNumber belongs to memberDetails
bool existingID( char IDNumber[], const vector< MemberRecord > &memberDetails );

// output all memberDetails into the file Members.dat
void saveMemberDetails( const vector< MemberRecord > &memberDetails );

int main()
{
   vector< MemberRecord > memberDetails; // member details for all members
   int numMembers = 0;                     // number of members

   loadMemberDetails( memberDetails );


   cout << "Welcome to the Cashbox Party World!\n\n";

   int choice;

   while( true )
   {
      cout << "1 - Login\n";
      cout << "2 - Registration\n";
      cout << "3 - End\n";

      do cout << "\nEnter your choice (1~3): ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );
      cout << endl;

      switch ( choice )
      {
      case 1:
         login( memberDetails );
         break;

      case 2:
         registration( memberDetails );
         break;

      case 3:
         saveMemberDetails( memberDetails );
         cout << "Thank you! Goodbye!\n\n";
         system( "pause" );
         return 0;

      default:
         cout << "\nIncorrect choice!\n";
         break;
      }
   }

   system( "pause" );
}

void loadMemberDetails( vector< MemberRecord > &memberDetails )
{
    MemberRecord in;
    int a;
    char id[12], pass[24], name[8];
    ofstream outFile("Members.dat", ios::app | ios::binary);
    outFile.close();

    ifstream inFile("Members.dat", ios::in | ios::binary);
    inFile.seekg(0, ios::end);
    int x = inFile.tellg()/sizeof(MemberRecord);
    inFile.seekg(0, ios::beg);

    for(a=0; a<x; a++){
        inFile.read((char*)&in, sizeof(MemberRecord));
        memberDetails.push_back(in);
        //cout << in.IDNumber << " " << in.name << " " << in.password << endl;
    }

}

int inputAnInteger( int begin, int end )
{
    char input;

    cin >> input;

    if (input>='1' && input<='3')
        return input-'0';
    else
        return -1;
}

void login( const vector< MemberRecord > &memberDetails )
{
    int a;
    char id[12], pass[24];

    while(1){
        cout << "Please enter your ID number: ";
        cin >> id;
        cout << "Enter your password: ";
        cin >> pass;
        cout << endl;

        if (valid(id, pass, memberDetails))
            break;
        else
            cout << "Invalid account number or password. Please try again.\n\n";
    }
}

bool valid( char IDNumber[], char password[],
            const vector< MemberRecord > &memberDetails )
{
    int a;

    for(a=0; a<memberDetails.size(); a++){
        if (!(strcmp(IDNumber, memberDetails[a].IDNumber)) && !(strcmp(password, memberDetails[a].password)))
            return true;
    }
    return false;
}

void registration( vector< MemberRecord > &memberDetails )
{
    MemberRecord re;

    cout << "Input your ID Number: ";
    cin >> re.IDNumber;
    cout << endl;

    if (legalID(re.IDNumber))
        cout << "The ID number " << re.IDNumber << " is illegal.\n\n";
    else if (existingID(re.IDNumber, memberDetails)){
        cout << "You are already a member!\n\n";
    }
    else{
        cout << "Input your Name: ";
        cin >> re.name;
        cout << "\nChoose a password: ";
        cin >> re.password;
        memberDetails.push_back(re);
        cout << "\nRegistration Completed!\n\n";
    }
}

bool legalID( char IDNumber[] )
{
    int a, total=0;
    char cpy=IDNumber[0];

    if (strlen(IDNumber) != 10)
        return true;
    else if (!((IDNumber[0]>='a'&&IDNumber[0]<='z') || (IDNumber[0]>='A'&&IDNumber[0]<='Z')))
        return true;

    for (a=1; a<strlen(IDNumber); a++){
        if (!(IDNumber[a]>='0'&&IDNumber[a]<='9'))
            return true;
    }

    if (IDNumber[0]>='a'&&IDNumber[0]<='h')
        total = IDNumber[0]-'a'+10;
    else if (IDNumber[0]>='A'&&IDNumber[0]<='H')
        total = IDNumber[0]-'A'+10;
    else if (IDNumber[0]-'i'==0)
        total = 34;
    else if (IDNumber[0]-'I'==0)
        total = 34;
    else if (IDNumber[0]>='j'&&IDNumber[0]<='n')
        total = IDNumber[0]-'j'+18;
    else if (IDNumber[0]>='J'&&IDNumber[0]<='N')
        total = IDNumber[0]-'J'+18;
    else if (IDNumber[0]-'o'==0)
        total = 35;
    else if (IDNumber[0]-'O'==0)
        total = 35;
    else if (IDNumber[0]>='p'&&IDNumber[0]<='v')
        total = IDNumber[0]-'p'+23;
    else if (IDNumber[0]>='P'&&IDNumber[0]<='V')
        total = IDNumber[0]-'P'+23;
    else if (IDNumber[0]-'w'==0)
        total = 32;
    else if (IDNumber[0]-'W'==0)
        total = 32;
    else if (IDNumber[0]>='x'&&IDNumber[0]<='y')
        total = IDNumber[0]-'x'+30;
    else if (IDNumber[0]>='X'&&IDNumber[0]<='Y')
        total = IDNumber[0]-'X'+30;
    else if (IDNumber[0]-'z'==0)
        total = 33;
    else if (IDNumber[0]-'Z'==0)
        total = 33;

    IDNumber[0] = (total%10)+'0';
    total/=10;
    total+=IDNumber[9]-'0';
    for(a=0; a<9; a++)
        total += ((IDNumber[a]-'0')*(9-a));

    IDNumber[0] = cpy;
    if (total%10)
        return true;

    return false;

}

bool existingID( char IDNumber[], const vector< MemberRecord > &memberDetails )
{
    int a;
    for(a=0; a<memberDetails.size(); a++){
        if (!(strcmp(IDNumber, memberDetails[a].IDNumber)))
            return true;
    }
    return false;
}

void saveMemberDetails( const vector< MemberRecord > &memberDetails )
{
    int a;
    ofstream outFile("Members.dat", ios::out | ios::binary);

    for(a=0; a<memberDetails.size(); a++){
        outFile.write(reinterpret_cast<const char*> (&(memberDetails[a])), sizeof(MemberRecord));
    }
}
