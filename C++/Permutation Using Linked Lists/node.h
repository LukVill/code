#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <string>
using std::string;
using std::cout;

class Node
{
public:
	// default constructor
	Node();
	// string constructor
	Node(string s);
	// string and node ptr constructor
	Node(string, Node*);
	// string, next, and prev
	Node(string s, Node* ptr, Node* prev);
	// destructor
	~Node();

	// Getters and Setters
	// returns data as string type
	string getData() { return data; }
	// returns p as Node ptr type
	Node* getP() { return p; }
	// returns prior as Node ptr type
	Node* getPrev() { return prev; }
	// sets data
	void setData(string d) { data = d; }
	// set ptr of node after this current node
	void setP(Node* ptr) { p = ptr; }
	// set ptr of prior node
	void setPrev(Node* ptr) { prev = ptr; }

private:
	// holds string value
	string data;
	// holds address to next node in list
	Node* p;
	// holds addres of previous node in list
	Node* prev;
};

#endif
