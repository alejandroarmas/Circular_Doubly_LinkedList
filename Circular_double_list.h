/***************************************************************
Problem: Assignment 2.1
Question: Your assignment is to create a circular doubly 
linked list CLASS TEMPLATE 
Name: Alejandro Armas 
ID: 1433110
Date: 12/1/2018
Status: complete 
****************************************************************/
#ifndef CIRCULAR_DOUBLE_LIST_H
#define CIRCULAR_DOUBLE_LIST_H

#include <stdexcept>

template <class Type>
class Double_node {

public:

	Type node_value;
	Double_node<Type>* previous_node;
	Double_node<Type>* next_node;

	Double_node() {}; //default contructor
	Double_node(Type const & object, Double_node * prev, Double_node * next);
	~Double_node() {}; // default destructor

	Type value() const { return node_value; }
	Double_node* next() const { return next_node; }
	Double_node* previous() const { return previous_node; }

	template <class Type>
	Double_node(Type const & object, Double_node* prev = nullptr,
		Double_node* next = nullptr) {

		node_value = object;
		previous_node = prev;
		next_node = next;
	}
};

template <class Type>
class Circular_double_list {

private:
	Double_node<Type>* list_head;
	int list_size;

public:

	Circular_double_list() {
		list_head = nullptr;
		list_size = 0;
	}
	Circular_double_list(const Circular_double_list & blueprint) {
		swap(blueprint);
	}

	~Circular_double_list() {
		clear();
	}

	//accessors prototypes
	int size() const { return list_size;}
	bool empty() const { return !list_size;}
	Type front() const; 
	Type back() const; 
	Type at(int element) const; 
	Double_node<Type> *head() const { return list_head;}
	int count(Type const &) const;

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

//accessors 

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

	Double_node<Type>* nodePtr = nullptr; //to traverse the list 

	if (!list_head) {
		throw std::underflow_error("Element does not exist");
	}
	else {
		nodePtr = list_head;
	}
	return nodePtr->previous_node->node_value;
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
// mutators 
// ********

template<class Type>
void Circular_double_list<Type>::swap(const Circular_double_list & blueprint) {

	int size = blueprint.size();

	if (list_head) {
		clear();
	} //if there are items in list, clear

	for (int i = 0; i < size; i++) {
		insertAt(i, blueprint.at(i));
	}
}

template <class Type>
void Circular_double_list<Type>::push_front(Type const & data) {

	Double_node<Type>* newNode; //added to front
	Double_node<Type>* nodePtr; //used to transverse list

	newNode = new Double_node<Type>; //pointing to allocated memory of node
	newNode->node_value = data; // gave data to new node
	newNode->next_node = nullptr;
	newNode->previous_node = nullptr; //set node pointers null

	if (!list_head) {
		newNode->next_node = newNode;
		newNode->previous_node = newNode; //pointers point to itself
	}
	else {
		nodePtr = list_head;
		list_head->previous_node = newNode;
		// previous of current head now points to new node
		newNode->next_node = list_head; // new node points to current head

		while (nodePtr->next_node != list_head) { // to move to next node, peek ahead
			nodePtr = nodePtr->next_node;
		}
		nodePtr->next_node = newNode; //last node points to newNode
		newNode->previous_node = nodePtr; //newNode points to last node
	}

	list_head = newNode; //head points to newNode
	list_size++; //public variable so might need function to update
}

template <class Type>
void Circular_double_list<Type>::push_back(Type const & data) {
	Double_node<Type>* newNode; //added to front
	Double_node<Type>* nodePtr; //used to transverse list

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
		nodePtr = list_head;
		list_head->previous_node = newNode;
		// previous of current head now points to new node
		newNode->next_node = list_head; // new node points to current head

		while (nodePtr->next_node != list_head) { // to move to next node, peek ahead
			nodePtr = nodePtr->next_node;
		}

		nodePtr->next_node = newNode; //last node points to newNode
		newNode->previous_node = nodePtr; //newNode points to last node
	}

	list_size++; //public variable so might need function to update
}

template <class Type>
Type Circular_double_list<Type>::pop_front() { 

	Double_node<Type>* newHead = nullptr; //temporary new head pointer
	Double_node<Type>* nodePtr = nullptr; //used to transverse list
	Type data;

	if (!list_head) {
		throw std::underflow_error("No front element at index 0");
	}
	else{
		data = list_head->node_value; //node value inserted to be returned
		newHead = list_head->next_node; //newHead is second element now
		nodePtr = list_head;

		while (nodePtr->next_node != list_head) {
			nodePtr = nodePtr->next_node;
		}
		nodePtr->next_node = newHead; //points last node to newHead
		newHead->previous_node = nodePtr; //points newHead to last node

		delete list_head; //delete memory in front node
		list_head = (size() == 1) ? nullptr : newHead;
		//head will point to new head or nullptr depending if there was 1 element

		list_size--; //public variable so might need function to update
	}
	return data;
}

template <class Type>
Type Circular_double_list<Type>::pop_back() { 

	Double_node<Type>* nodePtr = nullptr; //used to transverse list
	Type data;

	if (!list_head) {
		throw std::underflow_error("No element at index n"); }
	else {
		nodePtr = list_head;

		while (nodePtr->next_node != list_head) {
			nodePtr = nodePtr->next_node;
		}

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

	if (list_head) { //if list empty, do nothing
		nodePtr = list_head;
		for (int i = 0; i < n; i++) { //nodePtr points to n position
			nodePtr = nodePtr->next_node;
		}
		nodePtr->next_node->previous_node = nodePtr->previous_node;
		//  (n+1) node points backwards to (n-1) node
		nodePtr->previous_node->next_node = nodePtr->next_node;
		//  (n-1) node points forward to (n+1) node
		(n) || (list_head = nodePtr->next_node);
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
		else cout << "Error: Value not found, returning -1" << endl;
	}
	else cout << "Error: List Empty, returning -1" << endl;

	return index;
}

template<class Type>
void Circular_double_list<Type>::clear() {

	Double_node<Type>* nodePtr; //used to transverse list
	int size = list_size;

	if (list_head) { //if list is empty do nothing else
		for (int i = 0; i < size; i++) {
			eraseAt(i);
		}
	}
}
#endif
