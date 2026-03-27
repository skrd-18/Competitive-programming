// Idea is very simple. Basically, keep adding each integer to the sequence until the sum drops below 0.
// If sum is negative, that should reset the sequence.
#include <iostream>
#include <vector>

class Solution
{
public:
    int maxSubArray(int A[], int n)
    {
        int ans = A[0], i, j, sum = 0;
        for (i = 0; i < n; i++)
        {
            sum += A[i];
            ans = max(sum, ans);
            sum = max(sum, 0);
        }
        return ans;
    }
};

int main(int argc, char const *argv[])
{
    Solution sol;
    return 0;
}
