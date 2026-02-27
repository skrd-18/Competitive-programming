import java.util.LinkedList;
import java.util.Queue;

public class Main {
    public static void main(String[] args) {
        char[][] grid = {{'1', '1', '1', '1', '0'}, {'1', '1', '0', '1', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '0', '0', '0'}};
        // Using Flood Fill algorithm
        System.out.println(numIslands(grid));
    }

    public static int numIslands(char[][] grid) {
        int count = 0;

        int m = grid.length, n = grid[0].length;
        boolean[][] visited = new boolean[m][n];
        Queue<int[]> queue = new LinkedList<>();

        for (int i = 0; i < grid.length; ++i)
            for (int j = 0; j < grid[0].length; ++j) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    queue.offer(new int[]{i, j}); // add {0, 0}
                    visited[i][j] = true;

                    bfsFill(grid, queue, visited);
                    // dfsFill(grid,i,j);
                    count += 1;
                }
            }
        return count;
    }


    private static void bfsFill(char[][] grid, Queue<int[]> queue, boolean[][] visited) {
        int m = grid.length; // number of rows
        int n = grid[0].length; // number of columns
        int[][] dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            for (int[] dir : dirs) {
                int x = curr[0] + dir[0];
                int y = curr[1] + dir[1];

                if (x < 0 || x >= m || y < 0 || y >= n || visited[x][y] || grid[x][y] == '0') continue;

                visited[x][y] = true;
                queue.offer(new int[]{x, y});
            }
        }
    }

    public static void dfsFill(char[][] grid, int i, int j) {
        if (i >= 0 && j >= 0 && i < grid.length && j < grid[0].length && grid[i][j] == '1') {
            grid[i][j] = '0';
            dfsFill(grid, i + 1, j);
            dfsFill(grid, i - 1, j);
            dfsFill(grid, i, j + 1);
            dfsFill(grid, i, j - 1);
        }
    }
}