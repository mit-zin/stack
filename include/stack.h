#ifndef STACK_T_H
#define STACK_T_H

#include <stdio.h>

typedef double stack_elem_t;

const stack_elem_t POISON = (stack_elem_t) 0XB0B15DEAD;

typedef struct
{
    stack_elem_t* data;
    unsigned int size, capacity;
} Stack_t;

#endif
