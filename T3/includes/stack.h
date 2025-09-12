#ifndef _STACK_H
#define _STACK_H

#define STACK_SIZE 100

#define STACK_IS_EMPTY -1

typedef struct
{
    int top;
    float items[STACK_SIZE];

} Stack;

Stack *stack_create_empty();
Stack *stack_empty(Stack *stack);
bool stack_is_full(Stack *stack);
void stack_push(Stack *stack, float item);
int stack_top_item(Stack *stack, float *top_item);
float stack_pop(Stack *stack);
bool stack_is_empty(Stack *stack);
float stack_peek(Stack *stack);
int stack_top(Stack *stack);
void ui_exp_numbers(Stack *stack);
void ui_list(Stack *stack);
#endif
