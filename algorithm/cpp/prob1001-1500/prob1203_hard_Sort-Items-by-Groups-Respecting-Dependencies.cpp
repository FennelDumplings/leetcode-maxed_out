// prob1203: Sort Items by Groups Respecting Dependencies

/*
 * There are n items each belonging to zero or one of m groups where group[i] is the group that the i-th item belongs to
 * and it's equal to -1 if the i-th item belongs to no group. The items and the groups are zero indexed. A group can have no item belonging to it.
 * Return a sorted list of the items such that:
 * The items that belong to the same group are next to each other in the sorted list.
 * There are some relations between these items where beforeItems[i] is a list containing all the items that should come before the i-th
 * item in the sorted array (to the left of the i-th item).
 * Return any solution if there is more than one solution and return an empty list if there is no solution.
 */

/*
 * Constraints:
 * 1 <= m <= n <= 3*10^4
 * group.length == beforeItems.length == n
 * -1 <= group[i] <= m-1
 *  0 <= beforeItems[i].length <= n-1
 *  0 <= beforeItems[i][j] <= n-1
 *  i != beforeItems[i][j]
 *  beforeItems[i] does not contain duplicates elements.
 */

#include <vector>
#include <queue>

using namespace std;

// 两层 TopSort
// 参考 acwing 代码 https://www.acwing.com/solution/LeetCode/content/4745/
class Solution {
public:
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        vector<vector<int> > g(n + m); // 记录组对应哪些项目

        // 外层 TopSort, 组编号为 [n, n + m - 1]
        vector<vector<int> > g_outer(n + m), g_inner(n);
        vector<int> indegrees_outer(n + m, 0), indegrees_inner(n, 0);

        for(int i = 0; i < n; ++i)
            if(group[i] != -1) // 第 i 个项目
                g[group[i] + n].push_back(i);

        // 建立两种图的关系
        for(int i = 0; i < n; ++i)
            for(int x: beforeItems[i])
            {
                if(group[x] == -1)
                {
                    if(group[i] == -1)
                        g_outer[x].push_back(i);
                    else
                        g_outer[x].push_back(group[i] + n);
                }
                else
                {
                    if(group[i] == -1)
                        g_outer[group[x] + n].push_back(i);
                    else
                    {
                        if(group[x] != group[i])
                            g_outer[group[x] + n].push_back(group[i] + n);
                        else
                            g_inner[x].push_back(i);
                    }
                }
            }

        // 统计外部关系的入度
        for(int i = 0; i < m + n; ++i)
            for(int j = 0; j < (int)g_outer[i].size(); ++j)
                ++indegrees_outer[g_outer[i][j]];

        // 统计内部依赖关系每个点的入度
        for(int i = 0; i < n; i++)
            for(int j = 0; j < (int)g_inner[i].size(); ++j)
                ++indegrees_inner[g_inner[i][j]];

        queue<int> q;
        for(int i = 0; i < m + n; ++i)
            if(indegrees_outer[i] == 0)
                q.push(i);

        vector<int> sorted_outer = top_sort(q, g_outer, indegrees_outer);
        if((int)sorted_outer.size() != m + n)
            return {};

        vector<int> result;
        for(int v: sorted_outer)
        {
            if(v < n)
            {
                // 当前是项目
                if(group[v] == -1) // 项目不属于任何组
                    result.push_back(v);
            }
            else
            {
                // 当前点是一个组
                int cnt = 0;
                for(int j: g[v])
                {
                    // 当前组 v 下的项目 j
                    ++cnt;
                    if(indegrees_inner[j] == 0)
                        q.push(j);
                }
                vector<int> sorted_inner = top_sort(q, g_inner, indegrees_inner);
                if((int)sorted_inner.size() != cnt)
                    return {};
                result.insert(result.end(), sorted_inner.begin(), sorted_inner.end());
            }
        }
        return result;
    }

private:
    vector<int> top_sort(queue<int>& q, const vector<vector<int> >& g, vector<int>& indegrees)
    {
        // start 已经进队
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
