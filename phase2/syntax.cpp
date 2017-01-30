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

#define BAD_MATCH 1
#define BAD_SPECI 2

using namespace std;

//Expression Rules
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
void xprsLIST();

//Asignment Rule
void assignment();

//Declarator Rules
void declarator();
void declaratorList();
void declaration();
void declarations();

//Specifier Rule
void specifier();

//Statement Rules
void statement();
void statements();

//Pointer Rule
size_t pointers(); //Should never return a negative number.

//Parameter Rules
void parameter();
void parameterList();
void parameters();

//Global Declaration Rules
void globalDeclaration();
void globalDecList();
void globalDec();

//Global Variables
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

//Expression Rules Implementation
void xprsOR(){
	xprsAND(); //Recurse
	while(lookahead == OR){
		match(OR); //Advance the lexer
		xprsAND();
		cout << "or" << endl;
	}
}

void xprsAND(){
	xprsEQUAL(); //Recurse
	while(lookahead == AND){
		match(AND); //Advance the lexer
		cout << "and" << endl;
		xprsEQUAL();
	}
}

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

void xprsPLMN(){
	xprsMDR();
	while( (lookahead==ADD) || (lookahead==SUB) ){
		if(lookahead == ADD){
			match(ADD);
			xprsMDR();
			cout << "add" << endl;
		}
		else{
			match(SUB);
			xprsMDR();
			cout << "sub" << endl;
		}
	}
}

void xprsMDR(){
	xprsOPS();
	while( (lookahead == MUL) || (lookahead == DIV) || (lookahead == REM)){
		if(lookahead == MUL){
			match(MUL);
			cout << "mul" << endl;
		}
		else if(lookahead == DIV){
			match(DIV);
			cout << "div" << endl;
		}
		else{
			match(REM);
			cout << "rem" << endl;
		}
	}
}

void xprsOPS(){
	xprsINDEX();
	while( (lookahead==ADDR) || (lookahead=='*') || (lookahead==NOT) || (lookahead=='-') || (lookahead==SIZEOF) ){ //TODO: straighten out what these equivalences should be WRT tokens.h
		if(lookahead == ADDR){
			match(ADDR);
			xprsOPS();
			cout << "addr" << endl;
		}
		else if(lookahead == '*'){ 
			match('*');
			xprsOPS();
			cout << "deref" << endl;
		}
		else if(lookahead == NOT){
			match(NOT);
			xprsOPS();
			cout << "not" << endl;
			
		}
		else if(lookahead == '-'){
			match('-');
			xprsOPS();
			cout << "sub" << endl;
		}
		else{
			match(SIZEOF);
			xprsOPS();
			cout << "sizeof" << endl;
		}
	}
}


void xprsINDEX(){
	if(lookahead==LBRACKET){
		match(LBRACKET);
		xprsOR();
		match(RBRACKET);
		cout << "index" << endl;
	}
	else xprsLAST();
}

void xprsLAST(){
	if(lookahead == ID){ //ID, ID(), and ID(Expression-List) case
		match(ID);
		if(lookahead == LPAREN){
			match(LPAREN);
			xprsLIST();
			match(RPAREN);
		}
	}
	else if(lookahead == LPAREN){ //(Expression-Or) case
		match(LPAREN);
		xprsOR();
		match(RPAREN);
	}
	else if(lookahead == NUM){ //Number case
		match(NUM);
	}
	else if(lookahead == STRING){ //String case
		match(STRING);
	}
}

void xprsLIST(){
	xprsOR();
	while(lookahead == COMMA){
		match(COMMA);
		xprsLIST();
	}
}

//Assignment Rules Implementation
void assignment(){
	xprsOR();
	while(lookahead == '='){
		match('=');
		xprsOR();
	}


}

//Declarator Rules Implementation
void declarator(){
	pointers();
	match(ID);
	if(lookahead == LBRACKET){
		match(LBRACKET);
		match(NUM);
		match(RBRACKET);
	}
}

void declaratorList(){
	declarator();
	while(lookahead == COMMA){
		match(COMMA);
		declarator();
	}
}

void declaration(){
	specifier();
	declaratorList();
	match(SEMICOLON);//Fails if no semicolon present.
}

void declarations(){
	if((lookahead == INT) || (lookahead==CHAR) || (lookahead==VOID)){
		declaration();
		while( (lookahead == INT) || (lookahead == CHAR) || (lookahead == VOID) ){
			//TODO: Unsure if this avoid left-recursion or not.
			match(lookahead);
			declaration();
			//declarations();
		}
	}
}

//Pointer Rule Implementation
size_t pointers(){
	size_t deref_num=0;
	while(lookahead == DEREF){
		match(DEREF);
		deref_num++;
	}
	return deref_num;
}

//Parameter Rules Implementation
void parameter(){
	specifier();
	pointers();
	match(ID); //Fails if ID not present after removing a specifier and a pointer from the front of input
}

void parameterList(){
	parameter();
	while(lookahead == COMMA){
		match(COMMA);
		parameter();
		//parameterList();
	}
}

void parameters(){
	if(lookahead == VOID){
		match(VOID);
	}
	else parameterList();
}

//Specifier Rule Implementation
void specifier(){
	if(lookahead == INT) match(INT);
	else if(lookahead == CHAR) match(CHAR);
	else if(lookahead == VOID) match(VOID);
	else{
		report("Bad specifier. Exiting");
		cerr << "lookahead => " << lookahead << endl;
		exit(BAD_SPECI);
	}
}

//Statement Rules Implementation
void statement(){
	if(lookahead == LBRACE){
		match(LBRACE);
		declarations();
		statements();
		match(RBRACE);
	}
	else if(lookahead == RETURN){
		match(RETURN);
		xprsOR();
		match(SEMICOLON);
	}
	else if(lookahead == WHILE){
		match(WHILE);
		match(LPAREN);
		xprsOR();
		match(RPAREN);
		statement();
	}
	else if(lookahead == FOR){
		match(FOR);
		match(LPAREN);
		assignment();
		match(SEMICOLON);
		xprsOR();
		match(SEMICOLON);
		assignment();
		match(RPAREN);
		statement();
	}
	else if(lookahead == IF){
		match(IF);
		match(LPAREN);
		xprsOR();
		match(RPAREN);
		statement();
		if(lookahead == ELSE){
			match(ELSE);
			statement();
		}
	}
	else{
		assignment();
		match(SEMICOLON);
	}

}

void statements(){
	while(lookahead != RBRACE) statement();
}

//Global Declaration Rules Implementation
void globalDec(){
	pointers();
	match(ID);
	if(lookahead == LPAREN){
		match(LPAREN);
		parameters();
		match(RPAREN);
	}
	else if(lookahead == LBRACKET){
		match(LBRACKET);
		match(NUM);
		match(RBRACKET);
	}
}

void globalDecList(){
	globalDec();
	if(lookahead == COMMA){
		match(COMMA);
		globalDecList();
	}
}

void fog(){ //function or global declaration rule
	specifier();
	pointers();
	match(ID);
	cerr << "[FOG] specifier, pointer, and identifier check good." << endl;
	if(lookahead == LPAREN){
		match(LPAREN);
		parameters();
		match(RPAREN);
		cerr << "[FOG] parameter check good. " << endl;
		if(lookahead == LBRACE){ //Function definition rules
			match(LBRACE);
			declarations();
			statements();
			match(RBRACE);
			cerr << "[FOG] Function-definition check good." << endl;
		}
		else globalDecList();
	}
	else if(lookahead == LBRACKET ){
		match(LBRACKET);
		match(NUM);
		match(RBRACKET);
		cerr << "[FOG] Index check good." << endl;
		if(lookahead == COMMA){
			match(COMMA);
			globalDecList();
		}
		cerr << "[FOG] Global declarator or global declarator list check good." << endl;
	}
	else if(lookahead == COMMA){
		match(COMMA);
		globalDecList();
	}
	else cerr << "[FOG] Did nothing this time round." << endl;
}

//Main
int main(){
	lookahead = lexan(lexbuf);

	while(lookahead != DONE){
		fog();
		cerr << "[MAIN] fog() exited without errors." << endl;
		cerr << "[MAIN] lookahead: " << lookahead << endl;
	}

	return 0;
}
