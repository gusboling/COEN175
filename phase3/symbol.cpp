#include <string>

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
