#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#define MAX_LINE_LENGTH 64

int main()
{
    struct node* temp;
    struct redBlack* tree;
    int key;
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
                    break;
                    
                case 'r':
                    temp = nodeSearch(tree, tree->root, key);

                    if(temp != NULL)
                        nodeDelete(tree, temp);
                    break;
                    
                default:
                    printf("Comando inválido: %c\n", command);
            }
        }
    }
    
    //Cleaning buffer
    getchar();
    printTreeInOrder(tree, tree->root, 0);
    destroyTree(tree, tree->root);
    free(tree->nil);
    free(tree);
    return 0;
}
