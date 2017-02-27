/*
 * File:	Type.cpp
 *
 * Description:	This file contains the member function definitions for
 *		types in Simple C.  A type is either a scalar type, an
 *		array type, or a function type.
 *
 *		Note that we simply don't like putting function definitions
 *		in the header file.  The header file is for the interface.
 *		Actually, we prefer opaque pointer types in C where you
 *		don't even get to see what's inside, much less touch it.
 *		But, C++ lets us have value types with access control
 *		instead of just always using pointer types.
 *
 *		Extra functionality:
 *		- equality and inequality operators
 *		- predicate functions such as isArray()
 *		- stream operator
 *		- the error type
 */

# include <cassert>
# include "Type.h"
# include "tokens.h"

using namespace std;


/*
 * Function:	Type::Type (constructor)
 *
 * Description:	Initialize this type as an error type.
 */

Type::Type()
    : _kind(ERROR)
{
}


/*
 * Function:	Type::Type (constructor)
 *
 * Description:	Initialize this type object as a scalar type.
 */

Type::Type(int specifier, unsigned indirection)
    : _specifier(specifier), _indirection(indirection), _kind(SCALAR)
{
}


/*
 * Function:	Type::Type (constructor)
 *
 * Description:	Initialize this type object as an array type.
 */

Type::Type(int specifier, unsigned indirection, unsigned length)
    : _specifier(specifier), _indirection(indirection), _length(length)
{
    _kind = ARRAY;
}


/*
 * Function:	Type::Type (constructor)
 *
 * Description:	Initialize this type object as a function type.
 */

Type::Type(int specifier, unsigned indirection, Parameters *parameters)
    : _specifier(specifier), _indirection(indirection), _parameters(parameters)
{
    _kind = FUNCTION;
}


/*
 * Function:	Type::operator ==
 *
 * Description:	Return whether another type is equal to this type.  The
 *		parameter lists are checked for function types, which C++
 *		makes so easy.  (At least, it makes something easy!)
 */

bool Type::operator ==(const Type &rhs) const
{
    if (_kind != rhs._kind)
	return false;

    if (_kind == ERROR)
	return true;

    if (_specifier != rhs._specifier)
	return false;

    if (_indirection != rhs._indirection)
	return false;

    if (_kind == SCALAR)
	return true;

    if (_kind == ARRAY)
	return _length == rhs._length;

    if (_parameters == rhs._parameters)
	return true;

    if (_parameters == nullptr || rhs._parameters == nullptr)
	return false;

    return *_parameters == *rhs._parameters;
}


/*
 * Function:	Type::operator !=
 *
 * Description:	Well, what do you think it does?  Why can't the language
 *		generate this function for us?  Because they think we want
 *		it to do something else?  Yeah, like that'd be a good idea.
 */

bool Type::operator !=(const Type &rhs) const
{
    return !operator ==(rhs);
}


/*
 * Function:	Type::operator =
 *
 * Description: An overloaded assignment operator for the Type class.All members of this 
 * 		type are set equal to the corresponding members of the rhs type.
 */
void Type::operator =(const Type &rhs) 
{
	_specifier = rhs.specifier();
	_indirection = rhs.indirection();

	if(rhs.isScalar()) _kind = SCALAR;
	else if(rhs.isArray())
	{
		_kind = ARRAY;
		_length = rhs.length();
	}
	else if(rhs.isFunction())
	{
		_kind = FUNCTION;
		_parameters = rhs.parameters();
	}
	else _kind = ERROR;
}


/*
 * Function:	Type::isArray
 *
 * Description:	Return whether this type is an array type.
 */

bool Type::isArray() const
{
    return _kind == ARRAY;
}


/*
 * Function:	Type::isScalar
 *
 * Description:	Return whether this type is a scalar type.
 */

bool Type::isScalar() const
{
    return _kind == SCALAR;
}


/*
 * Function:	Type::isFunction
 *
 * Description:	Return whether this type is a function type.
 */

bool Type::isFunction() const
{
    return _kind == FUNCTION;
}


/*
 * Function:	Type::isError
 *
 * Description:	Return whether this type is an error type.
 */

bool Type::isError() const
{
    return _kind == ERROR;
}


/*
 * Function:	Type::specifier (accessor)
 *
 * Description:	Return the specifier of this type.
 */

int Type::specifier() const
{
    return _specifier;
}


/*
 * Function:	Type::indirection (accessor)
 *
 * Description:	Return the number of levels of indirection of this type.
 */

unsigned Type::indirection() const
{
    return _indirection;
}


/*
 * Function:	Type::length (accessor)
 *
 * Description:	Return the length of this type, which must be an array
 *		type.  Is there an better way than calling assert?  There
 *		certainly isn't an easier way.
 */

unsigned Type::length() const
{
    assert(_kind == ARRAY);
    return _length;
}


/*
 * Function:	Type::parameters (accessor)
 *
 * Description:	Return the parameters of this type, which must be a
 *		function type.
 */

Parameters *Type::parameters() const
{
    assert(_kind == FUNCTION);
    return _parameters;
}

/*
 * Function:	Type::promote 
 *
 * Description: If applicable, return the promoted form of this type.
 * 		Otherwise, return a copy of this type.
 *
 * 		char -> int
 *		array of T -> pointer to a T
 */

Type Type::promote() const
{
	Type promote_result = Type(); 

	if(isScalar() && (_specifier == CHAR))
	{
		promote_result = Type(INT);
	}
	else if(isArray())
	{
		int ptr_specifier = _specifier;
		unsigned ptr_indirection = 1;
		promote_result = Type(ptr_specifier, ptr_indirection);
	}
	else
	{
		promote_result = *this;	
	}
	return promote_result;
}

bool Type::isInt() const
{
	if(*this == Type(INT)) return true;
	else return false;
}

bool Type::isPointer() const
{
	Type promoted_form = this->promote();
	if(!promoted_form.isFunction() && (promoted_form.indirection() > 0)) return true;
	else return false;
}

bool Type::isPredicate() const
{
	Type promoted_form = this->promote();
	if(promoted_form.isInt() || promoted_form.isPointer()) return true;
	else return false;
}

bool Type::isCompatible(const Type &that) const
{
	Type promoted_this = this->promote();
	Type promoted_that = that.promote();

	if(promoted_this.isPredicate() && promoted_that.isPredicate())
	{
		if(promoted_this == promoted_that) return true; //this and that are identical predicate types
	}

	else if(promoted_this.isPointer() && (promoted_this.specifier() != VOID))
	{
		if(promoted_that.isPointer() && (promoted_that.specifier() == VOID)) return true; //this is of type 'POINTER<T>' and that is of type 'POINTER<VOID>
	}

	else if(promoted_that.isPointer() && (promoted_that.specifier() != VOID))
	{
		if(promoted_this.isPointer() && (promoted_this.specifier() == VOID)) return true; //that is of type 'POINTER<T>' and this is of type 'POINTER<VOID>'
	}

 	return false;
}

/*
 * Function:	operator <<
 *
 * Description:	Write a type to the specified output stream.  At least C++
 *		let's us do some cool things.
 */

ostream &operator <<(ostream &ostr, const Type &type)
{
    if (type.isError())
	ostr << "error";

    else {
	if (type.specifier() == INT)
	    ostr << "int";
	else if (type.specifier() == CHAR)
	    ostr << "char";
	else if (type.specifier() == VOID)
	    ostr << "void";
	else
	    ostr << type.specifier();		// shouldn't happen

	if (type.indirection() > 0) {
	    ostr << " ";

	    for (unsigned i = 0; i < type.indirection(); i ++)
		ostr << "*";
	}

	if (type.isArray())
	    ostr << "[" << type.length() << "]";

	else if (type.isFunction()) {
	    ostr << "(";

	    if (type.parameters() != nullptr) {
		if (type.parameters()->size() == 0)
		    ostr << "void";
		else
		    for (unsigned i = 0; i < type.parameters()->size(); i ++) {
			if (i > 0)
			    ostr << ", ";
			ostr << (*type.parameters())[i];
		    }
	    }

	    ostr << ")";
	}
    }

    return ostr;
}
