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

	osResult = -4; //Reset offset 

	//Calculate offset for function body
	for(unsigned i=0; i < functionSyms.size(); i++)
	{
		if( functionSyms[i]->type().isInteger() || functionSyms[i]->type().isPointer() )
		{
			functionSyms[i]->_offset = offset;
			offset = offset - 4;
		}
		else
		{
			functionSyms[i]->_offset = offset;
			int arrayOffset = functionSyms[i]->type().length() * 4; //Is this right? Ask Gabe.
			offset = offset - arrayOffset;
		}

	}

	_id->_offset = osResult; //Set function symbol-offset to calculated offset result
}
