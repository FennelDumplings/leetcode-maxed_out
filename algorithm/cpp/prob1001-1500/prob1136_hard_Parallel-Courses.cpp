// prob1136: Parallel Courses

/*
 * https://leetcode-cn.com/problems/parallel-courses/
 */

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int minimumSemesters(int N, vector<vector<int>>& relations) {
        vector<vector<int>> g(N + 1);
        vector<int> indegrees(N + 1);
        for(const vector<int>& edge: relations)
        {
            g[edge[0]].push_back(edge[1]);
            ++indegrees[edge[1]];
        }
        queue<int> q;
        vector<bool> visited(N + 1, false);
        for(int i = 1; i <= N; ++i)
        {
            if(indegrees[i] == 0)
            {
                q.push(i);
                visited[i] = true;
            }
        }
        int d = 0;
        vector<int> level_nodes;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            ++d;
            for(int node: level_nodes)
            {
                for(int son: g[node])
                {
                    if(visited[son])
                        continue;
                    --indegrees[son];
                    if(indegrees[son] == 0)
                    {
                        visited[son] = true;
                        q.push(son);
                    }
                }
            }
        }
        for(int i = 1; i <= N; ++i)
            if(!visited[i])
                return -1;
        return d;
    }
};
