/*
 * File:	checker.h
 *
 * Description:	This file contains the public function declarations for the
 *		semantic checker for Simple C.
 */

using namespace std;

# ifndef CHECKER_H
# define CHECKER_H

#include <string>

# include "Scope.h"
# include "Type.h"


Scope *openScope();
Scope *closeScope();

Symbol *defineFunction(const std::string &name, const Type &type);
Symbol *declareFunction(const std::string &name, const Type &type);
Symbol *declareVariable(const std::string &name, const Type &type);
Symbol *checkIdentifier(const std::string &name);
Symbol *checkFunction(const std::string &name, Parameters params);

Type checkLogicalOR(Type left, Type right);
Type checkLogicalAND(Type left, Type right);

Type checkLogicalEQ(Type left, Type right);
Type checkLogicalNEQ(Type left, Type right);

Type checkRelationalExpr(Type left, Type right, string binary_operator);

Type checkAdditiveExpr(Type left, Type right, string binary_operator);

Type checkMultiplicativeExpr(Type left, Type right, string binary_operator);

Type checkNegationExpr(Type right);
Type checkNegativeExpr(Type right);
Type checkDerefExpr(Type right);
Type checkAddressExpr(Type right, bool lvalue);
Type checkSizeofExpr(Type right);

Type checkPostFixExpr(Type left, Type right);

void checkReturnStmt(Type right);
void checkWhileStmt(Type right);
void checkForStmt(Type right);
void checkIfStmt(Type right);
void checkAssignment(Type left, Type right, bool lvalue); 

# endif /* CHECKER_H */
