#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the array program
void load( string *program, int &numLines );

// deletes the comment beginning with "//" from sourceLine if any
void delComment( string &sourceLine );

// deletes all string constants from sourceLine
void delStrConsts( string &sourceLine );

// deletes all character constants from sourceLine
void delCharConsts( string &sourceLine );

// deletes the first identifier from sourceLine, and returns it
string delFirstIdentifier( string &sourceLine );

// stores all non-keyword strings in the array identifiers into a text file
void store( string *identifiers, int numIdentifiers );

// return true if and only if "str" is a C++ keyword
bool keyword( string str );

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( string *identifiers, int pos );

const string keywords[] = { "auto", "break", "case", "char", "const",
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
   string *program = new string[ 500 ];
   int numLines = 0;

   // reads in a C++ program from a cpp file, and put it to the array program
   load( program, numLines );

   string *identifiers = new string[ 500 ];
   string firstIdentifier;
   string null;
   int numIdentifiers = 0;

   for( int i = 0; i < numLines; i++ )
   {
      delComment( program[ i ] ); // deletes the comment beginning with "//" from program[ i ]
      delStrConsts( program[ i ] ); // deletes all string constants from program[ i ]
      delCharConsts( program[ i ] ); // deletes all character constants from program[ i ]

      // extracts all identifiers from program[ i ], and put them into the array identifiers
      while( ( firstIdentifier = delFirstIdentifier( program[ i ] ) ) != null )
         identifiers[ numIdentifiers++ ] = firstIdentifier;
   }

   // stores all non-keyword strings in the array identifiers into a text file
   store( identifiers, numIdentifiers );

   delete[] program;
   delete[] identifiers;

	system( "pause" );
}

void load( string *program, int &numLines )
{
    int a;
    string in;
    ifstream inFile("test.cpp", ios::in);

    if (!inFile){
        cout << "File could not be open!\n";
        exit(1);
    }

    for(a=0; getline(inFile, in); a++){
        program[a] = in;
        numLines++;
        //cout << in << endl;
    }
}

void delComment( string &sourceLine )
{
    int a;

    if (sourceLine!=""){
        for(a=0; a<sourceLine.size()-1; a++){
            if (sourceLine[a]=='/' && sourceLine[a+1]=='/'){
                sourceLine.erase(sourceLine.begin()+a, sourceLine.end());
                break;
            }
        }
    }
}

void delStrConsts( string &sourceLine )
{
    int a;
    int start=-1, end=-1;

    for(a=0; a<sourceLine.size(); a++){
        if (sourceLine[a]=='\"'){
            if (start==-1)
                start=a;
            else if (end==-1)
                end=a;

            if(start!=-1 && end!=-1){
                sourceLine.erase(sourceLine.begin()+start, sourceLine.begin()+end+1);
                break;
            }
        }
    }
}

void delCharConsts( string &sourceLine )
{
    int a;
    int start=-1, end=-1;

    for(a=0; a<sourceLine.size(); a++){
        if (sourceLine[a]=='\''){
            if (start==-1)
                start=a;
            else if (end==-1)
                end=a;

            if(start!=-1 && end!=-1){
                sourceLine.erase(sourceLine.begin()+start, sourceLine.begin()+end+1);
                break;
            }
        }
    }
}

string delFirstIdentifier( string &sourceLine )
{
    int a, b, start, end;

    if (sourceLine=="")
        return sourceLine;
    else{
        for(a=0; a<sourceLine.size(); a++){
            start=-1;
            end=-1;
            for(b=a; b<sourceLine.size(); b++){
                if(sourceLine[b]=='_' || (sourceLine[b]>='a'&&sourceLine[b]<='z') || (sourceLine[b]>='A'&&sourceLine[b]<='Z')){
                    if (start==-1)
                        start=b;
                }
                else if(sourceLine[b]=='_' || (sourceLine[b]>='0'&&sourceLine[b]<='9') || (sourceLine[b]>='a'&&sourceLine[b]<='z') || (sourceLine[b]>='A'&&sourceLine[b]<='Z'))
                    continue;
                else{
                    if (start!=-1)
                        end=b;
                    break;
                }
            }

            if (start!=-1 && end!=-1){
                string re(sourceLine.begin()+start, sourceLine.begin()+end);
                sourceLine.erase(sourceLine.begin()+start, sourceLine.begin()+end);
                //cout << re << endl;
                return re;
            }
        }
        return "";
    }
}

void store( string *identifiers, int numIdentifiers )
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
    }
}

bool keyword( string str )
{
    int a;

    for(a=0; a<sizeof(keywords)/sizeof(keywords[0]); a++){
        if (str==keywords[a])
            return true;
    }
    return false;
}

bool duplicate( string *identifiers, int pos )
{
    int a;

    for(a=0; a<pos; a++){
        if (identifiers[pos]==identifiers[a])
            return true;
    }
    return false;
}
