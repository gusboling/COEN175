/*
 * File:	generator.cpp
 *
 * Description:	This file contains the public and member function
 *		definitions for the code generator for Simple C.
 *
 *		Extra functionality:
 *		- putting all the global declarations at the end
 */

# include <sstream>
# include <iostream>
# include "generator.h"
# include "machine.h"

using namespace std;

static unsigned maxargs;


/*
 * Function:	operator <<
 *
 * Description:	Convenience function for writing the operand of an
 *		expression.
 */

ostream &operator <<(ostream &ostr, Expression *expr)
{
    return ostr << expr->_operand;
}


/*
 * Function:	Identifier::generate
 *
 * Description:	Generate code for an identifier.  Since there is really no
 *		code to generate, we simply update our operand.
 */

void Identifier::generate()
{
    stringstream ss;


    if (_symbol->_offset != 0)
	ss << _symbol->_offset << "(%ebp)";
    else
	ss << global_prefix << _symbol->name();

    _operand = ss.str();
}


/*
 * Function:	Number::generate
 *
 * Description:	Generate code for a number.  Since there is really no code
 *		to generate, we simply update our operand.
 */

void Number::generate()
{
    stringstream ss;


    ss << "$" << _value;
    _operand = ss.str();
}


# if STACK_ALIGNMENT == 4

/*
 * Function:	Call::generate
 *
 * Description:	Generate code for a function call expression, in which each
 *		argument is simply a variable or an integer literal.
 */

void Call::generate()
{
    unsigned numBytes = 0;


    for (int i = _args.size() - 1; i >= 0; i --) {
	_args[i]->generate();
	cout << "\tpushl\t" << _args[i] << endl;
	numBytes += _args[i]->type().size();
    }

    cout << "\tcall\t" << global_prefix << _id->name() << endl;

    if (numBytes > 0)
	cout << "\taddl\t$" << numBytes << ", %esp" << endl;
}

# else

/*
 * If the stack has to be aligned to a certain size before a function call
 * then we cannot push the arguments in the order we see them.  If we had
 * nested function calls, we cannot guarantee that the stack would be
 * aligned.
 *
 * Instead, we must know the maximum number of arguments so we can compute
 * the size of the frame.  Again, we cannot just move the arguments onto
 * the stack as we see them because of nested function calls.  Rather, we
 * have to generate code for all arguments first and then move the results
 * onto the stack.  This will likely cause a lot of spills.
 *
 * For now, since each argument is going to be either a number of in
 * memory, we just load it into %eax and then move %eax onto the stack.
 */

void Call::generate()
{
    if (_args.size() > maxargs)
	maxargs = _args.size();

    for (int i = _args.size() - 1; i >= 0; i --) {
	_args[i]->generate();
	cout << "\tmovl\t" << _args[i] << ", %eax" << endl;
	cout << "\tmovl\t%eax, " << i * SIZEOF_ARG << "(%esp)" << endl;
    }

    cout << "\tcall\t" << global_prefix << _id->name() << endl;
}

# endif


/*
 * Function:	Assignment::generate
 *
 * Description:	Generate code for this assignment statement, in which the
 *		right-hand side is an integer literal and the left-hand
 *		side is an integer scalar variable.  Actually, the way
 *		we've written things, the right-side can be a variable too.
 */

void Assignment::generate()
{
    _left->generate();
    _right->generate();

    cout << "\tmovl\t" << _right << ", %eax" << endl;
    cout << "\tmovl\t%eax, " << _left << endl;
}


/*
 * Function:	Block::generate
 *
 * Description:	Generate code for this block, which simply means we
 *		generate code for each statement within the block.
 */

void Block::generate()
{
    for (unsigned i = 0; i < _stmts.size(); i ++)
	_stmts[i]->generate();
}


/*
 * Function:	Function::generate
 *
 * Description:	Generate code for this function, which entails allocating
 *		space for local variables, then emitting our prologue, the
 *		body of the function, and the epilogue.
 */

void Function::generate()
{
    int offset = 0;


    /* Generate our prologue. */

    allocate(offset);
    cout << global_prefix << _id->name() << ":" << endl;
    cout << "\tpushl\t%ebp" << endl;
    cout << "\tmovl\t%esp, %ebp" << endl;
    cout << "\tsubl\t$" << _id->name() << ".size, %esp" << endl;


    /* Generate the body of this function. */

    maxargs = 0;
    _body->generate();

    offset -= maxargs * SIZEOF_ARG;

    while ((offset - PARAM_OFFSET) % STACK_ALIGNMENT)
	offset --;


    /* Generate our epilogue. */

    cout << "\tmovl\t%ebp, %esp" << endl;
    cout << "\tpopl\t%ebp" << endl;
    cout << "\tret" << endl << endl;

    cout << "\t.globl\t" << global_prefix << _id->name() << endl;
    cout << "\t.set\t" << _id->name() << ".size, " << -offset << endl;

    cout << endl;
}


/*
 * Function:	generateGlobals
 *
 * Description:	Generate code for any global variable declarations.
 */

void generateGlobals(const Symbols &globals)
{
    if (globals.size() > 0)
	cout << "\t.data" << endl;

    for (unsigned i = 0; i < globals.size(); i ++) {
	cout << "\t.comm\t" << global_prefix << globals[i]->name();
	cout << ", " << globals[i]->type().size();
	cout << ", " << globals[i]->type().alignment() << endl;
    }
}

/*
 * Function: Expression::generate
 *
 * Description: Generate code for "||" operator, and other expressions recursively
 */

void Expression::generate()
{
	cout << "Nothing here yet (Expression::generate)" << endl;	
}

/*
 * Function: LogicalOr::generate_left
 *
 * Description: Generate code for the left operand of the "||" operator
 */

void LogicalOr::generate_left()
{
	_left->generate();

	cout << "movl\t" << _left << ",%eax" << endl;
	cout << "cmpl\t$0,%eax" << endl;
	cout << "jne\t" << label_prefix << endl; //TODO: Figure out how to generate label code
}

/*
 * Function: LogicalAnd::generate_right
 *
 * Description: Generate code for the right operand of the "||" operator
 */

void LogicalOr::generate_right()
{
	_right->generate();

	cout << "movl\t" << _right << ",%eax" << endl;
	cout << "cmpl\t$0,%eax" << endl;
}

/*
 * Function: LogicalAnd::generate_left
 *
 * Description: Generate code for the left operand of the "&&" operator
 */

void LogicalAnd::generate_left()
{
	_left->generate();

	cout << "movl\t" << _left << ",%eax" << endl;
	cout << "cmpl\t$0,%eax" << endl;
	cout << "je\t" << label_prefix << endl;
}

/*
 * Function: LogicalAnd::generate_right
 *
 * Description: Generate code for the right operand of the "&&" operator
 */

void LogicalAnd::generate_right()
{
	_right->generate();

	cout << "movl\t" << _right << ",%eax" << endl;
	cout << "cmpl\t$0,%eax" << endl;
}
