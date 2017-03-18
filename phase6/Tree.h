/*
 * File:	Tree.h
 *
 * Description:	This file contains the class definitions for abstract
 *		syntax trees in Simple C.
 *
 *		The base class Node cannot not be instantiated (the
 *		constructor is private).  It provides empty functions for
 *		storage allocation and code generation.
 *
 *		A Node is either a Function, representing a function
 *		definition, or a Statement, which also cannot be
 *		instantiated (again, the constructor is private).
 *
 *		Since the compiler has a very functional design (semantic
 *		checking, storage allocation, code generation), its design
 *		doesn't necessarily mesh well with a tree designed using
 *		object-orientation.  So, here is my compromise:
 *
 *		Tree.h - class definitions
 *		Tree.cpp - constructors and accessors
 *		allocator.cpp - member functions to do storage allocation
 *		generator.cpp - member functions to do code generation
 */

# ifndef TREE_H
# define TREE_H
# include <string>
# include <vector>
# include "Scope.h"

typedef std::vector<class Statement *> Statements;
typedef std::vector<class Expression *> Expressions;


/* The base class */

class Node {
protected:
    typedef std::string string;
    Node() {}

public:
    virtual ~Node() {}
    virtual void allocate(int &offset) const {}
    virtual void generate() {}
};


/* Any type of statement: return, while, if, block, and expression */

class Statement : public Node {
protected:
    Statement() {}
};


/* An expression, and yes, an expression is a statement */

class Expression : public Statement {
protected:
    Type _type;
    bool _lvalue;
    Expression(const Type &_type = Type());

public:
    string _operand;
    const Type &type() const;
    bool lvalue() const;

	void generate();
	void generate(bool &indirect);
};


/* A string literal */

class String : public Expression {
    string _value;

public:
    String(const string &value);
    const string &value() const;
};


/* An identifier expression */

class Identifier : public Expression {
    const Symbol *_symbol;

public:
    Identifier(const Symbol *symbol);
    const Symbol *symbol() const;
    virtual void generate();
};


/* A number (i.e., integer) */

class Number : public Expression {
    string _value;

public:
    Number(unsigned value);
    Number(const string &value);
    const string &value() const;
    virtual void generate();
};


/* A function call expression: id ( args ) */

class Call : public Expression {
    const Symbol *_id;
    Expressions _args;

public:
    Call(const Symbol *id, const Expressions &args, const Type &type);
    virtual void generate();
};


/* A logical negation expression: ! expr */

class Not : public Expression {
    Expression *_expr;

public:
    Not(Expression *expr, const Type &type);
	void generate();
};


/* An arithmetic negation expression: - expr */

class Negate : public Expression {
    Expression *_expr;

public:
    Negate(Expression *expr, const Type &type);
	void generate();
};


/* A dereference expression: * expr */

class Dereference : public Expression {
    Expression *_expr;

public:
    Dereference(Expression *expr, const Type &type);
	void generate(bool &indirect);
	void generate();
};


/* An address expression: & expr */

class Address : public Expression {
    Expression *_expr;

public:
    Address(Expression *expr, const Type &type);
};


/* An integer promotion expression: (int) expr */

class Promote : public Expression {
    Expression *_expr;

public:
    Promote(Expression *expr);
	void generate();
};


/* A multiply expression: left * right */

class Multiply : public Expression {
    Expression *_left, *_right;

public:
    Multiply(Expression *left, Expression *right, const Type &type);
	void generate();
};


/* A divide expression: left / right */

class Divide : public Expression {
    Expression *_left, *_right;

public:
    Divide(Expression *left, Expression *right, const Type &type);
	void generate();
};


/* A remainder expression: left % right */

class Remainder : public Expression {
    Expression *_left, *_right;

public:
    Remainder(Expression *left, Expression *right, const Type &type);
	void generate();
};


/* An addition expression: left + right */

class Add : public Expression {
    Expression *_left, *_right;

public:
    Add(Expression *left, Expression *right, const Type &type);
	void generate();
};


/* A subtraction expression: left - right */

class Subtract : public Expression {
    Expression *_left, *_right;

public:
    Subtract(Expression *left, Expression *right, const Type &type);
	void generate();
};


/* A less-than expression: left < right */

class LessThan : public Expression {
    Expression *_left, *_right;

public:
    LessThan(Expression *left, Expression *right, const Type &type);
	void generate();
};


/* A greater-than expression: left > right */

class GreaterThan : public Expression {
    Expression *_left, *_right;

public:
    GreaterThan(Expression *left, Expression *right, const Type &type);
	void generate();
};


/* A less-than-or-equal expression: left <= right */

class LessOrEqual : public Expression {
    Expression *_left, *_right;

public:
    LessOrEqual(Expression *left, Expression *right, const Type &type);
	void generate();
};


/* A greater-than-or-equal expression: left >= right */

class GreaterOrEqual : public Expression {
    Expression *_left, *_right;

public:
    GreaterOrEqual(Expression *left, Expression *right, const Type &type);
	void generate();
};


/* An equality expression: left == right */

class Equal : public Expression {
    Expression *_left, *_right;

public:
    Equal(Expression *left, Expression *right, const Type &type);
	void generate();
};


/* An inequality expression: left != right */

class NotEqual : public Expression {
    Expression *_left, *_right;

public:
    NotEqual(Expression *left, Expression *right, const Type &type);
	void generate();
};


/* A logical-and expression: left && right */

class LogicalAnd: public Expression {
    Expression *_left, *_right;

public:
    LogicalAnd(Expression *left, Expression *right, const Type &type);
	void generate();
};


/* A logical-or expression: left || right */

class LogicalOr : public Expression {
    Expression *_left, *_right;

public:
    LogicalOr(Expression *left, Expression *right, const Type &type);
	void generate();
};


/* An assignment statement: left = right */

class Assignment : public Statement {
    Expression *_left, *_right;

public:
    Assignment(Expression *left, Expression *right);
    virtual void generate();
};


/* A return statement: return expr */

class Return : public Statement {
    Expression *_expr;

public:
    Return(Expression *expr);
	void generate();
};


/* A block (compound) statement: { decls stmts } */

class Block : public Statement {
    Scope *_decls;
    Statements _stmts;

public:
    Block(Scope *decls, const Statements &stmts);
    Scope *declarations() const;
    virtual void allocate(int &offset) const;
    virtual void generate();
};


/* A while statement: while ( expr ) stmt */

class While : public Statement {
    Expression *_expr;
    Statement *_stmt;

public:
    While(Expression *expr, Statement *stmt);
    virtual void allocate(int &offset) const;
};


/* A for statement: for ( init ; expr ; incr ) stmt */

class For : public Statement {
    Statement *_init;
    Expression *_expr;
    Statement *_incr;
    Statement *_stmt;

public:
    For(Statement *init, Expression *expr, Statement *incr, Statement *stmt);
    virtual void allocate(int &offset) const;
};


/* An if-then or if-then-else statement: if ( expr ) thenStmt else elseStmt */

class If : public Statement {
    Expression *_expr;
    Statement *_thenStmt, *_elseStmt;

public:
    If(Expression *expr, Statement *thenStmt, Statement *elseStmt);
    virtual void allocate(int &offset) const;
};


/* A function definition: id() { body } */

class Function : public Node {
    const Symbol *_id;
    Block *_body;

public:
    Function(const Symbol *id, Block *body);
    virtual void allocate(int &offset) const;
    virtual void generate();
};

# endif /* TREE_H */
