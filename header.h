#pragma once
#include <stack>
#include <string>
#include <list>

class Expression_Manager {	
public:
	void set_infix();
	std::string balanced_parentheses_check();
	bool is_operator(char ch);
	bool is_parenthesis(char ch);
	bool isHigherPrecedence(char op1, char op2);
private:
	std::string infix;
	std::stack<char> bracket_stack;
	std::stack<char> operator_stack;
	std::string postfix = "";
};
// Queue class
namespace KW {
	template <typename itemtype>
	class Queue {
	private:
		std::list<itemtype> queue;
		int queue_size;
	public:
		// adds a value to the end of the queue
		void push_back(itemtype obj) {
			queue.push_back(obj);
			queue_size += 1;
		}
		// removes first value in the queue and returns it
		itemtype pop_front() {
			queue_size -= 1;
			itemtype val = queue.front();
			queue.pop_front();
			return val;
		}
		//  returns the item in the front of the queue without removing it
		itemtype front() {
			return queue.front();
		}
		// return if the queue is empty
		bool isempty() {
			return queue_size == 0;
		}
		// return the size of the queue
		int size() {
			return queue_size;
		}
	};
}