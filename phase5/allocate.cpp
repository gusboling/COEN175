#include "tokens.h"
#include "Tree.h"
#include "Symbol.h"
#include "Scope.h"
#include "Type.h"

using namespace std;

void Function::allocate(int &offset){
	int osResult = 4; //Initialize offset equal to 4

	Type functionType = _id->type();
	int numParams = *functionType.parameters().size();

	for(int i=0; i < numParams; i++) osResult = osResult + 4; //For each parameter, incremement offset by 4



	_id->offset = osResult; //Set function symbol-offset to calculated offset result
}
