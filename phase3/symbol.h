//Libraries
#include <string>

//Program Headers
#include "type.h"

using namespace std;

#ifndef SYMBOL_H
#define SYMBOL_H
class Symbol{
private:
    string _name;
    Type _t;
    bool _def;

public:
    //Constructor
    Symbol();
    Symbol(string name, const Type& t, bool def=false);

    //Getters
    bool isDef() const;
    string name() const;
};
#endif
