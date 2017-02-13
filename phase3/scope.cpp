//Libraries
#include <string>
#include <vector>

//Program Headers
#include "type.h"
#include "symbol.h"

//File Header
#include "scope.h"

using namespace std;

Scope::Scope(){
	_parent = NULL;
}

Scope::Scope(Scope* parent){
	_parent = parent;
}

Symbol* Scope::find(string name){
	for(unsigned i=0; i < _symPointers.size(); i++){
		if(name == _symPointers[i]->name()){
			return _symPointers[i];
		}
	}
	return NULL;
}

Symbol* Scope::lookup(string name){
	//Check current scope first
	Symbol* localResult = this->find(name);
	if(localResult != NULL) return localResult;

	//If name isn't in current scope, try parent (RECURSIVE)
	else if(this->_parent != NULL){
		return this->_parent->lookup(name);
	}
	
	else return NULL;
}

Scope* Scope::getParent() const{
	return _parent;
}

void Scope::insert(Symbol* s){
	//TODO: insert code for redefintiion/redeclaration errors
	_symPointers.push_back(s);
}
