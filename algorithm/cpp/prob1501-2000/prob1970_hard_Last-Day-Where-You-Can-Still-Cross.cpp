#include <vector>

using namespace std;

class Solution {
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        int n = row * col;
        int left = 1, right = n;
        while(left < right)
        {
            int mid = (left + right + 1) / 2;
            if(check(row, col, cells, mid))
                left = mid;
            else
                right = mid - 1;
        }
        return left;
    }

private:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    bool check(const int row, const int col, const vector<vector<int>>& cells, int mid)
    {
        vector<vector<int>> matrix(row, vector<int>(col, 0));
        for(int i = 0; i < mid; ++i)
        {
            matrix[cells[i][0] - 1][cells[i][1] - 1] = 1;
        }
        vector<vector<bool>> visited(row, vector<bool>(col, false));
        for(int j = 0; j < col; ++j)
        {
            if(visited[0][j])
                continue;
            if(matrix[0][j] == 1)
                continue;
            visited[0][j] = true;
            if(dfs(matrix, visited, 0, j, row, col))
                return true;
        }
        return false;
    }

    bool dfs(const vector<vector<int>>& matrix, vector<vector<bool>>& visited, int i, int j, const int row, const int col)
    {
        if(i == row - 1)
            return true;
        for(int d = 0; d < 4; ++d)
        {
            int x = i + dx[d];
            int y = j + dy[d];
            if(x < 0 || x >= row || y < 0 || y >= col)
                continue;
            if(visited[x][y])
                continue;
            visited[x][y] = true;
            if(matrix[x][y] == 1)
                continue;
            if(dfs(matrix, visited, x, y, row, col))
                return true;
        }
        return false;
    }
};
