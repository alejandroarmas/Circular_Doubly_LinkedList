/***************************************************************
Name: Alejandro Armas

// CircularDoublyLinkList.h
// Circular Doubly Linked List Interface

****************************************************************/
#ifndef CIRCULAR_DOUBLE_LIST_H
#define CIRCULAR_DOUBLE_LIST_H

#include "DoubleNode.h"
#include <stdexcept>
#include <iostream>

template <class Type>
class Circular_double_list {

private:
	Double_node<Type>* list_head;
	int list_size;

public:

	Circular_double_list() : list_head(nullptr), list_size(0) {}

	Circular_double_list(const Circular_double_list &);

	~Circular_double_list() {
		clear();
	}

	//accessors prototypes
	int size() const { return list_size; }
	bool empty() const { return !list_size; }
	Type front() const;
	Type back() const;
	Type at(int) const;
	Double_node<Type> *end() const { return list_head->previous_node; }
	Double_node<Type> *head() const { return list_head; }
	int count(Type const &) const;

	// operators
	void operator = (const Circular_double_list &);
	bool operator == (const Circular_double_list &);
	bool operator != (const Circular_double_list &);

	//mutators prototypes	
	void swap(const Circular_double_list &);
	void push_front(Type const &);
	void push_back(Type const &);
	Type pop_front();
	Type pop_back();
	void insertAt(int, Type const &);
	void eraseAt(int);
	int find(Type const &);
	void clear();
};

#include "CircularDoublyLinkList.tpp"

#endif
