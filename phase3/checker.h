//Libraries
#include <string>
#include <vector>

//Program Headers
#include "scope.h"
#include "symbol.h"
#include "type.h"

using namespace std;

#ifndef CHECKER_H
#define CHECKER_H

//Scope Variables
typedef vector<class Scope> ScopeList;

//Output functions for open and close scopes
void openScope();
void closeScope();

//DEFUNCT (DELETE WHEN STABLE)
void printArrayDec(string name, unsigned ind, int spec);
void printScalarDec(string name, unsigned ind, int spec);
void printVarDec(string name, unsigned ind, int spec);

//Ouput function for definitions
void printDef(string name, unsigned ind, int spec);

//Output function for symbol uses
void printSymUse(); //TODO: figure out if this needs to take arguments...

//Output functions for declarations
void declareArray(string name, int spec, unsigned ind, unsigned length);
void declareVar(string name, Type t);
void declareFunction(string name, int spec, unsigned ind);
#endif /* CHECKER_H */
