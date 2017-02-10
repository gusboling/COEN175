//Libraries
#include <string>

//Program Headers
#include "symbol.h"
#include "type.h"

using namespace std;

#ifndef CHECKER_H
#define CHECKER_H

//Output functions for open and close scopes
void printOpen();
void printClose();

//Output function for declarations
void printArrayDec(string name, unsigned ind, int spec);
void printScalarDec(string name, unsigned ind, int spec);
void printVarDec(string name, unsigned ind, int spec);
void printFunDec(string name, unsigned ind, int spec);

//Ouput function for definitions
void printDef(string name, unsigned ind, int spec);

//Output function for symbol uses
void printSymUse(); //TODO: figure out if this needs to take arguments...

void declareArray(string name, int spec, unsigned ind, unsigned length);
void declareVar(string name, Type t);
#endif /* CHECKER_H */
