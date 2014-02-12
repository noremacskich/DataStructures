#include <iostream>
//=================
// Linked List
//=================
using namespace std;

void int manager(const int size){
	free_size = size;
	free = new Free_Node;
	free->Start_byte = 0;
	free->end_byte = size-1;
	free->size = size;
	free->next = null;
}

typdef struct free_node * freeptr;

struct Free_Node
{	
	int start;
	int end;
	int size;
	freeptr next;
}

typedef struct allocatted_node * allocptr;

struct allocatted_node
{
	int start;
	int end;
	int size;
	int id;
	allocptr next;
}

void printList(List){
	//new pointer
	
	//point it at list
	
	// traverse the list
	while (
		// print out the values
		cout << "Start:" << start << endl;
		cout << "End:" << end << endl;
		cout << "Size:" << size << endl;
		cout << "ID:" << id << endl << endl;
		// move on to next node
		
	)
	
}

int main(){

	return 0;
}