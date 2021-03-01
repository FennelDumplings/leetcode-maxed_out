// prob1284: Minimum Number of Flips to Convert Binary Matrix to Zero Matrix

/*
 * https://leetcode-cn.com/problems/minimum-number-of-flips-to-convert-binary-matrix-to-zero-matrix/
 */

#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

struct State
{
    int s;
    int d;
    State(int s, int d):s(s),d(d){}
};

class Solution {
public:
    int minFlips(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        int board = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(mat[i][j] == 1)
                    board |= 1 << (i * m + j);
            }
        unordered_set<int> visited;
        visited.insert(board);
        queue<State> q;
        q.push(State(board, 0));
        while(!q.empty())
        {
            State cur = q.front();
            q.pop();
            if(cur.s == 0)
                return cur.d;
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < m; ++j)
                {
                    int nxt_s = cur.s;
                    int idx = i * m + j;
                    nxt_s ^= 1 << idx;
                    for(int d = 0; d < 4; ++d)
                    {
                        int adj_i = i + dx[d], adj_j = j + dy[d];
                        if(adj_i < 0 || adj_i >= n || adj_j < 0 || adj_j >= m)
                            continue;
                        int adj_idx = adj_i * m + adj_j;
                        nxt_s ^= 1 << adj_idx;
                    }
                    if(visited.count(nxt_s) > 0)
                        continue;
                    visited.insert(nxt_s);
                    q.push(State(nxt_s, cur.d + 1));
                }
        }
        return -1;
    }

private:
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
};
