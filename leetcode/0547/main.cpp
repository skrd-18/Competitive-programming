// https://github.com/stevenhalim/cpbook-code/blob/master/ch2/ourown/unionfind_ds.cpp
#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;

class UnionFind
{ // OOP style
private:
    vi p, rank, setSize; // vi p is the key part
    int numSets;

public:
    UnionFind(int N)
    {
        p.assign(N, 0);
        for (int i = 0; i < N; ++i)
            p[i] = i;
        rank.assign(N, 0);    // optional speedup
        setSize.assign(N, 1); // optional feature
        numSets = N;          // optional feature
    }

    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

    int numDisjointSets() { return numSets; }            // optional
    int sizeOfSet(int i) { return setSize[findSet(i)]; } // optional

    void unionSet(int i, int j)
    {
        if (isSameSet(i, j))
            return;                         // i and j are in same set
        int x = findSet(i), y = findSet(j); // find both rep items
        if (rank[x] > rank[y])
            swap(x, y); // keep x 'shorter' than y
        p[x] = y;       // set x under y
        if (rank[x] == rank[y])
            ++rank[y];            // optional speedup
        setSize[y] += setSize[x]; // combine set sizes at y
        --numSets;                // a union reduces numSets
    }
};

class Solution
{
public:
    // This method instantiates and uses UnionFind internally
    // Accept the 2D vector using const& to avoid copying memory
    int findCircleNum(const vector<vector<int>> &isConnected)
    {
        size_t n = isConnected.size();
        UnionFind uf(n);

        for (size_t i = 0; i < n; i += 1)
        {
            for (size_t j = i + 1; j < n; j += 1)
            {
                if (isConnected[i][j] == 1)
                    uf.unionSet(i, j);
            }
        }
        return uf.numDisjointSets();
    }
};

int main(int argc, char const *argv[])
{
    std::vector<std::vector<int>> isConnected = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}};

    // Instantiate the Solution class
    Solution solver;

    // Call the Solution method and capture the output
    int result = solver.findCircleNum(isConnected);

    // Print the final result
    std::cout << "Number of connected components: " << result << std::endl;

    return 0;
}