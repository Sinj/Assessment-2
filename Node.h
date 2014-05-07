//Definition of the Node class
#ifndef __Node_H_INCLUDED__   // if node.h hasn't been included yet...
#define __Node_H_INCLUDED__   //   #define this so the compiler knows it has been included
template <class T>
class Node
{
public:
	//payload for the node - defined by T
	T M, N,
		ParentX, ParentY, G, H, F;
	//pointer to the next node
	Node *next;
	Node *previous;

	Node();
	~Node();
};

template <class T>
Node<T>::Node()
{
}

template <class T>
Node<T>::~Node()
{
}

#endif