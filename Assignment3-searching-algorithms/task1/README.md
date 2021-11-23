# Task 1 – Binary Search Tree

## The following were the instructions for Task 1

Implement a binary search tree using char as the data records. First edit the TreeNode
struct in the bst.h file to create a suitable structure to represent a node.

Next, implement the following functions in bst_skeleton.c, and test them from your own
separate main file (which should NOT be submitted to submitty):

1. void tree_insert ( Tree_Node** root, char data );
Creates a new node in the tree in the appropriate position for a binary search tree.

2. Tree_Node* create_bst (char data[]);
Creates a new binary search tree representing the data, which is terminated by ‘\n’
(note, you do not need to optimise the tree created)

3. Tree_Node* tree_search ( Tree_Node* root, char data );
If a value exists in the tree, return a pointer to that node, otherwise return NULL.

4. void tree_print_sorted ( Tree_Node* root );
Traverse the tree, printing the data held in every node, in smallest-to-greatest sorted
order.

5. void tree_delete ( Tree_Node* root );
Delete every node in the tree without creating a memory leak.
