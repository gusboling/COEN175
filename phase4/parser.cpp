//TODO: Update defunct calls to "void expression()". Needs to be 


// PARSER.CPP: Recursive descent parser implementation

//Libraries
# include <cstdlib>
# include <iostream>

//Program Headers
# include "checker.h"
# include "tokens.h"
# include "lexer.h"


using namespace std;

//Global Variables
static int lookahead;
static string lexbuf;

static Type expression(bool &lvalue);
static void statement();
//End Global Variables

static void error()
{
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

static void match(int t)
{
    if (lookahead != t){
		cout << "[MATCH][ERROR] lookahead(" << lookahead << ") does not match token(" << t << ")" << endl;
		error();
	}
	
    lookahead = lexan(lexbuf);
}


/*
 * Function:	expect
 *
 * Description:	Match the next token against the specified token, and
 *		return its lexeme.  We must save the contents of the buffer
 *		from the lexical analyzer before matching, since matching
 *		will advance to the next token.
 */

static string expect(int t)
{
    string buf = lexbuf;
    match(t);
    return buf;
}


/*
 * Function:	number
 *
 * Description:	Match the next token as a number and return its value.
 */

static unsigned number()
{
    int value;


    value = strtoul(expect(NUM).c_str(), NULL, 0);
    return value;
}


/*
 * Function:	isSpecifier
 *
 * Description:	Return whether the given token is a type specifier.
 */

static bool isSpecifier(int token)
{
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

static int specifier()
{
    int typespec = ERROR;


    if (isSpecifier(lookahead)) {
	typespec = lookahead;
	match(lookahead);
    } else
	error();

    return typespec;
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

static unsigned pointers()
{
    unsigned count = 0;


    while (lookahead == '*') {
	match('*');
	count ++;
    }

    return count;
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

static void declarator(int typespec)
{
    unsigned indirection;
    string name;


    indirection = pointers();
    name = expect(ID);

    if (lookahead == '[') {
	match('[');
	declareVariable(name, Type(typespec, indirection, number()));
	match(']');
    } else
	declareVariable(name, Type(typespec, indirection));
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

static void declaration()
{
    int typespec;


    typespec = specifier();
    declarator(typespec);

    while (lookahead == ',') {
	match(',');
	declarator(typespec);
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

static void declarations()
{
    while (isSpecifier(lookahead))
	declaration();
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

static Type primaryExpression(bool &lvalue)
{
    string name;
	Type left;

    if (lookahead == '(') {
		match('(');
		left = expression(lvalue);
		match(')');
		//Result type is the same as enclosed expression type, lvalue is same as enclosed expression lvalue.

    } 
	else if (lookahead == STRING) {
		string buf_string = expect(STRING);
		left = Type(CHAR, 0, buf_string.length()); 
		lvalue = false;
		//Result is of type "array of char, length=string.length" and is not an lvalue

    } 
	else if (lookahead == NUM) {
		match(NUM);
		left = Type(INT);
		lvalue = false;
		//Result is of type "int" and is not an lvalue
    } 
	
	else if (lookahead == ID) {
		name = expect(ID);
		Parameters params;

		if (lookahead == '(') {
	    	match('(');

	    	if (lookahead != ')') {
				params.push_back(expression(lvalue));
				while (lookahead == ',') {
		    		match(',');
					params.push_back(expression(lvalue));
				}
	    	}

	    	match(')');
	    	Symbol *result = checkFunction(name, params); 
			left = result->type(); 
		}
		else 
		{
			Symbol* sym_ptr = checkIdentifier(name);
			left = sym_ptr->type();
		}

    } 
	else 
	{
	 	left = Type();
		error();
	}
	return left;
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

static Type postfixExpression(bool &lvalue)
{
    Type left = primaryExpression(lvalue);

    while (lookahead == '[') {
		match('[');
		Type right = expression(lvalue);
		match(']');
		left = checkPostFixExpr(left, right);
		lvalue = true;
		return left;
    }

	return left;
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

static Type  prefixExpression(bool &lvalue)
{
	Type left;
    if (lookahead == '!') {
		match('!');
		Type right = prefixExpression(lvalue);
		//Type left = checkNegationExpr(right); //TODO: Implement in checker
		lvalue = false;
		return left;

   	} else if (lookahead == '-') {
		match('-');
		Type right = prefixExpression(lvalue);
		//Type left = checkNegativeExpr(right); //TODO: Implement in checker
		lvalue = false;
		return left;

    } else if (lookahead == '*') {
		match('*');
		Type right = prefixExpression(lvalue);
		//Type left = checkDerefExpr(right); //TODO: Implement in checker
		lvalue = true;
		return left;

    } else if (lookahead == '&') {
		match('&');
		Type right = prefixExpression(lvalue);
		//Type left = checkAddressExpr(right); //TODO: Implement in checker
		lvalue = false;
		return left;

    } else if (lookahead == SIZEOF) {
		match(SIZEOF);
		Type right = prefixExpression(lvalue);
		//Type left = checkSizeofExpression(right); //TODO: Implement in checker
		lvalue = false;
		return left;
    
	} else {
		Type left = postfixExpression(lvalue);
		return left;
	}
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

static Type multiplicativeExpression(bool &lvalue)
{
    Type left = prefixExpression(lvalue);

    while (1) {
		if (lookahead == '*') {
	    	match('*');
	    	Type right = prefixExpression(lvalue);
			//left = checkMultiplicativeExpression(left, right); //TODO: Implement in checker
			lvalue = false;

		} else if (lookahead == '/') {
	    	match('/');
	    	Type right = prefixExpression(lvalue);
			//left = checkMultiplicativeExpression(left, right); //TODO: Implement in checker
			lvalue = false;

		} else if (lookahead == '%') {
	    	match('%');
	    	Type right = prefixExpression(lvalue);
			//left = checkMultiplicativeExpression(left, right); //TODO: Implement in checker
			lvalue = false;

		} else {
			return left;
	    	break;
    	}
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

static Type additiveExpression(bool &lvalue)
{
    Type left = multiplicativeExpression(lvalue);

    while (1) {
		if (lookahead == '+') {
	    	match('+');
	    	Type right = multiplicativeExpression(lvalue);
			left = checkAdditiveExpr(left, right, "+"); //TODO: Implement in checker
			lvalue = false;
		} 
		else if (lookahead == '-') {
	    	match('-');
	    	Type right = multiplicativeExpression(lvalue);
			left = checkAdditiveExpr(left, right, "-"); //TODO: Implement in checker
			lvalue = false;
		}	 
		else{
			return left;
	    	break;
    	}
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

static Type relationalExpression(bool &lvalue)
{
    Type left = additiveExpression(lvalue);

    while (1) {
		if (lookahead == '<') {
	    	match('<');
	    	Type right = additiveExpression(lvalue);
			left = checkRelationalExpr(left, right, "<"); 
			lvalue = false;

		} else if (lookahead == '>') {
	    	match('>');
	    	Type right = additiveExpression(lvalue);
			left = checkRelationalExpr(left, right, ">"); 
			lvalue = false;

		} else if (lookahead == LEQ) {
	    match(LEQ);
	    Type right = additiveExpression(lvalue);
		left = checkRelationalExpr(left, right, "<=");
		lvalue = false;

		} else if (lookahead == GEQ) {
	    	match(GEQ);
	    	Type right = additiveExpression(lvalue);
			left = checkRelationalExpr(left, right, ">=");
			lvalue = false;
	
		} else {
			return left;
	    	break;
		}
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

static Type equalityExpression(bool &lvalue){
    Type left = relationalExpression(lvalue);

    while (1) {
		if (lookahead == EQL) {
	    	match(EQL);
	    	Type right = relationalExpression(lvalue);
			left = checkLogicalEQ(left, right); 
			lvalue = false;

		} else if (lookahead == NEQ) {
	    	match(NEQ);
	    	Type right = relationalExpression(lvalue);
			left = checkLogicalNEQ(left, right); 
			lvalue = false;

		} else {
			return left;
	    	break;
		}
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

static Type logicalAndExpression(bool &lvalue){
    Type left = equalityExpression(lvalue);
	cout << "[AND] left: " << left << endl;

    while (lookahead == AND) {
		match(AND);
		Type right = equalityExpression(lvalue);
		cout << "[AND][2] right: " << right << endl;
		left = checkLogicalAND(left, right); 
		lvalue = false;
    }
	return left;
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

static Type expression(bool &lvalue){
    Type left = logicalAndExpression(lvalue); 
	cout << "[OR] left: " << left << endl;

    while (lookahead == OR) {
		match(OR);
		Type right = logicalAndExpression(lvalue);
		cout << "[OR][2] right: " << right << endl;
		left = checkLogicalOR(left, right);
		cout << "[OR][3] left-post-check: " << left << endl;
		lvalue = false;
    }
	return left;
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

static void statements()
{
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

static void assignment()
{
	bool lvalue_original = false;
    Type left = expression(lvalue_original); //Is this right? (1/2)

    if (lookahead == '=') {
		match('=');
		Type right = expression(lvalue_original); //Is this right? (2/2)
    }

	//TODO: Implement something for this in checker.
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

static void statement()
{
	bool lvalue_original = false;
	Type right;

    if (lookahead == '{') {
		match('{');
		openScope();
		declarations();
		statements();
		closeScope();
		match('}');

    } else if (lookahead == RETURN) {
		match(RETURN);
		right = expression(lvalue_original);
		match(';');
		//checkReturnStatement(right); //TODO: Implement in checker

    } else if (lookahead == WHILE) {
		match(WHILE);
		match('(');
		right = expression(lvalue_original);
		match(')');
		statement();
		//checkWhileStatement(right); //TODO: Implement in checker

    } else if (lookahead == FOR) {
		match(FOR);
		match('(');
		assignment();
		match(';');
		right = expression(lvalue_original);
		match(';');
		assignment();
		match(')');
		statement();
		//checkForStatement(right); //TODO: Implement in checker

    } else if (lookahead == IF) {
		match(IF);
		match('(');
		right = expression(lvalue_original);
		//CheckIfStatement(right); //TODO: Implement in checker
		match(')');
		statement();
		

		if(lookahead == ELSE) {
	    	match(ELSE);
	    	statement();
		}

    } else {
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

static Type parameter()
{
    int typespec;
    unsigned indirection;
    string name;
    Type type;


    typespec = specifier();
    indirection = pointers();
    name = expect(ID);

    type = Type(typespec, indirection);
    declareVariable(name, type);
    return type;
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

static Parameters *parameters()
{
    int typespec;
    unsigned indirection;
    Parameters *params;
    string name;
    Type type;


    openScope();
    params = new Parameters();

    if (lookahead == VOID) {
	typespec = VOID;
	match(VOID);

	if (lookahead == ')')
	    return params;

    } else
	typespec = specifier();

    indirection = pointers();
    name = expect(ID);

    type = Type(typespec, indirection);
    declareVariable(name, type);
    params->push_back(type);

    while (lookahead == ',') {
	match(',');
	params->push_back(parameter());
    }

    return params;
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

static void globalDeclarator(int typespec)
{
    unsigned indirection;
    string name;


    indirection = pointers();
    name = expect(ID);

    if (lookahead == '[') {
	match('[');
	declareVariable(name, Type(typespec, indirection, number()));
	match(']');

    } else if (lookahead == '(') {
	match('(');
	declareFunction(name, Type(typespec, indirection, parameters()));
	closeScope();
	match(')');

    } else
	declareVariable(name, Type(typespec, indirection));
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

static void remainingDeclarators(int typespec)
{
    while (lookahead == ',') {
	match(',');
	globalDeclarator(typespec);
    }

    match(';');
}


/*
 * Function:	topLevelDeclaration
 *
 * Description:	Parse a global declaration or function definition.
 *
 * 		global-or-function:
 * 		  specifier pointers identifier remaining-decls
 * 		  specifier pointers identifier [ num ] remaining-decls
 * 		  specifier pointers identifier ( parameters ) remaining-decls 
 * 		  specifier pointers identifier ( parameters ) { ... }
 */

static void topLevelDeclaration()
{
    int typespec;
    unsigned indirection;
    Parameters *params;
    string name;


    typespec = specifier();
    indirection = pointers();
    name = expect(ID);

    if (lookahead == '[') {
	match('[');
	declareVariable(name, Type(typespec, indirection, number()));
	match(']');
	remainingDeclarators(typespec);

    } else if (lookahead == '(') {
	match('(');
	params = parameters();
	match(')');

	if (lookahead == '{') {
	    defineFunction(name, Type(typespec, indirection, params));
	    match('{');
	    declarations();
	    statements();
	    closeScope();
	    match('}');

	} else {
	    closeScope();
	    declareFunction(name, Type(typespec, indirection, params));
	    remainingDeclarators(typespec);
	}

    } else {
	declareVariable(name, Type(typespec, indirection));
	remainingDeclarators(typespec);
    }
}


/*
 * Function:	main
 *
 * Description:	Analyze the standard input stream.
 */

int main()
{
    openScope();
    lookahead = lexan(lexbuf);

    while (lookahead != DONE)
	topLevelDeclaration();

    closeScope();
    exit(EXIT_SUCCESS);
}
