#ifndef DOUBLE_NODE
#define DOUBLE_NODE

template <class T>
class Double_node {

	public:

		T node_value;

		Double_node<T>* previous_node;

		Double_node<T>* next_node;

		Double_node() {}; //default contructor

		Double_node(T const & object, Double_node * prev = nullptr, Double_node * next = nullptr):
			node_value(object),
			previous_node(prev),
			next_node(next) 
			{};

		~Double_node() {}; // default destructor

		T value() const { return node_value; }

		Double_node* next() const { return next_node; }

		Double_node* previous() const { return previous_node; }	

};
#endif
