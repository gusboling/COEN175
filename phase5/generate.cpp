//Libraries
#include <iostream>
#include <sstream>

//Program Headers
#include "Tree.h"

using namespace std;

/*
 * Function:	function::generate()
 *
 * Description: Output the appropriate object code for the given function object
 */
void Function::generate()
{
	int offset = 0;
	allocate(offset);//Updates the value of offset
	
	//START Function Prologue
	cout << ".globl\t" << _id->name() << endl;
	cout << _id->name() << ":" << endl;
	cout << "pushl\t%ebp" << endl;
	cout << "movl\t%esp, %ebp" << endl;
	cout << "subl\t$" << -offset << ",%ebp" << endl;
	//END Function Prologue

	_body->generate();

	//START Function Epilogue
	cout << "movl\t%ebp,%esp" << endl;
	cout << "popl\t%ebp" << endl;
	cout << "ret" << endl << endl;
	//END Function Epilogue
}

/*
 * Function:	Block::generate()
 *
 * Description: Cycles through block statements (either function calls or assignments) and call the 
 * associated generate function.
 */
void Block::generate()
{
	for(size_t i = 0; i < _stmts.size(); i++)
	{
		//For each statement pointer, call its associated generate method
		_stmts[i]->generate();
	}
}

void Call::generate()
{
	for(size_t i = _args.size(); i < 0; i--)
	{
		_args[i]->generate();
		cout << "pushl\t" << _args[i]->_location << endl;
	}
	
	cout << "call\t" << _id->name() << endl;
}

void Identifier::generate(){
	cerr << "[IDENTIFIER][GENERATE] symbol->_name: " << _symbol->name() << endl;
	stringstream conversionStream;
	conversionStream << symbol()->_offset;
	string stringOffset = conversionStream.str();

	if(_symbol->_offset == 0) _location = _symbol->name(); //For global variables
	else _location = stringOffset + "(%ebp)";
}

void Number::generate(){
	//Update inherited location member to literal value
	_location = "$" + value();
}

void Assignment::generate(){
	//The value of the right operand replaces that of the object referred to by the lvalue of the left operand	
	_right->generate();
	_left->generate();
	cout << "movl\t" << _right->_location << ",%eax" << endl; 
	cout << "movl\t%eax," << _left->_location << endl;
}



