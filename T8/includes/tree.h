#ifndef _LIST_H
#define _LIST_H

#include <data.h>

typedef struct Tree Tree;
typedef struct Element Element;

typedef enum PathType
{
    PATH_INORDER,
    PATH_PREORDER,
    PATH_POSORDER
} PathType;

void element_free(Element *aux);
Element *element_create(Data *data);
Tree *tree_create();
void tree_free_recursive(Element *elem);
void tree_free(Tree *tree);
int tree_get_elements(Tree *tree);
void tree_preorder_recursive(Element *elem, Data **list, int *pos);
void tree_inorder_recursive(Element *elem, Data **list, int *pos);
void tree_posorder_recursive(Element *elem, Data **list, int *pos);
Data **tree_list(Tree *tree, PathType path);
void tree_node_search_by_code_recursive(Element *node, int code, Element **out_element, bool *found, Element **parent);
Element *tree_search_by_code(Tree *tree, int code, bool *found, Element **parent);
int tree_add(Tree *tree, Data *data);
void tree_node_search_max_recursive(Element *node, Element **out_element, Element **parent);
int tree_remove(Tree *tree, int code);
Data *tree_search_by_code_pure(Tree *tree, int code);

#endif
