#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/* Initialization Functions ---------------------------*/

struct redBlack* createTree()
{
    struct redBlack* tree = (struct redBlack*) malloc(sizeof(struct redBlack));
    struct node* null = (struct node*) malloc(sizeof(struct node));

    null->key = 0;
    null->color = BLACK;
    null->right = null;
    null->left = null;
    null->dad = null;

    tree->root = null;
    tree->nil = null;
    return tree;
}

struct node* nodeCreate(struct redBlack* tree, int key)
{
    struct node* n = (struct node*) malloc(sizeof(struct node));

    n->left = tree->nil;
    n->right = tree->nil;
    n->dad = tree->nil;
    n->color = RED;
    n->key = key;

    return n;
}

/* Insertion -------------------------*/

void nodeInsert(struct redBlack* tree, struct node* n)
{
    struct node* y;  
    struct node* x;

    x = tree->root;
    y = tree->nil;

    while(x != tree->nil)
    {
        y = x;

        if(n->key < x->key)
            x = x->left;

        //Equal values goes to the right
        else
            x = x->right;
    }

    n->dad = y;

    if(y == tree->nil)
        tree->root = n;

    else if(n->key < y->key)
        y->left = n;
    
    else
        y->right = n;

    insertFixup(tree, n);
}

void insertFixup(struct redBlack* tree, struct node* n)
{
    struct node* y;

    while(n->dad->color == RED)
    {
        //If my dad is the left son
        //n will always have a grandpa because his dad needs to be red
        if(n->dad == n->dad->dad->left)
        {
            //y = uncle
            y = n->dad->dad->right;
            if(y->color == RED)
            {
                n->dad->color = BLACK;
                y->color = BLACK;
                n->dad->dad->color = RED;
                n = n->dad->dad;
            }
            else
            { 
                if(n == n->dad->right)
                {
                    n = n->dad;
                    leftRotation(tree, n);
                }
                n->dad->color = BLACK;
                n->dad->dad->color = RED;
                rightRotation(tree, n->dad->dad);
            }
        }
        else
        {
            //y = uncle
            y = n->dad->dad->left;
            if(y->color == RED)
            {
                n->dad->color = BLACK;
                y->color = BLACK;
                n->dad->dad->color = RED;
                n = n->dad->dad;
            }
            else
            {
                if(n == n->dad->left)
                {
                    n = n->dad;
                    rightRotation(tree, n);
                }

                n->dad->color = BLACK;
                n->dad->dad->color = RED;
                leftRotation(tree, n->dad->dad);
            }
        }
    }
    //The loop ends because n->dad is black
    //(if n is root his dad is tree->nil),
    //so the only problem that can occur is if the root is red;
    tree->root->color = BLACK;
}

/* Deletion ------------------------*/
void destroyTree(struct redBlack* tree, struct node* n)
{
    if(n->left != tree->nil)
        destroyTree(tree, n->left);

    if(n->right != tree->nil)
        destroyTree(tree, n->right);

    free(n);
    n = tree->nil;
}

/*Deleting node n at the tree*/
void nodeDelete(struct redBlack* tree, struct node* n)
{
    struct node* y;
    struct node* x;
    int origColor;

    y = n;
    origColor = y->color;

    if(n->left == tree->nil)
    {
        x = n->right;
        nodeTransplant(tree, n, n->right);
    }
    else if(n->right == tree->nil)
    {
        x = n->left;
        nodeTransplant(tree, n, n->left);
    }
    else
    {
        y = findMax(tree, n->left);
        origColor = y->color;
        x = y->left;

        if(y->dad == n)
            x->dad = y;
        else
        {
            nodeTransplant(tree, y, y->left);
            y->left = n->left;
            y->left->dad = y;
        }

        nodeTransplant(tree, n, y);
        y->right = n->right;
        y->right->dad = y;
        y->color = n->color;
    }
    if(origColor == BLACK)
    {
        deleteFixup(tree, x);
        tree->nil->dad = tree->nil;
    }
    free(n);
}
void deleteFixup(struct redBlack* tree, struct node* n)
{
    struct node* y;

    while(n != tree->root && n->color == BLACK)
    {
        if(n == n->dad->left)
        {
            y = n->dad->right;
            if(y->color == RED)
            {
                y->color = BLACK;
                n->dad->color = RED;
                leftRotation(tree, n->dad);
                y = n->dad->right;
            }
            if(y->left->color == BLACK && y->right->color == BLACK)
            {
                y->color = RED;
                n = n->dad;

                //Remove double red 
                if (n->color == RED)
                {
                    n->color = BLACK;
                    break;
                }
            } 
            else {
                if(y->right->color == BLACK)
                {
                    y->left->color = BLACK;
                    y->color = RED;
                    rightRotation(tree, y);
                    y = n->dad->right;
                }
                
                y->color = n->dad->color;
                n->dad->color = BLACK;
                y->right->color = BLACK;
                leftRotation(tree, n->dad);
                n = tree->root;
            }
        }
        else
        {
            y = n->dad->left;
            if(y->color == RED)
            {
                y->color = BLACK;
                n->dad->color = RED;
                rightRotation(tree, n->dad);
                y = n->dad->left;
            }
            if(y->right->color == BLACK && y->left->color == BLACK)
            {
                y->color = RED;
                n = n->dad;
                //Remove double red 
                if (n->color == RED)
                {
                    n->color = BLACK;
                    break;
                }
            } 
            else
            {
                if(y->left->color == BLACK)
                {
                    y->right->color = BLACK;
                    y->color = RED;
                    leftRotation(tree, y);
                    y = n->dad->left;
                }

                y->color = n->dad->color;
                n->dad->color = BLACK;
                y->left->color = BLACK;
                rightRotation(tree, n->dad);
                n = tree->root;
            }
        }
    }
}

/* Auxiliar functions -------------------------------------------- */

struct node* nodeSearch(struct redBlack* tree, struct node* n, int key)
{
    if(n == tree->nil)
        return tree->nil;

    if(n->key == key)
        return n;

    if(n->key > key)
        return nodeSearch(tree, n->left, key);

    return nodeSearch(tree, n->right, key);
}

struct node* findMin(struct redBlack* tree, struct node* n)
{
    if(n->left != tree->nil)
        return findMin(tree, n->left);

    return n;
}

struct node* findMax(struct redBlack* tree, struct node* n)
{
    if(n->right != tree->nil)
        return findMax(tree, n->right);

    return n;
}
/*Change the x node with his right son, the right son will be his dad, and the x node will be the left son*/
struct node* leftRotation(struct redBlack* tree, struct node* x)
{
    struct node* y;

    y = x->right;
    x->right = y->left;
    
    if(y->left != tree->nil)
        y->left->dad = x;

    y->dad = x->dad;

    if(x->dad == tree->nil)
        tree->root = y;
    else if(x == x->dad->left)
        x->dad->left = y;
    else
        x->dad->right = y;

    y->left = x;
    x->dad = y;

    return y;
}

struct node* rightRotation(struct redBlack* tree, struct node* x)
{
    struct node* y;

    y = x->left;
    x->left = y->right;
    
    if(y->right != tree->nil)
        y->right->dad = x;

    y->dad = x->dad;

    if(x->dad == tree->nil)
        tree->root = y;
    else if(x == x->dad->right)
        x->dad->right = y;
    else 
        x->dad->left = y;

    y->right = x;
    x->dad = y;

    return y;
}

void nodeTransplant(struct redBlack* tree, struct node* u, struct node* v)
{
    if(u->dad == tree->nil)
        tree->root = v;
    else if(u == u->dad->left)
        u->dad->left = v;
    else
        u->dad->right = v;

    v->dad = u->dad;
}

void printTreeInOrder(struct redBlack* tree, struct node* n, int level)
{
    if(n == tree->nil)
        return;

    printTreeInOrder(tree, n->left, level + 1);
    printf("%d,%d,%d\n", n->key, level, n->color);
    printTreeInOrder(tree, n->right, level + 1);
}

void printTreePreOrder(struct redBlack* tree, struct node* n, int level)
{
    if(n == tree->nil)
        return;

    printf("%d,%d,%d\n", n->key, level, n->color);
    printTreePreOrder(tree, n->left, level + 1);
    printTreePreOrder(tree, n->right, level + 1);
}

void printTreePosOrder(struct redBlack* tree, struct node* n, int level)
{
    if(n == tree->nil)
        return;

    printTreePosOrder(tree, n->left, level + 1);
    printTreePosOrder(tree, n->right, level + 1);
    printf("%d,%d,%d\n", n->key, level, n->color);
}


