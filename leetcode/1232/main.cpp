#include <iterator>
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    bool checkStraightLine(vector<vector<int>> &coordinates)
    {
        int dx = coordinates[1][0] - coordinates[0][0];
        int dy = coordinates[1][1] - coordinates[0][1];

        for (int i = 1; i < coordinates.size() - 1; i++) // bounds is correct
        {
            int next_dx = coordinates[i + 1][0] - coordinates[i][0];
            int next_dy = coordinates[i + 1][1] - coordinates[i][1];

            // Cross-multiply to avoid division by zero and truncation
            if (dy * next_dx != next_dy * dx)
            {
                return false;
            }
        }
        return true;
    }
};

int main(int argc, char const *argv[])
{
    Solution sol;
    vector<vector<int>> coordinates = {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}};

    cout << "Answer: " << sol.checkStraightLine(coordinates) << endl;
    return 0;
}
