#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "bstdb.h"

//struct of type Node
typedef struct Node Node;
struct Node{
    char* book_title;
    int word_count;
	int height;
	int unique_id;
    struct Node * left;
    struct Node * right;
};

//global variables -- values initialised in bstdb_init()
Node* root;
bool isbalanced;
int insertions;
int traversals;

//function to initialise memory and vairables -- return 1 if successful initialisation and 0 if not
int
bstdb_init ( void ) {

	//allocate memory to root
	root = (Node*)malloc(sizeof(Node));

	//if successful, return 1
	if(root) {
		root->height = 1;
		root->left = NULL;
		root->right = NULL;
		root->book_title = NULL;
		isbalanced = true;
		insertions = 0;
		traversals = 0;
		return 1;
	}

	//otherwise return 0
	else return 0;
}

//function to get return height
int height(Node *node) { 
    if (node == NULL) {
        return 0; 
	}	
    return node->height; 
} 

//function to return the maximum out of two ints
int max(int a, int b) { 
    if (a > b) {
		return a;
	}  
	else return b; 
} 

//function for AVL Tree -- rotate right
Node* rotate_right(Node* root) { 
	//initialise two variables
    Node *n_root = root->left; 
    Node *temp_var = n_root->right; 
  
    //Perform the rotation 
    n_root->right = root; 
    root->left = temp_var; 
  
    //Update heights 
	root->height = max(height(root->left), height(root->right))+1; 
    n_root->height = max(height(n_root->left), height(n_root->right))+1; 

    //Return new root 
    return n_root; 
} 

//function for AVL Tree -- rotate left
Node* rotate_left(Node *n_root) { 
    Node *root = n_root->right; 
    Node *temp_var = root->left; 
  
    //Perform the rotation 
    root->left = n_root; 
    n_root->right = temp_var; 
  
    //Update heights 
	n_root->height = max(height(n_root->left), height(n_root->right))+1; 
    root->height = max(height(root->left), height(root->right))+1; 
  
    //Return new root 
    return root; 
} 

//function to check whether the tree is balanced (use bool from the header stdbool.h)
bool balanced(Node* root) {
	//malloc
	Node *temp = (Node*)malloc(sizeof(Node));
    temp = root;
	int balance;
	//if NULL return false
    if (temp == NULL) {
        return false;
    }
    //recurse before
    balanced(temp->left);
	//if the node is NOT NULL, check the balance of children
    if (temp != NULL) { 
        
		if (temp == NULL) {
			balance = 0;
		}
		else {
			balance = height(temp->left) - height(temp->right);
		}
		if ((balance > 1) || (balance < -1)) {
			isbalanced = false;
		}
    }
    //recurse after
    balanced(temp->right);

	if (isbalanced) {
		return true;
	}
	else {
		return false;
	}
}

//function to generate a unique ID. Simply increments a counter for each new node to be added.
int id_generator() {
	static int count= 0;
	count++;
	return count;
}

//function to insert new nodes into the tree
Node * tree_insert(Node* root, char* name, int word_count, int unique_id){
	//allocate memory and create temporary variable
	Node *temp ;
	temp = (Node*)malloc(sizeof(Node));
	temp = root;
	//if the variable is not in the tree
	if (temp == NULL){	
		Node *temp = (Node*)malloc(sizeof(Node));
		//update each value of the struct
		temp->unique_id = unique_id;
		temp->right = NULL;
		temp->left = NULL;
		temp->word_count = word_count;
		//for titles of books, use a calloc to help allocate the title properly
		temp->book_title = calloc(strlen(name) + 1, sizeof(char));
		//if the book exists, copy the name of it to the book_title slot
		if (temp->book_title)
			strcpy(temp->book_title, name);
			//otherwise delete it
		else {
			Node *del = (Node*)malloc(sizeof(Node));
			del = temp;
			free(del);
			temp = NULL;
		}
		//incrememnt height and insertions -- return temp
		temp->height = 1;
		insertions++;
		return temp;
	}

	//if the ID is less than the ID in temp then recursively traverse left 
	if (unique_id < temp->unique_id) {
		temp->left = tree_insert(temp->left, name, word_count, unique_id);
	}
	//if the ID is greater than the ID in temp then recursively traverse right
	else if(unique_id > temp->unique_id) {
		temp->right = tree_insert(temp->right, name, word_count, unique_id);
	}
	//otherwise return temp
	else
		return temp;

	// Update the height of the previous nodes -- used for checking balance
	if (height(temp->left) > height(temp->right)) {
    	temp->height = 1 + height(temp->left);
	}
	else {
		temp->height = 1 + height(temp->right);
	}
	//initiliase a balance variable. If a root doesn't exist then balance is 0.
	int balance;
	if (temp == NULL) {
		balance = 0;
	}
	//otherwise, let balance be the difference between the left and right heights
	else {
		balance = height(temp->left) - height(temp->right);
	}

	//If the tree is unbalanced, there are 4 cases 
    //The left left case, where the tree needs to be rotated right
    if ((balance > 1) && (unique_id < temp->left->unique_id)) {
        return rotate_right(temp);
	}
    //The right right case, where the tree needs to be rotated left
    if ((balance < -1) && unique_id > (temp->right->unique_id)) {
        return rotate_left(temp); 
	}
    //The left right case, where the tree needs to be rotated left then return the rotation to the right
    if ((balance > 1) && (unique_id > temp->left->unique_id)) { 
        temp->left = rotate_left(temp->left); 
        return rotate_right(temp); 
    } 
    //The right left case, where the tree needs to be rotated right then return the rotation to the left
    if ((balance < -1) && (unique_id < temp->right->unique_id)) { 
        temp->right = rotate_right(temp->right); 
        return rotate_left(temp); 
    } 
    // return the original node
    return temp; 
}

//bstdb_add function
int
bstdb_add ( char *name, int word_count ) {
	// This function should create a new node in the binary search tree, 
	// populate it with the name and word_count of the arguments and store
	// the result in the tree.
	//
	// This function should also generate and return an identifier that is
	// unique to this document. A user can find the stored data by passing
	// this ID to one of the two search functions below.
	//
	// How you generate this ID is up to you, but it must be an integer. Note
	// that this ID should also form the keys of the nodes in your BST, so
	// try to generate them in a way that will result in a balanced tree.
	//
	// If something goes wrong and the data cannot be stored, this function
	// should return -1. Otherwise it should return the ID of the new node

	//generate a unique_id that is an integer
    int unique_id = id_generator();
	
	//allocate memory
	Node *temp = (Node*)malloc(sizeof(Node));
	//insert 
	root = tree_insert(root, name, word_count, unique_id);
	//if something is wrong
	if (temp == NULL){
		printf("something seems to have gone wrong.");
		return -1;
	}
	//return the id
	return unique_id;
}

//function to search for a root
Node* tree_search(Node* root, int doc_id){
	//if the root is NULL them return NULL
	Node *temp = NULL;
	if (root == NULL) {
		return NULL;
	}
	//if the IDs are equal, return that root
	if (root->unique_id == doc_id) {
		traversals++;
		return root;
	}
	//if the ID in the root is bigger then search to the left
	else if (root->unique_id > doc_id) {
		traversals++;
		temp = tree_search(root->left, doc_id);
	}
	//otherwise, if the ID in the root is smaller, search to the right
	else {
		traversals++;
		temp = tree_search(root->right, doc_id);
	}
	//return NULL if smth. went wrong
	return temp;
}

int
bstdb_get_word_count ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the word_count of the node with the corresponding doc_id.
	// If the required node is not found, this function should return -1
    Node *temp = NULL;
    //search the tree for a certain ID
	temp = tree_search(root, doc_id);
	if (temp == NULL){
		return -1;
	}
	//Return the word_count associated with that ID
	return temp->word_count;
}

char*
bstdb_get_name ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the name of the node with the corresponding doc_id.
	// If the required node is not found, this function should return NULL or 0
	Node *temp = NULL;
    //Search the tree for a certain ID
	temp = tree_search(root, doc_id);
	if (temp == NULL){
		return NULL;
	}
	//return the book title associated with that ID
	return temp->book_title;
}

void
bstdb_stat ( void ) {
	// Use this function to show off! It will be called once after the 
	// profiler ends. The profiler checks for execution time and simple errors,
	// but you should use this function to demonstrate your own innovation.
	// Suggestions or things you might want to demonstrate are given below,
	// but in general what you choose to show here is up to you. This function
	// counts for marks so make sure it does something interesting or useful.
	//  + Check if your tree is balanced and print the result
	bool balance_check = balanced(root);
	if (balance_check){
		printf("\n>>> The tree is balanced");
	 }
	else {
		printf("\n>>> The tree is not balanced.");
	}
	// + Does the number of nodes in the tree match the number you expect
	//    based on the number of insertions you performed?
	//
	printf("\n>>> There were %d insertions.", insertions);
	//  + How many nodes on average did you need to traverse in order to find
	//    a search result? 
	float avgnodes = ((float)traversals/(float)insertions);
	printf("\n>>> Out of a total of %d traversals there were %f average traversals per search\n", traversals, avgnodes);
}

//function to free memory which will be called in quit
void tree_delete (Node* root ) {
	//If the root is NULL, exit
    if (root == NULL) {
        return; 
    }
	//recursively delete
    tree_delete(root->left);
    tree_delete(root->right); 
    free(root);
}

//quit function
void
bstdb_quit ( void ) {
	// This function will run once (and only once) when the program ends. Use
	// it to free any memory you allocated in the course of operating the
	// database.
	tree_delete(root);
}
