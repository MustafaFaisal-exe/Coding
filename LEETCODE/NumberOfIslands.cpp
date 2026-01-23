class Solution {
public:
    void checkAdjacent(int x, int y, int row, int col, const vector<vector<char>>& matrix, vector<vector<bool>>& visited, list<int>& lst) {
        if (x < 0 || x >= row || y < 0 || y >= col || visited[x][y] || matrix[x][y] == '0')
            return;

        visited[x][y] = 1;

        lst.push_back(matrix[x][y]);

        checkAdjacent(x + 1, y, row, col, matrix, visited, lst);
        checkAdjacent(x - 1, y, row, col, matrix, visited, lst);
        checkAdjacent(x, y + 1, row, col, matrix, visited, lst);
        checkAdjacent(x, y - 1, row, col, matrix, visited, lst);
    }

    int numIslands(vector<vector<char>>& grid) {
        vector<vector<bool>> visited;
        int row = grid.size();
        int col = grid[0].size();

        for (int i = 0; i < row; i++) {
            vector<bool> tmp(col);

            for (int j = 0; j < col; j++) {
                tmp[j] = false;
            }

            visited.push_back(tmp);
        }

        vector<list<int>> adj;
        int count = 0;

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (!visited[i][j] && grid[i][j] == '1') {
                    ++count;
                    list<int> lst;
                    lst.push_back(grid[i][j]);
                    checkAdjacent(i, j, row, col, grid, visited, lst);
                    visited[i][j] = 1;
                    adj.push_back(lst);
                }
            }
        }

        return count;
    }
};