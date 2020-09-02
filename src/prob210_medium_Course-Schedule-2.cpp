// prob210: Course Schedule II

/*
 * There are a total of n courses you have to take, labeled from 0 to n-1.
 * Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
 * Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.
 * There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.
 */

/*
 * Example 1:
 * Input: 2, [[1,0]]
 * Output: [0,1]
 * Explanation: There are a total of 2 courses to take. To take course 1 you should have finished
 *              course 0. So the correct course order is [0,1] .
 * Example 2:
 * Input: 4, [[1,0],[2,0],[3,1],[3,2]]
 * Output: [0,1,2,3] or [0,2,1,3]
 * Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both
 *              courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
 *                           So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3] .
 */

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int> > g(numCourses);
        vector<int> indegrees(numCourses, 0);
        for(vector<int> &prerequisite: prerequisites)
        {
            g[prerequisite[1]].push_back(prerequisite[0]);
            ++indegrees[prerequisite[0]];
        }

        queue<int> q;
        for(int i = 0; i < numCourses; ++i)
        {
            if(indegrees[i] == 0)
                q.push(i);
        }

        vector<int> result(numCourses, 0);
        int i = 0;
        while(!q.empty())
        {
            int cur = q.front();
            q.pop();
            result[i] = cur;
            ++i;
            for(int son: g[cur])
            {
                --indegrees[son];
                if(indegrees[son] == 0)
                    q.push(son);
            }
        }

        if(i != numCourses) return vector<int>();
        return result;
    }
};

class Solution_2 {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int> > g(numCourses);
        vector<int> indegrees(numCourses, 0);
        for(vector<int> &prerequisite: prerequisites)
        {
            g[prerequisite[1]].push_back(prerequisite[0]);
            ++indegrees[prerequisite[0]];
        }

        vector<int> result = top_sort(g, indegrees);
        if((int)result.size() != numCourses) return vector<int>();
        return result;
    }

    vector<int> top_sort(const vector<vector<int> >& g, vector<int>& indegrees)
    {
        int n = g.size();
        queue<int> q;
        for(int i = 0; i < n; ++i)
        {
            if(indegrees[i] == 0)
                q.push(i);
        }
        vector<int> result;
        while(!q.empty())
        {
            int cur = q.front();
            q.pop();
            result.push_back(cur);
            for(int son: g[cur])
            {
                --indegrees[son];
                if(indegrees[son] == 0)
                    q.push(son);
            }
        }
        return result;
    }
};


#include <stack>
#include <algorithm>

class Solution_3 {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int> > g(numCourses);
        vector<int> indegrees(numCourses, 0);
        for(vector<int> &prerequisite: prerequisites)
        {
            g[prerequisite[1]].push_back(prerequisite[0]);
            ++indegrees[prerequisite[0]];
        }

        vector<int> result = top_sort(g, indegrees);
        if((int)result.size() != numCourses) return vector<int>();
        return result;
    }

    vector<int> top_sort(const vector<vector<int> >& g, vector<int>& indegrees)
    {
        int n = g.size();
        vector<int> result;
        vector<int> visited(n, 0);
        for(int i = 0; i < n; ++i)
        {
            if(indegrees[i] == 0)
                if(!dfs(g, i, visited, result))
                    return {};
        }
        reverse(result.begin(), result.end());
        return result;
    }

    bool dfs(const vector<vector<int> >& g, int node, vector<int>& visited, vector<int>& result)
    {
        if(visited[node] == 2)
            return true;
        if(visited[node] == 1)
            return false;
        visited[node] = 1;
        for(int son: g[node])
            if(!dfs(g, son, visited, result))
                return false;
        result.push_back(node);
        visited[node] = 2;
        return true;
    }
};
