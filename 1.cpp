#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>

#include "tokeni.h"
using namespace std;

void greska()
{
    cerr<<"leksicka greska: failed"<<endl;
    exit(EXIT_FAILURE);
}

void E();
void I();
void N();
void P();
void U();
void IP();

int lookahead;
extern int yylex();
int value = 0;

void E(){

    if (lookahead == '<' || lookahead == '(' || lookahead == num_token)
    {
//         cout<<"dobro je"<<endl;
        cout<<"E => I\n";
        I();
    }
    else if (lookahead == id_token) {

        cout<<"E => N\n";
        N();
    }
    else if (lookahead == print_token)
    {
        cout<<"E => P\n";
        P();
    }
    else
        greska();

}
void N()
{
    if (lookahead == id_token)
    {
        cout<<"N => id = I\n";
        lookahead = yylex();
//         cout<<(char)lookahead<<endl;
        lookahead = yylex();
//         cout<<(char)lookahead<<endl;
        I();

    }
    else
        greska();
}
void P()
{
    if (lookahead == print_token)
    {
        cout<<"P => print ( I )"<<endl;
        lookahead = yylex();
        I();
        lookahead = yylex();
        if (lookahead != ')')
        {
            cerr<<"ocekivano na kraju: )"<<endl;
            exit(EXIT_FAILURE);
        }
    }
    else
        greska();
}


void I() {

    if (lookahead == eoi_token)
    {
        cout<<"zasto?"<<endl;
    }
    if (lookahead == '<')
    {
        cout<<"I => UI'\n";
        U();
        IP();
    }
    else
        if (lookahead == '(')
        {
            cout<<"I => (I)I'\n";
            I();
            lookahead = yylex();
            if (lookahead != ')')
            {
                cerr<<"ocekivano na ulazu: )"<<endl;
                exit(EXIT_FAILURE);
            }
            IP();
        }
    else
        if (lookahead == num_token)
        {
            cout<<"I => num * I I'\n";
            lookahead = yylex();
//             cout<<(char)lookahead<<endl;
            if (lookahead != '*')
            {
                cerr<<"ocekivano na ulazu: *\n";
                exit(EXIT_FAILURE);
            }
            lookahead = yylex();
//             cout<<(char)lookahead<<endl;
            I();
            IP();
        }
    else if (lookahead == id_token)
    {
        cout<<"I => id\n";
        lookahead = yylex();

    }
    else
        greska();

}
void IP(){
    if (lookahead == '+')
    {
        cout<<"I' => +I I'\n";
        I();
        IP();
    }
    else if (lookahead == eoi_token || lookahead == ')' || lookahead == '+')
    {
        cout<<"I' => eps\n";
    }
    else
        greska();

}
void U(){

    if (lookahead == '<')
    {
        lookahead = yylex();
        lookahead = yylex();
        lookahead = yylex();
        lookahead = yylex();
        lookahead = yylex();
        lookahead = yylex();
//         cout<<(char)lookahead<<endl;
        if (lookahead != '>')
        {
            cerr<<"ocekivano na ulazu >"<<endl;
            exit(EXIT_FAILURE);
        }
        lookahead = yylex();
    }

}

int main()
{
    lookahead = yylex();
    E();

    if (lookahead == eoi_token || lookahead == EOF)
        cout<<"izraz je prihvacen"<<endl;
    else
        cout<<"izraz nije prihvacen"<<endl;

//     cout<<value<<endl;
    return 0;
}
