#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stack.h>

typedef struct Stack
{
    int top;
    float items[STACK_SIZE];

} Stack;

Stack *stack_create_empty()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (!stack)
        return NULL;

    stack->top = 0;

    return stack;
}

bool stack_is_full(Stack *stack)
{
    return stack->top == STACK_SIZE;
}

bool stack_is_empty(Stack *stack)
{
    return !stack->top;
}

int stack_push(Stack *stack, float item)
{
    if (stack_is_full(stack))
    {
        printf("Stack is full \n");
        return 1;
    }

    stack->items[stack->top] = item;
    stack->top++;
    return 0;
}

int stack_pop(Stack *stack, float *item)
{
    if (stack_is_empty(stack))
    {
        printf("Stack is empty \n");
        return 1;
    }
    stack->top--;

    *item = stack->items[stack->top];
    return 0;
}

int stack_peek(Stack *stack, float *item)
{
    if (stack_is_empty(stack))
    {
        printf("Stack is empty \n");
        return 1;
    }

    *item = stack->items[stack->top - 1];
    return 0;
}

int stack_size(Stack *stack)
{
    return stack->top;
}