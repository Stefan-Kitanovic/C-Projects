#include <stdio.h>
#include <stdlib.h>

#define MAX_IME (100+1)
#define MAX_PREZIME (100+1)

/// jagoda banana bez slaga
/// nutela kiki

typedef struct model
{
    int id;
    char ime[MAX_IME];
    char prezime[MAX_PREZIME];
}MODEL;

typedef struct descriptor
{
    MODEL model;
    struct descriptor * left;
    struct descriptor * right;
}DESCRIPTOR;

void Insert(DESCRIPTOR ** root, DESCRIPTOR * jewNode);
DESCRIPTOR * CreateDesktiptor(int id, const char * ime, const char * prezime);
void PrintTree(DESCRIPTOR * root);


int main()
{
    DESCRIPTOR * root;
    root = NULL;

    Insert(&root, CreateDesktiptor(10, "Stefan", "Kitanovic"));
    Insert(&root, CreateDesktiptor(1, "Vlada", "Ivanovic"));
    Insert(&root, CreateDesktiptor(20, "Bebojsa", "Bobic"));
    Insert(&root, CreateDesktiptor(8, "Dragan", "Rukavina"));
    Insert(&root, CreateDesktiptor(18, "Milan", "Djurisic"));
    Insert(&root, CreateDesktiptor(24, "Milica", "Bjekovic"));
    Insert(&root, CreateDesktiptor(5, "Natasa", "Peric"));
    Insert(&root, CreateDesktiptor(209, "Una", "Jovic"));

    PrintTree(root);

    return 0;
}

DESCRIPTOR * CreateDesktiptor(int id, const char * ime, const char * prezime)
{
    DESCRIPTOR * desc;
    desc = malloc ( sizeof(DESCRIPTOR) );
    desc->left = NULL;
    desc->right = NULL;
    desc->model.id = id;
    strcpy(desc->model.ime, ime);
    strcpy(desc->model.prezime, prezime);

    return desc;
}

void Insert(DESCRIPTOR ** root, DESCRIPTOR * jewNode)
{
    if ( *root == NULL )
    {
        *root = jewNode;
        (*root)->left = NULL;
        (*root)->right = NULL;
        return;
    }

    DESCRIPTOR * curr;
    curr = *root;

    if ( jewNode->model.id < curr->model.id )
    {
        if ( curr->left == NULL )
        {
            curr->left = jewNode;
        }
        else
        {
            Insert(&(curr->left), jewNode);
        }
    }
    else if ( jewNode->model.id > curr->model.id )
    {
        if ( curr->right == NULL )
        {
            curr->right = jewNode;
        }
        else
        {
            Insert(&(curr->right), jewNode);
        }
    }
    else
    {
        printf("Cannot have same ID.\n");
    }

}

void PrintDescriptor( DESCRIPTOR d )
{
    printf ( "IME: %s, PREZIME: %s, ID: %d\n", d.model.ime, d.model.prezime, d.model.id);
}

void PrintTree(DESCRIPTOR * root)
{
    if ( root == NULL)
    {
        return;
    }

    PrintDescriptor(*root);
    printf("ID: %d, LEFT\n", root->model.id);
    PrintTree(root->left);
    printf("ID: %d, RIGHT\n", root->model.id);
    PrintTree(root->right);
    printf("END %d\n", root->model.id);
}
