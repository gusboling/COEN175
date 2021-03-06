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
	cout << "\tpushl\t%ebp" << endl;
	cout << "\tmovl\t%esp, %ebp" << endl;
	cout << "\tsubl\t$" << -offset << ",%esp" << endl;
	//END Function Prologue

	_body->generate();

	//START Function Epilogue
	cout << "\tmovl\t%ebp,%esp" << endl;
	cout << "\tpopl\t%ebp" << endl;
	cout << "\tret" << endl << endl;
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
		//cout << "\t"; //So it looks nice...
		_stmts[i]->generate();
	}
}

void Call::generate()
{
	for(int i = (int)_args.size()-1; i >= 0; i--)
	{
		_args[i]->generate();
		cout << "\tpushl\t" << _args[i]->_location << endl;
	}
	
	cout << "\tcall\t" << _id->name() << endl;
}

void Identifier::generate(){
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
	cout << "\tmovl\t" << _right->_location << ",%eax" << endl; 
	cout << "\tmovl\t%eax," << _left->_location << endl;
}



