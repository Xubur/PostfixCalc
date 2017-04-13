#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;
void evaluateExpression(string);
bool evaluateOpr(char);
bool evaluateGrammar(string);
void printResult(stack<int>);
/*
	This program has a few basic rules.
	1. You must have a space between each number set unless the int is multiple digits long.
		a. 4 33 + 222 + 1111 +=
	2. Every expression must end with an = sign. White spaces following the = sign will be ignored for this check.
	3. Expression must not be empty.
		a. No, not even spaces count. Nice try :-)
	4. There must be two ints in the stack for a computation to occur.
		a. You can have as many numbers in the stack as you'd like but as soon as an operator is called
			it will check to see that there are only two ints in the stack. No more, no less.
			 i. As we are only reading from a text file, I will not change this to ensure only 2 ints in
				the stack at a time. If we were reading from live input, I would.
		b. There may be a stack over flow bug here but I don't even know how to check for that right now
	5. After an operation is performed, the previous 2 numbers will be removed, and the result will be added into the stack.
*/
int main(void) {
	ifstream fileIn;
	string expression;
	fileIn.open("input.txt");
	getline(fileIn, expression);
	if (evaluateGrammar(expression)) // if syntax is acceptable, proceed.
		evaluateExpression(expression);
	else
		return 265;
}

void evaluateExpression(string line)
{
	stack<int> myStack;
	for (int i = 0; i < (int)line.length(); i++) {
		if (line[i] == ' ' || line[i] == ',') //if we have a seperator operand, continue on
		{
			continue;
		}
		if (evaluateOpr(line[i])) { // if we are looking at an operator character...
			if (myStack.size() == 2) { // proper number of ints in stack
				int op2 = myStack.top(); myStack.pop(); // we set the second to the top as we evaluate from left to right (bottom up)
				int op1 = myStack.top(); myStack.pop();
				switch (line[i])
				{
				case '+':
					myStack.push(op1 + op2);
					//cout << "We're left with: " << myStack.top() << endl;
					break;
				case '-':
					myStack.push(op1 - op2);
					//cout << "We're left with: " << myStack.top() << endl;
					break;
				case '*':
					myStack.push(op1 * op2);
					//cout << "We're left with: " << myStack.top() << endl;
					break;
				case '/':
					myStack.push(op1 / op2);
					//cout << "We're left with: " << myStack.top() << endl;
					break;
				default:
					cout << "\a This should never be reached. \a" << endl; // Never ever should this be reached, the char has to be an operator and all are identified.
					for (int i = 0; i < 100; i++)
					{
						cout << "STOP BREAKING MY STUFF." << endl;
					}
					break;
				}
			}
			else {
				cout << "\a Error: Improper number of integers in expression. "/*\nSize: " << myStack.size() << "\nNeeded: 2" */ << endl;
				//cout << "Printing..." << endl;
				//printResult(myStack);
				break;
			}
		}
		else {
			if (line[i] == '=')
			{
				//cout << "End detected. Printing." << endl;
				printResult(myStack);
				break;
			}
			if (isdigit(line[i]))
			{
				string strTemp;
				strTemp = line[i]; // add the character to the string.
				if (isdigit(line[i + 1])) //if the very next character is a number and not a space, a comma, or an operator,
				{
					//cout << "Detected multi-digit int." << endl;
					while (isdigit(line[i + 1])) // while there are digits directly following the current number(char)
					{
						//cout << "init temp: " << strTemp << endl;
						//cout << "Next character digit is: " << line[i + 1] << endl;
						strTemp += line[i + 1]; //add the neighboring number to the string
						//cout << "transformed temp: " << strTemp << endl;
						i++;
					}
				}
				myStack.push(stoi(strTemp)); // push the string converted to an int to the stack. If the number is only 1 digit, no transformation occurs and it is simply pushed
				//cout << "Pushed: " << myStack.top() << endl;
			}

		}

	}

}

void discardExp()
{
	// Don't see a need for this
}

bool evaluateOpr(char input)
{
	if (input == '+' || input == '-' || input == '*' || input == '/')
		return true;
	return false;
}
bool evaluateGrammar(string input) //true if proper, false if improper
{
	input.erase(std::remove_if(input.begin(), input.end(), isspace), input.end()); // remove whitespaces for our copy to iterate through
	if (input.length() == 0)
	{
		cout << "\a Error: Empty Expression.\a" << endl;
		return false;
	}
	else if (input.back() != '=') {
		cout << "\a Error: Expression does not end with an equal sign operator. (=) " << endl;
		return false;
	}
	int equalSignCount = 0;
	for (int i = 0; i < (int)input.size(); i++) //count number of = signs in expression
	{
		//cout << "Current character is: " << input[i] << endl;
		if (equalSignCount > 1)
		{
			cout << "\a Error: Multiple '=' found." << endl;
			return false;
		}
		if (input[i] == '=')
			equalSignCount++;
	}
	return true; // otherwise we passed all tests
}
void printResult(stack<int> inStack)
{
	cout << "Contents of stack: " << endl;
	cout << "Size: " << inStack.size() << endl;
	while (!inStack.empty()) //loop through the stack and print contents
	{
		cout << "[" << inStack.top() << "]" << endl;
		inStack.pop();
	}
}