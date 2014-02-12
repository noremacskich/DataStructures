#include <iostream>

using namespace std;

typedef struct TREENODE * TREEPTR;

struct TREENODE{
	int key;
	TREEPTR lchild;
	TREEPTR rchild;
};

// prototypes
int getroot(const TREEPTR root);


// functions
bool isempty(const TREEPTR root){
	/*
	if(root == NULL )
		return true;
	else
		return false;
	*/
	
	return (root==NULL);
}

void insert(TREEPTR & root, const int num){
	
	// ground condition
	if(root==NULL){
		
		// Create the Node
		root = new TREENODE;
		
		// Initialize the node
		root->key = num;
		root->lchild = NULL;
		root->rchild = NULL;
		
	}else if(root->key > num){
		// Go to the left
		insert(root->lchild, num);
		
	}else if(root->key < num){
		// Go to the right
		insert(root->rchild, num);
	}else if(root->key == num){
	// this will occur if num is equal to key
		cout << "key == num" << endl;
	}
}

bool search(const TREEPTR root, const int num){
	// print out the root
	//cout << getroot(root) << endl;
	
	// ground condition
	if(root == NULL) // empty tree
		return false;
	
	// ground condition 2 - found num in tree
	if(root->key == num){
		// won't work if root is empty
		return true;
	}
	
	if( root->key > num ){
		// move to the left
		search(root->lchild, num);
	}else{
		// move to the right
		search(root->rchild, num);
	}
	
}

int getroot(const TREEPTR root){
	if(!isempty(root))
		return root->key;
	else
		return -99; // Root is empty
}

int main(void){
	TREEPTR	root;
	
	root = NULL; // make it an empty tree
	
	insert(root, 5);
	insert(root, 10);
	insert(root, 3);
	insert(root, 14);
	
	if ( search(root, 14) == true)  // == if ( isempty(root) )
		cout << "Found" << endl;
	else
		cout << "not Found" << endl;
	
	return 0;
}