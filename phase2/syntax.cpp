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
void xprsPLMN();
void xprsMDR();
void xprsOPS();
void xprsINDEX();
void xprsLAST();

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

//Rule for "||" expressions
void xprsOR(){
	xprsAND(); //Recurse
	while(lookahead == OR){
		match(OR); //Advance the lexer
		cout << "or" << endl;
		xprsAND();
	}
}

//Rule for "&&" expressions
void xprsAND(){
	xprsEQUAL(); //Recurse
	while(lookahead == AND){
		match(AND); //Advance the lexer
		cout << "and" << endl;
		xprsEQUAL();
	}
}

//Rule for "==" and "!=" expressions
void xprsEQUAL(){
	xprsINEQUAL();
	while( (lookahead == EQUAL) || (lookahead == NOTEQUAL) ){
		if(lookahead == EQUAL){
			match(EQUAL);
			cout << "eql" << endl;
			xprsINEQUAL();
		}
		else{
			match(NOTEQUAL);
			cout << "neq" << endl;
			xprsINEQUAL();
		}			
	}
}

//Rule for "<", "<", ">=", and ">" expressions
void xprsINEQUAL(){
	xprsPLMN();
	while( (lookahead == GTN) || (lookahead == LTN) || (lookahead == GREATERTHANOREQUAL) || (lookahead == LESSTHANOREQUAL) ) { //TODO: Should this be an "if" statement instead of a loop?
		if(lookahead == GTN){
			match(GTN);
			cout << "gtn" << endl;
			xprsPLMN();
		}
		else if(lookahead == LTN){
			match(LTN);
			cout << "ltn" << endl;
			xprsPLMN();
		}
		else if(lookahead == GREATERTHANOREQUAL){
			match(GREATERTHANOREQUAL);
			cout << "geq" << endl;
			xprsPLMN();
		}
		else{
			match(LESSTHANOREQUAL);
			cout << "leq" << endl;
			xprsPLMN();
		}
	}
}

//Rule for "+" and "-" expressions
void xprsPLMN(){
	xprsMDR();
	while( (lookahead==ADD) || (lookahead==SUB) ){
		if(lookahead == ADD){
			match(ADD);
			cout << "add" << endl;
			xprsMDR();
		}
		else{
			match(SUB);
			cout << "sub" << endl;
			xprsMDR();
		}	
	}
}

//Rule for "*", "/", and "%" expressions [(M)ultiplication, (D)ivision, (R)emainder]
void xprsMDR(){
	xprsOPS();
	while( (lookahead == MUL) || (lookahead == DIV) || (lookahead == REM)){
		if(lookahead == MUL){
			match(MUL);
			cout << "mul" << endl;
			xprsOPS();
		}
		else if(lookahead == DIV){
			match(DIV);
			cout << "div" << endl;
			xprsOPS();
		}
		else{
			match(REM);
			cout << "rem" << endl;
			xprsOPS();
		}
	}
}

void xprsOPS(){
	xprsINDEX();
	while( (lookahead=='&') || (lookahead=='*') || (lookahead=='!') || (lookahead=='-') || (lookahead==SIZEOF) ){ //TODO: straighten out what these equivalences should be WRT tokens.h
		if(lookahead == '&'){
			match('&');
			cout << "addr" << endl;
			xprsINDEX();
		}
		else if(lookahead == '*'){
			match('*');
			cout << "deref" << endl;
			xprsINDEX();	
		}
		else if(lookahead == '!'){
			match('!');
			cout << "not" << endl;
			xprsINDEX();
		}
		else if(lookahead == '-'){
			match('-');
			cout << "neg" << endl;
			xprsINDEX();
		}
		else{
			match(SIZEOF);
			cout << "sizeof" << endl;
		}	
	}
}

void xprsINDEX(){
	//TODO
}

void xprsLAST(){
	//TODO
}

void statement(){
	//TODO

}

int main(){
	lookahead = lexan(lexbuf);
	cerr << "Found token: " << lookahead << endl;
	while(lookahead != DONE){
		lookahead = lexan(lexbuf);
		cerr << "Found token: " << lookahead << endl;
	}	
	return 0;
}
