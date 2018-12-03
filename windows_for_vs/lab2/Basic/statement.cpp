/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include "program.h"
#include "../StanfordCPPLib/tokenscanner.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}

void Run::execute(EvalState & state){
}

StatementType Run::gettype() {
	return RUN;
}

bool Run::is_statement(TokenScanner statement) {
	string temp = statement.nextToken();
	if (temp != "RUN" || statement.hasMoreTokens()) return 0;
		else return 1;
}