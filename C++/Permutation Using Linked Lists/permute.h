// FILE: permute.h
// Written by: Luke Villanueva
// Purpose: HEADER file for permute.cpp
// Notes:  

#ifndef PERMUTE_H
#define PERMUTE_H
#include <string>
#include "node.h"
using std::string;



class Permute
{

public:
	// default constructor
	Permute();
	// string constructor
	Permute(string, string);
	// destructor
	~Permute();

	// Getters and Setters
	// returns entire first string
	inline string getFirstString() { return firstString; }
	// returns entire second string
	inline string getSecondString() { return secondString; }
	// returns total of permutations in linked list
	inline int getTotal() { return total; }
	// set firstString
	inline void setFirstString(string s) { firstString = s; }
	// set secondString
	inline void setSecondString(string s) { secondString = s; }
	// set total
	inline void setTotal(int n) { total = n; }
	// update length of S1
	inline void updateS1Len() { s1Len = firstString.length(); }


	// Functions
	// Use parameter 0 when first calling this function
	// USES FIRSTNODE, LASTNODE, AND S1LEN
	void permutation(int start);

	// prints completed permutation at specified index
	void print(int); 

	// sets up permutation linked list with firstString's letter in each node
	void setupPermList();

private:
	// holds first permutation
	Node* firstNode;
	// holds last last permutation
	Node* lastNode;
	// holds first letter of S1 in current permutation
	Node* headPerm;
	// holds last letter of S1 in current permutation
	Node* tailPerm;
	// holds total of permuated versions of s1
	int total;
	// holds the length of s1
	int s1Len;
	// holds firstString
	string firstString;
	// holds secondString
	string secondString;


	// Functions
	// USES HEADPERM AND TAILPERM
	void swap(Node* n1, Node* n2);

	// once a permutation is completed, it is submitted to the permanent list of permutations
	// uses headperm, tailperm, firstNode, lastNode
	void submitString();

	// searches node in perm linked list via its index, returns target's address
	// uses HEADPERM AND TAILPERM
	Node* search(Node*,int);

	// cleans up perm linked list in preparation for a new permutation 
	void cleanPermLinkedList();

};

// given string s and index, returns char at index as string type
inline string charAt(string s, int index)
{
	string temp = "";
	return temp + s[index];
}

#endif PERMUTE_H
