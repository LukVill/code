// FILE: node.cpp
// Written by: Luke Villanueva
// Purpose: implementation file for node.h
// Notes:	N/A
#include "node.h"

Node::Node()
{
	data = "";
	p = nullptr;
	prev = nullptr;
}

Node::Node(string s)
{
	data = s;
	p = nullptr;
	prev = nullptr;
}

Node::Node(string s, Node* ptr)
{
	data = s;
	p = ptr;
	prev = nullptr;
}

Node::Node(string s, Node* ptr, Node* prev)
{
	data = s;
	p = ptr;
	prev = prev;
}

Node::~Node()
{
	data = "";
	p = nullptr;
	prev = nullptr;
}