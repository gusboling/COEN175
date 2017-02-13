//Libraries
#include <string>
#include <iostream>

//Program Headers
#include "lexer.h"

//File Header
#include "error.h"

using namespace std;

void conf_types(string name){
	cerr << "line " << lineno << ": conflicting types for '" << name << "'"  << endl;
}

void redef(string name){
	cerr << "line " << lineno << ": redefinition of '" << name << "'" << endl;
}

void redec(string name){
	cerr << "line " << lineno << ": redeclaration of '" << name << "'" << endl;
}

void undec(string name){
	cerr << "line " << lineno << ": '" << name << "' undeclared" << endl;
}

void void_type(string name){
	cerr << "line " << lineno << ": '" << name << "' has type void" << endl;
}
