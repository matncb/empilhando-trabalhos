#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <tree.h>
#include <data.h>

typedef struct Element
{
    struct Element *left;
    struct Element *right;

    Data *data;

} Element;

typedef struct Tree
{
    struct Element *root;
    int elements;
} Tree;

void element_free(Element *aux)
{
    if (aux == NULL)
        return;
    data_free(aux->data);
    free(aux);
    return;
}

Tree *tree_create()
{
    Tree *tree = (Tree *)malloc(sizeof(tree));
    if (tree == NULL)
        return NULL;

    tree->root = NULL;  
    tree->elements = 0;

    return tree;
}

void tree_dfs_free(Element *elem)
{
    if (!elem) return;
    tree_dfs_free(elem->left);
    tree_dfs_free(elem->right);
    element_free(elem);
}

void tree_free(Tree *tree)
{
    if (!tree) return;
    tree_dfs_free(tree->root);
    free(tree);
}

int tree_get_elements(Tree *tree)
{
    if (!tree) return -1;
    return tree->elements;
}

int tree_add(Tree *tree, Data *data)
{
    if (tree == NULL) return 1;

    Element *aux = tree->root;
    int compare = DATA1_BEFORE;

    while ((compare == DATA1_BEFORE) && aux != NULL)
    {
        compare = data_compare_order(aux->data, data);

        if (compare == DATA_EQUAL)
        {
            // já existe um contato com esse nome
            return 2;
        }
        else if (compare == DATA2_BEFORE)
        {
            break;
        }

        aux = aux->right;
    }

    if (aux == NULL) return tree_add_right(tree,data);

    return tree_add_before(tree,aux,data);
}
