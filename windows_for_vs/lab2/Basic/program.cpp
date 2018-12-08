/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include <algorithm>
#include "program.h"
#include "statement.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "evalstate.h"
#include "parser.h"
using namespace std;

Program::Program() {
}

Program::~Program() {
}

void Program::clear() {
	Linenumber.clear();
	codes.clear();
}

void Program::addSourceLine(int lineNumber, string line, lineStatement linetype) {
	if (linetype == Clearline) {
		if (binary_search(Linenumber.begin(), Linenumber.end(), lineNumber)) removeSourceLine(lineNumber); 
		return;
	}
	int t = lower_bound(Linenumber.begin(), Linenumber.end(), lineNumber) - Linenumber.begin();

	if (t == Linenumber.size()) {
		Linenumber.push_back(lineNumber);
		type.push_back(linetype);
		codes.insert(pair<int, string>(lineNumber, line));
		return;
	}

	if (Linenumber[t] == lineNumber) {
		type[t] = linetype;
		codes[lineNumber] = line;
		return;
	}
	int p = Linenumber.size() - 1;
	Linenumber.push_back(Linenumber[p]);
	type.push_back(type[p]);
	for (int i = p; i > t; --i) {
		Linenumber[i] = Linenumber[i - 1];
		type[i] = type[i - 1];
	}
	Linenumber[t] = lineNumber;
	type[t] = linetype;
	codes.insert(pair<int, string>(lineNumber, line));
}

void Program::removeSourceLine(int lineNumber) {
	int t = lower_bound(Linenumber.begin(), Linenumber.end(), lineNumber) - Linenumber.begin();
	codes.erase(lineNumber);
	int p = Linenumber.size() - 1;
	for (int i = t; i < p; ++i) {
		Linenumber[i] = Linenumber[i + 1];
		type[i] = type[i + 1];
	}
	Linenumber.erase(Linenumber.end() - 1);
	type.erase(type.end() - 1);
}

string Program::getSourceLine(int lineNumber) {
	return codes[lineNumber];
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
     // Replace this stub with your own code
}

Statement *Program::getParsedStatement(int lineNumber) {
	return NULL;
}

int Program::getFirstLineNumber() {
	if (Linenumber.size() == 0) return -1;
    return Linenumber[0];     // Replace this stub with your own code
}

int Program::getNextLineNumber(int lineNumber) {
	int t = lower_bound(Linenumber.begin(), Linenumber.end(), lineNumber) - Linenumber.begin();
	if (t == Linenumber.size() - 1 || type[t] == END) return -1;
	return Linenumber[t + 1];
}

void Program::listProgram()
{
	for (int i = 0; i < Linenumber.size(); ++i)
		cout << codes[Linenumber[i]] << endl;
}

void Program::runProgram(EvalState &state)
{
	Statement *pr = NULL; int lineNumber = getFirstLineNumber(); int i;
	while (lineNumber != -1){
		i = lower_bound(Linenumber.begin(), Linenumber.end(), lineNumber) - Linenumber.begin();
		if (type[i] == REM) { pr = NULL; }
		if (type[i] == LET) {
			Let let(getSourceLine(lineNumber), true); 
			pr = &let; 
			pr->is_statement(state); 
			pr->execute(state);
		}
		if (type[i] == INPUT) {
			Input t_input(getSourceLine(lineNumber)); pr = &t_input; pr->is_statement(state); pr->execute(state);
		}
		if (type[i] == PRINT) {
			Print print(getSourceLine(lineNumber), true); pr = &print; pr->execute(state);
		}
		if (type[i] == IF) {
			If t_if(getSourceLine(lineNumber), true); pr = &t_if; pr->is_statement(state);  pr->execute(state);
			int temp = t_if.getlinenum();
			if (temp != -1) {
				lineNumber = temp;
				if (!binary_search(Linenumber.begin(), Linenumber.end(), lineNumber)) error("LINE NUMBER ERROR");
				continue;
			}
		}
		if (type[i] == GOTO) {
			Goto t_goto(getSourceLine(lineNumber));	pr = &t_goto; pr->is_statement(state); lineNumber = t_goto.getlinenum(); 
			if (!binary_search(Linenumber.begin(), Linenumber.end(), lineNumber)) error("LINE NUMBER ERROR");
			continue;
		}
		lineNumber = getNextLineNumber(lineNumber);
	}
	pr = NULL;
}