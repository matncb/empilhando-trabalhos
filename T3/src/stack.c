#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stack.h>

Stack *stack_create_empty()
{
    Stack *stack = (Stack*) malloc(sizeof(Stack));
    if (!stack) return NULL;

    stack->top = 0;
    
    return stack;
} 

Stack *stack_empty(Stack *stack)
{
    free(stack);
    return stack_create_empty();
} 

bool stack_is_full(Stack *stack)
{
    if (stack->top == LENGTH) return true;
    return false;
}

bool stack_is_empty(Stack *stack)
{
    if (!stack->top) return true;
    return false;
} 

void stack_push(Stack *stack, float item)
{
    if (stack_is_full(stack))
    {
        printf("Stack is full");
        return;
    }
    
    stack->items[stack->top] = item;
    stack->top++;
    return ;
}

void stack_pop(Stack *stack)
{
    if (stack_is_empty(stack))
    {
        printf("Stack is empty");
        return;
    }
    stack->top--;
}

int stack_top_item(Stack *stack, float* top_item)
{
    if (stack_is_empty(stack))
    {
        printf("Stack is empty");
        return 0;
    }
    
    *top_item =  stack->items[stack->top -1];  
    return 1;  
}