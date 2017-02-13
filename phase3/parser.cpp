/*
 * File:	parser.c
 *
 * Description:	This file contains the public and private function and
 *		variable definitions for the recursive-descent parser for
 *		Simple C.
 */

//Libraries
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>

//Program Headers
#include "tokens.h"
#include "checker.h"
#include "lexer.h"

using namespace std;

static int lookahead;
static string lexbuf;

static void expression();
static void statement();

/*
 * Function:	error
 *
 * Description:	Report a syntax error to standard error.
 */
static void error(){
    if (lookahead == DONE)
	report("syntax error at end of file");
    else
	report("syntax error at '%s'", lexbuf);

    exit(EXIT_FAILURE);
}


/*
 * Function:	match
 *
 * Description:	Match the next token against the specified token.  A
 *		failure indicates a syntax error and will terminate the
 *		program since our parser does not do error recovery.
 */
static void match(int token){
    if (lookahead != token){
		cerr << "[MATCH] Lookahead(" << lookahead <<") does not match expected Token(" << token << ")" << endl;
		error();
	}
    lookahead = lexan(lexbuf);
}

//Function: expect
//Description: get the current lexbuf and return it if match succeeds.
static string expect(int token){
    string buffer = lexbuf;
    match(token);
    return buffer;
}

//Function: expectNumber
//Description: get the current lexbuf, and return its integer equivalent if match(NUM) suceeds.
static unsigned expectNumber(){
    unsigned number_result;
    string buffer = lexbuf;
    match(NUM);
    sscanf(buffer.c_str(), "%d", &number_result);
    return number_result;
}

/*
 * Function:	isSpecifier
 *
 * Description:	Return whether the given token is a type specifier.
 */
static bool isSpecifier(int token){

	if(token == INT || token == CHAR || token == VOID){
		cout << "[INFO] Function-definition parameter found" << endl;
	}

    return token == INT || token == CHAR || token == VOID;
}

/*
 * Function:	specifier
 *
 * Description:	Parse a type specifier.  Simple C has only ints, chars, and
 *		void types.
 *
 *		specifier:
 *		  int
 *		  char
 *		  void
 */
static int specifier(){
    if (isSpecifier(lookahead)){
        int spec = lookahead;
        match(lookahead);
        return spec;
    }
    else{
		error();
		return 0;
    }
}


/*
 * Function:	pointers
 *
 * Description:	Parse pointer declarators (i.e., zero or more asterisks).
 *
 *		pointers:
 *		  empty
 *		  * pointers
 */

static unsigned pointers(){
    unsigned ind = 0;
    while (lookahead == '*'){
	ind++;
	match('*');
	cout << "[MATCH] Matched '*'" << endl;
    }
    return ind;
}


/*
 * Function:	declarator
 *
 * Description:	Parse a declarator, which in Simple C is either a scalar
 *		variable or an array, with optional pointer declarators.
 *
 *		declarator:
 *		  pointers identifier
 *		  pointers identifier [ num ]
 */

static void declarator(int spec){ //TODO: Add some form of output to this function
    unsigned ind = pointers();
    string name = expect(ID);
    cout << "Pointer ID => " << name << endl;
    if (lookahead == '[') {
    	match('[');
    	unsigned length = expectNumber(); 
    	match(']');
	Type t(ARRAY, spec, ind);
	t.length = length;
	declareVar(name, t);
    }
    else declareVar(name, Type(SCALAR, spec, ind));
}


/*
 * Function:	declaration
 *
 * Description:	Parse a local variable declaration.  Global declarations
 *		are handled separately since we need to detect a function
 *		as a special case.
 *
 *		declaration:
 *		  specifier declarator-list ';'
 *
 *		declarator-list:
 *		  declarator
 *		  declarator , declarator-list
 */

static void declaration(int spec){
    declarator(spec);

    while (lookahead == ','){
    	match(',');
    	declarator(spec);
    }
    match(';');
}


/*
 * Function:	declarations
 *
 * Description:	Parse a possibly empty sequence of declarations.
 *
 *		declarations:
 *		  empty
 *		  declaration declarations
 */

static void declarations(int s){
    while (isSpecifier(lookahead)) declaration(s);
}


/*
 * Function:	primaryExpression
 *
 * Description:	Parse a primary expression.
 *
 *		primary-expression:
 *		  ( expression )
 *		  identifier ( expression-list )
 *		  identifier ( )
 *		  identifier
 *		  string
 *		  num
 *
 *		expression-list:
 *		  expression
 *		  expression , expression-list
 */

static void primaryExpression(){
    if (lookahead == '(') {
    	match('(');
    	expression();
    	match(')');
    }
    else if (lookahead == STRING) {
	       match(STRING);
    }
    else if (lookahead == NUM) {
	       match(NUM);
    }
    else if (lookahead == ID) {
    	match(ID);

    	if (lookahead == '(') {
    	    match('(');

    	    if (lookahead != ')') {
        		expression();
        		while (lookahead == ',') {
        		    match(',');
        		    expression();
        		}
    	    }

    	    match(')');
    	}
    }
    else error();
}


/*
 * Function:	postfixExpression
 *
 * Description:	Parse a postfix expression.
 *
 *		postfix-expression:
 *		  primary-expression
 *		  postfix-expression [ expression ]
 */

static void postfixExpression(){
    primaryExpression();

    while (lookahead == '[') {
	match('[');
	expression();
	match(']');
	cout << "index" << endl;
    }
}


/*
 * Function:	prefixExpression
 *
 * Description:	Parse a prefix expression.
 *
 *		prefix-expression:
 *		  postfix-expression
 *		  ! prefix-expression
 *		  - prefix-expression
 *		  * prefix-expression
 *		  & prefix-expression
 *		  sizeof prefix-expression
 */

static void prefixExpression(){
    if (lookahead == '!') {
	match('!');
	prefixExpression();
	cout << "not" << endl;

    } else if (lookahead == '-') {
	match('-');
	prefixExpression();
	cout << "neg" << endl;

    } else if (lookahead == '*') {
	match('*');
	prefixExpression();
	cout << "deref" << endl;

    } else if (lookahead == '&') {
	match('&');
	prefixExpression();
	cout << "addr" << endl;

    } else if (lookahead == SIZEOF) {
	match(SIZEOF);
	prefixExpression();
	cout << "sizeof" << endl;

    } else
	postfixExpression();
}


/*
 * Function:	multiplicativeExpression
 *
 * Description:	Parse a multiplicative expression.  Simple C does not have
 *		cast expressions, so we go immediately to prefix
 *		expressions.
 *
 *		multiplicative-expression:
 *		  prefix-expression
 *		  multiplicative-expression * prefix-expression
 *		  multiplicative-expression / prefix-expression
 *		  multiplicative-expression % prefix-expression
 */

static void multiplicativeExpression(){
    prefixExpression();

    while (1) {
	if (lookahead == '*') {
	    match('*');
	    prefixExpression();
	    cout << "mul" << endl;

	} else if (lookahead == '/') {
	    match('/');
	    prefixExpression();
	    cout << "div" << endl;

	} else if (lookahead == '%') {
	    match('%');
	    prefixExpression();
	    cout << "rem" << endl;

	} else
	    break;
    }
}


/*
 * Function:	additiveExpression
 *
 * Description:	Parse an additive expression.
 *
 *		additive-expression:
 *		  multiplicative-expression
 *		  additive-expression + multiplicative-expression
 *		  additive-expression - multiplicative-expression
 */

static void additiveExpression(){
    multiplicativeExpression();

    while (1) {
	if (lookahead == '+') {
	    match('+');
	    multiplicativeExpression();
	    cout << "add" << endl;

	} else if (lookahead == '-') {
	    match('-');
	    multiplicativeExpression();
	    cout << "sub" << endl;

	} else
	    break;
    }
}


/*
 * Function:	relationalExpression
 *
 * Description:	Parse a relational expression.  Note that Simple C does not
 *		have shift operators, so we go immediately to additive
 *		expressions.
 *
 *		relational-expression:
 *		  additive-expression
 *		  relational-expression < additive-expression
 *		  relational-expression > additive-expression
 *		  relational-expression <= additive-expression
 *		  relational-expression >= additive-expression
 */

static void relationalExpression(){
    additiveExpression();

    while (1) {
	if (lookahead == '<') {
	    match('<');
	    additiveExpression();
	    cout << "ltn" << endl;

	} else if (lookahead == '>') {
	    match('>');
	    additiveExpression();
	    cout << "gtn" << endl;

	} else if (lookahead == LEQ) {
	    match(LEQ);
	    additiveExpression();
	    cout << "leq" << endl;

	} else if (lookahead == GEQ) {
	    match(GEQ);
	    additiveExpression();
	    cout << "geq" << endl;

	} else
	    break;
    }
}


/*
 * Function:	equalityExpression
 *
 * Description:	Parse an equality expression.
 *
 *		equality-expression:
 *		  relational-expression
 *		  equality-expression == relational-expression
 *		  equality-expression != relational-expression
 */

static void equalityExpression(){
    relationalExpression();

    while (1) {
	if (lookahead == EQL) {
	    match(EQL);
	    relationalExpression();
	    cout << "eql" << endl;

	} else if (lookahead == NEQ) {
	    match(NEQ);
	    relationalExpression();
	    cout << "neq" << endl;

	} else
	    break;
    }
}


/*
 * Function:	logicalAndExpression
 *
 * Description:	Parse a logical-and expression.  Note that Simple C does
 *		not have bitwise-and expressions.
 *
 *		logical-and-expression:
 *		  equality-expression
 *		  logical-and-expression && equality-expression
 */

static void logicalAndExpression(){
    equalityExpression();

    while (lookahead == AND) {
	match(AND);
	equalityExpression();
	cout << "and" << endl;
    }
}


/*
 * Function:	expression
 *
 * Description:	Parse an expression, or more specifically, a logical-or
 *		expression, since Simple C does not allow comma or
 *		assignment as an expression operator.
 *
 *		expression:
 *		  logical-and-expression
 *		  expression || logical-and-expression
 */

static void expression(){
    logicalAndExpression();

    while (lookahead == OR) {
	match(OR);
	logicalAndExpression();
	cout << "or" << endl;
    }
}


/*
 * Function:	statements
 *
 * Description:	Parse a possibly empty sequence of statements.  Rather than
 *		checking if the next token starts a statement, we check if
 *		the next token ends the sequence, since a sequence of
 *		statements is always terminated by a closing brace.
 *
 *		statements:
 *		  empty
 *		  statement statements
 */

static void statements(){
    while (lookahead != '}')
	statement();
}


/*
 * Function:	Assignment
 *
 * Description:	Parse an assignment statement.
 *
 *		assignment:
 *		  expression = expression
 *		  expression
 */

static void assignment(){
    expression();

    if (lookahead == '=') {
	match('=');
	expression();
    }
}


/*
 * Function:	statement
 *
 * Description:	Parse a statement.  Note that Simple C has so few
 *		statements that we handle them all in this one function.
 *
 *		statement:
 *		  { declarations statements }
 *		  return expression ;
 *		  while ( expression ) statement
 *		  for ( assignment ; expression ; assignment ) statement
 *		  if ( expression ) statement
 *		  if ( expression ) statement else statement
 *		  assignment ;
 */

static void statement(){
    if (lookahead == '{') {
    	match('{');
        int spec = specifier();
    	declarations(spec);
    	statements();
    	match('}');
    }
    else if (lookahead == RETURN) {
    	match(RETURN);
    	expression();
    	match(';');
    }
    else if (lookahead == WHILE) {
    	match(WHILE);
    	match('(');
    	expression();
    	match(')');
    	statement();
    }
    else if (lookahead == FOR) {
    	match(FOR);
    	match('(');
    	assignment();
    	match(';');
    	expression();
    	match(';');
    	assignment();
    	match(')');
    	statement();
    }
    else if (lookahead == IF) {
    	match(IF);
    	match('(');
    	expression();
    	match(')');
    	statement();

    	if (lookahead == ELSE) {
    	    match(ELSE);
    	    statement();
    	}
    }
    else {
    	assignment();
    	match(';');
    }
}


/*
 * Function:	parameter
 *
 * Description:	Parse a parameter, which in Simple C is always a scalar
 *		variable with optional pointer declarators.
 *
 *		parameter:
 *		  specifier pointers identifier
 */

static void parameter(){
    specifier();
    pointers();
    match(ID);
}


/*
 * Function:	parameters
 *
 * Description:	Parse the parameters of a function, but not the opening or
 *		closing parentheses.
 *
 *		parameters:
 *		  void
 *		  void pointers identifier remaining-parameters
 *		  char pointers identifier remaining-parameters
 *		  int pointers identifier remaining-parameters
 *
 *		remaining-parameters:
 *		  empty
 *		  , parameter remaining-parameters
 */

static void parameters(){
    if (lookahead == VOID) {
	match(VOID);

	if (lookahead == ')')
	    return;

    } else
	specifier();

    pointers();
    match(ID);

    while (lookahead == ',') {
	match(',');
	parameter();
    }
}


/*
 * Function:	globalDeclarator
 *
 * Description:	Parse a declarator, which in Simple C is either a scalar
 *		variable, an array, or a function, with optional pointer
 *		declarators.
 *
 *		global-declarator:
 *		  pointers identifier
 *		  pointers identifier [ num ]
 *		  pointers identifier ( parameters )
 */

static void globalDeclarator(int spec){

    unsigned ind = pointers();
    string name = expect(ID);
    match(ID);

    if (lookahead == '[') {
        match('[');
		int length = expectNumber();
        match(']');
		declareArray(name, spec, ind, length);
    }
    else if (lookahead == '(') {
		declareFunction(name, spec, ind);
        openScope(); 
        match('(');
        parameters();
        match(')');
        closeScope();
    }
    else{
        declareVar(name, Type(SCALAR, spec, ind));
    }
}


/*
 * Function:	remainingDeclarators
 *
 * Description:	Parse any remaining global declarators after the first.
 *
 * 		remaining-declarators
 * 		  ;
 * 		  , global-declarator remaining-declarators
 */

static void remainingDeclarators(int spec){

    while (lookahead == ',') {
	       match(',');
           globalDeclarator(spec);
    }
    match(';');
}


/*
 * Function:
 *
 * Description:	Parse a global declaration or function definition.
 *
 * 		global-or-function:
 * 		  specifier pointers identifier remaining-decls
 * 		  specifier pointers identifier [ num ] remaining-decls
 * 		  specifier pointers identifier ( parameters ) remaining-decls
 * 		  specifier pointers identifier ( parameters ) { ... }
 */

static void topLevelDeclaration(){
    int spec = specifier();
    unsigned ind = pointers();
    string name = expect(ID);

    if (lookahead == '[') {
    	match('[');
    	int length = expectNumber();
    	match(']');
		declareArray(name, spec, ind, length); 
    	remainingDeclarators(spec);
    }

    else if (lookahead == '(') {
    	match('(');
    	parameters();
    	match(')');
		declareFunction(name, spec, ind);
    	if (lookahead == '{') {
            openScope(); 
    	    match('{');
    	    declarations(spec);
    	    statements();
    	    match('}');
            closeScope();
    	}
        else remainingDeclarators(spec);
    }

    else{ 
		declareVar(name, Type(SCALAR, spec, ind));
		remainingDeclarators(spec);
	}
}


/*
 * Function:	main
 *
 * Description:	Analyze the standard input stream.
 */

int main(){
    lookahead = lexan(lexbuf);

    while (lookahead != DONE)
	topLevelDeclaration();

    exit(EXIT_SUCCESS);
}
