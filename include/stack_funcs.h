#ifndef STACK_FUNCS_H
#define STACK_FUNCS_H

#include "errors.h"
#include "stack.h"
#include "verify_funcs.h"

const int RECALLOC_COEF = 2;

typedef enum
{
    DECREASE_CAPACITY = -1,
    FREE_DATA         = 0,
    INCREASE_CAPACITY = 1
} recalloc_mode_t;

errors_t CreateStack (Stack_t **stack, unsigned int capacity, unsigned int *stk_errors);
errors_t StackPop    (Stack_t *stack, stack_elem_t *poped_elem, unsigned int *stk_errors);
errors_t StackPush   (Stack_t *stack, stack_elem_t pushed_elem, unsigned int *stk_errors);
errors_t DestroyStack(Stack_t **stack_ptr, unsigned int *stk_errors);


#endif
