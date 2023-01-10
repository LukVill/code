// Function: function implementation of a priority queue data structure
// Author : Luke Villanueva (NOTE: main.cpp and pqueue1.h are NOT by Luke)


#include <stdlib.h> // provides size_t
#include "pqueue1.h"

typedef int Item;

PriorityQueue::PriorityQueue()
{
	head_ptr = nullptr;
	many_nodes = 0;
}

PriorityQueue::PriorityQueue(const PriorityQueue& source)
{

	// since this is copy constructor, there is no
	// need to check for existing queue list

	// check for self assignment
	if (&source != this)
	{

		many_nodes = source.many_nodes;

		// initialize head_ptr
		head_ptr = new Node();

		// make parser for new linked list
		Node* newIndex = head_ptr;

		// COPY INFO FROM EVERY NODE
		// starting from head_ptr, while index's link is NOT equal
		// to null, set index to the next node's link

		// check for empty queue
		if (source.many_nodes != 0)
		{
			for (Node* index = source.head_ptr; index != NULL; index = index->link)
			{
				// copy data and priority
				newIndex->data = index->data;
				newIndex->priority = index->priority;

				// create new node after newIndex
				newIndex->link = new Node();

				// parse newIndex to its next node
				newIndex = newIndex->link;
			}

			// after copying list, set last elem's link in new list to be NULL
			//delete newIndex->link;
			newIndex->link = nullptr;
		}

		// if it IS an empty queue
		else
		{
			// no need for newIndex 
			delete newIndex;

			head_ptr = nullptr;
			many_nodes = 0;
		}


	}
}

PriorityQueue::~PriorityQueue()
{
	if (many_nodes != 0)
	{
		Node* temp;
		while (head_ptr->link != nullptr)
		{
			// set temp equal to headptr
			temp = head_ptr;
			// set headptr to next node
			head_ptr = head_ptr->link;

			// delete headptr node via temp
			delete temp;
		}
		// delete head_ptr to finish off last elem
		delete head_ptr;
		// dereference pointers
		temp = nullptr;
	}
	head_ptr = nullptr;
	many_nodes = 0;
}

void PriorityQueue::operator=(const PriorityQueue& source)
{

	// check for self assignment
	if (&source != this)
	{

		// since operator= could have an existing list,
		// check for list in current queue
		// delete and dereference all nodes
		if (many_nodes != 0)
		{
			Node* temp;
			while (head_ptr->link != nullptr)
			{
				// set temp equal to headptr
				temp = head_ptr;
				// set headptr to next node
				head_ptr = head_ptr->link;

				// delete headptr node via temp
				delete temp;
			}
			// delete head_ptr to finish off last elem
			delete head_ptr;
			// dereference pointers
			temp = nullptr;
		}

		many_nodes = source.many_nodes;

		// initialize head_ptr
		head_ptr = new Node();

		// make parser for new linked list
		Node* newIndex = head_ptr;

		// COPY INFO FROM EVERY NODE
		// starting from head_ptr, while index's link is NOT equal
		// to null, set index to the next node's link

		// check for empty queue in source
		if (source.many_nodes != 0)
		{
			for (Node* index = source.head_ptr; index != nullptr; index = index->link)
			{
				// copy data and priority
				newIndex->data = index->data;
				newIndex->priority = index->priority;

				// create new node after newIndex
				newIndex->link = new Node();

				// parse newIndex to its next node
				newIndex = newIndex->link;
			}

			// after copying list, set last elem's link in new list to be NULL
			newIndex->link = nullptr;
		}

		// if it IS an empty queue
		else
		{
			// no need for newIndex 
			delete newIndex;

			head_ptr = nullptr;
			many_nodes = 0;
		}
	}
}

// higher priority number, the more front the item is in the queue
// use loop to check if every item in queue has a lower priority
// if entry has lower priority than current item, insert it after current
// otherwise, if the end of the list has been reached, attach it
void PriorityQueue::insert(const Item& entry, unsigned int priority)
{
	// Case: empty list
	// if list is empty, then just insert entry as the head ptr
	if (many_nodes == 0)
	{
		head_ptr = new Node();
		head_ptr->data = entry;
		head_ptr->priority = priority;
		head_ptr->link = nullptr;
	}

	// Case: all else (i.e. many_nodes>0)
	else
	{
		// ptr to node before currNode
		Node* priorNode = nullptr;
		// current indexer for linked list
		Node* currNode = head_ptr;

		// while entry priority is less than currNode priority
		// AND currNode isn't the last node
		while ((currNode->priority) > priority && currNode->link!=nullptr)
		{
			// parses currNode to 
			priorNode = currNode;
			currNode = currNode->link;
		}

		// Case: priority is higher/equal to currNode priority 
		// OR reached end of list
		//if (currNode->priority <= priority)
		//{

			// MAKING NEW NODE FOR ENTRY

			// insert entry before currNode
			
			// make new node for entry
			Node* entryNode = new Node();

			// set info into entryNode
			entryNode->data = entry;
			entryNode->priority = priority;


			// PLACING NODE INTO QUEUE
			
			// Case: ONLY if currNode reached the last node
			if (currNode->link == nullptr && currNode->priority >priority)
			{
				// set link of currNode to entrynode
				// (setting entryNode after currNode, at end of list)
				currNode->link = entryNode;

				// set link of entryNode to null
				// (setting entryNode to be last element)
				entryNode->link = nullptr;
			}

			// Case: entry replaces head_ptr
			// if entry's priority is higher than head_ptr's,
			// replace head_ptr with entry;
			else if (head_ptr->priority < priority)
			{
				// set link of entryNode to currNode
				// (setting entryNode before currNode)
				entryNode->link = currNode;

				// set head_ptr to entryNode
				// (setting entryNode at head of linked list)
				head_ptr = entryNode;
			}

			// if priority is higher than currNode priority, 
			// insert before currNode
			else if (currNode->priority < priority)
			{
				// set link of entryNode to currNode 
				// (setting entryNode before currNode in the queue)
				entryNode->link = currNode;

				// set link of priorNode to entryNode
				// (setting entryNode after priorNode in the queue)
				priorNode->link = entryNode;
			}

			// if priority is equal to currNode priority,
			// attach after currNode
			else if (currNode->priority == priority)
			{
				// set link of entryNode to currNode's link
				// (setting entryNode before node after currNode)
				entryNode->link = currNode->link;

				// set link of currNode to entryNode
				// (setting entryNode after currNode)
				currNode->link = entryNode;
			}

		//}
	}

	// after inserting entry, increment size by 1
	many_nodes++;

}

// Precondition: size()>0
// Postcondition: highest priority item is returned and REMOVED
// from queue
// returns the data in the first node
Item PriorityQueue::get_front()
{
	if (many_nodes > 0)
	{
		// holds the item data
		Item result = head_ptr->data;

		// make temp node ptr to first elem
		Node* temp = head_ptr;

		// set head ptr to next node
		head_ptr = head_ptr->link;

		// delete first node
		delete temp;
		temp = nullptr;

		// decrement size because the node is deleted
		many_nodes--;

		// return data, with the data removed from the list
		return result;
	}
}