#include "Circular_double_list.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <iomanip>

using namespace std;

template <class T>
void print(const Circular_double_list<T>& reference) {

	for (int i = 0; i < reference.size(); i++) {
		cout << reference.at(i) << " ";
	}
	cout << endl;
}

void displayFunctionMenu() {

	cout << setw(36) << "Welcome to Function Display Menu " << endl
		<< " 1. size()" << endl
		<< " 2. empty()" << endl
		<< " 3. front()" << endl
		<< " 4. back()" << endl
		<< " 5. at(int)" << endl
		<< " 6. head()" << endl
		<< " 7. count(Type)" << endl
		<< " 8. swap(Circular_double_list<Type>)" << endl
		<< " 9. push_front(Type)" << endl
		<< "10. push_back(Type)" << endl
		<< "11. pop_front()" << endl
		<< "12. pop_back()" << endl
		<< "13. insertAt(int, Type)" << endl
		<< "14. eraseAt(int)" << endl
		<< "15. find(Type)" << endl
		<< "16. clear()" << endl 
		<< "17. Exit" << endl;
}
int main() {

	Circular_double_list<string> test;

	Circular_double_list<string> test2;

	string responseS, index;
	int response, n;

	displayFunctionMenu();
	do {
		cout << endl << "Enter a menu value: " << endl;
		getline(cin, responseS);
		stringstream(responseS) >> response;


		switch (response) {

		case 1: {
			cout << "The Circlular_Linked_List size is: " << test.size() << endl << endl;

		}
				break;
		case 2: {
			cout << "The Circlular_Linked_List is " <<
				((test.empty()) ? ("empty.") : ("not empty.")) << endl
				<< endl;
			break;
		}
		case 3: {
			cout << "The Circlular_Linked_List front element is: ";
			try {
				cout << test.front();
			}
			catch (underflow_error & e) {
				cout << endl << "Error: Exception Caught" << endl;
				cout << e.what();
			}
			cout << endl << endl;
			break;
		}
		case 4: {
			cout << "The Circlular_Linked_List back element is: ";
			try {
				cout << test.back();
			}
			catch (underflow_error & e) {
				cout << endl << "Error: Exception Caught" << endl;
				cout << e.what();
			}
			cout << endl << endl;
			break;
		}
		case 5: {
			cout << "Enter an input 0 - " << test.size() - 1 << endl;
			//if list is empty, then will say enter input from 0 - - 1
			getline(cin, index);
			stringstream(index) >> n;
			cout << "The Circlular_Linked_List node at index " << n << ": ";
			try {
				cout << test.at(n);
			}
			catch (underflow_error & e) {
				cout << endl << "Error: Exception Caught" << endl;
				cout << e.what();
			}
			cout << endl << endl;
			break;
		}
		case 6: {
			cout << "The Circlular_Linked_List head pointer is: " << test.head() << endl << endl;
			break;
		}
		case 7: {
			cout << "Enter an Type to see how many times it appears "
				<< "in Circlular_Linked_List " << endl;
			getline(cin, index); //test is a linked list of string, therefor reusing index
			cout << "There are " << test.count(index) <<
				" instances of " << index << endl << endl;
			break;
		}
		case 8: {
			cout << "Copying test linked list into test2." << endl;
			test2.swap(test);
			cout << "Printing test2 linked list" << endl << endl;
			print(test2);
			break;
		}
		case 9: {
			cout << "Enter an Type to add to index 0 of "
				<< "Circlular_Linked_List " << endl;
			getline(cin, index);
			stringstream ss(index);

			while (ss >> index) {
				test.push_front(index);
			}
			break;
		}
		case 10: {
			cout << "Enter an Type to add to index "<< test.size() 
				<< " of Circlular_Linked_List " << endl;
			getline(cin, index);
			stringstream ss(index);

			while (ss >> index) {
				test.push_back(index);
			}
			break;
		}
		case 11: {
			cout << "Removing from index 0 "
				<< " of Circlular_Linked_List!!" << endl;
			try {
				test.pop_front();
			}
			catch (underflow_error & e) {
				cout << endl << "Error: Exception Caught" << endl;
				cout << e.what();
			}
			cout << endl << endl;
			break;
		}
		case 12: {
			cout << "Removing from index " << test.size() 
			 << " of Circlular_Linked_List!!" << endl;
			try {
				test.pop_back();
			}
			catch (underflow_error & e) {
				cout << endl << "Error: Exception Caught" << endl;
				cout << e.what();
			}
			cout << endl << endl;
			break;
		}
		case 13: {
			cout << "Which index would you like to add a value to?" << endl;
			getline(cin, index);
			stringstream(index) >> n;
			cout << "Enter an Type to add to index " << n
				<< " of Circlular_Linked_List " << endl;
			getline(cin, index);
			test.insertAt(n, index);
			break;
		}
		case 14: {
			cout << "Which index would you delete a value from?" << endl;
			getline(cin, index);
			stringstream(index) >> n;
			test.eraseAt(n);
			break;
		}
		case 15: {
			cout << "Type a value to see where instance is located" << endl;
			getline(cin, index);
			cout << index << " is located at index: " << test.find(index) 
			<< endl << endl; 
			break;
		}
		case 16: {
			cout << "Erasing entire list" << endl;
			test.clear();
		}

		}
		cout << setw(20) << "Your list contains: ";
		((test.empty()) && (cout << "nothing"));
		print(test);
	} while (response > 0 && response <= 16);

		return 0;
}
