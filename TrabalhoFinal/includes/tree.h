#ifndef _TREE_H
#define _TREE_H

#include <person.h>

typedef struct Tree Tree;
typedef struct Element Element;

typedef enum PathType
{
    PATH_INORDER,
    PATH_PREORDER,
    PATH_POSORDER
} PathType;

Element *element_create(Person *person);
Tree *tree_create();
void tree_free_recursive(Element *elem);
void tree_free(Tree *tree);
int tree_get_elements(Tree *tree);
void tree_preorder_recursive(Element *elem, Person **list, int *pos);
void tree_inorder_recursive(Element *elem, Person **list, int *pos);
void tree_posorder_recursive(Element *elem, Person **list, int *pos);
Person **tree_list(Tree *tree, PathType path);
void tree_node_search_by_playlist_size_recursive(Element *node, int size, Element **out_element, bool *found, Element **parent);
Element *tree_search_by_playlist_size(Tree *tree, int size, bool *found, Element **parent);
int tree_add(Tree *tree, Person *person);
void tree_node_search_max_recursive(Element *node, Element **out_element, Element **parent);
int tree_remove(Tree *tree, int playlist_size);
Person *tree_search_by_playlist_size_pure(Tree *tree, int playlist_size);
int tree_remove_node(Tree *tree, Element *search, Element *parent);
int get_playlist_size(Person *person);

#endif

