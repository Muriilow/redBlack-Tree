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

    //printf("Digite agora os proximos valores numericos da arvore redBlack\n");
    //printf("Caso queira finalizar o programa digite qualquer caractere!\n");

    while (fgets(line, MAX_LINE_LENGTH, stdin) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';
        //printf("Linha lida: %s\n", line);

        if (sscanf(line, "%c %d", &command, &key) == 2) 
        {

            switch (command) {
                case 'i':
                    temp = nodeCreate(tree, key);
                    nodeInsert(tree, temp);
                    //printTreeInOrder(tree, tree->root);
                    break;
                    
                case 'r':
                    temp = nodeSearch(tree, tree->root, key);

                    if(temp != NULL)
                    {
                        nodeDelete(tree, temp);
                        //printTreeInOrder(tree, tree->root);
                    }
                    break;
                    
                default:
                    printf("Comando inválido: %c\n", command);
            }
        }
    }
    
    //while(scanf("%d", &mode) == 1)
    //{
    //    if(mode == 1)
    //    {
    //        if (scanf("%d", &key) != 1)
    //            return 1;

    //        temp = nodeCreate(tree, key);
    //        nodeInsert(tree, temp);
    //    }
    //    else if(mode == 2)
    //    {
    //        if (scanf("%d", &key) != 1)
    //            return 1;

    //        temp = nodeSearch(tree, tree->root, key);

    //        if(temp != NULL)
    //            nodeDelete(tree, temp);
    //        
    //    }
    //}
    
    
    //Limpando buffer
    getchar();
    return 0;
}
