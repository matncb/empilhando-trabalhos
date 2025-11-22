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

} Element;

typedef struct Tree
{
    struct Element *root;
    int elements;
} Tree;

int get_playlist_size(Person *person)
{
    if (!person) return 0;
    PlayList *pl = (PlayList *)person_get_playlist(person);
    if (!pl) return 0;
    return playlist_get_elements(pl);
}

static void tree_element_free(Element *aux)
{
    if (aux == NULL) return;
    // Não libera person aqui, pois pode ser compartilhado com poplist
    // A liberação será feita pela poplist
    free(aux);
    return;
}

Element *element_create(Person *person)
{
    if (!person) return NULL;
    Element *aux = (Element*) malloc(sizeof(Element));
    if (!aux) return NULL;

    aux->person = person;

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


void tree_node_search_by_playlist_size_recursive(Element *node, int size, Element **out_element, bool *found, Element **parent)
{
    int node_size = get_playlist_size(node->person);
    
    if(node_size == size){
        *out_element = node;
        *found = true;
        return;
    }

    if(node_size < size)
    {
        if (node->right == NULL)
        {
            *out_element = node;
            *found = false;
            return;
        }
        *parent = node;
        return tree_node_search_by_playlist_size_recursive(node->right, size, out_element, found, parent);
    }

    if (node->left == NULL)
    {
        *out_element = node;
        *found = false;
        return;
    }
    *parent = node;
    return tree_node_search_by_playlist_size_recursive(node->left, size, out_element, found, parent);
}

Element *tree_search_by_playlist_size(Tree *tree, int size, bool *found, Element **parent)
{
    if (tree == NULL || tree->root == NULL) return NULL;

    Element *out_element = NULL;
    tree_node_search_by_playlist_size_recursive(tree->root, size, &out_element, found, parent);
    return out_element;
}

Person *tree_search_by_playlist_size_pure(Tree *tree, int playlist_size) 
{
    if (tree == NULL || tree -> root == NULL) return NULL;
    bool found = false;
    Element *out_element = NULL;
    Element *parent = NULL;
    tree_node_search_by_playlist_size_recursive(tree->root, playlist_size, &out_element, &found, &parent);
    if (found)
        return out_element->person;

    return NULL;
}

int tree_add(Tree *tree, Person *person)
{
    if (tree == NULL) return 2;

    int person_size = get_playlist_size(person);
    bool found = false;
    Element *parent = NULL;

    Element *search = tree_search_by_playlist_size(tree, person_size, &found, &parent);
    if (found) return 1; // Já existe pessoa com mesmo tamanho de playlist

   
    Element *node = element_create(person);
    if (!node) return 2;

    if (search == NULL)
    {
        tree->root = node;
        tree->elements++;
        return 0;
    }

    int search_size = get_playlist_size(search->person);

    if (person_size < search_size)
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

        tree_element_free(search);
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

        tree_element_free(search);
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

        tree_element_free(search);
        tree->elements--;
        return 0;
    }

    return 1;
}

int tree_remove(Tree *tree, int playlist_size)
{
    if (tree == NULL) return 2;

    bool found = false;
    Element *parent = NULL;

    Element *search = tree_search_by_playlist_size(tree, playlist_size, &found, &parent);
    if (!found) return 1;

    if (!tree_remove_node(tree,search, parent)) return 0;
    
    Element *new_root_parent = search;
    Element *new_root = NULL;

    tree_node_search_max_recursive(search->left, &new_root, &new_root_parent);

    Person *aux = search->person;
    search->person = new_root->person;
    new_root->person = aux;

    if (!tree_remove_node(tree, new_root, new_root_parent)) return 0;

    return 1;
 
}

