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
}

Symbol* Scope::find(string name){
	for(unsigned i=0; i < this->symPointers.size(); i++){
		if(name == this->symPointers[i]->name()){
			return this->symPointers[i];
		}
	}
	return NULL;
}

Symbol* Scope::lookup(string name){
	return NULL;
}

void Scope::insert(Symbol* s){
	this->symPointers.push_back(s);
}
