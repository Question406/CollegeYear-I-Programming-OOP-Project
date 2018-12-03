/*
 * File: Basic.cpp
 * ---------------
 * Name: [JIYI]
 * Section: [JIYI]
 * This file is the starter project for the BASIC interpreter from
 * OOP2 Of ACM Programming
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"

#include "statement.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);

/* Main program */

int main() {
   EvalState state;
   Program program;
   cout << "Stub implementation of BASIC" << endl;
   while (true) {
      try {
         processLine(getLine(), program, state);
      } catch (ErrorException & ex) {
         cerr << "Error: " << ex.getMessage() << endl;
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

void processLine(string line, Program & program, EvalState & state){
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);

	Expression *exp = parseExp(scanner);
	int t = exp->eval(state);
	cout << t << endl;

	string head = scanner.nextToken();
	if (head == "") return;
	int thead; //possible Line number
	stringstream stream(head);
	stream >> thead;
	if (thead != 0) {
		program.addSourceLine(thead, line);
	}
	else printf("Invalid line\n");



	/*
	cout << scanner.nextToken() << '\n';
	scanner.saveToken(scanner.nextToken());
	line = scanner.nextToken();
	cout << line << '\n';
	cout << scanner.nextToken() << '\n';
    /*Expression *exp = parseExp(scanner);
    int value = exp->eval(state);
    cout << value << endl;
    delete exp;*/
}