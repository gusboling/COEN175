#include "type.h"
#include <cstdlib>
#include <ostream>

Type::Type(kind new_kind, int specifier, unsigned indirection){
	_kind = new_kind;
	_specifier = specifier;
	_indirection = indirection;
}

kind Type::get_kind() const{ 
	return _kind;
}

int Type::get_specifier() const{
	return _specifier;
}

unsigned Type::get_indirection() const{
	return _indirection;
}

bool Type::operator ==(const Type &that) const{
	if(_kind != that.get_kind()) return false;
	else if(_specifier != that.get_specifier()) return false;
	else if(_indirection != that.get_indirection()) return false;
	else return true;
}

bool Type::operator !=(const Type &that) const{
	return !(*this == that);
}

std::ostream &operator <<(std::ostream &ostr, const Type &type){
	ostr << "(" << type.get_kind() << "," << type.get_specifier() << "," << type.get_indirection() << ")";
	return ostr;
}
