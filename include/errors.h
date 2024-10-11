#ifndef ERRORS_H
#define ERRORS_H

typedef enum
{
    SUCCESS             = 0,
    FILE_NULL_PTR       = 1,
    STACK_ERROR         = 2,
    STK_ERRORS_NULL_PTR = 3,
    NULL_PTR            = 4,
    UNKNOWN_ERROR       = 5
} errors_t;

#endif
