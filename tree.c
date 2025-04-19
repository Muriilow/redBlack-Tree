#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

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

struct node* nodeSearch(struct redBlack* tree, struct node* n, int key)
{
    if(n == tree->nil)
        return tree->nil;

    fprintf(stderr, "search\n");
    if(n->key == key)
    {
        fprintf(stderr, "found it\n");
        return n;
    }

    if(n->key > key)
    {
        fprintf(stderr, "left\n");
        return nodeSearch(tree, n->left, key);
    }

    fprintf(stderr, "right\n");
    return nodeSearch(tree, n->right, key);
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
void nodeInsert(struct redBlack* tree, struct node* n)
{
    struct node* temp; //Nodo que vai guardar a informacao do ultimo nodo nao-nulo 
    struct node* x; //Nodo que vai encontrar posicao correta 

    x = tree->root;
    temp = tree->nil;

    fprintf(stderr, "while\n");
    while(x != tree->nil)
    {
        temp = x;
        if(n->key < x->key)
        {
            fprintf(stderr, "teste\n");
            x = x->left;
        }
        else
            x = x->right;
    }

    n->dad = temp;

    if(temp == tree->nil) //Nao percorremos nenhum valor abaixo 
        tree->root = n;
    else if(n->key < temp->key)
    {
        fprintf(stderr, "key<key\n");
        temp->left = n;
    }
    else
        temp->right = n;

    insertFixup(tree, n);
}

void insertFixup(struct redBlack* tree, struct node* n)
{
    fprintf(stderr, "insert\n");
    struct node* temp;

    while(n->dad->color == RED)
    {
        //If my dad is the left son
        //n will always have a grandpa because his dad needs to be red
        if(n->dad == n->dad->dad->left)
        {
            //temp = uncle
            temp = n->dad->dad->right;
            if(temp->color == RED)
            {
                n->dad->color = BLACK;
                temp->color = BLACK;
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
            //temp = uncle
            temp = n->dad->dad->left;
            if(temp->color == RED)
            {
                n->dad->color = BLACK;
                temp->color = BLACK;
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
    //The loop ends because n->dad is black (if n is root his dad is tree->nil), so the only problem that can occur is if the root is red;
    tree->root->color = BLACK;
}

void printTreeInOrder(struct redBlack* tree, struct node* n)
{
    if(n == tree->nil)
        return;

    printTreeInOrder(tree, n->left);

    printf("%d\n", n->key);

    printTreeInOrder(tree, n->right);
}

void printTreePreOrder(struct redBlack* tree, struct node* n)
{
    if(n == tree->nil)
        return;

    printf("%d\n", n->key);

    printTreePreOrder(tree, n->left);

    printTreePreOrder(tree, n->right);
}

void printTreePosOrder(struct redBlack* tree, struct node* n)
{
    if(n == tree->nil)
        return;

    printTreePosOrder(tree, n->left);

    printTreePosOrder(tree, n->right);

    printf("%d\n", n->key);
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

//void destroyTree(struct node* n)
//{
//    if(n->left != tree->nil)
//        destroyTree(n->left);
//
//    if(n->right != tree->nil)
//        destroyTree(n->right);
//
//    free(n);
//    n = tree->nil;
//}

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

/*Deleting node n at the tree*/
void nodeDelete(struct redBlack* tree, struct node* n)
{
    struct node* temp;
    struct node* aux;
    int origColor;

    temp = n;
    origColor = temp->color;

    if(n->left == tree->nil)
    {
        aux = n->right;
        nodeTransplant(tree, n, n->right);
    }
    else if(n->right == tree->nil)
    {
        aux = n->left;
        nodeTransplant(tree, n, n->left);
    }
    else
    {
        temp = findMin(tree, n->right);
        origColor = temp->color;
        aux = temp->right;

        if(temp->dad == n)
            aux->dad = temp;
        else
        {
            nodeTransplant(tree, temp, temp->right);
            temp->right = n->right;
            temp->right->dad = n;
        }

        nodeTransplant(tree, n, temp);
        temp->left = n->left;
        temp->left->dad = n;
        temp->color = n->color;
    }
    if(origColor == BLACK)
        deleteFixup(tree, aux);

    free(n);
}
int deleteFixup(struct redBlack* tree, struct node* n)
{
    struct node* temp;

    while(n != tree->root && n->color == BLACK)
    {
        if(n == n->dad->left)
        {
            temp = n->dad->right;
            if(temp->color == RED)
            {
                temp->color = BLACK;
                n->dad->color = RED;
                leftRotation(tree, n->dad);
                temp = n->dad->right;
            }
            if(temp->left->color == BLACK && temp->right->color == BLACK)
            {
                temp->color = RED;
                n = n->dad;
            } 
            else {
                if(temp->right->color == BLACK)
                {
                    temp->left->color = BLACK;
                    temp->color = RED;
                    rightRotation(tree, temp);
                    temp = n->dad->right;
                }
                
                //temp->color = n->dad->color;
                //n->dad->color = BLACK;
                //temp->right->color = BLACK;
                //leftRotation(tree, n->dad);
                //n = tree->root;
            }
        }
        else
        {
            temp = n->dad->left;
            if(temp->color == RED)
            {
                temp->color = BLACK;
                n->dad->color = RED;
                rightRotation(tree, n->dad);
                temp = n->dad->left;
            }
            if(temp->right->color == BLACK && temp->left->color == BLACK)
            {
                temp->color = RED;
                n = n->dad;
            } 
            else if(temp->left->color == BLACK)
            {
                temp->right->color = BLACK;
                temp->color = RED;
                leftRotation(tree, temp);
                temp = n->dad->left;
            }
        }
    }
}
