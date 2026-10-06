#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

#define STACK_CAP 10000
typedef struct
{
    int buf[STACK_CAP];
    int top;
} my_stack_t;

static void stack_init(my_stack_t *s)
{
    if (s != NULL)
        s->top = 0;
}

static bool stack_push(my_stack_t *s, int value)
{
    // I need to put an overflow guard
    if (s->top >= STACK_CAP)
        return false;
    s->buf[s->top++] = value;
    return true;
}

static bool stack_pop(my_stack_t *s, int *out)
{
    // I need to put an underflow guard
    if (s->top <= 0) // at this point top needs to be at least 1 to not return false
        return false;
    *out = s->buf[--s->top];
    return true;
}

bool isValid(char *s)
{
    // Note that *s should not be modified, it should be const char *s

    // Early Exit Optimization
    if (strlen(s) % 2 != 0)
        return false;

    my_stack_t st;
    stack_init(&st);
    for (; *s; s++)
    {
        if (*s == '(' || *s == '[' || *s == '{')
        {
            // push to the stack
            if (!stack_push(&st, *s))
                return false;
        }

        if (*s == ')' || *s == ']' || *s == '}')
        {
            int o;
            if (!stack_pop(&st, &o))
                return false;

            if ((*s == ')' && o != '(') || (*s == ']' && o != '[') || (*s == '}' && o != '{'))
            {
                return false;
            }
        }
    }

    return st.top == 0;
}

int main(int argc, char const *argv[])
{

    char *s = "(())";
    printf("result = %d\n", isValid(s));
    return 0;
}
