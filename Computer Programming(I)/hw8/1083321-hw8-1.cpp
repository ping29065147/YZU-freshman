#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <string>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the array program
void load( char( *program )[ 100 ], int &numLines );

// deletes the comment beginning with "//" from sourceLine if any
void delComment( char sourceLine[] );

// deletes all string constants from sourceLine
void delStrConsts( char sourceLine[] );

// deletes all character constants from sourceLine
void delCharConsts( char sourceLine[] );

// extracts all identifiers from sourceLine, and put them into the array identifiers
void extractIdentifiers( char sourceLine[], char identifiers[][ 32 ], int &numIdentifiers );

// stores all non-keyword strings in the array identifiers into a text file
void store( char ( *identifiers )[ 32 ], int numIdentifiers );

// returns true if and only if str is a C++ keyword
bool keyword( char str[] );

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( char ( *identifiers )[ 32 ], int pos );

const char keywords[][ 20 ] = { "auto", "break", "case", "char", "const",
                                "continue", "default", "define","do", "double",
                                "else", "enum", "extern", "float", "for",
                                "goto", "if", "int", "long", "register",
                                "return", "short", "signed", "sizeof",
                                "static", "struct", "switch", "typedef",
                                "union", "unsigned", "void", "volatile",
                                "while", "bool", "catch", "class",
                                "const_cast", "delete", "dynamic_cast",
                                "explicit", "false", "friend", "inline",
                                "mutable", "namespace", "new", "operator",
                                "private", "protected", "public",
                                "reinterpret_cast", "static_cast", "template",
                                "this", "throw", "true", "try", "typeid",
                                "typename", "using", "virtual", "include" };

int main()
{
   char ( *program )[ 100 ] = new char[ 500 ][ 100 ]();
   int numLines = 0;

   // reads in a C++ program from a cpp file, and put it to the array program
   load( program, numLines );

   char ( *identifiers )[ 32 ] = new char[ 500 ][ 32 ]();
   int numIdentifiers = 0;

   for( int i = 0; i < numLines; i++ )
   {
      delComment( program[ i ] ); // deletes the comment beginning with "//" from program[ i ]
      delStrConsts( program[ i ] ); // deletes all string constants from program[ i ]
      delCharConsts( program[ i ] ); // deletes all character constants from program[ i ]

      if( strcmp( program[ i ], "" ) != 0 )
         extractIdentifiers( program[ i ], identifiers, numIdentifiers );
         // extracts all identifiers from program[ i ], and put them into the array identifiers
   }

   // stores all non-keyword strings in the array identifiers into a text file
   store( identifiers, numIdentifiers );

   delete[] program;
   delete[] identifiers;

	system( "pause" );
}

void load( char( *program )[ 100 ], int &numLines )
{
    int a, b;
    string in;
    ifstream inFile("test.cpp", ios::in);

    if (!inFile){
        cout << "File could not be open!\n";
        exit(1);
    }

    for(a=0; getline(inFile, in); a++){
        for(b=0; b<in.size(); b++)
            program[a][b] = in[b];
        numLines++;
    }
}

void delComment( char sourceLine[] )
{
    int a, b;
    bool check=false;

    for(a=0; a<strlen(sourceLine); a++){
        if (sourceLine[a]-' '!=0 && sourceLine-'\t'!=0){
            check = true;
            break;
        }
    }

    if (check){
        for(a=0; a<strlen(sourceLine)-1; a++){
            if (sourceLine[a]-'/'==0 && sourceLine[a+1]-'/'==0){
                for(b=a; b<strlen(sourceLine); b++)
                    sourceLine[b]=' ';
                break;
            }
        }
    }
}

void delStrConsts( char sourceLine[] )
{
    int a, b;
    int start=-1, end=-1;

    for(a=0; a<strlen(sourceLine); a++){
        if (sourceLine[a]-'\"'==0){
            if (start==-1)
                start=a;
            else if (end==-1)
                end=a;

            if(start!=-1 && end!=-1){
                for(b=start; b<=end; b++)
                    sourceLine[b]=' ';
                break;
            }
        }
    }
}

void delCharConsts( char sourceLine[] )
{
    int a, b;
    int start=-1, end=-1;

    for(a=0; a<strlen(sourceLine); a++){
        if (sourceLine[a]-'\''==0){
            if (start==-1)
                start=a;
            else if (end==-1)
                end=a;

            if(start!=-1 && end!=-1){
                for(b=start; b<=end; b++)
                    sourceLine[b]=' ';
                break;
            }
        }
    }
}

void extractIdentifiers( char sourceLine[], char identifiers[][ 32 ], int &numIdentifiers )
{
    int a, b, start, end;

    for(a=0; a<strlen(sourceLine); a++){
        start=-1;
        end=-1;
        for(b=a; b<strlen(sourceLine); b++){
            if(sourceLine[b]-'_'==0 || (sourceLine[b]-'a'>=0&&sourceLine[b]-'z'<=0) || (sourceLine[b]-'A'>=0&&sourceLine[b]-'Z'<=0)){
                if (start==-1)
                    start=b;
            }
            else if(sourceLine[b]-'_'==0 || (sourceLine[b]-'0'>=0&&sourceLine[b]-'9'<=0) || (sourceLine[b]-'a'>=0&&sourceLine[b]-'z'<=0) || (sourceLine[b]-'A'>=0&&sourceLine[b]-'Z'<=0))
                continue;
            else{
                if (start!=-1)
                    end=b;
                break;
            }
        }

        if (start!=-1 && end!=-1){
            for(b=0; b<end-start; b++){
                identifiers[numIdentifiers][b] = sourceLine[start+b];
                sourceLine[start+b]=' ';
            }
            numIdentifiers++;
        }
    }

}

void store( char ( *identifiers )[ 32 ], int numIdentifiers )
{
    int a, b;
    ofstream outFile("result.txt", ios::out);

    if (!outFile){
        cout << "File could not be open!\n";
        exit(1);
    }

    for(a=0; a<numIdentifiers; a++){
        if (!keyword(identifiers[a]) && !duplicate(identifiers, a)){
            cout << identifiers[a] << endl;
            outFile << identifiers[a] << endl;
        }
        //cout << identifiers[a] << endl;
    }

    //delete[] identifiers;
}

bool keyword( char str[] )
{
    int a, b;

    for(a=0; a<sizeof(keywords)/sizeof(keywords[0]); a++){

        if (strlen(str)!=strlen(keywords[a]))
            continue;

        for(b=0; b<strlen(str); b++){
            if (str[b]==keywords[a][b])
                continue;
            else
                break;
        }
        if (b==strlen(str))
            return true;
    }
    return false;
}

bool duplicate( char ( *identifiers )[ 32 ], int pos )
{
    int a, b;

    for(a=0; a<pos; a++){

        if (strlen(identifiers[pos]) != strlen(identifiers[a]))
            continue;

        for(b=0; b<strlen(identifiers[pos]); b++){
            if (identifiers[pos][b]==identifiers[a][b])
                continue;
            else
                break;
        }
        if (b==strlen(identifiers[pos]))
            return true;
    }
    return false;
}
