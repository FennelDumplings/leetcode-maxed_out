// prob1583: Count Unhappy Friends

/*
 * https://leetcode-cn.com/problems/count-unhappy-friends/
 */


#include <vector>

using namespace std;

class Solution {
public:
    int unhappyFriends(int n, vector<vector<int>>& preferences, vector<vector<int>>& pairs) {
        vector<vector<int>> adj(n, vector<int>(n, -1)); // adj[x][y] := (x, y) 的亲近排名
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n - 1; ++j)
                adj[i][preferences[i][j]] = j;
        }
        vector<bool> unhappy(n, false);

        for(const vector<int>& e1: pairs)
        {
            int x = e1[0], y = e1[1];
            for(const vector<int>& e2: pairs)
            {
                int u = e2[0], v = e2[1];
                if(x == u)
                    continue;
                if(adj[x][u] < adj[x][y] && adj[u][x] < adj[u][v])
                    unhappy[x] = true;
                swap(u, v);
                if(x == u)
                    continue;
                if(adj[x][u] < adj[x][y] && adj[u][x] < adj[u][v])
                    unhappy[x] = true;
            }
            swap(x, y);
            for(const vector<int>& e2: pairs)
            {
                int u = e2[0], v = e2[1];
                if(x == u)
                    continue;
                if(adj[x][u] < adj[x][y] && adj[u][x] < adj[u][v])
                    unhappy[x] = true;
                swap(u, v);
                if(x == u)
                    continue;
                if(adj[x][u] < adj[x][y] && adj[u][x] < adj[u][v])
                    unhappy[x] = true;
            }
        }
        int ans = 0;
        for(bool flag: unhappy)
            if(flag)
                ++ans;
        return ans;
    }
};
