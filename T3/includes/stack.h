#ifndef _STACK_H
#define _STACK_H

#define LENGTH 100

typedef struct
{
    int top;
    float items[LENGTH];

} Stack;

Stack *stack_create_empty();
Stack *stack_empty(Stack *stack);
bool stack_is_full(Stack *stack);
void stack_push(Stack *stack, float item);
float stack_top_item(Stack *stack);
void stack_pop(Stack *stack);
bool stack_is_empty(Stack *stack);

#endif
