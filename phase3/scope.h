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
	Scope* getParent() const;

	//Setters
	void insert(Symbol* s);

	//Methods
	Symbol* find(string name); //Checks for name in the current scope, returns NULL if absent
	Symbol* lookup(string name); //Checks for name in the current & enclosing scopes, returns NULL if absent
};
#endif
