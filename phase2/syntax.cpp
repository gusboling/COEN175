#include <iostream>
#include <string>
#include <cstdlib>
#include "tokens.h"
#include "lexer.h"

using namespace std;

#define BAD_MATCH 666

void match();
void xprsOR();
void xprsAND();
void xprsEQUAL();

string lexbuf; //Buffer for token-text
int lookahead; //Variable for storing token #'s

//FUNCTION: "match"
//PRE: token and lookahead are both integers
//POST: If token != lookahead, report the error and exit. Otherwise, set lookahead equal to the next token from the input.
void match(int token){	
	if(token == lookahead) lookahead = lexan(lexbuf);
	else{
		report("Token and lookahead don't match. Exiting.");
		exit(BAD_MATCH);
	}  
}

//FUNCTION: "xprsOR" -> expression-OR
//PRE: lookahead is an integer
void xprsOR(){
	match(OR);
	cout << "or" << endl;
	xprsAND();
	while(lookahead == OR){
		match(OR);
		cout << "or" << endl;
		xprsAND();
	}
}

void xprsAND(){
	match(AND);
	cout << "and" << endl;
	xprsEQUAL();
	while(lookahead == AND){
		match(AND);
		cout << "and" << endl;
		xprsEQUAL();
	}
}

void xprsEQUAL(){
	//TODO	
}

void statement(){
	//TODO

}

int main(){
	cout << "Compilation successful." << endl;
	lookahead = lexan(lexbuf);
	while(lookahead != DONE){
		statement();
	}	
	return 0;
}
