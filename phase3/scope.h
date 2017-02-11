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
	Scope* _parent;
	SymbolList _symPointers;
public:
	//Constructors
	Scope();
	Scope(Scope* parent);
	
	//Getters

	//Setters

	//Methods
	Symbol* find(string name);
	Symbol* lookup(string name);
	void insert(Symbol* s);
};
#endif
