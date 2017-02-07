#include <string>

using namespace std;

#ifndef CHECKER_H
#define CHECKER_H

//Output functions for open and close scopes
static void printOpen();
static void printClose();

//Output function for declarations
static void printArrayDec(string name, unsigned ind, int spec);
static void printScalarDec(string name, unsigned ind, int spec);
static void printVarDec(string name, unsigned ind, int spec);
static void printFunDec(string name, unsigned ind, int spec);

//Ouput function for definitions
static void printDef(string name, unsigned ind, int spec);

//Output function for symbol uses
static void printSymUse(); //TODO: figure out if this needs to take arguments...

#endif /* CHECKER_H */
