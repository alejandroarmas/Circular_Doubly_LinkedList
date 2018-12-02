# Circular_Doubly_LinkedList
This abstract data structure contains only a list_head and a counter for container size.

UML Function diagram 

 - list_head:Double_node
 - list_size:Integer
 + create():Circular_double_list
// copy constructor
 + create( in cdl:Circular_double_list ):Circular_double_list
 + size():Integer
 + empty():Boolean
 + front():Type
 + back():Type
 + at(in index:Integer):Type
 + head():Double_node
 + count( in obj:Type ):Integer
 + swap( inout list:Circular_double_list )
 + push_front( in obj:Type )
 + push_back( in obj:Type )
 + pop_front():Type
 + pop_back():Type
 + insertAt (in index:Integer , in obj:Type)
 + eraseAt(in index:Integer)
 + find ( in obj:Type ):Integer
 + clear ()
 + destroy() 
