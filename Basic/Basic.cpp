/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "statement.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

enum ControlStatement { INVALID, LIST, RUN, QUIT, CLEAR, HELP };
/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);

void initializeScanner(TokenScanner & scanner, string line);

lineStatement runLine(string line, EvalState & state, bool run);

ControlStatement is_ControlStatement(string line);


/* Main program */

int main() {
   EvalState state;
   Program program;
   //cout << "Stub implementation of BASIC" << endl;
   while (true) {
      try {
         processLine(getLine(), program, state);
      } catch (ErrorException & ex) {
         cout << ex.getMessage() << endl;
      }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program & program, EvalState & state) {
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
	string head = scanner.nextToken();
	if (head == "") return;

	bool lineControlStatement = false;
	switch (is_ControlStatement(line)) {
		case INVALID: break;
		case LIST: program.listProgram();  lineControlStatement = true; break;
		case RUN: program.runProgram(state); lineControlStatement = true; break;
		case QUIT: exit(0); lineControlStatement = true; break;
		case CLEAR: program.clear(); state.clear(); lineControlStatement = true; break;
		case HELP: cout << "I'm a basic Basic intrepreter~~ OvO" << endl; lineControlStatement = true; break;
	}

	if (lineControlStatement) return;

	if (!isdigit(head[0])) runLine(line, state, 1);
		else {
			lineStatement linetype = runLine(line, state, 0);
			int thead = stringToInteger(head);
			program.addSourceLine(thead, line, linetype);
		}
}

void initializeScanner(TokenScanner & scanner, string line) {
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
}

ControlStatement is_ControlStatement(string line) {
	TokenScanner scanner;
	initializeScanner(scanner, line);
	string head = scanner.nextToken();
	bool f = !scanner.hasMoreTokens();
	if (head == "LIST" && f) return LIST;
	if (head == "RUN" && f) return RUN;
	if (head == "QUIT" && f) return QUIT;
	if (head == "CLEAR" && f) return CLEAR;
	if (head == "HELP" && f) return HELP;
	return INVALID;
}

lineStatement runLine(string line, EvalState & state, bool run) {
	string _line = line;
	string head;
	TokenScanner scanner;
	initializeScanner(scanner, line);
	head = scanner.nextToken();
	if (!run) { head = scanner.nextToken(); _line = line.substr(line.find(head)); }
	Statement *pr;
	if (head == "") return Clearline;
	if (head == "LET") {
		Let let(line, run);
		pr = &let;
		if (!pr->is_statement(state)) { error("SYNTAX ERROR"); return Invalidline; }
		pr->execute(state);
		return LET;
	}

	if (head == "PRINT") {
		Print print(line, run);
		pr = &print;
		pr->execute(state);
		return PRINT;
	}

	if (head == "INPUT") {
		Input t_input(_line);
		pr = &t_input;
		if (!pr->is_statement(state)) { error("SYNTAX ERROR"); return Invalidline; }
		if (run) pr->execute(state);
		return INPUT;
	}

	if (head == "REM") return REM;

	if (head == "IF" && !run){
		If t_if(line, false);
		pr = &t_if;
		if (!pr->is_statement(state)) { error("SYNTAX ERROR"); return Invalidline; }
		return IF;
	}

	if (head == "GOTO" && !run) {
		Goto t_goto(_line);
		pr = &t_goto;
		if (! pr->is_statement(state)) { error("SYNTAX ERROR"); return Invalidline; }
		return GOTO;
	}

	if (head == "END" && !run) {
		if (scanner.hasMoreTokens()) { cout << "SYNTAX ERROR" << endl; return Invalidline; }
		return END;
	}
	
	
	error("SYNTAX ERROR");
}