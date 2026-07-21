#include <bits/stdc++.h>

using namespace std;

/*
Sample Input 1
5 3
T4 T1
*/
int main(int argc, char const *argv[])
{
    // Optimize standard I/O operations for competitive programming, kattis
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    unsigned int n, m = 0;
    cin >> n;
    cin >> m;

    std::vector<std::string> T;
    T.reserve(n);

    // We are using 0 based hashmap
    std::unordered_map<std::string, int> token_to_index;

    for (unsigned int i = 0; i < n; i += 1)
    {
        std::string token = "T" + std::to_string(i + 1);
        T.push_back(token);
        token_to_index[token] = i;
    }

    // print out the T array for verifiability
    // for (unsigned int k = 0; k < n; k += 1)
    // {
    // cout << "T[" << k << "] = " << T[k] << "\n";
    // }

    std::string first_token, second_token;
    for (unsigned int j = 0; j < m; j += 1)
    {
        cin >> first_token >> second_token;
        int idx1 = token_to_index[first_token];  // T4 = index 3
        int idx2 = token_to_index[second_token]; // T1 is index 0
        // cout << "idx1 = " << idx1 << " " << "idx2 = " << idx2 << "\n";

        if (idx1 > idx2)
        {
            // we need to swap
            // the range that is affected is (idx2 - idx1)
            // shift the unaffected elements in the range
            unsigned int range = (idx1 - idx2);
            // cout << "range " << range << "\n";
            // we will start with the idx1 (start) index
            for (unsigned int i = 0; i < range; i += 1)
            {
                unsigned current_index = idx2 + i + 1;       // because the T array is 0-based
                token_to_index[T[current_index]] = idx2 + i; // Bubble up
            }
            // Finally, we swap the first index and the second index
            std::string tmp = T[idx2];
            token_to_index[tmp] = idx1;
        }
        // Resort the array T
        for (unsigned int k = 0; k < n; k += 1)
        {
            std::string token = "T" + std::to_string(k + 1);
            unsigned int tmp = token_to_index[token];
            T[tmp] = token;
        }

        // print out the T array for verifiability
        // for (unsigned int k = 0; k < n; k += 1)
        // {
        // cout << "T[" << k << "] = " << T[k] << "\n";
        // }
    }

    for (unsigned int k = 0; k < n; k += 1)
    {
        cout << T[k] << " ";
    }
    cout << "\n";

    return 0;
}
