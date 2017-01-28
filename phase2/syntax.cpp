/* THE STORY THUS FAR:
 * 
 * Armed with nought but an aging laptop, our hero sets forth to write
 * a simple syntax-analysis program. Racing against time, he will need to
 * overcome multiple test cases before he can face the ultimate challenge of 
 * Lord Atkinson's scorching gaze. This is his story... and his code.
 *
 * Written by Augustus G. "The 'G' stands for 'generally sane'" Boling
 * 29 January 2017
 * COEN 175L
 */


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
void xprsNOTEQUAL();
void xprsINEQUAL();

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
	xprsAND();
	while(lookahead == OR){
		match(OR);
		cout << "or" << endl;
		xprsAND();
	}
}

void xprsAND(){
	xprsEQUAL();
	while(lookahead == AND){
		match(AND);
		cout << "and" << endl;
		xprsEQUAL();
	}
}

void xprsEQUAL(){
	xprsNOTEQUAL();
	while(lookahead == EQUAL){
		match(EQUAL);
		cout << "eql" << endl;
		xprsNOTEQUAL();
	}
}

void xprsNOTEQUAL(){
	xprsINEQUAL();
	while(lookahead == NOTEQUAL){
		match(NOTEQUAL);
		cout << "neq" << endl;
		xprsINEQUAL();
	}
}

void xprsINEQUAL(){
	//TODO
}

void statement(){
	//TODO

}

int main(){
	lookahead = lexan(lexbuf);
	while(lookahead != DONE){
		cerr << "Found token: " << lexbuf << endl;
		lookahead = lexan(lexbuf);
	}	
	return 0;
}
