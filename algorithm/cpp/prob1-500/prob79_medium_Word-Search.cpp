// prob79: Word Search

/*
 * Given a 2D board and a word, find if the word exists in the grid.
 * The word can be constructed from letters of sequentially adjacent cell,
 * where "adjacent" cells are those horizontally or vertically neighboring.
 * The same letter cell may not be used more than once.
 */

/*
 *Example:
 * board =
 * [
 *   ['A','B','C','E'],
 *   ['S','F','C','S'],
 *   ['A','D','E','E']
 * ]
 * Given word = "ABCCED", return true.
 * Given word = "SEE", return true.
 * Given word = "ABCB", return false.
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if(word.empty()) return true;
        if(board.empty()) return false;
        int n = board.size();
        int m = board[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(board[i][j] == word[0] && dfs(board, i, j, 0, visited, word))
                    return true;
        return false;
    }

private:
    bool dfs(const vector<vector<char> >& board, int x, int y, int w, vector<vector<bool> >& visited, const string& word)
    {
        // w:已经匹配到的字符数
        int nw = word.size();

        int n = board.size();
        int m = board[0].size();

        char cur = word[w];

        // 右，下，左，上
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};

        if(board[x][y] == cur)
        {
            if(w + 1 == nw) return true;
            visited[x][y] = true;
            for(int d = 0; d < 4; ++d)
            {
                if(x + dx[d] >= 0 && x + dx[d] < n && y + dy[d] >= 0 && y + dy[d] < m && !visited[x + dx[d]][y + dy[d]])
                {
                    if(dfs(board, x + dx[d], y + dy[d], w + 1, visited, word))
                        return true;
                }
            }
            visited[x][y] = false;
            return false;
        }
        else
            return false;
    }
};
