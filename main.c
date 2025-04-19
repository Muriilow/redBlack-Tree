#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main()
{
    struct node* temp;
    struct redBlack* tree;
    int mode, key;

    key = 0;
    temp = NULL;
    tree = createTree();

    printf("Digite agora os proximos valores numericos da arvore redBlack\n");
    printf("Caso queira finalizar o programa digite qualquer caractere!\n");

    while(scanf("%d", &mode) == 1)
    {
        if(mode == 1)
        {
            if (scanf("%d", &key) != 1)
                return 1;

            temp = nodeCreate(tree, key);
            nodeInsert(tree, temp);
        }
        else if(mode == 2)
        {
            if (scanf("%d", &key) != 1)
                return 1;

            temp = nodeSearch(tree, tree->root, key);

            if(temp != NULL)
                nodeDelete(tree, temp);
            
        }
    }
    
    printTreeInOrder(tree, tree->root);
    
    //Limpando buffer
    getchar();
    return 0;
}
