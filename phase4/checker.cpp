/*
 * File:	checker.cpp
 *
 * Description:	This file contains the public and private function and
 *		variable definitions for the semantic checker for Simple C.
 *
 *		If a symbol is redeclared, the existing declaration is
 *		retained and the redeclaration discarded.  This behavior
 *		seems to be consistent with GCC, and who are we to argue
 *		with GCC?
 *
 *		Extra functionality:
 *		- inserting an undeclared symbol with the error type
 */

# include <iostream>
# include "lexer.h"
# include "checker.h"
# include "nullptr.h"
# include "tokens.h"
# include "Symbol.h"
# include "Scope.h"
# include "Type.h"

# define FUNCDEFN 1


using namespace std;

static Scope *outermost, *toplevel;
static const Type error;
static const Type integer_type = Type(INT);

//Symbol Errors
static string redefined = "redefinition of '%s'";
static string redeclared = "redeclaration of '%s'";
static string conflicting = "conflicting types for '%s'";
static string undeclared = "'%s' undeclared";
static string void_object = "'%s' has type void";

//Type Errors
static string return_type = "invalid return type"; //E1
static string test_expression = "invalid type for test expression"; //E2
static string lvalue_required = "lvalue required in expression"; //E3
static string invalid_binary = "invalid operands to binary %s"; //E4
static string invalid_unary = "invalid operand to unary %s"; //E5
static string not_function = "called object is not a function"; //E6
static string invalid_arguments = "invalid arguments to called function"; //E7

/*
 * Function:	checkIfVoidObject
 *
 * Description:	Check if TYPE is a proper use of the void type (if the
 *		specifier is void, then the indirection must be nonzero or
 *		the kind must be a function).  If the type is proper, it is
 *		returned.  Otherwise, the error type is returned.
 */

static Type checkIfVoidObject(const string name, const Type &type)
{
    if (type.specifier() != VOID)
	return type;

    if (type.indirection() == 0 && !type.isFunction()) {
	report(void_object, name);
	return error;
    }

    return type;
}


/*
 * Function:	openScope
 *
 * Description:	Create a scope and make it the new top-level scope.
 */

Scope *openScope()
{
    toplevel = new Scope(toplevel);

    if (outermost == nullptr)
	outermost = toplevel;

    return toplevel;
}


/*
 * Function:	closeScope
 *
 * Description:	Remove the top-level scope, and make its enclosing scope
 *		the new top-level scope.
 */

Scope *closeScope()
{
    Scope *old = toplevel;
    toplevel = toplevel->enclosing();
    return old;
}


/*
 * Function:	defineFunction
 *
 * Description:	Define a function with the specified NAME and TYPE.  A
 *		function is always defined in the outermost scope.
 */

Symbol *defineFunction(const string &name, const Type &type)
{
    Symbol *symbol = declareFunction(name, type);

    if (symbol->_attributes & FUNCDEFN)
	report(redefined, name);

    symbol->_attributes = FUNCDEFN;
    return symbol;
}


/*
 * Function:	declareFunction
 *
 * Description:	Declare a function with the specified NAME and TYPE.  A
 *		function is always declared in the outermost scope.  Any
 *		redeclaration is discarded.
 */

Symbol *declareFunction(const string &name, const Type &type)
{
    cout << name << ": " << type << endl;
    Symbol *symbol = outermost->find(name);

    if (symbol == nullptr) {
	symbol = new Symbol(name, type);
	outermost->insert(symbol);

    } else if (type != symbol->type()) {
	report(conflicting, name);
	delete type.parameters();

    } else
	delete type.parameters();

    return symbol;
}


/*
 * Function:	declareVariable
 *
 * Description:	Declare a variable with the specified NAME and TYPE.  Any
 *		redeclaration is discarded.
 */

Symbol *declareVariable(const string &name, const Type &type)
{
    cout << name << ": " << type << endl;
    Symbol *symbol = toplevel->find(name);

    if (symbol == nullptr) {
	symbol = new Symbol(name, checkIfVoidObject(name, type));
	toplevel->insert(symbol);

    } else if (outermost != toplevel)
	report(redeclared, name);

    else if (type != symbol->type())
	report(conflicting, name);

    return symbol;
}



/*
 * Function:	checkIdentifier
 *
 * Description:	Check if NAME is declared.  If it is undeclared, then
 *		declare it as having the error type in order to eliminate
 *		future error messages.
 */

Symbol *checkIdentifier(const string &name)
{
    Symbol *symbol = toplevel->lookup(name);

    if (symbol == nullptr) {
	report(undeclared, name);
	symbol = new Symbol(name, error);
	toplevel->insert(symbol);
    }

    return symbol;
}


/*
 * Function:	checkFunction
 *
 * Description:	Check if NAME is a previously declared function.  If it is
 *		undeclared, then implicitly declare it.
 */

Symbol *checkFunction(const string &name, Parameters params)
{
    Symbol *symbol = toplevel->lookup(name);
    if (symbol == nullptr){
		symbol = declareFunction(name, Type(INT, 0, nullptr));
	}

	Type id_type = symbol->type();
	if(!id_type.isFunction()){
		report(not_function, ""); //E6: called object is not a function
	}
	
	else if(params.size() > 0){
		for(unsigned i=0; i < params.size(); i++){
			if(!params[i].isPredicate()){
				report(invalid_arguments,"");
				break;
			}
		}
	}	

    return symbol;
}

/*
 * Function: checkLogicalOR
 *
 * Description: performs typechecking for '||' operator
 */
Type checkLogicalOR(Type left, Type right){
	if(left.isPredicate() && right.isPredicate()){
		return Type(INT);
	}
	else{
		report(invalid_binary, "||"); //E4: invalid operands to binary ||
		return error;
	}
}

/*
 * Function: checkLogicalAND
 *
 * Description: performs typechecking for '&&' operator
 */
Type checkLogicalAND(Type left, Type right){
	if(left.isPredicate() && right.isPredicate()) return Type(INT);
	else
	{
		report(invalid_binary, "&&"); //E4: invalid operands to binary &&
		return error;
	}
}

/*
 * Function: checkLogicalEQ
 *
 * Description: performs typechecking for '==' operator
 */
Type checkLogicalEQ(Type left, Type right){
	if(left.isCompatible(right)) return Type(INT);
	else
	{
		report(invalid_binary,"==");
		return error;
	}
}

/*
 * Function: checkLogicalNEQ
 *
 * Description: peforms typechecking for '!=' operator
 */
Type checkLogicalNEQ(Type left, Type right){
	if(left.isCompatible(right)) return Type(INT);
	else
	{
		report(invalid_binary, "!=");
		return error;
	}
}

/*
 * Function: checkRelationalExpr
 *
 * Description: performs typechecking for '>', '<', '>=', '<=' operators
 */
Type checkRelationalExpr(Type left, Type right, string binary_operator)
{
	Type p_left = left.promote();
	Type p_right = right.promote();

	cout << "[CHECKER][RelExp] left: " << left << " right: " << right << endl;
	cout << "[CHECKER][RelExp] p_left: " << p_left << " p_right: " << p_right << endl;

	if((p_left == p_right) && p_left.isPredicate()) return Type(INT);
	else
	{
		report(invalid_binary, binary_operator);
		return error;
	}
}

/*
 * Function: checkAdditiveExpr
 *
 * Description: performs typechecking for '+', '-' binary operators
 */
Type checkAdditiveExpr(Type left, Type right, string binary_operator)
{
	Type result;

	if((left.specifier()==VOID) || (right.specifier()==VOID)){
		result = error;
	}

	else if(left.isInt() || right.isInt())
	{
		if(left.isInt() && right.isInt()) result = Type(INT);
		else if(left.isPointer() && right.isInt()) result = Type(left.specifier(), left.indirection());
		else if((binary_operator=="+") && left.isInt() && right.isPointer()) result = Type(right.specifier(), right.indirection());
	}

	else if((binary_operator=="-") && left.isPointer() && right.isPointer()){
		if(left == right) result = Type(left.specifier(), left.indirection());
	}

	if(result == error) report(invalid_binary, binary_operator);

	return result;
}

/*
 * Function: checkMultiplicativeExpr
 *
 * Description: performs typechecking for '*','/' binary operators
 */
Type checkMultiplicativeExpr(Type left, Type right, string binary_operator)
{
	if(left.isInt() && right.isInt()) return Type(INT);
	else
	{
		report(invalid_binary, binary_operator);
		return error;
	}
}

/*
 * Function: checkNegationExpr
 *
 * Description: performs typechecking on the unary '!' operator
 */
Type checkNegationExpr(Type right)
{
	if(right.isPredicate()) return Type(INT);
	else
	{
		report(invalid_unary, "!");
		return error;
	}
}

/*
 * Function: checkNegativeExpr 
 *
 * Description: performs typechecking on unary '-' operator
 */
Type checkNegativeExpr(Type right)
{
	if(right.isInt()) return Type(INT);
	else
	{
		report(invalid_unary, "-");
		return error;
	}
}

/*
 * Function: checkDerefExpr
 *
 * Description: performs typechecking on unary '*' operator
 */
Type checkDerefExpr(Type right)
{
	if(right.isPointer() && (right.specifier() != VOID)) return Type(right.specifier(), right.indirection()-1);
	else
	{
		report(invalid_unary, "*");
		return error;
	}
}

/*
 * Function: checkAddressExpr
 *
 * Description: performs typechecking on unary '&' operator
 */
Type checkAddressExpr(Type right, bool lvalue)
{
	if(lvalue) return Type(right.specifier(), right.indirection()+1);
	else
	{
		report(lvalue_required, "");
		return error;
	}
}

/*
 * Function: checkSizeofExpr
 *
 * Description: performs typechecking for unary 'sizeof' operator
 */
Type checkSizeofExpr(Type right)
{
	if(right.isPredicate()) return Type(INT);
	else
	{
		report(invalid_unary, "sizeof");
		return error;
	}
}

/*
 * Function: checkPostFixExpr
 *
 * Description: performs typechecking for postfix expressions
 */
Type checkPostFixExpr(Type left, Type right)
{
	if(left.isPointer() && right.isInt()){
		return Type(left.specifier());
	}
	else
	{	
		cout << "[CHECKER][PstFix] left: " << left << " right: " << right << endl;
		cout << "[CHECKER][PstFix] promoted left: " << left.promote() << endl;
		report(invalid_binary, "[]"); //E4: invalid operands to binary []
		return Type();
	}
}

/*
 * Function: checkAssignment
 *
 * Description: performs typechecking for assignments
 */
void checkAssignment(Type left, Type right, bool lvalue)
{
	if(!lvalue) report(lvalue_required, ""); //E3: lvalue required in expression
	else if(!left.isCompatible(right)) report(invalid_binary, "="); //E4: invalid operands to binary =
	else return;
}

/*
 * Function: checkReturnStmt
 *
 * Description: performs typechecking for assignment statements
 */
void checkReturnStmt(Type right){
	Scope* enclosing_scope = toplevel->enclosing();
	if(enclosing_scope != NULL)
	{
		Symbol* function_sym = enclosing_scope->symbols().back();
		Type function_type = function_sym->type();

		if(right.isCompatible(function_type)) return;
		else report(return_type, "");
	}
	else cout << "[CHECKER] NULL scope encountered" << endl;
}

/*
 * Function: checkWhileStmt
 *
 * Description: performs typechecking for while statements
 */
void checkWhileStmt(Type right)
{
	if(!right.isPredicate()) report(test_expression, "");
	else return;
}

/*
 * Function: checkForStmt
 *
 * Description: performs typechecking for for statements
 */
void checkForStmt(Type right)
{
	if(!right.isPredicate()) report(test_expression, "");
	else return;
}

/*
 * Function: checkIfStmt
 *
 * Description: performs typechecking for if statements
 */
void checkIfStmt(Type right){
	if(!right.isPredicate()) report(test_expression, "");
	else return;
}
