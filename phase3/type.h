#include <ostream>

#ifndef TYPE_H
#define TYPE_H

enum kind{
	SCALAR, ARRAY, FUNCTION
};

class Type{
private:
	kind _kind;
	int _specifier;
	unsigned _indirection;
public:
	//Constructor
	Type(kind kind, int specifier, unsigned indirection=0);

	//Getters	
	kind get_kind() const;
	int get_specifier() const;
	unsigned get_indirection() const;
	
	//Operator Overloads
	bool operator ==(const Type &that) const;
	bool operator !=(const Type &that) const;
	std::ostream &operator <<(std::ostream &ostr, const Type &type);
	
};

#endif //TYPE_H
	
