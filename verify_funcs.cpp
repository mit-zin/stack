#include <assert.h>
#include <stdbool.h>

#include "verify_funcs.h"

errors_t Dump(Stack_t *stack, unsigned int *stk_errors, const char *file_name, int line_num,
              const char *func_name)
{
    FILE *dump_out = fopen(".\\dump.txt", "a");
    if (!dump_out)
        return FILE_NULL_PTR;

    if (!stk_errors)
        fprintf(dump_out, "Stk_errors null ptr\n");
    else
    {
        if (*stk_errors & STACK_NULL_PTR)
            fprintf(dump_out, "Error: stack null pointer.\n");
        if (*stk_errors & DATA_NULL_PTR)
            fprintf(dump_out, "Error: data null pointer.\n");
        if (*stk_errors & SIZE_BIGGER_CAPACITY)
            fprintf(dump_out, "Error: size is bigger than capacity.\n");
        if (*stk_errors & STACK_CANARY_DAMAGED)
            fprintf(dump_out, "Error: stack canary damaged.\n");
        if (*stk_errors & DATA_CANARY_DAMAGED)
            fprintf(dump_out, "Error: data canary damaged.\n");
    }

    fprintf(dump_out, "stack [%#p]\n", stack);
    if (!stack)
        return SUCCESS;

    fprintf(dump_out, "CANARY: %X\n", *((int *)stack - 1));
    fprintf(dump_out, "CANARY: %X\n", *((int *)(stack + 1)));
    fprintf(dump_out, "\tcalled from %s:%d (%s)\n", file_name, line_num, func_name);
    fprintf(dump_out, "\tcapacity = %u\n", stack->capacity);
    fprintf(dump_out, "\tsize = %u\n", stack->size);
    fprintf(dump_out, "\tdata [%#p]\n", stack->data);
    if (stack->data)
    {
        fprintf(dump_out, "\t\tCANARY: %X\n", (int)stack->data[-1]);
        for (unsigned int i = 0; i < stack->capacity; i++)
            fprintf(dump_out, "\t\t[%u] = %f\n", i, stack->data[i]);

    }

    fprintf(dump_out, "\n\n\n");

    fclose(dump_out);

    return SUCCESS;
}

errors_t VerifyStack(Stack_t *stack, unsigned int *stk_errors)
{
    bool flag = true;

    if (!stk_errors)
    {
        flag = false;
        return STK_ERRORS_NULL_PTR;
    }

    if (!stack)
    {
        flag = false;
        *stk_errors |= STACK_NULL_PTR;
    }

    if (!stack->data)
    {
        flag = false;
        *stk_errors |= DATA_NULL_PTR;
    }

    if (stack->capacity < stack->size)
    {
        flag = false;
        *stk_errors |= SIZE_BIGGER_CAPACITY;
    }

    if (stack->data[-1] != CANARY)
    {
        flag = false;
        *stk_errors |= DATA_CANARY_DAMAGED;
    }

    if (stack && (*((int *)stack - 1) != CANARY || *((int *)(stack + 1)) != CANARY))
    {
        flag = false;
        *stk_errors |= STACK_CANARY_DAMAGED;
    }


    if (!flag)
        return STACK_ERROR;
    else
        return SUCCESS;
}
