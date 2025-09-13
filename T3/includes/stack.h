#ifndef _STACK_H
#define _STACK_H

#define STACK_SIZE 100

typedef struct
{
    int top;
    float items[STACK_SIZE];

} Stack;

Stack *stack_create_empty();
bool stack_is_full(Stack *stack);
int stack_push(Stack *stack, float item);
int stack_pop(Stack *stack, float *item);
int stack_peek(Stack *stack, float *item);
bool stack_is_empty(Stack *stack);
void ui_exp_numbers(Stack *stack);
void ui_list(Stack *stack);
#endif
