#ifndef TREE_H_
#define TREE_H_

#define BLACK 0
#define RED 1

struct node
{
    int key;
    int color;
    struct node* left;
    struct node* right;
    struct node* dad;
    void* value;
};

//Sentinel
struct redBlack
{
    struct node* root;
    struct node* nil;
};

//Creates a dinamically tree with the root being NULL and returns it. 
struct redBlack* createTree();

//Creates a red node with its respective key
struct node* nodeCreate(struct redBlack* tree, int key);

//Insert the node at the tree and find the best position to the node
void nodeInsert(struct redBlack* tree, struct node* n);

//Fix any problems created by inserting a new node at the tree
void insertFixup(struct redBlack* tree, struct node* n);

//Search the desired key from the tree
struct node* nodeSearch(struct redBlack* tree, struct node* n, int key);

//Find the minimum key value
struct node* findMin(struct redBlack* tree, struct node* n);

//Find the maximum key value
struct node* findMax(struct redBlack* tree, struct node* n);

//Free all the nodes to prevent memory leak
void destroyTree(struct redBlack*, struct node* n);

//Change the right son of x to be the father, and x to be the left child
struct node* leftRotation(struct redBlack* tree, struct node* x);

//Change the left son of x to be the father, and x to be the right child
struct node* rightRotation(struct redBlack* tree, struct node* x);

//Delete the node "n" from the tree
void nodeDelete(struct redBlack* tree, struct node* n);

//Fix any problems caused to the tree when deleting the node "n"
void deleteFixup(struct redBlack* tree, struct node* n);

//Change the dad of "v" to the dad of "u", and the child of the dad of "u" to "v"
void nodeTransplant(struct redBlack* tree, struct node* u, struct node* v);

//Print Functions
void printTreeInOrder(struct redBlack* tree, struct node* n, int level);

void printTreePreOrder(struct redBlack* tree, struct node* n, int level);

void printTreePosOrder(struct redBlack* tree, struct node* n, int level);
#endif
