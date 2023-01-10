#include "permute.h"
#include <string>
#include <cassert>
using std::string;

Permute::Permute()
{
	firstNode = nullptr;
	lastNode = firstNode;
	headPerm = firstNode;
	tailPerm = firstNode;
	firstString = "";
	secondString = "";
	total = 0;
	s1Len = 0;
}

Permute::Permute(string s1, string s2)
{
	firstNode = nullptr;
	lastNode = firstNode;
	headPerm = firstNode;
	tailPerm = firstNode;
	firstString = s1;
	secondString = s2;
	total = 0;
	s1Len = s1.length();
}

Permute::~Permute()
{
	Node* currNode = firstNode;
	while (currNode->getP() != nullptr)
	{
		Node* temp = currNode->getP();
		delete currNode;
		currNode = temp;
	}
	delete lastNode;
	delete currNode;
	lastNode = nullptr;
	currNode = nullptr;

	currNode = headPerm;
	while (currNode->getP() != nullptr)
	{
		Node* temp = currNode->getP();
		delete currNode;
		currNode = temp;
	}
	delete tailPerm;
	delete currNode;
	tailPerm = nullptr;
	currNode = nullptr;
}

// start: starting index of the permutation (usually at start)
// uses s1Len, but subtracts 1 for it uses the index as the final value
void Permute::permutation(int start)
{
	int endIndex = s1Len - 1;

	// finished a permutation, so complete the permutation
	// and then adding the string as a node in the permanent linked list
	if (start >= endIndex)
	{
		// add string to permanent list
		submitString();

		// if s1 is nothing, there was no real permutation
		if (s1Len == 0 && secondString.length()==0)
			total--;

		// DEBUG PRINT
		//if(total>0)
		//print(total - 1);

	}
	else
	{
		for (int i = start; i <= endIndex; i++)
		{
			// permuatate
			swap(search(headPerm,start), search(headPerm,i));

			// recursive function, permutating more
			permutation(start + 1);

			// backtrack 
			swap(search(headPerm,start), search(headPerm,i));

		}

	}

}

// Postcondition: prints out string at index
void Permute::print(int index)
{
	cout << search(firstNode, index)->getData();
}


// Precondition: headPerm and tailPerm are uninitialized and clean
// Postcondition: perm LinkedList is now filled with firstString's letters
void Permute::setupPermList()
{
	// check for empty case
	if (s1Len == 0)
		// don't permutate at all
		return;

	// clean PermLinkedList if headPerm or tailPerm not cleaned
	if(headPerm != nullptr || tailPerm != nullptr)
	cleanPermLinkedList();

	// otherwise, designate head and tail to be first char of s1
	headPerm = new Node(charAt(firstString, 0));
	tailPerm = headPerm;

	// while index hasn't reached length of s1, keep attaching new nodes with
	// each letter stored in them
	for (int i = 1; i < s1Len; i++)
	{
		// creates new node after tailPerm with next letter
		tailPerm->setP(new Node(charAt(firstString, i)));
		// set up new node
		tailPerm->getP()->setPrev(tailPerm);
		// set tailPerm to new Node
		tailPerm = tailPerm->getP();
	}

	// at this point, the entire firstString is dissected into the linked list, headed by headPerm
}

void Permute::swap(Node* n1, Node* n2)
{
	// check for self swap
	if (n1 == n2 || n1->getData() == n2->getData())
		return;

	// check for edge cases: if edge cases, make headPerm and tailPerm point to them
	if (n1 == headPerm)
	{
		// since n2 is going to swap with n1, make n2 headPerm
		headPerm = n2;
	}
	// check for tail
	if (n2 == tailPerm)
	{
		// since n1 is going to swap with n2, make n1 tailPerm
		tailPerm = n1;
	}

	Node* n1Prior = 0, * n1After = 0, * n2Prior = 0, * n2After = nullptr;
	// set priors and preceding nodes if they exist
	if (n1->getPrev() != nullptr)
	{
		n1Prior = n1->getPrev();
	}
	if (n1->getP() != nullptr)
	{
		n1After = n1->getP();
	}
	if (n2->getPrev() != nullptr)
	{
		n2Prior = n2->getPrev();
	}
	if (n2->getP() != nullptr)
	{
		n2After = n2->getP();
	}

	// case 1: they are next to each other
	if ((n1Prior == n2 && n2After == n1) || (n1After == n2 && n2Prior == n1))
	{
		// swap n2
		if (n1Prior != nullptr)
			n1Prior->setP(n2);	// set n2 after n1's prior
		n2->setPrev(n1Prior);	// set n1's prior before n2
		n2->setP(n1);	// set n1 after n2
		// swap n1
		if (n2After != nullptr)
			n2After->setPrev(n1); // set n1 before n2's p
		n1->setP(n2After); // set n2's p after n1
		n1->setPrev(n2); // set n2 before n1
	}

	// case 2: they are not next to each other
	else
	{
		// swap n2
		if (n1Prior != nullptr)
			n1Prior->setP(n2);
		if (n1After != nullptr)
			n1After->setPrev(n2);
		n2->setPrev(n1Prior);
		n2->setP(n1After);
		// swap n1
		if (n2Prior != nullptr)
			n2Prior->setP(n1);
		if (n2After != nullptr)
			n2After->setPrev(n1);
		n1->setPrev(n2Prior);
		n1->setP(n2After);
	}

}

void Permute::submitString()
{
	string str1 = "";
	string str2 = secondString;

	// currNode is linked list parser, started at headPerm
	for (Node* currNode = headPerm; currNode != nullptr;currNode = currNode->getP())
	{
		str1 += currNode->getData();
	}

	// concatenate the 2 parts of the string into the linked list
	str1 += str2;

	// the submitted string is now str1

	// check for empty case, initialize the nodes if empty
	if (firstNode == nullptr && lastNode == nullptr)
	{
		firstNode = new Node(str1);
		lastNode = firstNode;
	}
	// else, lastNode should be valid to add onto 
	else
	{
		// creates new node after lastNode
		lastNode->setP(new Node(str1));
		// set up new node
		lastNode->getP()->setPrev(lastNode);
		// set lastnode to the new node
		lastNode = lastNode->getP();
	}

	// increment total perms
	total++;

}

Node* Permute::search(Node* header, int index)
{
	// assert that index is less than linked list length
	// if it is headPerm, use s1Len; if it is firstNode, use total
	if (header == headPerm)
		assert(index <= s1Len);
	else if (header == firstNode)
		assert(index <= total);

	int i = 0;
	Node* currNode = header;

	// the node that loop stops on is target node
	for (; i!=index; currNode = currNode->getP())
	{
		i++;
	}

	// return address of node
	return currNode;
}

void Permute::cleanPermLinkedList()
{
	//clean up headperm and tailperm
	headPerm->setData("");
	headPerm->setP(nullptr);
	headPerm->setPrev(nullptr);
	tailPerm->setData("");
	tailPerm->setP(nullptr);
	tailPerm->setPrev(nullptr);
}