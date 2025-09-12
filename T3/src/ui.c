#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stack.h>
#include <ui.h>

int ui_get_top_2(Stack *stack, float *top_item1, float *top_item2)
{
    if (stack->top <= 2)
    {
        printf("Not enough elements");
        return 0;
    }

    stack_top_item(stack, top_item1);
    stack_pop(stack);
    stack_top_item(stack, top_item2);
    stack_pop(stack);

    return 1;
}

void ui_push_number(Stack *stack, float number)
{
    stack_push(stack, number);
    return;
}

void ui_sum_numbers(Stack *stack)
{
    float *top_item1, *top_item2;
    if (!(ui_get_top_2(stack, top_item1, top_item2)))
    {
        return;
    }

    float sum = *top_item1 + *top_item2;
    stack_push(stack, sum);

    printf("%f", sum);
}

void ui_subtract_numbers(Stack *stack)
{
    float *top_item1, *top_item2;
    if (!(ui_get_top_2(stack, top_item1, top_item2)))
    {
        return;
    }

    float diff = *top_item1 - *top_item2;
    stack_push(stack, diff);

    printf("%f", diff);
}

void ui_multiply_numbers(Stack *stack)
{
    float *top_item1, *top_item2;
    if (!(ui_get_top_2(stack, top_item1, top_item2)))
    {
        return;
    }

    float mul = (*top_item1) * (*top_item2);
    stack_push(stack, mul);

    printf("%f", mul);
}

void ui_divide_numbers(Stack *stack)
{
    float *top_item1, *top_item2;
    if (!(ui_get_top_2(stack, top_item1, top_item2)))
    {
        return;
    }

    float div = *top_item2 / *top_item1;
    stack_push(stack, div);

    printf("%f", div);
}

void ui_exp_numbers(Stack *stack)
{
    float *top_item1, *top_item2;
    if (!(ui_get_top_2(stack, top_item1, top_item2)))
    {
        return;
    }

    float exp = pow(*top_item2, *top_item1);
    stack_push(stack, exp);

    printf("%f", exp);
}
    
void ui_run()   
{
    bool loop = true;
    char command[INPT_CMD_MAX_LENGTH];

    while (loop)
    {
        scanf("%s", command);
        
        if (strcmp(command, "off") == 0)
        {
            loop = false;
            break;
        }
    }

    return ;
}