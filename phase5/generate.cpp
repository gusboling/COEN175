#include "Tree.h"

using namespace std;

void Function::generate(){
	int offset = 0;
	allocate(offset);
	
	//START Function Prologue
	cout << ".globl\t" << _id->name() << endl;
	cout << _id->name() << ":" << endl;
	cout << "pushl\t%ebp" << endl;
	cout << "movl\t%esp, %ebp" << endl;
	cout << "subl\t$" << -_offset << ",%ebp" << endl;
	//END Function Prologue

	_body->generate();

	//START Function Epilogue
	cout << "movl\t%ebp,%esp" << endl;
	cout << "popl\t%ebp" << endl;
	cout << "ret" << endl << endl;
	//END Function Epilogue
}

void Block::generate(){
	//TODO: What the hell goes here?
}

void Call::generate(){

}

void Identifier::generate(){

}

void Number::generate(){

}

void Assignment::generate(){

}



