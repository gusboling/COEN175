#include <iostream>
#include <string>
#include <vector>

#include "Type.h"
#include "tokens.h"

using namespace std;

int main(){
	//OVERLOADED ASSIGNMENT OPERATOR TESTS
	Type int_type = Type(INT);
	Type error_type = Type();
	bool result = (int_type == error_type);
	cout << "int_type == error_type:\nCORRECT: 0\nACTUAL: " << result << endl;

	error_type = int_type;
	result = (int_type == error_type);
	cout << "int_type == (error_type = int_type):\nCORRECT: 1\nACTUAL: " << result << endl;

	
	
	//PROMOTION TESTS (CHAR -> INT)
	Type char_type = Type(CHAR);
	result = (char_type == int_type);
	cout << "char_type == int_type:\nCORRECT: 0\nACTUAL: " << result << endl;

	Type promoted_char_type = char_type.promote();
	result = (promoted_char_type == int_type);
	cout << "promoted_char_type == int_type):\nCORRECT: 1\nACTUAL: " << result << endl;
	
	Type promoted_int_type = int_type.promote();
    Type fresh_int_type = Type(INT);
	cout << "promoted_int_type == int_type:\nCORRECT: 1\nACTUAL: " << (promoted_char_type == fresh_int_type) << endl;

	
	
	//PROMOTION TESTS (ARRAY<T> -> POINTER<T>)
	Type array_type = Type(INT, 0, 10); //Type of "Array of INT, length=10"
	Type pointer_type = Type(INT, 1);
	cout << "array_type == pointer_type:\nCORRECT: 0\nACTUAL: " << (array_type == pointer_type) << endl;

	Type promoted_array_type = array_type.promote();
	cout << "promoted_array_type == pointer_type:\nCORRECT: 1\nACTUAL: " << (promoted_array_type == pointer_type) << endl;

	Type promoted_pointer_type = pointer_type.promote();
	cout << "promoted_pointer_type == pointer_type:\nCORRECT: 1\nACTUAL: " << (promoted_pointer_type == pointer_type) << endl;


	//PREDICATE TESTS
	cout << "pointer_type.isPredicate():\nCORRECT: 1\nACTUAL: " << pointer_type.isPredicate() << endl;
	cout << "array_type.isPredicate():\nCORRECT: 1\nACTUAL: " << array_type.isPredicate() << endl;

	cout << "int_type.isPredicate():\nCORRECT: 1\nACTUAL: " << int_type.isPredicate() << endl;
	cout << "char_type.isPredicate():\nCORRECT: 1\nACTUAL: " << char_type.isPredicate() << endl;


	Parameters p;
	p.push_back(Type(INT));
	p.push_back(Type());
	Type function_type = Type(INT, 0, &p);
	cout << "function_type.isPredicate():\nCORRECT: 0\nACTUAL: " << function_type.isPredicate() << endl;	

	//TYPE COMPATIBILITY TESTS

return 0;}
