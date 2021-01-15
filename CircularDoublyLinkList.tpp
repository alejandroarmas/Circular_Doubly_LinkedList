/***************************************************************
Name: Alejandro Armas

// CircularDoublyLinkList.h
// Circular Doubly Linked List Class Definition

****************************************************************/
#include "CircularDoublyLinkList.h"
#include <stdexcept>
#include <iostream>


//copy constructor 
template <class Type>
Circular_double_list<Type>::Circular_double_list(const Circular_double_list & instance) {

	int traversals = instance.size();

	list_size = 0;
	list_head = nullptr; //inititalize defaults incase copy is empty 

	// *******************************//
	Double_node<Type>* newNode; //used to point at dynamically allocated nodes
	Double_node<Type>* pointer = instance.head(); //used to traverse copy

	for (int i = 0; i < traversals; i++) {
		
		newNode = new Double_node<Type>; 
		newNode->node_value = pointer->node_value; // gave data to new node from copy
		newNode->next_node = nullptr;
		newNode->previous_node = nullptr; //set node pointers null

		if (empty()) {
			newNode->next_node = newNode;
			newNode->previous_node = newNode; //pointers point to itself
			list_head = newNode; //head pointer only updated because it was nullptr b4
		}
		else {
			newNode->next_node = list_head;
			newNode->previous_node = list_head->previous_node;
			list_head->previous_node->next_node = newNode;
			list_head->previous_node = newNode;
		}
		list_size++;
		pointer = pointer->next(); //update pointer and container size
	}
}


// ********
// accessors 
// ******** 

template <class Type>
Type Circular_double_list<Type>::front() const {

	if (!list_head) {
		throw std::underflow_error("Element does not exist");
	}
	else {
		return list_head->node_value;
	}

}

template<class Type>
Type Circular_double_list<Type>::back() const {
	if (!list_head) {
		throw std::underflow_error("Element does not exist");
	}
	else {
	}
	return list_head->previous_node->node_value;
}

template<class Type>
Type Circular_double_list<Type>::at(int n) const {
	Double_node<Type>* nodePtr = nullptr; //to traverse the list 

	if (list_size == 0 || n >= list_size) {
		throw std::underflow_error("Index out of range");
	}
	else {
		nodePtr = list_head;

		for (int i = 0; i < n; i++) {
			nodePtr = nodePtr->next_node;
		} //nodePtr points on element n
		return nodePtr->node_value;

	}
}

template<class Type>
int Circular_double_list<Type>::count(Type const & data) const {

	int count = 0;
	Double_node<Type>* nodePtr = nullptr; //used to transverse list

	if (list_head) { //if list is empty, then return 0
		nodePtr = list_head;

		for (int i = 0; i < size(); i++) {
			(nodePtr->node_value == data) && (count++);
			//looks at data in each node, count increments if == data
			nodePtr = nodePtr->next_node;
		}
	}
	return count;
}

// ********
// operators
// ********

template<class Type>
void Circular_double_list<Type>::operator=(const Circular_double_list & copy) {
	swap(copy);
}

template<class Type>
bool Circular_double_list<Type>::operator==(const Circular_double_list & comparison) {

	bool flag = true;
	int sizC = comparison.size();

	if (size() != sizC) { // if they are different sizes, return false
		flag = false;
	}

	for (int i = 0; (flag)&&( i < sizC) ; i++) {
		
		if (at(i) != comparison.at(i)) {
			flag = false;
		}
		//if any element is different, return false
	}
	return flag;
}

template<class Type>
bool Circular_double_list<Type>::operator!=(const Circular_double_list & comparison) {

	bool flag = false;
	int sizC = comparison.size();

	if (size() != sizC) { // if they are different sizes, return true
		flag = true;
	}

	for (int i = 0; (!flag) && (i < sizC); i++) {

		if (at(i) != comparison.at(i)) { 
			flag = true;
		}
		//if any element is different, return true
	}
	return flag;
}



// ********
// mutators 
// ********

template<class Type>
void Circular_double_list<Type>::swap(const Circular_double_list & copy) {
	int siz = copy.size();

	if (!empty()) {
		clear();
	}
	
	for (int i = 0; i < siz; i++) {
		push_back(copy.at(i));
	}

}


template <class Type>
void Circular_double_list<Type>::push_front(Type const & data) {

	Double_node<Type>* newNode; //added to front

	newNode = new Double_node<Type>; //pointing to allocated memory of node
	newNode->node_value = data; // gave data to new node
	newNode->next_node = nullptr;
	newNode->previous_node = nullptr; //set node pointers null

	if (!list_head) {
		newNode->next_node = newNode;
		newNode->previous_node = newNode; //pointers point to itself
	}
	else {

		newNode->next_node = list_head; // new node front pointer points to current head
		newNode->previous_node = list_head->previous_node; //new node back points to element n


		list_head->previous_node->next_node = newNode;
		list_head->previous_node = newNode;

	}

	list_head = newNode; //head points to newNode
	list_size++; //public variable so might need function to update
}

template <class Type>
void Circular_double_list<Type>::push_back(Type const & data) {
	Double_node<Type>* newNode; //added to front

	newNode = new Double_node<Type>; //pointing to allocated memory of node
	newNode->node_value = data; // gave data to new node
	newNode->next_node = nullptr;
	newNode->previous_node = nullptr; //set node pointers null

	if (empty()) {
		newNode->next_node = newNode;
		newNode->previous_node = newNode; //pointers point to itself
		list_head = newNode; //head pointer only updated because it was nullptr b4
	}
	else {
		newNode->next_node = list_head;
		newNode->previous_node = list_head->previous_node;
		list_head->previous_node->next_node = newNode;
		list_head->previous_node = newNode;
	}
	list_size++; 
}

template <class Type>
Type Circular_double_list<Type>::pop_front() {

	Double_node<Type>* newHead = nullptr; //temporary new head pointer
	Type data;

	if (!list_head) {
		throw std::underflow_error("No front element at index 0");
	}
	else {
		data = list_head->node_value; //node value inserted to be returned
		newHead = list_head->next_node; //newHead is second element now
		list_head->previous_node->next_node = newHead; //points last node to newHead
		newHead->previous_node = list_head->previous_node; //points newHead to last node

		delete list_head; //delete memory in front node

		list_head = size() == 1 ? nullptr : newHead;
		//head will point to new head or nullptr depending if there was 1 element

		list_size--; //public variable so might need function to update
	}
	return data;
}

template <class Type>
Type Circular_double_list<Type>::pop_back() {

	Double_node<Type>* nodePtr = nullptr; //used to delete element
	Type data;

	if (!list_head) {
		throw std::underflow_error("No element at index n");
	}
	else {
		nodePtr = list_head->previous_node;

		data = nodePtr->node_value;

		nodePtr->previous_node->next_node = list_head;
		// n-1 element now points towards element 0
		list_head->previous_node = nodePtr->previous_node;
		// element 0 points to element n-1

		delete nodePtr; //delete memory of last node

		(list_size == 1) && (list_head = nullptr);
		//if size was 1 then head should point to null

		list_size--; //public variable so might need function to update
	}
	return data;
}

template <class Type>
void Circular_double_list<Type>::insertAt(int n, Type const & data) {

	Double_node<Type>* newNode; //added to be at count in list
	Double_node<Type>* nodePtr = nullptr; //used to transverse list
	newNode = new Double_node<Type>;
	newNode->node_value = data;
	newNode->next_node = nullptr;
	newNode->previous_node = nullptr;

	if (!list_head) { //if nothing in list, then data inserted to index 0
		newNode->next_node = newNode;
		newNode->previous_node = newNode; //pointers point to itself
		list_head = newNode; //head points to newNode
	}
	else {
		nodePtr = list_head;

		for (int i = 0; i < n; i++) {
			nodePtr = nodePtr->next_node;
		} //nodePtr points on element n

		nodePtr->previous_node->next_node = newNode;
		//newNode points backwards to element (n - 1)
		newNode->previous_node = nodePtr->previous_node;
		//element (n - 1) points forward to dynamically allocated newNode
		nodePtr->previous_node = newNode;
		//element n points backwards to newNode
		newNode->next_node = nodePtr;
		//newNode points to element n, thereby making it into n + 1

		(n) || (list_head = newNode); //update head pointer if insert at n = 0
	}
	list_size++;
	//function has no bounds restriction, so element will be added to
	//node n % .size() ex. if size 5, and n = 6, then element will add to index 1
	// I could add condition structure to push_front or push_back, 
	// if out of bounds but i thought this was pretty cool
}

template<class Type>
void Circular_double_list<Type>::eraseAt(int n) {

	Double_node<Type>* nodePtr = nullptr; //used to transverse list

	if (list_head && (n >= 0 && n < size())) { //if list empty or n is out bounds, do nothing
		nodePtr = list_head;
		for (int i = 0; i < n; i++) { //nodePtr points to n position
			nodePtr = nodePtr->next_node;
		}
		nodePtr->next_node->previous_node = nodePtr->previous_node;
		//  (n+1) node points backwards to (n-1) node
		nodePtr->previous_node->next_node = nodePtr->next_node;
		//  (n-1) node points forward to (n+1) node

		(n) || (list_head = list_head->next_node);
		//when index 0 is deleted, point head to index 1
		delete nodePtr;
		(list_size == 1) && (list_head = nullptr);
		//if size becomes 0, then head points to null
		list_size--;
	}
}

template<class Type>
int Circular_double_list<Type>::find(Type const & element) {

	int index = -1, //error index defaults
		count = 0;

	Double_node<Type>* nodePtr = nullptr;

	if (list_head) { //if not empty  
		nodePtr = list_head;

		while (!(nodePtr->node_value == element ||
			nodePtr->next_node == list_head)) {
			//stops loop if node data is equal to function argument or
			//entire list has been traversed 
			nodePtr = nodePtr->next_node;
			count++;
		}

		if (nodePtr->node_value == element) {
			index = count;
		}
		else std::cout << "Error: Value not found, returning -1" << std::endl;
	}
	else std::cout << "Error: List Empty, returning -1" << std::endl;

	return index;
}

template<class Type>
void Circular_double_list<Type>::clear() {

	int siz = size();

	if (list_head) { //if list is empty do nothing else
		for (int i = 0; i < siz; i++) {
			pop_front();
		}
	}
}
