#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

#define STACK_CAP 30000

typedef struct
{
    // what should I put as the maximum buffer size?
    // the problems constraints are -2^31 <= val <= 2^31 - 1
    int buf[30000];
    int top;
} MinStack;

MinStack *minStackCreate()
{
    /**
     * the return type is of type MinStack and it is a function returning a pointer to a MinStack*/
    MinStack *ms1 = (MinStack *)malloc(sizeof(MinStack)); // typecast into MinStack pointer
    return ms1;
}

void minStackPush(MinStack *obj, int value)
{
    // I need to put an overflow guard
    if (obj->top >= STACK_CAP)
        return false;
    obj->buf[obj->top++] = value;
    return true;
}

void minStackPop(MinStack *obj)
{
    // I need to put an underflow guard
    if (obj->top <= 0) // at this point top needs to be at least 1 to not return false
        return false;
    obj->buf[--obj->top] = NULL;
    return true;
}

int minStackTop(MinStack *obj)
{
    return obj->top;
}

int minStackGetMin(MinStack *obj)
{
}

void minStackFree(MinStack *obj)
{
    free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, value);

 * minStackPop(obj);

 * int param_3 = minStackTop(obj);

 * int param_4 = minStackGetMin(obj);

 * minStackFree(obj);
*/

int main(int argc, char const *argv[])
{

    return 0;
}
