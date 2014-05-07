//DoublyLinkedList.h
//Implementation of a doubly linked 
#ifndef __DoublyLinkedList_H_INCLUDED__   // if DoublyLinkedList.h hasn't been included yet...
#define __DoublyLinkedList_H_INCLUDED__   //   #define this so the compiler knows it has been included

#include "Node.h"
#include <stddef.h>
#pragma once

template <class T>
class DoublyLinkedList
{
public:
	//pointer to the first node in the list
	Node<T>* first;
	//Pointer to the last node in the list
	Node<T>* last;

	//keep track of the size
	int size = 0;

	//searches for a node
	Node<T>* DoublyLinkedList::Search();
	//search for a node using cords
	Node<T>* DoublyLinkedList<T>::NodeSearch(int x, int y);
	//searches nodes for values
	int DoublyLinkedList::Search1(int, int);
	//will pop a node and push it into another list
	void DoublyLinkedList<T>::PopPush(Node<T> *data, DoublyLinkedList<T> closed);
	//inserts a new node at the front of the list and sets its value
	void DoublyLinkedList::InsertFront(T R, T C, T Parx, T Pary, T Ge, T He);
	//insert a new node at the back of the list
	void DoublyLinkedList::InsertBack(T val);
	//insert a node in the middle of a list
	void DoublyLinkedList::InsertAfter(T val, Node<T> *after);
	//deletes a node from the list
	void DoublyLinkedList::RemoveNode();
	//gets the size of the list#
	int DoublyLinkedList::getSize();
	Node<T>* DoublyLinkedList<T>::Fsearch();

	DoublyLinkedList();
	~DoublyLinkedList();

};

//constructor for an empty list
template <class T>
DoublyLinkedList<T>::DoublyLinkedList()
{
	first = NULL;
}

//destructor
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{

}

template <class T>
void DoublyLinkedList<T>::PopPush(Node<T> *data, DoublyLinkedList<T> closed)
{
	Node<T> *tNext;
	Node<T> *tPrevious;

	tNext = data->next;
	tPrevious = data->previous;

	cout << closed.size << endl;
	cout << size << endl;

	//Delete in a while
	//cout << tNext << endl;
	//cout << tPrevious << endl;

	if (tPrevious != NULL){
		tPrevious->next = tNext;
	}
	if (tNext != NULL){
		tNext->previous = tPrevious;
	}

	//system("PAUSE");

	//Delete in a while
	//cout << tNext->previous << endl;
	//cout << tPrevious->next << endl;

	closed.InsertFront(data->ParentX, data->ParentY, data->M, data->M, data->H, data->G);
	data->next = NULL;
	data->previous = NULL;
	cout << closed.size << endl;
	size--;
	cout << size << endl;
	/*
	if (closed->first == NULL){
	closed.first = data;
	closed.last = data;
	}
	else{
	closed.first->previous = data;
	data->next = closed.first;
	closed.first = data;
	}*/
}

template <class T>
Node<T>* DoublyLinkedList<T>::NodeSearch(int x, int y)
{
	//create a temporary node
	Node<T> *key;
	//make it point to the same node as the list head
	key = first;
	//repeat while key points to a list element
	while (key)
	{
		if (key->M == x && key->N == y)
		{
			return key;
		}
		//increment the node to the next one
		key = key->next;
	}

	//if it doesnt find the value
	return NULL;
}

//-------------------------------------------------------------------------
//search the list for a node
template <class T>
Node<T>* DoublyLinkedList<T>::Search()
{
	//create a temporary node
	Node<T> *key;
	Node<T> *tmp;

	//make it point to the same node as the list head
	key = first;
	tmp = first;

	double fTmp = 10000;
	

	//repeat while key points to a list element
	while (key)
	{
		if (key->F < fTmp && key->F != 0)
		{
			tmp = key;
			fTmp = tmp->F;
		}
		//increment the node to the next one
		key = key->next;
	}
	/*
	cout << fTmp << endl;

	cout << tmp << endl;
	*/
	return tmp;
}

//test-search for X & Y 
template <class T>
int DoublyLinkedList<T>::Search1(int R, int C)
{
	//create a temporary node
	Node<T> *key;
	//make it point to the same node as the list head
	key = first;
	//repeat while key points to a list element
	while (key)
	{
		if (key->M == R && key->N == C)
		{
			return 1;
		}
		//increment the node to the next one
		key = key->next;
	}
	//if it doesnt find the value
	return 0;
}

//search for lowest F
template <class T>
Node<T>* DoublyLinkedList<T>::Fsearch()
{
	//create a temporary node
	Node<T> *key;
	Node<T> *tmp;

	//make it point to the same node as the list head
	key = first;
	tmp = first;

	int fTmp = 10000;


	//repeat while key points to a list element
	while (key)
	{
		if (key->f < fTmp && ket->f != 0)
		{
			tmp = key;
			fTmp == tmp->f;
		}
		//increment the node to the next one
		key = key->next;
	}

	return tmp;
}

//insert a node at the front of the list
template <class T>
void DoublyLinkedList<T>::InsertFront(T R, T C, T Parx, T Pary, T Ge, T He)
{
	//create a new node
	Node<T> *newNode = new Node<T>;
	//set the value of the new node
	newNode->M = R;
	newNode->N = C;
	newNode->ParentX = Parx;
	newNode->ParentY = Pary;
	newNode->G = Ge;
	newNode->H = He;
	newNode->F = newNode->G + He;

	//check if the list is empty
	if (first == NULL)
	{
		//set first and last to both point to newNode
		first = newNode;
		last = newNode;
	}
	else{
		//set the 'previous' pointer pointed to by 'first' to hold newNode's address
		first->previous = newNode;
		//set the next pointer of newNode to hold the next nodes address (address pointed to by first)
		newNode->next = first;
		//set first to point to newNode
		first = newNode;
	}
	size++;
}

//insert a node at the back of the list
template <class T>
void DoublyLinkedList<T>::InsertBack(T val)
{
	Node<T> *newNode = new Node<T>;
	newNode->value = val;

	if (last == NULL)
	{
		first = newNode;
		last = newNode;
	}
	else{
		//next pointer pointed to by 'last' assigned newNode's address
		last->next = newNode;
		//previous pointer in newNode assigned the address of the previous node (the address pointed to by last)
		newNode->previous = last;
		//assign the last pointer to point to the updated last element in the list
		last = newNode;
	}

	size++;
}


//insert a node in the middle of a list
template <class T>
void DoublyLinkedList<T>::InsertAfter(T val, Node<T> *after)
{
	if (after != NULL)
	{
		//create a new node
		Node<T> *newNode = new Node<T>;
		newNode->value = val;

		//set the previous pointer of the new node to point the Node it is after
		newNode->previous = after;
		//set the next pointer of the new node to point to the node after the new node
		newNode->next = after->next;
		//set the previous pointer of the node after the new node to point to the new node
		if (after->next)
		{
			after->next->previous = newNode;
		}
		//set the next pointer of the node before the new node to point to it
		after->next = newNode;

		size++;
	}

}

//get the list size
template <class T>
int DoublyLinkedList<T>::getSize()
{
	return size;
}
#endif