/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include "evalstate.h"
#include "exp.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include <string>

using namespace std;

 /*
  * Type: StatementType
  * --------------------
  * This enumerated type is used to differentiate the different
  * Statement types: RUN, IF_THEN, EXPRESSION, QUIT, LIST
  */

enum StatementType { RUN, IF_THEN, QUIT, LIST, GOTO};


/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

   Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

   virtual void execute(EvalState & state) = 0;

   virtual StatementType gettype() = 0;

   virtual bool is_statement(TokenScanner state) = 0;

};

/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */

class Run : public Statement{
private:
	std::string content;

public:
	Run(string _content) { content = _content; };

	~Run() { content = ""; };

	void execute(EvalState & state);

	StatementType gettype() { return RUN; };

	bool is_statement(TokenScanner statement);
};

/* If_Then Class*/

class If_Then : public Statement {
private:
	std::string content;

public:
	If_Then(string _content) : content(_content) {};

	~If_Then() { content = ""; };

	void execute(EvalState & state);

	StatementType gettype() { return IF_THEN; };

	bool is_statement(TokenScanner statement);
};

/* Quit Class*/

class Quit : public Statement {
private:
	std::string content;

public:
	Quit(string _content) : content(_content) {};

	~Quit() { content = ""; };

	void execute(EvalState & state);

	StatementType gettype() { return QUIT; };

	bool is_statement(TokenScanner statement);
};

/* List Class*/

class List : public Statement {
private:
	std::string content;

public:
	List(string _content) : content(_content) {};

	~List() { content = ""; };

	void execute(EvalState & state);

	StatementType gettype() { return LIST; };

	bool is_statement(TokenScanner statement);
};

/* Goto Class*/

class Goto : public Statement {
private:
	std::string content;

public:
	Goto(string _content) : content(_content) {};

	~Goto() { content = ""; };

	void execute(EvalState & state);

	StatementType gettype() { return GOTO; };

	bool is_statement(TokenScanner statement);
};

#endif