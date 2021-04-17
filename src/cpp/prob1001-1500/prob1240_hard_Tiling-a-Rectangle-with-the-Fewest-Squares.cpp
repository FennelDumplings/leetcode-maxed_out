// prob1240: Tiling a Rectangle with the Fewest Squares

/*
 * https://leetcode-cn.com/problems/tiling-a-rectangle-with-the-fewest-squares/
 */

#include <vector>

using namespace std;

// 基础搜索
// 6 * 7 528ms
class Solution1 {
public:
    int tilingRectangle(int n, int m) {
        board = vector<vector<bool>>(n, vector<bool>(m, false));
        int ans = n * m;
        dfs(0, ans);
        return ans;
    }

private:
    vector<vector<bool>> board;

    void dfs(int cnt, int& ans)
    {
        int x = -2, y = -2;
        if(check(x, y))
        {
            ans = min(ans, cnt);
            return;
        }
        int n = board.size(), m = board[0].size();
        int len = 1;
        while(check(x, y, n, m, len))
        {
            set(x, y, len);
            dfs(cnt + 1, ans);
            reset(x, y, len);
            ++len;
        }
    }

    void reset(int i, int j, int len)
    {
        for(int x = i; x < i + len; ++x)
            for(int y = j; y < j + len; ++y)
                board[x][y] = false;
    }

    void set(int i, int j, int len)
    {
        for(int x = i; x < i + len; ++x)
            for(int y = j; y < j + len; ++y)
                board[x][y] = true;
    }

    bool check(int i, int j, int n, int m, int len)
    {
        if(i + len > n || j + len > m)
            return false;
        for(int x = i; x < i + len; ++x)
            for(int y = j; y < j + len; ++y)
            {
                if(board[x][y])
                    return false;
            }
        return true;
    }

    bool check(int& x, int& y)
    {
        int n = board.size(), m = board[0].size();
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(!board[i][j])
                {
                    x = i;
                    y = j;
                    return false;
                }
        return true;
    }
};


// 最优性剪枝
// 12 * 13  1360ms
class Solution2 {
public:
    int tilingRectangle(int n, int m) {
        board = vector<vector<bool>>(n, vector<bool>(m, false));
        int ans = n * m;
        dfs(0, ans);
        return ans;
    }

private:
    vector<vector<bool>> board;

    void dfs(int cnt, int& ans)
    {
        if(cnt >= ans)
            return;
        int x = -2, y = -2;
        if(check(x, y))
        {
            ans = min(ans, cnt);
            return;
        }
        int n = board.size(), m = board[0].size();
        int len = 1;
        while(check(x, y, n, m, len))
        {
            set(x, y, len);
            dfs(cnt + 1, ans);
            reset(x, y, len);
            ++len;
        }
    }

    void reset(int i, int j, int len)
    {
        for(int x = i; x < i + len; ++x)
            for(int y = j; y < j + len; ++y)
                board[x][y] = false;
    }

    void set(int i, int j, int len)
    {
        for(int x = i; x < i + len; ++x)
            for(int y = j; y < j + len; ++y)
                board[x][y] = true;
    }

    bool check(int i, int j, int n, int m, int len)
    {
        if(i + len > n || j + len > m)
            return false;
        for(int x = i; x < i + len; ++x)
            for(int y = j; y < j + len; ++y)
            {
                if(board[x][y])
                    return false;
            }
        return true;
    }

    bool check(int& x, int& y)
    {
        int n = board.size(), m = board[0].size();
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(!board[i][j])
                {
                    x = i;
                    y = j;
                    return false;
                }
        return true;
    }
};

// 搜索顺序
// 8 * 8  900ms
class Solution3 {
public:
    int tilingRectangle(int n, int m) {
        board = vector<vector<bool>>(n, vector<bool>(m, false));
        int ans = n * m;
        dfs(0, ans);
        return ans;
    }

private:
    vector<vector<bool>> board;

    void dfs(int cnt, int& ans)
    {
        int x = -2, y = -2;
        if(check(x, y))
        {
            ans = min(ans, cnt);
            return;
        }
        int n = board.size(), m = board[0].size();
        int len = min(n - x, m - y);
        while(len >= 1 && check(x, y, n, m, len))
        {
            set(x, y, len);
            dfs(cnt + 1, ans);
            reset(x, y, len);
            --len;
        }
    }

    void reset(int i, int j, int len)
    {
        for(int x = i; x < i + len; ++x)
            for(int y = j; y < j + len; ++y)
                board[x][y] = false;
    }

    void set(int i, int j, int len)
    {
        for(int x = i; x < i + len; ++x)
            for(int y = j; y < j + len; ++y)
                board[x][y] = true;
    }

    bool check(int i, int j, int n, int m, int len)
    {
        if(i + len > n || j + len > m)
            return false;
        for(int x = i; x < i + len; ++x)
            for(int y = j; y < j + len; ++y)
            {
                if(board[x][y])
                    return false;
            }
        return true;
    }

    bool check(int& x, int& y)
    {
        int n = board.size(), m = board[0].size();
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(!board[i][j])
                {
                    x = i;
                    y = j;
                    return false;
                }
        return true;
    }
};


// 最优性剪枝 + 搜索顺序
// 17 * 23  1776ms
class Solution {
public:
    int tilingRectangle(int n, int m) {
        board = vector<vector<bool>>(n, vector<bool>(m, false));
        int ans = n * m;
        dfs(0, ans);
        return ans;
    }

private:
    vector<vector<bool>> board;

    void dfs(int cnt, int& ans)
    {
        if(cnt >= ans)
            return;
        int x = -2, y = -2;
        if(check(x, y))
        {
            ans = min(ans, cnt);
            return;
        }
        int n = board.size(), m = board[0].size();
        int len = min(n - x, m - y);
        while(len >= 1 && check(x, y, n, m, len))
        {
            set(x, y, len);
            dfs(cnt + 1, ans);
            reset(x, y, len);
            --len;
        }
    }

    void reset(int i, int j, int len)
    {
        for(int x = i; x < i + len; ++x)
            for(int y = j; y < j + len; ++y)
                board[x][y] = false;
    }

    void set(int i, int j, int len)
    {
        for(int x = i; x < i + len; ++x)
            for(int y = j; y < j + len; ++y)
                board[x][y] = true;
    }

    bool check(int i, int j, int n, int m, int len)
    {
        if(i + len > n || j + len > m)
            return false;
        for(int x = i; x < i + len; ++x)
            for(int y = j; y < j + len; ++y)
            {
                if(board[x][y])
                    return false;
            }
        return true;
    }

    bool check(int& x, int& y)
    {
        int n = board.size(), m = board[0].size();
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(!board[i][j])
                {
                    x = i;
                    y = j;
                    return false;
                }
        return true;
    }
};
