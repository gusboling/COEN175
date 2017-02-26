#include <iostream>
#include <string>

#include "Type.h"
#include "tokens.h"

using namespace std;

int main(){
	Type int_type = Type(INT);
	Type error_type = Type();

	//OVERLOADED EQUALITY OPERATOR TESTS
	bool result = (int_type == error_type);
	cout << "int_type == error_type:\nCORRECT: 0\nACTUAL: " << result << endl;

	error_type = int_type;
	result = (int_type == error_type);
	cout << "int_type == (error_type = int_type):\nCORRECT: 1\nACTUAL: " << result << endl;

	//PROMOTION TESTING (CHAR -> INT)
	Type char_type = Type(CHAR);
	result = (char_type == int_type);
	cout << "char_type == int_type:\nCORRECT: 0\nACTUAL: " << result << endl;

	Type promoted_char_type = char_type.promote();
	result = (promoted_char_type == int_type);
	cout << "promoted_char_type == int_type):\nCORRECT: 1\nACTUAL: " << result << endl;

	//PROMOTION TESTING (ARRAY<T> -> POINTER<T>)
	Type array_type = Type(INT, 0, 10); //Type of "Array of INT, length=10"
	Type pointer_type = Type(INT, 1);
	cout << "array_type == pointer_type:\nCORRECT: 0\nACTUAL: " << (array_type == pointer_type) << endl;

	Type promoted_array_type = array_type.promote();
	cout << "promoted_array_type == pointer_type:\nCORRECT: 1\nACTUAL: " << (promoted_array_type == pointer_type) << endl;

	cout << "promoted_char_type == promoted_array_type:\nCORRECT: 0\nACTUAL: " << (promoted_char_type == promoted_array_type) << endl;

	return 0;
}
