#include "header.h"
#include <iostream>
#include <map>

//Isa Ortiz-Acosta
// CS 303
// Due: 11/12/23


//Gets an infix expression from the user and sets the infix to the input
void Expression_Manager::set_infix(){
	std::string inString;
	std::cout << "Enter an infix expression: ";
	std::cin >> inString; // receive the input from the user
	infix = inString; // sets infix to the input
}
//returns if the character is an operator
bool Expression_Manager::is_operator(char ch) {
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%';

}
// return if the character is a parenthese
bool Expression_Manager::is_parenthesis(char ch) {
	return ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']';
}

bool Expression_Manager::isHigherPrecedence(char op1, char op2) {
	std::map<char, int> precedence{ {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'%', 2} };
	return precedence[op1] >= precedence[op2];
}
// checks if parentheses in the infix equation are balanced
std::string Expression_Manager::balanced_parentheses_check() {
	for (int i = 0; i < infix.length(); i++) {// iterate through the infix string
		if (is_parenthesis(infix[i])) {
			if (infix[i] == '{' || infix[i] == '(' || infix[i] == '[') { // if the character in the string is an opening bracket
				bracket_stack.push(infix[i]); // add it to the stack
			}
			else if (infix[i] == '}' || infix[i] == ')' || infix[i] == ']') {// if the character is a closing bracket
				// check if its matching opening bracket is the top in the stack, otherwise return the error message
				if (bracket_stack.empty())
					return "Expression did not pass the Balanced Parantheses Check";
				else if (infix[i] == '}' && bracket_stack.top() != '{')
					return "Expression did not pass the Balanced Parantheses Check";
					
				else if (infix[i] == ')'&& bracket_stack.top() != '(')
					return "Expression did not pass the Balanced Parantheses Check";
				else if (infix[i] == ']' && bracket_stack.top() != '[')
					return "Expression did not pass the Balanced Parantheses Check";
				else
					bracket_stack.pop();
			}
		}
		// If the character is not a bracket, continue to the next character
		else
			continue;
	}

	// If the expression passed the balanced parentheses check, then proceed to building the postfix equation
	for (int i = 0; i < infix.length(); i++) {
		// if the character is a digit or variable, then add to postfix
		if (isalnum(infix[i]))
			postfix += infix[i];
		// if it is an operator, check its precedence to the top of the operator stack and add it if needed
		else if (is_operator(infix[i])) {
			if (operator_stack.empty())
				operator_stack.push(infix[i]);
			else {
				if (isHigherPrecedence(infix[i], operator_stack.top()))
					operator_stack.push(infix[i]);
				else {
					while (!operator_stack.empty() && isHigherPrecedence(operator_stack.top(), infix[i])) {
						postfix += operator_stack.top();
						operator_stack.pop();
					}
					operator_stack.push(infix[i]);
				}
			}
		}
		// if the character is a parenthesis, add it to the operator if it is opening, or search for the opening parenthesis if it is closing.
		else if (is_parenthesis(infix[i])) {
			if (infix[i] == '(' || infix[i] == '{' || infix[i] == '[')
				operator_stack.push(infix[i]);
			else {
				while (!operator_stack.empty() && operator_stack.top() != '(' && operator_stack.top() != '[' && operator_stack.top() != '{') {
					postfix += operator_stack.top();
						operator_stack.pop();
				}
				operator_stack.pop();
			}
		}		
	}
	while (!operator_stack.empty()) {
		postfix += operator_stack.top();
		operator_stack.pop();
	}
	return postfix;
};



int main() {
	Expression_Manager obj;
	obj.set_infix();
	std::cout << obj.balanced_parentheses_check();
	KW::Queue<int> my_queue;
	my_queue.push_back(3);
	my_queue.push_back(4);
	my_queue.push_back(5);
	my_queue.push_back(6);
	std::cout << std::endl << my_queue.pop_front();
	std::cout << std::endl << my_queue.size();
}
