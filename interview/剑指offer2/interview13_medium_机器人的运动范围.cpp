// interview13: 机器人的运动范围

/*
 * https://leetcode-cn.com/problems/ji-qi-ren-de-yun-dong-fan-wei-lcof/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int movingCount(int m, int n, int k) {
        // 1 <= n,m <= 100
        // 0 <= k <= 20
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int result = 0;
        visited[0][0] = true;
        dfs(0, 0, visited, result, k);
        return result;
    }

private:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    void dfs(int i, int j, vector<vector<bool>>& visited, int& result, int k)
    {
        ++result;
        int m = visited.size(), n = visited[0].size();
        for(int d = 0; d < 4; ++d)
        {
            int x = i + dx[d], y = j + dy[d];
            if(x < 0 || x >= m || y < 0 || y >= n)
                continue;
            if(visited[x][y])
                continue;
            if(!check(x, y, k))
                continue;
            visited[x][y] = true;
            dfs(x, y, visited, result, k);
        }
    }

    bool check(int x, int y, int k)
    {
        int ans = 0;
        while(x)
        {
            ans += x % 10;
            if(ans > k)
                return false;
            x /= 10;
        }
        while(y)
        {
            ans += y % 10;
            if(ans > k)
                return false;
            y /= 10;
        }
        return true;
    }
};
