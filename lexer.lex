%option noyywrap
%option noinput
%option nounput

%{

    #include <iostream>
    #include <cstdlib>
    #include <cstring>
    #include <string>

    using namespace std;

    #include "tokeni.h"

    extern int value;
%}



%%
"print" {
    return print_token;
}

[0-9]+ {

    value = atoi(yytext);
    return num_token;
}
[+<(,)>=*-] {
    return *yytext;
}


[a-zA-Z]+ {
    return id_token;
}

[\n] {
    return eoi_token;
}


[ \t] {

}

. {
    cerr<<"leksicka greska: nije prepoznat token"<<endl;
    exit(EXIT_FAILURE);
}

%%
