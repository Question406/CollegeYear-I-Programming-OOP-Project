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


enum lineStatement{Invalidline, GOTO, REM, PRINT, IF, INPUT, END, LET, Clearline};
//

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

#include "evalstate.h"
#include "exp.h"

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

   virtual bool is_statement(EvalState & state) = 0;
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

 /*-----------------------------------------------------*/

class Let : public Statement {
private:
	string line;
	string var;
	int value;
	bool run;

public:
	Let(string _line, bool _run) : line(_line) , run(_run) {};
	~Let() {};
	void execute(EvalState & state);
	bool is_statement(EvalState & state);
};

/*-----------------------------------------------------*/

class Input : public Statement {
private:
	string var, line;
private:
	void getvar();

public:
	Input(string _line) : line(_line) {};
	~Input() {};
	void execute(EvalState & state);
	bool is_statement(EvalState & state);
};


/*-----------------------------------------------------*/
class If : public Statement {
private:
	char if_op;
	bool run;
	string line;
	string exp1, exp2;
	int value1, value2, linenum, gotolinenum;

public:
	If(string _line, bool _run) : line(_line), run(_run) {};
	~If() {};
	void execute(EvalState & state);
	bool is_statement(EvalState & state);
	int getlinenum();
};


/*-----------------------------------------------------*/
class Goto : public Statement {
private:
	string line;
	int linenum;
public:
	Goto(string _line) : line(_line) {};
	~Goto() {};
	void execute(EvalState & state) {};
	bool is_statement(EvalState & state);
	int getlinenum() { return linenum; }
};

/*-----------------------------------------------------*/
class Print : public Statement {
private:
	string line;
	bool run;
public:
	Print(string _line, bool _run) : line(_line), run(_run) {};
	~Print() {};
	void execute(EvalState & state);
	bool is_statement(EvalState & state) { return false; };
};

#endif