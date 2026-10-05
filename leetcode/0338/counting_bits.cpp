#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> countBits(int n)
    {
        /*
        0
        1
        2
        3
        4
        ...
        n
        */
        vector<int> output(n + 1);
        for (int i = 0; i < n + 1; i += 1)
        {
            uint32_t value = (uint32_t)i;
            size_t count = 0;
            while (value != 0)
            {
                value = value & (value - 1);
                count += 1;
            }
            output[i] = count;
        }
        return output;
    }
};
