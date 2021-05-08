// prob130: Surrounded Regions

/*
 * Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.
 * A region is captured by flipping all 'O's into 'X's in that surrounded region.
 */

/*
 * Example:
 * X X X X
 * X O O X
 * X X O X
 * X O X X
 * After running your function, the board should be:
 * X X X X
 * X X X X
 * X X X X
 * X O X X
 */

/*
 * Explanation:
 * Surrounded regions shouldn’t be on the border, which means that any 'O' on the border of
 * the board are not flipped to 'X'. Any 'O' that is not on the border and it is not connected to an 'O' on
 * the border will be flipped to 'X'. Two cells are connected if they are adjacent cells connected horizontally or vertically.
 */

#include <vector>
#include <queue>

using namespace std;

// 从外往里 BFS
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if(board.empty()) return;
        int n = board.size(), m = board[0].size();
        if(n <= 2 || m <= 2) return;
        queue<pair<int, int>> q;
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        for(int j = 0; j < m; ++j)
        {
            if(board[0][j] == 'O')
            {
                q.push(pair<int, int>(0, j));
                board[0][j] = '.';
            }
            if(board[n - 1][j] == 'O')
            {
                q.push(pair<int, int>(n - 1, j));
                board[n - 1][j] = '.';
            }
        }
        for(int i = 1; i < n - 1; ++i)
        {
            if(board[i][0] == 'O')
            {
                q.push(pair<int, int>(i, 0));
                board[i][0] = '.';
            }
            if(board[i][m - 1] == 'O')
            {
                q.push(pair<int, int>(i, m - 1));
                board[i][m - 1] = '.';
            }
        }
        while(!q.empty())
        {
            pair<int, int> cur = q.front();
            q.pop();
            for(int d = 0; d < 4; ++d)
            {
                if(_check(cur.first + dx[d], cur.second + dy[d], board))
                {
                    q.push(pair<int, int>(cur.first + dx[d], cur.second + dy[d]));
                    board[cur.first + dx[d]][cur.second + dy[d]] = '.';
                }
            }
        }
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(board[i][j] == 'O')
                    board[i][j] = 'X';
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(board[i][j] == '.')
                    board[i][j] = 'O';
    }

private:
    bool _check(int i, int j, const vector<vector<char> >& board) const
    {
        int n = board.size(), m = board[0].size();
        if(i < 0 || i >= n || j < 0 || j >= m)
            return false;
        if(board[i][j] != 'O')
            return false;
        return true;
    }
};

// 线性推进，DFS
class Solution_2 {
public:
    void solve(vector<vector<char>>& board) {
        if(board.empty()) return;
        int n = board.size(), m = board[0].size();
        if(n <= 2 || m <= 2) return;
        vector<vector<bool> > visited(n, vector<bool>(m, false));
        vector<pair<int, int> > dfs_path;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(board[i][j] == 'O' && !visited[i][j])
                {
                    dfs_path.clear();
                    if(!dfs(board, i, j, dfs_path, visited))
                    {
                        for(pair<int, int> dfs_point: dfs_path)
                            board[dfs_point.first][dfs_point.second] = 'X';
                    }
                }
            }
    }

private:
    bool dfs(vector<vector<char>>& board, int i, int j, vector<pair<int, int> >& dfs_path, vector<vector<bool> >& visited)
    {
        if(_out_of_range(i, j, board))
            return true;

        if(board[i][j] != 'O' || visited[i][j])
            return false;

        visited[i][j] = true;
        dfs_path.push_back(pair<int, int>(i, j));

        bool flag = false;
        flag ||= dfs(board, i + 1, j, dfs_path, visited);
        flag ||= dfs(board, i - 1, j, dfs_path, visited);
        flag ||= dfs(board, i, j + 1, dfs_path, visited);
        flag ||= dfs(board, i, j - 1, dfs_path, visited);
        return flag;
    }

    bool _out_of_range(int i, int j, const vector<vector<char> >& board) const
    {
        int n = board.size(), m = board[0].size();
        if(i < 0 || i >= n || j < 0 || j >= m)
            return true;
        return false;
    }
};
