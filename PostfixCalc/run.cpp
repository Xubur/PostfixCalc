#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include <stack>

using namespace std;
void evaluateExpression();

int main(void) {
	evaluateExpression();
	return 0;
}

void evaluateExpression()
{
	ifstream fileIn;
	string writeLine;
	fileIn.open("input.txt");
	stack<int> myStack;
	
	if (fileIn.is_open())
	{
		while (getline(fileIn, writeLine))
		{
			for (char in : writeLine)
			{
				if (in == '+' || in == '-' || in == '*' || in == '/' || in == '=')
					if (myStack.empty())
						cout << "Error: missing numbers prior to operator. ";
					else
					{
						int num2 = myStack.top();
						//cout << "got first number: " << num2;
						myStack.pop();
						//cout << "popped first number. " << endl;
						int num1 = myStack.top();
						//cout << "got second number: " << num1;
						myStack.pop();
						//cout << "popped second number." << endl;
						switch (in)
						{
						case '+':
							//cout << "Let's add " << num1 << " + " << num2 << "." << endl;
							myStack.push(num1 + num2);
							cout << "We're left with: " << myStack.top() << endl;
							break;
						case '-':
							myStack.push(num1 - num2);
							cout << "We're left with: " << myStack.top() << endl;
							break;
						case '*':
							myStack.push(num1 * num2);
							cout << "We're left with: " << myStack.top() << endl;
							break;
						case '/':
							myStack.push(num1 / num2);
							cout << "We're left with: " << myStack.top() << endl;
							break;
						default:
							cout << "We will run print func here." << endl;
							break;
						}
					}
				else
					if (!isdigit(in))
						cout << "Error, current value: " << in << " is not a digit and was not recognized as an operator. Furthermore, output will cease here as we have an error in expression." << endl;
					else {
						if (myStack.size() > 2) {
							cout << "Error: stack has two members, and no operator." << endl;
							cout << "Size of stack: " << myStack.size() << endl;
						}
						//else if (((int)in - 48) )
						else
						{
							//cout << "pushing number: " << in << endl;
							myStack.push((int)in - 48);
							//cout << "Successful. Testing...\n Top(): " << myStack.top() << endl;
						}
					}
				// if stack already has two members, throw error
				// else add to stack

			}
		}
		fileIn.close();
	}
}

void evaluateOpr()
{

}

void discardExp()
{

}

void printResult()
{

}