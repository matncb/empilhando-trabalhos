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
    int balance_factor;

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
    aux->balance_factor = 0;

    aux->left = NULL;
    aux->right  = NULL;
    return aux;
}

Tree *tree_create()
{
    Tree *tree = (Tree *)malloc(sizeof(Tree));
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
    bool found = false;
    Element *out_element = NULL;
    Element *parent = NULL;
    tree_node_search_by_code_recursive(tree->root, code, &out_element, &found, &parent);
    if (found)
        return out_element->data;

    return NULL;
}


void tree_node_search_max_recursive(Element *node, Element **out_element,  Element **parent)
{
    *out_element = node;
    if (!node->right) return ;
    *parent = node;
    tree_node_search_max_recursive(node->right, out_element, parent);
}

int tree_remove_node(Tree *tree, Element *search, Element *parent)
{
    if ((!search->left) && (!search->right))
    {
        if (!parent)
        {
            tree->root = NULL;
        }
        else if (parent->right == search)
        {
            parent->right = NULL;
        }
        else
        {
            parent->left = NULL;
        }

        element_free(search);
        tree->elements--;
        return 0;
    }

    if ((!search->left) && (search->right))
    {
        if (!parent)
        {
            tree->root = search->right;
        }
        else if (parent->right == search)
        {
            parent->right = search->right;
        }
        else
        {
            parent->left = search->right;
        }

        element_free(search);
        tree->elements--;
        return 0;
    }

    if ((search->left) && (!search->right))
    {
        if (!parent)
        {
            tree->root = search->left;
        }
        else if (parent->right == search)
        {
            parent->right = search->left;
        }
        else
        {
            parent->left = search->left;
        }

        element_free(search);
        tree->elements--;
        return 0;
    }

    return 1;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int calculate_height(Element *node)
{
    if (node == NULL) return -1;
    return 1 + max(calculate_height(node->left), calculate_height(node->right));
}

int calculate_balance_factor(Element *node)
{
    if (node == NULL) return 0;
    int height_right = calculate_height(node->right);
    int height_left = calculate_height(node->left);
    return height_right - height_left;
}

void update_balance_factor(Element *node)
{
    if (node == NULL) return;
    node->balance_factor = calculate_balance_factor(node);
}

Element *rotate_right(Element *y)
{
    Element *x = y->left;
    Element *T2 = x->right;

    x->right = y;
    y->left = T2;

    update_balance_factor(y);
    update_balance_factor(x);

    return x;
}

Element *rotate_left(Element *x)
{
    Element *y = x->right;
    Element *T2 = y->left;

    y->left = x;
    x->right = T2;

    update_balance_factor(x);
    update_balance_factor(y);

    return y;
}

Element *balance_node(Element *node)
{
    if (node == NULL) return NULL;

    update_balance_factor(node);
    int bf = node->balance_factor;

    if (bf > 1)
    {
        if (node->right != NULL && node->right->balance_factor >= 0)
            return rotate_left(node);
        
        if (node->right != NULL && node->right->balance_factor < 0)
        {
            node->right = rotate_right(node->right);
            return rotate_left(node);
        }
    }

    if (bf < -1)
    {
        if (node->left != NULL && node->left->balance_factor <= 0)
            return rotate_right(node);
        
        if (node->left != NULL && node->left->balance_factor > 0)
        {
            node->left = rotate_left(node->left);
            return rotate_right(node);
        }
    }

    return node;
}

Element *tree_add_recursive(Element *node, Data *data, bool *already_exists)
{
    if (node == NULL)
    {
        Element *new_node = element_create(data);
        if (new_node == NULL)
        {
            *already_exists = false;
            return NULL;
        }
        return new_node;
    }

    int compair = data_compare_order_by_code(data, data_get_code(node->data));

    if (compair == DATA_EQUAL)
    {
        *already_exists = true;
        return node;
    }

    if (compair == DATA1_BEFORE)
        node->left = tree_add_recursive(node->left, data, already_exists);
    else
        node->right = tree_add_recursive(node->right, data, already_exists);

    return balance_node(node);
}

int tree_add(Tree *tree, Data *data)
{
    if (tree == NULL) return 2;

    bool already_exists = false;
    tree->root = tree_add_recursive(tree->root, data, &already_exists);

    if (already_exists) return 1;
    if (tree->root == NULL) return 2;

    tree->elements++;
    return 0;
}

Element *find_min_node(Element *node)
{
    Element *current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

Element *tree_remove_recursive(Element *node, int code, bool *found, Data **removed_data)
{
    if (node == NULL)
    {
        *found = false;
        return NULL;
    }

    int compair = data_compare_order_by_code(node->data, code);

    if (compair == DATA_EQUAL)
    {
        *found = true;

        if (node->left == NULL)
        {
            Element *temp = node->right;
            *removed_data = node->data;
            free(node);
            return temp;
        }
        else if (node->right == NULL)
        {
            Element *temp = node->left;
            *removed_data = node->data;
            free(node);
            return temp;
        }

        Element *min_node = find_min_node(node->right);
        *removed_data = node->data;
        node->data = min_node->data;

        bool temp_found;
        Data *temp_data = NULL;
        node->right = tree_remove_recursive(node->right, data_get_code(min_node->data), &temp_found, &temp_data);
    }
    else if (compair == DATA1_BEFORE)
    {
        Data *temp_data = NULL;
        node->right = tree_remove_recursive(node->right, code, found, &temp_data);
        if (*found)
        {
            *removed_data = temp_data;
        }
    }
    else
    {
        Data *temp_data = NULL;
        node->left = tree_remove_recursive(node->left, code, found, &temp_data);
        if (*found)
        {
            *removed_data = temp_data;
        }
    }

    return balance_node(node);
}

int tree_remove(Tree *tree, int code)
{
    if (tree == NULL) return 2;

    bool found = false;
    Data *removed_data = NULL;
    
    tree->root = tree_remove_recursive(tree->root, code, &found, &removed_data);

    if (!found) return 1;

    if (removed_data != NULL)
    {
        data_free(removed_data);
    }
    
    tree->elements--;
    return 0;
}