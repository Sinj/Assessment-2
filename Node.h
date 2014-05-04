#pragma once
//Definition of the Node class

template <class T>
class Node
{
public:
		//payload for the node - defined by T
		T N,S,W,E,
		  Parent, G = 10, H, F;
		//pointer to the next node
		Node *next;

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

