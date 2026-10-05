#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *countBits(int n, int *returnSize)
{
    int *ptr = (int *)malloc((n + 1) * sizeof(int));
    if (ptr == NULL)
    {
        *returnSize = 0;
        return NULL;
    }
    ptr[0] = 0;
    for (size_t i = 1; i <= n; i += 1)
    {
        ptr[i] = ptr[i >> 1] + (i & 1);
    }
    *returnSize = n + 1;
    return ptr;
}

int main(int argc, char const *argv[])
{
    int returnSize = 0;
    size_t n = 10;
    int *result = countBits(n, &returnSize);
    for (size_t i = 0; i <= n; i += 1)
    {
        printf("i(%d) : %d\n", i, result[i]);
    }
    free(result);
    return 0;
}
