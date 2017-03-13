/*
 * File:	Symbol.cpp
 *
 * Description:	This file contains the member function definitions for
 *		symbols in Simple C.  At this point, a symbol merely
 *		consists of a name, a type, and attributes.
 */

# include "Symbol.h"

using std::string;


/*
 * Function:	Symbol::Symbol (constructor)
 *
 * Description:	Initialize a symbol object.
 */

Symbol::Symbol(const string &name, const Type &type)
    : _name(name), _type(type), _attributes(0), _offset(0)
{
}


/*
 * Function:	Symbol::name (accessor)
 *
 * Description:	Return the name of this symbol.
 */

const string &Symbol::name() const
{
    return _name;
}


/*
 * Function:	Symbol::type (accessor)
 *
 * Description:	Return the type of this symbol.
 */

const Type &Symbol::type() const
{
    return _type;
}
