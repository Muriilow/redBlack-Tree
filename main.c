#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#define MAX_LINE_LENGTH 256

int main()
{
    struct node* temp;
    struct redBlack* tree;
    int mode, key;
    char line[MAX_LINE_LENGTH];
    char command;

    key = 0;
    temp = NULL;
    tree = createTree();

    while (fgets(line, MAX_LINE_LENGTH, stdin) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

        if (sscanf(line, "%c %d", &command, &key) == 2) 
        {

            switch (command) {
                case 'i':
                    temp = nodeCreate(tree, key);
                    nodeInsert(tree, temp);
                    printTreeInOrder(tree, tree->root);
                    break;
                    
                case 'r':
                    temp = nodeSearch(tree, tree->root, key);

                    if(temp != NULL)
                    {
                        nodeDelete(tree, temp);
                        printTreeInOrder(tree, tree->root);
                    }
                    break;
                    
                default:
                    printf("Comando inválido: %c\n", command);
            }
        }
    }
    
    //Cleaning buffer
    getchar();

    //Removing the rest of the tree
    destroyTree(tree, tree->root);
    free(tree->nil);
    free(tree);
    return 0;
}
