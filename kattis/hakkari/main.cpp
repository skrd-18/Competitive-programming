#include <iostream>
#include <vector>
#include <sys/types.h>
#include <string>
#include <algorithm>
#include <utility>
using namespace std;

int main(int argc, char const *argv[])
{
    int n, m, number_of_mines = 0;
    cin >> n >> m;
    vector<pair<int, int>> coords;
    vector<string> grid;

    string line;
    // 2. IMPORTANT: Clear the newline character left in the buffer by 'cin >>'
    // Otherwise, the first getline() will read an empty string.

    // 3. Read each row of the grid
    for (int i = 0; i < n; ++i)
    {
        cin >> line;
        grid.push_back(line);
    }

    for (int r = 0; r < n; r += 1)
    {
        for (int c = 0; c < m; c += 1)
        {
            if (grid[r][c] == '*')
            {
                number_of_mines += 1;
                coords.emplace_back(r + 1, c + 1);
            }
        }
    }
    cout << number_of_mines << endl;
    for (auto p : coords)
    {
        cout << p.first << " " << p.second << endl;
    }
    return 0;
}