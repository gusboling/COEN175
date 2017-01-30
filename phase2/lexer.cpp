/*
* File:	lexer.cpp
*
* Description:	This file contains the public and private function and
*		variable definitions for the lexical analyzer for Simple C.
*/

# include <cstdio>
# include <cctype>
# include <string>
# include <iostream>
# include "lexer.h"
# include "tokens.h"

using namespace std;
int numerrors, lineno = 1;

/* Later, we will associate token values with each keyword */

static string keywords[] = {
	"auto",
	"break",
	"case",
	"char",
	"const",
	"continue",
	"default",
	"do",
	"double",
	"else",
	"enum",
	"extern",
	"float",
	"for",
	"sgoto",
	"if",
	"int",
	"long",
	"register",
	"return",
	"short",
	"signed",
	"sizeof",
	"static",
	"struct",
	"switch",
	"typedef",
	"union",
	"unsigned",
	"void",
	"volatile",
	"while",
};

# define numKeywords (sizeof(keywords) / sizeof(keywords[0]))


/*
* Function:	report
*
* Description:	Report an error to the standard error prefixed with the
*		line number.  We'll be using this a lot later with an
*		optional string argument, but C++'s stupid streams don't do
*		positional arguments, so we actually resort to snprintf.
*		You just can't beat C for doing things down and dirty.
*/

void report(const string &str, const string &arg){
	char buf[1000];

	snprintf(buf, sizeof(buf), str.c_str(), arg.c_str());
	cerr << "line " << lineno << ": " << buf << endl;
	numerrors ++;
}


/*
* Function:	lexan
*
* Description:	Read and tokenize the standard input stream.  The lexeme is
*		stored in a buffer.
*/

int lexan(string &lexbuf){
	int p;
	unsigned i;
	static int c = cin.get();
	int result;

	/* The invariant here is that the next character has already been read
	and is ready to be classified.  In this way, we eliminate having to
	push back characters onto the stream, merely to read them again. */

	while (!cin.eof()) {
	lexbuf.clear();


	/* Ignore white space */

	while (isspace(c)) {
	if (c == '\n')
	lineno ++;

	c = cin.get();
	}


	/* Check for an identifier or a keyword */

	if (isalpha(c) || c == '_') {
	do {
	lexbuf += c;
	c = cin.get();
	} while (isalnum(c) || c == '_');

	for (i = 0; i < numKeywords; i ++)
	if (keywords[i] == lexbuf)
	break;

	if (i < numKeywords)
	result = AUTO + i; //tokens.h defines the first keyword - "auto" - as 261.
	else
	result = ID;

	return result;


	/* Check for a number */

	} else if (isdigit(c)) {
	do {
	lexbuf += c;
	c = cin.get();
	} while (isdigit(c));

	result = NUM;
	return result;


	/* There must be an easier way to do this.  It might seem stupid at
	this point to recognize each token separately, but eventually
	we'll be returning separate token values to the parser, so we
	might as well do it now. */

	} else {
	lexbuf += c;

	switch(c) {


	/* Check for '||' */

	case '|':
		c = cin.get();
		result = ERROR;
		if (c == '|') {
		    lexbuf += c;
		    c = cin.get();
		    result = OR;
		}
		return result;


	/* Check for '=' and '==' */

	case '=':
		c = cin.get();
		result = ASG;
		if (c == '=') {
		    lexbuf += c;
		    c = cin.get();
				result = EQUAL;
		}
		return result;



	/* Check for '&' and '&&' */

	case '&':
	c = cin.get();

	if (c == '&') {
		lexbuf += c;
		c = cin.get();
		result = AND;
		return result;
	}

	result = ADDR;
	return result;


	/* Check for '!' and '!=' */

	case '!':
	c = cin.get();

	if (c == '=') {
	lexbuf += c;
	c = cin.get();
	result = NOTEQUAL;
	return result;
	}

	result = NOT;
	return result;


	/* Check for '<' and '<=' */

	case '<':
	c = cin.get();

	if (c == '=') {
	lexbuf += c;
	c = cin.get();
	result = LESSTHANOREQUAL;
	return result;
	}

	result = LTN;
	return result;


	/* Check for '>' and '>=' */

	case '>':
	c = cin.get();

	if (c == '=') {
	lexbuf += c;
	c = cin.get();
	result = GREATERTHANOREQUAL;
	return result;
	}

	result = GTN;
	return result;


	/* Check for '-', '--', and '->' */

	case '-':
	c = cin.get();

	if (c == '-') {
	lexbuf += c;
	c = cin.get();
	result = DECREMENT;
	return result;
	} else if (c == '>') {
	lexbuf += c;
	c = cin.get();
	result = POINTER;
	return result;
	}
	result = SUB;
	return result;


	/* Check for '+' and '++' */

	case '+':
	c = cin.get();

	if (c == '+') {
	lexbuf += c;
	c = cin.get();
	result = INCREMENT;
	return result;
	}

	result = ADD;
	return result;


	/* Check for simple, single character tokens */

	case '*':
	c = cin.get();
	result = MUL;
	return result;
	case '%':
	c = cin.get();
	result = REM;
	return result;
	case ';':
	c = cin.get();
	result = SEMICOLON;
	return result;
	case '(':
	c = cin.get();
	result = LPAREN;
	return result;
	case ')':
	c = cin.get();
	result = RPAREN;
	return result;
	case '[':
	c = cin.get();
	result = LBRACKET;
	return result;
	case ']':
	c = cin.get();
	result = RBRACKET;
	return result;
	case '{':
	c = cin.get();
	result = LBRACE;
	return result;
	case '}':
	c = cin.get();
	result = RBRACE;
	return result;
	case '.':
	c = cin.get();
	result = PERIOD;
	return result;
	case ',':
	c = cin.get();
	result = COMMA;
	return result;


	/* Check for '/' or a comment */

	case '/':
	c = cin.get();

	if (c == '*') {
	do {
	while (c != '*' && !cin.eof()) {
	if (c == '\n')
	lineno ++;

	c = cin.get();
	}

	c = cin.get();
	} while (c != '/' && !cin.eof());

	c = cin.get();
	break;

	} else {
	result = DIV;
	return result;
	}


	/* Check for a string literal */

	case '"':
	do {
	p = c;
	c = cin.get();
	lexbuf += c;
	} while ((c != '"' || p == '\\') && c != '\n' && !cin.eof());

	if (c == '\n' || cin.eof())
	report("malformed string literal");

	c = cin.get();
	result = STRING;
	return result;


	/* Handle EOF here as well */

	case EOF:
	return DONE;


	/* Everything else is illegal */

	default:
	c = cin.get();
	break;
	}
	}
	}

	return ERROR;
}
