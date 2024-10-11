#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stack_funcs.h"

static errors_t Recalloc (Stack_t *stack, recalloc_mode_t mode, unsigned int *stk_errors);

errors_t CreateStack(Stack_t **stack_ptr, unsigned int capacity, unsigned int *stk_errors)
{

    if (!stk_errors)
        return STK_ERRORS_NULL_PTR;
    if (!stack_ptr)
    {
        *stk_errors |= STACK_NULL_PTR;
        return STACK_ERROR;
    }

    char *cnr_ptr = (char *) calloc(1, sizeof(Stack_t) + 2 * sizeof(int));
    *stack_ptr = (Stack_t *)(cnr_ptr + sizeof(int));
    *(int *)cnr_ptr = CANARY;
    *(int *)(cnr_ptr + sizeof(Stack_t) + sizeof(int)) = CANARY;

    (*stack_ptr)->data = (stack_elem_t *) calloc(capacity + 2, sizeof(stack_elem_t));
    (*stack_ptr)->data += 1;
    (*stack_ptr)->size = 0;
    (*stack_ptr)->capacity = capacity;
    (*stack_ptr)->data[-1] = (stack_elem_t)CANARY;


    VERIFY_STACK(*stack_ptr, stk_errors);

    return SUCCESS;
}

errors_t StackPush(Stack_t *stack, stack_elem_t pushed_elem, unsigned int *stk_errors)
{
    VERIFY_STACK(stack, stk_errors);

    if (stack->size == stack->capacity)
        Recalloc(stack, INCREASE_CAPACITY, stk_errors);

    stack->data[stack->size] = pushed_elem;
    stack->size++;

    VERIFY_STACK(stack, stk_errors);

    return SUCCESS;
}

errors_t StackPop(Stack_t *stack, stack_elem_t *poped_elem, unsigned int *stk_errors)
{
    if (!poped_elem)
        return NULL_PTR;


    *poped_elem = stack->data[stack->size];
    stack->data[stack->size] = POISON;
    stack->size--;


    if (stack->size < stack->capacity / RECALLOC_COEF)
        Recalloc(stack, DECREASE_CAPACITY, stk_errors);

    VERIFY_STACK(stack, stk_errors);


    return SUCCESS;
}

static errors_t Recalloc(Stack_t *stack,  recalloc_mode_t mode, unsigned int *stk_errors)
{
    VERIFY_STACK(stack, stk_errors);

    switch (mode)
    {
        case INCREASE_CAPACITY :
            stack->data--;
            stack->data = (stack_elem_t *) realloc(
                stack->data, (stack->capacity * RECALLOC_COEF + 2) * sizeof(stack_elem_t));
            stack->data++;

            stack->capacity *= RECALLOC_COEF;



            for (unsigned int i = stack->size; i < stack->capacity; i++)
                stack->data[i] = POISON;

            break;
        case DECREASE_CAPACITY :
            stack->data--;
            stack->data = (stack_elem_t *) realloc(
                stack->data, (stack->capacity / RECALLOC_COEF + 2) * sizeof(stack_elem_t));
            stack->data++;

            stack->capacity /= RECALLOC_COEF;



            break;
        case FREE_DATA :
            free(stack->data);
            stack->size = 0;
            stack->capacity = 0;
            return SUCCESS;
            break;
        default:
            return UNKNOWN_ERROR;
    }

    VERIFY_STACK(stack, stk_errors);

    return SUCCESS;
}

errors_t DestroyStack(Stack_t **stack_ptr, unsigned int *stk_errors)
{
    VERIFY_STACK(*stack_ptr, stk_errors);

    Recalloc(*stack_ptr, FREE_DATA, stk_errors);

    free((int *) *stack_ptr - 1);

    return SUCCESS;
}
