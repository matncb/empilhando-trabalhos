#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
    if (aux == NULL) return;
    data_free(aux->data);
    free(aux);
    return;
}

Element *element_create(Data *data)
{
    if (!data) return NULL;
    Element *aux = (Element*) malloc(sizeof(Element));
    if (!aux) return NULL;

    aux->data = data;

    aux->left = NULL;
    aux->right  = NULL;
    return aux;
}

Tree *tree_create()
{
    Tree *tree = (Tree *)malloc(sizeof(tree));
    if (tree == NULL) return NULL;

    tree->root = NULL;
    tree->elements = 0;

    return tree;
}

void tree_free_recursive(Element *elem)
{
    if (!elem) return;
    tree_free_recursive(elem->left);
    tree_free_recursive(elem->right);
    element_free(elem);
}

void tree_free(Tree *tree)
{
    if (!tree) return;
    tree_free_recursive(tree->root);
    free(tree);
}

int tree_get_elements(Tree *tree)
{
    if (!tree) return -1;
    return tree->elements;
}

void tree_preorder_recursive(Element *elem, Data **list, int *pos)
{
    if (!elem) return;
    list[*pos] = elem->data;
    (*pos)++;
    tree_preorder_recursive(elem->left, list, pos);
    tree_preorder_recursive(elem->right, list, pos);
}

void tree_inorder_recursive(Element *elem, Data **list, int *pos)
{
    if (!elem) return;
    tree_inorder_recursive(elem->left, list, pos);
    list[*pos] = elem->data;
    (*pos)++;
    tree_inorder_recursive(elem->right, list, pos);
}

void tree_posorder_recursive(Element *elem, Data **list, int *pos)
{
    if (!elem) return;
    tree_posorder_recursive(elem->left, list, pos);
    tree_posorder_recursive(elem->right, list, pos);
    list[*pos] = elem->data;
    (*pos)++;
}

Data **tree_list(Tree *tree, PathType path)
{
    if (tree == NULL)
        return NULL;
    if (tree->elements == 0)
        return NULL;

    Data **list = (Data **)malloc(tree->elements * sizeof(Data *));
    if (list == NULL) return NULL;

    int pos = 0;

    switch (path)
    {
    case PATH_INORDER:
        tree_inorder_recursive(tree->root, list, &pos);    
        break;

    case PATH_PREORDER:
        tree_preorder_recursive(tree->root, list, &pos);
        break;

    case PATH_POSORDER:
        tree_posorder_recursive(tree->root, list, &pos);    
        break;
    }  
    
    return list;
}


void tree_node_search_by_code_recursive(Element *node, int code, Element **out_element, bool *found, Element **parent)
{
    int compair = data_compare_order_by_code(node->data, code);
    if(compair == DATA_EQUAL){
        *out_element = node;
        *found = true;
        return;
    }

    if(compair == DATA1_BEFORE)
    {
        if (node->right == NULL)
        {
            *out_element = node;
            *found = false;
            return;
        }
        *parent = node;
        return tree_node_search_by_code_recursive(node->right, code, out_element, found, parent);
    }

    if (node->left == NULL)
    {
        *out_element = node;
        *found = false;
        return;
    }
    *parent = node;
    return tree_node_search_by_code_recursive(node->left, code, out_element, found, parent);
}

Element *tree_search_by_code(Tree *tree, int code, bool *found, Element **parent)
{
    if (tree == NULL || tree->root == NULL) return NULL;

    Element *out_element = NULL;
    tree_node_search_by_code_recursive(tree->root, code, &out_element, found, parent);
    return out_element;
}

Data *tree_search_by_code_pure(Tree *tree, int code) 
{
    if (tree == NULL || tree -> root == NULL) return NULL;
    bool found;
    Element *out_element = NULL;
    Element *parent = NULL;
    tree_node_search_by_code_recursive(tree->root, code, &out_element, &found, &parent);
    if (found)
        return out_element->data;

    return NULL;
}

int tree_add(Tree *tree, Data *data)
{
    if (tree == NULL) return 2;

    bool found;
    Element *parent = NULL;

    Element *search = tree_search_by_code(tree, data_get_code(data), &found, &parent);
    if (found) return 1;

   
    Element *node = element_create(data);
    if (!node) return 2;

    if (search == NULL)
    {
        tree->root = node;
        tree->elements++;
        return 0;
    }

    int compair = data_compare_order_by_code(data, data_get_code(search->data));

    if (compair == DATA1_BEFORE)
    {
       search->left = node;
    }
    else
    {
        search->right = node;
    }

    tree->elements++;
    return 0;
}

void tree_node_search_max_recursive(Element *node, Element **out_element,  Element **parent)
{
    *out_element = node;
    if (!node->right) return ;
    *parent = node;
    tree_node_search_max_recursive(node->right, out_element, parent);
}

int tree_remove(Tree *tree, int code)
{
    if (tree == NULL) return 2;

    bool found;
    Element *parent = NULL;

    Element *search = tree_search_by_code(tree, code, &found, &parent);
    if (!found) return 1;

    Element *new_root_parent = search;
    Element *new_root = NULL;

    if (search->left)
    {
        tree_node_search_max_recursive(search->left, &new_root, &new_root_parent);
    }
    else
    {
        new_root = search->right;
        new_root_parent = search;
    }
    
    if (parent->left == search)
    {
        parent->left = new_root;
    }
    else
    {
        parent->right = new_root;
    }
    
    if (new_root_parent->left == new_root)
    {
        new_root_parent->left = NULL;
    }
    else
    {
        new_root_parent->right = NULL;
    }

    element_free(search);
    tree->elements--;
    return 0;
}
 