/*
 * File:	Symbol.h
 *
 * Description:	This file contains the class definition for symbols in
 *		Simple C.  At this point, a symbol merely consists of a
 *		name and a type, neither of which you can change, along
 *		with attributes, which you can change.  The attributes are
 *		actually public, because as the symbol class itself, we
 *		place no constraints on what values an attribute may have.
 */

# ifndef SYMBOL_H
# define SYMBOL_H
# include <string>
# include "Type.h"

class Symbol {
    typedef std::string string;
    string _name;
    Type _type;

public:
    int _attributes;
    int _offset;

    Symbol(const string &name, const Type &type);
    const string &name() const;
    const Type &type() const;
};

# endif /* SYMBOL_H */
