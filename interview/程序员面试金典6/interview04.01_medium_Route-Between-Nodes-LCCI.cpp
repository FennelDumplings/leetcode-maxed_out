// interview04.01: Route Between Nodes LCCI

/*
 * Given a directed graph, design an algorithm to find out whether there is a route between two nodes.
 */

/*
 * Example1:
 *
 *  Input: n = 3, graph = [[0, 1], [0, 2], [1, 2], [1, 2]], start = 0, target = 2
 *  Output: true
 * Example2:
 *
 *  Input: n = 5, graph = [[0, 1], [0, 2], [0, 4], [0, 4], [0, 1], [1, 3], [1, 4], [1, 3], [2, 3], [3, 4]], start = 0, target = 4
 *  Output true
 */

/*
 * Note:
 * 0 <= n <= 100000
 * All node numbers are within the range [0, n].
 * There might be self cycles and duplicated edges.
 */

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    bool findWhetherExistsPath(int n, vector<vector<int>>& graph, int start, int target) {
        vector<vector<int> > g(n);
        for(vector<int> &edge: graph)
            g[edge[0]].push_back(edge[1]);
        vector<bool> visited(n, false);
        visited[start] = true;
        return dfs(g, visited, start, target);
    }

private:
    bool dfs(vector<vector<int> >& g, vector<bool>& visited, int cur, int target)
    {
        for(int son: g[cur])
        {
            if(son == target) return true;
            if(visited[son]) continue;
            visited[son] = true;
            if(dfs(g, visited, son, target))
                return true;
            visited[son] = false;
        }
        return false;
    }
};

class Solution_2 {
public:
    bool findWhetherExistsPath(int n, vector<vector<int>>& graph, int start, int target) {
        vector<vector<int> > g(n);
        for(vector<int> &edge: graph)
            g[edge[0]].push_back(edge[1]);
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;
        while(!q.empty())
        {
            int cur = q.front();
            q.pop();
            for(int son: g[cur])
            {
                if(son == target) return true;
                if(visited[son]) continue;
                q.push(son);
                visited[son] = true;
            }
        }
        return false;
    }
};

// 双向 BFS
// 实际跑的结果更慢
class Solution_3 {
public:
    bool findWhetherExistsPath(int n, vector<vector<int>>& graph, int start, int target) {
        vector<vector<int> > g1(n);
        vector<vector<int> > g2(n);
        for(vector<int> &edge: graph)
            g1[edge[0]].push_back(edge[1]);
        for(vector<int> &edge: graph)
            g2[edge[1]].push_back(edge[0]);
        vector<bool> visited1(n, false);
        vector<bool> visited2(n, false);
        queue<int> q1, q2;
        q1.push(start), q2.push(target);
        visited1[start] = true;
        visited2[target] = true;
        while(!q1.empty() && !q2.empty())
        {
            int cur1 = q1.front();
            q1.pop();
            int cur2 = q2.front();
            q2.pop();
            for(int son: g1[cur1])
            {
                if(visited2[son]) return true;
                if(visited1[son]) continue;
                q1.push(son);
                visited1[son] = true;
            }
            for(int son: g2[cur2])
            {
                if(visited1[son]) return true;
                if(visited2[son]) continue;
                q2.push(son);
                visited2[son] = true;
            }
        }
        return false;
    }
};
