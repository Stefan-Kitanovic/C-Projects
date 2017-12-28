#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 20+1

typedef struct struktura_st
{
    double broj;
    struct struktura_st *next;
} STRUKTURA;

void push ( STRUKTURA ** root, double broj );
double pop ( STRUKTURA ** root );
void printList ( STRUKTURA * root );
void popovanje ( STRUKTURA ** root, FILE *inputFile );

int main()
{
    STRUKTURA *root;
    root = NULL;
/*
    push(&root, 15);
    push(&root, 26);
    push(&root, 32);
    push(&root, 78);

    printList(root);
    printf("\n\n%lf\n\n", pop(&root));
    printList(root);
*/
    FILE *inputFile;
    inputFile = fopen("postfix_izraz.txt", "r");
    popovanje(&root, inputFile);
    fclose(inputFile);

    return 0;
}

void push ( STRUKTURA ** root, double broj )
{
    STRUKTURA *newNode;

    if ( (*root) == NULL )
    {
        *root = (STRUKTURA *)malloc(sizeof(STRUKTURA));
        (*root)->broj = broj;
        (*root)->next = NULL;
        return;
    }

    newNode = (STRUKTURA *)malloc(sizeof(STRUKTURA));
    newNode->broj = broj;
    newNode->next = *root;
    *root = newNode;
}

double pop ( STRUKTURA ** root )
{
    STRUKTURA *temp;
    temp = *root;

    (*root) = (*root)->next;
    double broj = temp->broj;
    free(temp);

    return broj;
}

void printList ( STRUKTURA * root )
{
    STRUKTURA *temp;
    temp = root;

    while ( temp != NULL )
    {
        printf("[%lf]\n", temp->broj);
        temp = temp->next;
    }
}

void popovanje ( STRUKTURA ** root, FILE *inputFile )
{
    char oper[2];
    while ( fscanf(inputFile, "%c", oper) != EOF )
    {
        if ( oper[0] == ' ' )
        {
            continue;
        }

        if ( oper[0] <= '9' && oper[0] >= '0' )
        {
            double broj = atof(oper);
            push(root, broj);
        }
        else
        {
            double operand2 = pop(root);
            double operand1 = pop(root);
            switch ( oper[0] )
            {
                case '+':
                {
                    push(root, operand1 + operand2);
                    break;
                }
                case '-':
                {
                    push(root, operand1 - operand2);
                    break;
                }
                case '/':
                {
                    if ( operand2 == 0 )
                    {
                        push(root,0);
                        break;
                    }

                    push(root,operand1 / operand2);
                    break;
                }
                case '*':
                {
                    push(root,operand1 * operand2);
                    break;
                }
            }
        }
    }

    printf("Rezultat: %.2f\n", pop(root));
    fclose(inputFile);
}
