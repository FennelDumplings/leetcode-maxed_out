// interview12: 矩阵中的路径

/*
 * https://leetcode-cn.com/problems/ju-zhen-zhong-de-lu-jing-lcof/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if(word.empty()) return true;
        int n = board.size(), m = board[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(board[i][j] == word[0])
                {
                    visited[i][j] = true;
                    if(dfs(board, i, j, word, 1, visited))
                        return true;
                    visited[i][j] = false;
                }
        return false;
    }

private:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    bool dfs(const vector<vector<char>>& board, int i, int j, const string& word, int len, vector<vector<bool>>& visited)
    {
        int lw = word.size();
        if(len == lw)
            return true;
        int n = board.size(), m = board[0].size();
        for(int d = 0; d < 4; ++d)
        {
            int x = i + dx[d], y = j + dy[d];
            if(x < 0 || x >= n || y < 0 || y >= m)
                continue;
            if(visited[x][y])
                continue;
            if(board[x][y] != word[len])
                continue;
            visited[x][y] = true;
            if(dfs(board, x, y, word, len + 1, visited))
                return true;
            visited[x][y] = false;
        }
        return false;
    }
};
