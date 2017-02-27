#include <iostream>

#include "checker.h"
#include "Type.h"
#include "tokens.h"

using namespace std;

int main(){
	Parameters params;
	params.push_back(Type(INT));
	params.push_back(Type(INT));
    
	Type int_type = Type(INT);
	Type function_type = Type(INT, 0, &params);
	Type pointer_type = Type(INT, 1);

	cout << "int_type.isPredicate(): " << int_type.isPredicate() << endl;
	cout << "function_type.isPredicate(): " << function_type.isPredicate() << endl;

	Type LO_result = checkLogicalOR(int_type, function_type);

return 0;}
