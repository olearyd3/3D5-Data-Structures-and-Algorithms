#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

//create a new node in the appropriate position for a BST
void tree_insert(Tree_Node** root, char data){
    //allocate new memory in the tree for a new root
    if(*root == NULL) {
        Tree_Node* new_root = (Tree_Node*)malloc(sizeof(Tree_Node));
        //make the current data be the new root of the tree and set before and after to NULL
        new_root->data = data;
        new_root->before = NULL;
        new_root->after = NULL;
        *root = new_root;
        return;
    }
    //recursively insert. Go to the node before if the new data is smaller in value
    if(data < (*root)->data) {
        tree_insert(&(*root)->before, data);
    }
    //if the new data is larger or equal in value go to the node after.
    else {
        tree_insert(&(*root)->after, data);
    }
}

//create a new BST representing data, terminated by '\0'
Tree_Node* create_bst (char data[]){
    //set the root equal to NULL
    Tree_Node* root = NULL;
    int i = 0;
    //insert once
    tree_insert(&root, data[i++]);
    //while not at the end of the string of characters keep inserting the data into the tree
        while (data[i] != '\0') {
            tree_insert(&root, data[i++]);
        }
    //return the root of the tree
    return root;
}

//If a value exists in the tree return a pointer to that node, otherwise return NULL
Tree_Node* tree_search(Tree_Node* root, char data){
    //if the root doesn't exist return NULL
    if (root == NULL) {
        return NULL;
    }
    //if the data being searched for matches the data in the root return the root
    if(data == root->data) {
        return root;
    }
    //if the data is lower in value, recursively search before
    else if(data < root->data) {
        return tree_search(root->before, data);
    }
    //if the data is higher in value, recursively search after
    else {
        return tree_search(root->after, data);
    }
}

//Traverse the tree, printing the data held in every node from smallest-greatest
void tree_print_sorted(Tree_Node* root){
    //if the root is null do nothing
    if(root == NULL) {
        return;
    }
    //print the tree by recursively calling the pritn function
    else {
        tree_print_sorted(root->before);
        printf("%c", root->data);
        tree_print_sorted(root->after);
    }
}

//delete every node without creating memory leak
void tree_delete(Tree_Node* root){
    //if the root doesn't exist return
    if(root == NULL) {
        return;
    }
    //recursively delete the roots
    tree_delete(root->before);
    tree_delete(root->after);
    free(root);
}
