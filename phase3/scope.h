//Libraries
#include <string>
#include <vector>

//Program Headers
#include "symbol.h"
#include "type.h"

#ifndef SCOPE_H
#define SCOPE_H

typedef std::vector<Symbol *> SymbolList; 

class Scope{
private:
	SymbolList symPointers;
public:
	//Constructors
	Scope();
	
	//Getters

	//Setters

	//Methods
	Symbol* find(string name);
	Symbol* lookup(string name);
	void insert(Symbol* s);
};
#endif
