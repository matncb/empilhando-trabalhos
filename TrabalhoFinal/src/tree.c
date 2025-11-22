#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <tree.h>
#include <person.h>
#include <playlist.h>

typedef struct Element
{
    struct Element *left;
    struct Element *right;

    Person *person;
    int balance_factor;

} Element;

typedef struct Tree
{
    struct Element *root;
    int elements;
} Tree;

int tree_get_playlist_size(Person *person)
{
    if (!person) return 0;
    PlayList *pl = (PlayList *)person_get_playlist(person);
    if (!pl) return 0;
    return playlist_get_elements(pl);
}

void tree_element_free(Element *aux)
{
    if (aux == NULL) return;
    free(aux);
    return;
}

Element *tree_element_create(Person *person)
{
    if (!person) return NULL;
    Element *aux = (Element*) malloc(sizeof(Element));
    if (!aux) return NULL;

    aux->person = person;
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
    tree_element_free(elem);
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

void tree_preorder_recursive(Element *elem, Person **list, int *pos)
{
    if (!elem) return;
    list[*pos] = elem->person;
    (*pos)++;
    tree_preorder_recursive(elem->left, list, pos);
    tree_preorder_recursive(elem->right, list, pos);
}

void tree_inorder_recursive(Element *elem, Person **list, int *pos)
{
    if (!elem) return;
    tree_inorder_recursive(elem->left, list, pos);
    list[*pos] = elem->person;
    (*pos)++;
    tree_inorder_recursive(elem->right, list, pos);
}

void tree_posorder_recursive(Element *elem, Person **list, int *pos)
{
    if (!elem) return;
    tree_posorder_recursive(elem->left, list, pos);
    tree_posorder_recursive(elem->right, list, pos);
    list[*pos] = elem->person;
    (*pos)++;
}

Person **tree_list(Tree *tree, PathType path)
{
    if (tree == NULL)
        return NULL;
    if (tree->elements == 0)
        return NULL;

    Person **list = (Person **)malloc(tree->elements * sizeof(Person *));
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

int tree_max(int a, int b)
{
    return (a > b) ? a : b;
}

int tree_calculate_height(Element *node)
{
    if (node == NULL) return -1;
    return 1 + tree_max(tree_calculate_height(node->left), tree_calculate_height(node->right));
}

int tree_calculate_balance_factor(Element *node)
{
    if (node == NULL) return 0;
    int height_right = tree_calculate_height(node->right);
    int height_left = tree_calculate_height(node->left);
    return height_right - height_left;
}

void tree_update_balance_factor(Element *node)
{
    if (node == NULL) return;
    node->balance_factor = tree_calculate_balance_factor(node);
}

Element *tree_rotate_right(Element *y)
{
    Element *x = y->left;
    Element *T2 = x->right;

    x->right = y;
    y->left = T2;

    tree_update_balance_factor(y);
    tree_update_balance_factor(x);

    return x;
}

Element *tree_rotate_left(Element *x)
{
    Element *y = x->right;
    Element *T2 = y->left;

    y->left = x;
    x->right = T2;

    tree_update_balance_factor(x);
    tree_update_balance_factor(y);

    return y;
}

Element *tree_balance_node(Element *node)
{
    if (node == NULL) return NULL;

    tree_update_balance_factor(node);
    int bf = node->balance_factor;

    if (bf > 1)
    {
        if (node->right != NULL && node->right->balance_factor >= 0)
            return tree_rotate_left(node);
        
        if (node->right != NULL && node->right->balance_factor < 0)
        {
            node->right = tree_rotate_right(node->right);
            return tree_rotate_left(node);
        }
    }

    if (bf < -1)
    {
        if (node->left != NULL && node->left->balance_factor <= 0)
            return tree_rotate_right(node);
        
        if (node->left != NULL && node->left->balance_factor > 0)
        {
            node->left = tree_rotate_left(node->left);
            return tree_rotate_right(node);
        }
    }

    return node;
}

int tree_compare_by_playlist_size(Person *person1, int size)
{
    int size1 = tree_get_playlist_size(person1);
    
    if (size1 < size)
        return -1;
    else if (size1 > size)
        return 1;
    
    return 0;
}

Element *tree_add_recursive(Element *node, Person *person, bool *already_exists)
{
    if (node == NULL)
    {
        Element *new_node = tree_element_create(person);
        if (new_node == NULL)
        {
            *already_exists = false;
            return NULL;
        }
        return new_node;
    }

    int node_size = tree_get_playlist_size(node->person);
    int compair = tree_compare_by_playlist_size(person, node_size);

    if (compair == 0)
    {
        *already_exists = true;
        return node;
    }

    if (compair < 0)
        node->left = tree_add_recursive(node->left, person, already_exists);
    else
        node->right = tree_add_recursive(node->right, person, already_exists);

    return tree_balance_node(node);
}

int tree_add(Tree *tree, Person *person)
{
    if (tree == NULL) return 2;

    bool already_exists = false;
    tree->root = tree_add_recursive(tree->root, person, &already_exists);

    if (already_exists) return 1;
    if (tree->root == NULL) return 2;

    tree->elements++;
    return 0;
}

Element *tree_find_min_node(Element *node)
{
    Element *current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

Element *tree_remove_recursive(Element *node, int playlist_size, bool *found, Person **removed_person)
{
    if (node == NULL)
    {
        *found = false;
        return NULL;
    }

    int compair = tree_compare_by_playlist_size(node->person, playlist_size);

    if (compair == 0)
    {
        *found = true;

        if (node->left == NULL)
        {
            Element *temp = node->right;
            *removed_person = node->person;
            free(node);
            return temp;
        }
        else if (node->right == NULL)
        {
            Element *temp = node->left;
            *removed_person = node->person;
            free(node);
            return temp;
        }

        Element *min_node = tree_find_min_node(node->right);
        *removed_person = node->person;
        node->person = min_node->person;

        bool temp_found;
        Person *temp_person = NULL;
        int min_size = tree_get_playlist_size(min_node->person);
        node->right = tree_remove_recursive(node->right, min_size, &temp_found, &temp_person);
    }
    else if (compair < 0)
    {
        Person *temp_person = NULL;
        node->right = tree_remove_recursive(node->right, playlist_size, found, &temp_person);
        if (*found)
        {
            *removed_person = temp_person;
        }
    }
    else
    {
        Person *temp_person = NULL;
        node->left = tree_remove_recursive(node->left, playlist_size, found, &temp_person);
        if (*found)
        {
            *removed_person = temp_person;
        }
    }

    return tree_balance_node(node);
}

int tree_remove(Tree *tree, int playlist_size)
{
    if (tree == NULL) return 2;

    bool found = false;
    Person *removed_person = NULL;
    
    tree->root = tree_remove_recursive(tree->root, playlist_size, &found, &removed_person);

    if (!found) return 1;
    
    tree->elements--;
    return 0;
}

Element *tree_search_recursive(Element *node, int playlist_size, bool *found)
{
    if (node == NULL)
    {
        *found = false;
        return NULL;
    }

    int compair = tree_compare_by_playlist_size(node->person, playlist_size);

    if (compair == 0)
    {
        *found = true;
        return node;
    }

    if (compair < 0)
        return tree_search_recursive(node->right, playlist_size, found);
    else
        return tree_search_recursive(node->left, playlist_size, found);
}

Person *tree_search_by_playlist_size(Tree *tree, int playlist_size)
{
    if (tree == NULL || tree->root == NULL) return NULL;

    bool found = false;
    Element *result = tree_search_recursive(tree->root, playlist_size, &found);
    
    if (found && result)
        return result->person;

    return NULL;
}
