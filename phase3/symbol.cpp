//Library
#include <string>

//Program Headers
#include "type.h"

//File Header
#include "symbol.h"

using namespace std;

Symbol::Symbol(string name, Type t, bool def=false){
    _name = name;
    _t = t;
    _def = def;
}

string Symbol::name() const{
    return name;
}

bool Symbol::isDef() const{
    return _def;
}
