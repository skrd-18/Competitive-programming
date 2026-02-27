#include <iostream>
#include <vector>
#include <queue>

int main() {
    class Solution {
    public:
        int numIslands(std::vector<std::vector<char>> &grid) {
            if (grid.empty() || grid[0].empty()) {
                return 0;
            }
            int height = grid.size();
            int width = grid[0].size();
            int answer = 0;

            int visited[height + 1][width + 1];

            auto inside = [&](int row, int column) {
                return (0 <= row && row < height) && (0 <= column && column < width);
            };

            std::vector<std::pair<int, int>>
                    directions{{1,  0},
                               {-1, 0},
                               {0,  1},
                               {0,  -1}};

            for (int row = 0; row < height; ++row) {
                for (int column = 0; column < width; ++column) {
                    if (!visited[row][column] && grid[row][column] == '1') {
                        // perform BFS
                        answer += 1;
                        std::queue<std::pair<int, int>> q;
                        q.push({row, column});
                        visited[row][column] = true;

                        while (!q.empty()) {
                            std::pair<int, int> p = q.front();
                            q.pop();
                            // p.first, p.second
                            // check thy neighbours
                            for (std::pair<int, int> direc: directions) {
                                int new_row = p.first + direc.first;
                                int new_column = p.second + direc.second;

                                if (inside(new_row, new_column) && !visited[new_row][new_column] &&
                                    grid[new_row][new_column] == '1') {
                                    q.push({new_row, new_column});
                                    visited[new_row][new_column] = true;

                                }
                            }
                        }

                    }
                }
            }
            return answer;
        };
    };

    // create a solution object
    Solution solution;
    std::vector<std::vector<char>> grid = {{'1', '1', '1', '1', '0'},
                                           {'1', '1', '0', '1', '0'},
                                           {'1', '1', '0', '0', '0'},
                                           {'0', '0', '0', '0', '0'}};
    int print_value = solution.numIslands(grid);
    std::cout << print_value << std::endl;

    return 0;
}