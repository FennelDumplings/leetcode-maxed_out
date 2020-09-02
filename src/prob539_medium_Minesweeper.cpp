// prob539: Minesweeper

/*
 * https://leetcode-cn.com/problems/minesweeper/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        vector<vector<char>> result = board;
        process(Point(click[0], click[1]), result);
        return result;
    }

private:
    int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
    int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};

    struct Point
    {
        int x, y;
        Point(int x, int y):x(x),y(y){}
    };

    void process(Point p, vector<vector<char>>& result)
    {
        if(result[p.x][p.y] == 'M')
        {
            result[p.x][p.y] = 'X';
            return;
        }

        // board[p.x][p.y] == 'E'
        dfs(p, result);
    }

    void dfs(Point p, vector<vector<char>>& result)
    {
        int n = result.size(), m = result[0].size();

        // result[p.x][p.y] == 'E'
        int cnt = 0;
        for(int d = 0; d < 8; ++d)
        {
            int x = p.x + dx[d];
            int y = p.y + dy[d];
            if(x < 0 || x >= n || y < 0 || y >= m)
                continue;
            if(result[x][y] == 'M')
                ++cnt;
        }
        if(cnt > 0)
        {
            result[p.x][p.y] = '0' + cnt;
            return;
        }
        result[p.x][p.y] = 'B';

        for(int d = 0; d < 8; ++d)
        {
            int x = p.x + dx[d];
            int y = p.y + dy[d];
            if(x < 0 || x >= n || y < 0 || y >= m)
                continue;
            if(result[x][y] == 'E')
                dfs(Point(x, y), result);
        }
    }
};
