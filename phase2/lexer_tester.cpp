/*
 * File:	lexer.cpp
 *
 * Description:	This file contains the public and private function and
 *		variable definitions for the lexical analyzer for Simple C.
 */
# include <cstdlib>
# include <cstdio>
# include <string>
# include <iostream>
# include "lexer.h"
# include "tokens.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

using namespace std;

int lookahead;
string lexbuf;

static struct {
    string lexeme;
    int token;
} keywords[] = {
    {"auto",     AUTO},
    {"break",    BREAK},
    {"case",     CASE},
    {"char",     CHAR},
    {"const",    CONST},
    {"continue", CONTINUE},
    {"default",  DEFAULT},
    {"do",       DO},
    {"double",   DOUBLE},
    {"else",     ELSE},
    {"enum",     ENUM},
    {"extern",   EXTERN},
    {"float",    FLOAT},
    {"for",      FOR},
    {"goto",     GOTO},
    {"if",       IF},
    {"int",      INT},
    {"long",     LONG},
    {"register", REGISTER},
    {"return",   RETURN},
    {"short",    SHORT},
    {"signed",   SIGNED},
    {"sizeof",   SIZEOF},
    {"static",   STATIC},
    {"struct",   STRUCT},
    {"switch",   SWITCH},
    {"typedef",  TYPEDEF},
    {"union",    UNION},
    {"unsigned", UNSIGNED},
    {"void",     VOID},
    {"volatile", VOLATILE},
    {"while",    WHILE},
};

# define numKeywords (sizeof(keywords) / sizeof(keywords[0]))

void printFor(int token)
{
    int i;

    // Check for keyword
    for (i = 0; i < numKeywords; ++i)
    {
        if (keywords[i].token == token)
        {
            cout << "keyword:" << lexbuf << endl;
            return;
        }
    }

    switch (token)
    {
        case ERROR:
            exit(EXIT_FAILURE);
        case ID:
            cout << "identifier:" << lexbuf << endl;
            return;
        case NUM:
            cout << "number:" << lexbuf << endl;
            return;
        case STRING:
            cout << "string:" << lexbuf << endl;
            return;
        default:
            cout << "operator:" << lexbuf << endl;
            return;
    }
}

int main()
{
    lookahead = lexan(lexbuf);

    while (lookahead != DONE)
	{
        printFor(lookahead);
        lookahead = lexan(lexbuf);
    }

    exit(EXIT_SUCCESS);
}
