#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <set.h>

Set* set_create(int* array, int length)
{
    Set* set = (Set*) malloc(sizeof(Set));
    if (!set) return NULL;

    if (!length)
    {
        set->data = NULL;
        set->length = 0;
        return set;
    }

    int* unique_elements = (int*) malloc(sizeof(int)*length); 
    if(!unique_elements) return NULL;

    int unique_elements_qnt = 0;
    
    for (int i = 0; i < length; i++)
    {
        bool repeated = false;
        for (int j = 0; j < unique_elements_qnt; j++)
        {
            if (array[i] == unique_elements[j])
            {
                repeated = true;
            }
        }

        if (!repeated)
        {
            unique_elements[unique_elements_qnt] = array[i];
            unique_elements_qnt++;
        }
    }

    int* temp = (int*) realloc(unique_elements, sizeof(int)*unique_elements_qnt);
    if(!temp)
    {
        free(unique_elements);
        free(set);
        return NULL;
    } 

    unique_elements = temp;
    set->data = unique_elements;
    set->length = unique_elements_qnt;
    
    return set;
}

void set_destroy(Set* set)
{
    free(set->data);
    free(set);
    return;
}

void set_print(Set* set)
{
    for (int i = 0; i < set->length; i++)
    {
        printf("%d ", set->data[i]);
    }
    printf("\n");
    
    return ;
}

Set* set_union(Set* setA, Set* setB)
{
    int total_data_size = setA->length + setB->length;

    if (total_data_size == 0)
    {
        return set_create(NULL, 0);
    }

    int* total_data = (int*) malloc(sizeof(int)*total_data_size);
    if (!total_data) return NULL;

    int pos = 0;
    for (int i = 0; i < setA->length; i++)
    {
        total_data[pos] = setA->data[i];
        pos++;
    }
    for (int i = 0; i < setB->length; i++)
    {
        total_data[pos] = setB->data[i];
        pos++;    

    }

    Set* set_union = set_create(total_data, pos);
    free(total_data);
    return set_union;
}


Set* set_intersect(Set* setA, Set* setB)
{
    int total_data_size = setA->length + setB->length;

    if (total_data_size == 0)
    {
        return set_create(NULL, 0);
    }

    int* total_data = (int*) malloc(sizeof(int)*total_data_size);
    if (!total_data) return NULL;

    int pos = 0;
    for (int i = 0; i < setA->length; i++)
    {
        for (int j = 0; j < setB->length; j++)
        {
            if(setA->data[i] == setB->data[j])
            {
                total_data[pos] = setA->data[i];
                pos++;
            }
        }
    }

    Set* set_intersect = set_create(total_data, pos);
    free(total_data);
    return set_intersect;
}


Set* set_difference(Set* setA, Set* setB)
{
    int total_data_size = setA->length + setB->length;

    if (total_data_size == 0)
    {
        return set_create(NULL, 0);
    }

    int* total_data = (int*) malloc(sizeof(int)*total_data_size);
    if (!total_data) return NULL;

    int pos = 0;
    for (int i = 0; i < setA->length; i++)
    {
        bool is_on_b = false;
        for (int j = 0; j < setB->length; j++)
        {
            if(setA->data[i] == setB->data[j])
            {
                is_on_b = true;
                break;
            }
        }
        if(!is_on_b){
            total_data[pos] = setA->data[i];
            pos++;
        }
    }

    Set* set_difference = set_create(total_data, pos);
    free(total_data);
    return set_difference;
}

bool set_has(Set* set, int x)
{
    for (int i =0; i<set->length; i++)
    {
        if (set->data[i] == x)
        {
            return true;
        }
    }
    return false;
}
