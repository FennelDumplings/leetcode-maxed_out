// prob1514: Path with Maximum Probability

/*
 * https://leetcode-cn.com/problems/path-with-maximum-probability/
 */

#include <queue>
#include <vector>

using namespace std;

struct To
{
    int v;
    double w;
    To(int v, double w):v(v),w(w){}
};

struct State
{
    int v;
    double p;
    State(int v, double p):v(v),p(p){}
};

struct HeapCmp
{
    bool operator()(const State& s1, const State& s2) const
    {
        return s1.p < s2.p;
    }
};

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        vector<vector<To>> g(n);
        int m = edges.size();
        for(int i = 0; i < m; ++i)
        {
            g[edges[i][0]].emplace_back(edges[i][1], succProb[i]);
            g[edges[i][1]].emplace_back(edges[i][0], succProb[i]);
        }
        priority_queue<State, vector<State>, HeapCmp> pq;
        pq.push(State(start, 1.0));
        vector<bool> visited(n, false);
        while(!pq.empty())
        {
            State s = pq.top();
            pq.pop();
            if(s.v == end)
                return s.p;
            if(visited[s.v])
                continue;
            visited[s.v] = true;
            for(const To &nxt: g[s.v])
            {
                if(visited[nxt.v]) continue;
                pq.push(State(nxt.v, nxt.w * s.p));
            }
        }
        return 0.0;
    }
};
