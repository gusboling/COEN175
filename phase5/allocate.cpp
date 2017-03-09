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
	int osResult = 8; 
	Symbols functionSyms = _body->declarations()->symbols(); //Get vector of function symbols from Block member	
	
	//Calculate offset for function parameters
	int numParams = _id->type().parameters()->size();
	int numLocals = functionSyms.size();

	for(int i=0; i < numParams; i++) 
	{
		functionSyms[i]->_offset = osResult;		
		osResult = osResult + 4; 
	}

	osResult = 0;  

	//Calculate offset for function body
	for(int i=numParams; i < numLocals; i++)
	{
		if( functionSyms[i]->type().isInteger() || functionSyms[i]->type().isPointer() )
		{
			osResult = osResult - 4;
			functionSyms[i]->_offset = osResult; 
		}
		else if( functionSyms[i]->type().isArray() )
		{
			int arrayOffset = functionSyms[i]->type().length() * 4; 
			osResult = osResult - arrayOffset;
			functionSyms[i]->_offset = offset;
		}

	}

	//offset = osResult; //Set function symbol-offset to calculated offset result
}
