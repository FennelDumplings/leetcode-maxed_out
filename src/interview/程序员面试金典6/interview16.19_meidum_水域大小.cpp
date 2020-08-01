// interview16.19: 水域大小

/*
 * https://leetcode-cn.com/problems/pond-sizes-lcci/
 */

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> pondSizes(vector<vector<int>>& land) {
        int n = land.size(), m = land[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        using PII = pair<int, int>;
        queue<PII> q;
        vector<int> result;
        int dx[8] = {0, 0, 1, 1, 1, -1, -1, -1};
        int dy[8] = {1, -1, 1, -1, 0, 1, -1, 0};
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                if(land[i][j] != 0) continue;
                if(visited[i][j]) continue;
                visited[i][j] = true;
                q.push(PII(i, j));
                int cnt = 0;
                while(!q.empty())
                {
                    PII cur = q.front();
                    q.pop();
                    ++cnt;
                    for(int d = 0; d < 8; ++d)
                    {
                        int x = cur.first + dx[d];
                        int y = cur.second + dy[d];
                        if(x >= n || x < 0 || y >= m || y < 0)
                            continue;
                        if(land[x][y] != 0)
                            continue;
                        if(visited[x][y])
                            continue;
                        visited[x][y] = true;
                        q.push(PII(x, y));
                    }
                }
                result.push_back(cnt);
            }
        }
        sort(result.begin(), result.end());
        return result;
    }
};
