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
	return NULL;
}

void Scope::insert(Symbol* s){
	_symPointers.push_back(s);
}
