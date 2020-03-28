// prob207: Course Schedule

/*
 * There are a total of numCourses courses you have to take, labeled from 0 to numCourses-1.
 * Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
 * Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?
 */

/*
 * 你可以假定输入的先决条件中没有重复的边。
 * 1 <= numCourses <= 10^5
 */

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int> > g(numCourses);
        vector<int> indegrees(numCourses, 0);
        for(vector<int> &prerequisite: prerequisites)
        {
            g[prerequisite[1]].push_back(prerequisite[0]);
            ++indegrees[prerequisite[0]];
        }

        queue<int> q;
        for(int i = 0; i < numCourses; ++i)
            if(indegrees[i] == 0)
                q.push(i);

        int n = numCourses;
        while(!q.empty())
        {
            int cur = q.front();
            q.pop();
            --n;
            for(int son: g[cur])
            {
                --indegrees[son];
                if(indegrees[son] == 0)
                    q.push(son);
            }
        }
        return n == 0;
    }
};
