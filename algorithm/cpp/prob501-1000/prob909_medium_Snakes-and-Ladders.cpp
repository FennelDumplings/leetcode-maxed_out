// prob909: Snakes and Ladders

/*
 * https://leetcode-cn.com/problems/snakes-and-ladders/
 */

#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct State
{
    int i;
    int d;
    State(int i, int d):i(i),d(d){}
};

class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int N = board.size();
        // 1 -> N * N
        vector<vector<int>> D(N * N + 1);
        vector<int> ladder(N * N + 1, -1);
        for(int i = 1; i < N * N; ++i)
        {
            for(int j = i + 1; j <= min(i + 6, N * N); ++j)
                D[i].push_back(j);
            int x = (i - 1) / N;
            int y = (i - 1) % N;
            if(x & 1)
                y = N - 1 - y;
            x = N - 1 - x;
            if(board[x][y] != -1)
                ladder[i] = board[x][y];
        }
        queue<State> q;
        vector<bool> visited(N * N + 1);
        visited[1] = true;
        q.push(State(1, 0));
        while(!q.empty())
        {
            State cur = q.front();
            q.pop();
            if(cur.i == N * N)
                return cur.d;
            for(int nxt: D[cur.i])
            {
                if(ladder[nxt] != -1)
                {
                    if(!visited[ladder[nxt]])
                    {
                        visited[ladder[nxt]] = true;
                        q.push(State(ladder[nxt], cur.d + 1));
                    }
                }
                else
                {
                    if(!visited[nxt])
                    {
                        visited[nxt] = true;
                        q.push(State(nxt, cur.d + 1));
                    }
                }
            }
        }
        return -1;
    }
};
