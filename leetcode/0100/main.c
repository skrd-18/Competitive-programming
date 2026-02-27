#include "../../header-files/common.h"
#include <stdbool.h>

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool isSameTree(struct TreeNode *p, struct TreeNode *q)
{
    if (p == NULL && q == NULL)
        return true;
    if (p == NULL || q == NULL)
        return false;
    if (p->val != q->val)
        return false;
    return isSameTree(p->right, q->right) && isSameTree(p->left, q->left);
}

int main(int argc, char const *argv[])
{
    // Write driver code here
    struct TreeNode right = {.val = 1, .left = NULL, .right = NULL};
    struct TreeNode *p_right = &right;
    struct TreeNode left = {.val = 1, .left = NULL, .right = NULL};
    struct TreeNode *p_left = &left;
    struct TreeNode p = {.val = 1, .left = p_left, .right = p_right};

    struct TreeNode right_q = {.val = 1, .left = NULL, .right = NULL};
    struct TreeNode *q_right = &right_q;
    struct TreeNode left_q = {.val = 1, .left = NULL, .right = NULL};
    struct TreeNode *q_left = &left_q;
    struct TreeNode q = {.val = 1, .left = q_left, .right = q_right};

    printf("%d\n", isSameTree(&p, &q));

    return 0;
};
