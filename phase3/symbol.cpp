//Library
#include <string>

//Program Headers
#include "type.h"

//File Header
#include "symbol.h"

using namespace std;

Symbol::Symbol(){
}

Symbol::Symbol(string name, const Type& t, bool def){
    _name = name;
    _t = t;
    _def = def;
}

string Symbol::name() const{
    return _name;
}

bool Symbol::isDef() const{
    return _def;
}
