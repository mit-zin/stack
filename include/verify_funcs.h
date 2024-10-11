#ifndef VERIFY_FUNCS_H
#define VERIFY_FUNCS_H

#include "errors.h"
#include "stack.h"


const int CANARY = (stack_elem_t) 0XB00B5;

typedef enum
{
    STACK_NULL_PTR       = 1,
    DATA_NULL_PTR        = 2,
    SIZE_BIGGER_CAPACITY = 4,
    STACK_CANARY_DAMAGED = 8,
    DATA_CANARY_DAMAGED  = 16
} stack_errors_t;

errors_t VerifyStack(Stack_t *stack, unsigned int *stk_errors);
errors_t Dump(Stack_t *stack, unsigned int *stk_errors, const char * file_name, int line_num,
          const char * func_name);

#define DUMP(STACK, STK_ERRORS) Dump(STACK, STK_ERRORS, __FILE__, __LINE__, __func__)

#define VERIFY_STACK(STACK, STK_ERRORS) do               \
    {                                                    \
        errors_t res = VerifyStack(STACK, STK_ERRORS);   \
        if (res)                                         \
        {                                                \
            if (DUMP(STACK, STK_ERRORS))                 \
                printf("Error: dump file null pointer.");\
            assert(0);                                   \
        }                                                \
    } while(0)

#endif

