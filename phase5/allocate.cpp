//Libraries
#include <iostream>

//Program Headers
#include "tokens.h"
#include "Tree.h"
#include "Symbol.h"
#include "Scope.h"
#include "Type.h"

using namespace std;

void Function::allocate(int &offset){
	int osResult = 8; //Initialize offset equal to 4
	Symbols functionSyms = _body->declarations()->symbols(); //Get vector of function symbols from Block member	
	
	//Calculate offset for function parameters
	int numParams = _id->type().parameters()->size();

	for(int i=0; i < numParams; i++) 
	{
		functionSyms[i]->_offset = osResult;		
		osResult = osResult + 4; //For each parameter, incremement offset by 4
	}

	osResult = 0; //Reset offset 

	//Calculate offset for function body
	for(unsigned i=0; i < functionSyms.size(); i++)
	{
		if( functionSyms[i]->type().isInteger() || functionSyms[i]->type().isPointer() )
		{
			osResult = osResult - 4;
			functionSyms[i]->_offset = osResult; 
			//cerr << "[ALLOCATE][FUNC_SYM][INT|PTR] name: " << functionSyms[i]->name() << " offset: " << functionSyms[i]->_offset << endl;
		}
		else
		{
			int arrayOffset = functionSyms[i]->type().length() * 4; //Is this right? Ask Gabe.
			//cerr << "[ALLOCATE][FUNC_SYM][ARRAY] name: " << functionSyms[i]->name() << " offset: " << functionSyms[i]->_offset << endl;
			osResult = osResult - arrayOffset;
			functionSyms[i]->_offset = offset;
		}

	}

	offset = osResult; //Set function symbol-offset to calculated offset result
}
