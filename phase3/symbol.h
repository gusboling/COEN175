#include <string>

#include "type.h"

using namespace std;

class Symbol{
private:
    string _name;
    Type _t;
    bool _def;

public:
    //Constructor
    Symbol(string name, Type t, bool def=false);

    //Getters
    bool isDef() const;
    string name() const;
};
