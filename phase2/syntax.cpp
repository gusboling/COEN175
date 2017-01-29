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
	while( (lookahead==ADDR) || (lookahead=='*') || (lookahead==NOT) || (lookahead=='-') || (lookahead==SIZEOF) ){ //TODO: straighten out what these equivalences should be WRT tokens.h
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
	declaration();
	while( (lookahead == INT) || (lookahead == CHAR) || (lookahead == VOID) ){
		//TODO: Unsure if this avoid left-recursion or not.
		match(lookahead);
		declaration();
		//declarations();
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
		exit(BAD_SPECI);
	}
}

//Statement Rules Implementation
void statement(){
	//TODO

}

//Main
int main(){
	lookahead = lexan(lexbuf);
	cerr << "Found token: " << lookahead << endl;
	while(lookahead != DONE){
		lookahead = lexan(lexbuf);
		cerr << "Found token: " << lookahead << endl;
	}	
	return 0;
}
