// 20200531
// 3. 重新规划路线


#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        vector<vector<PIB> > g(n);
        for(const vector<int>& connection: connections)
        {
            int from = connection[0], to = connection[1];
            g[from].push_back(PIB(to, true));
            g[to].push_back(PIB(from, false));
        }

        queue<int> q;
        vector<bool> visited(n, false);
        visited[0] = true;
        q.push(0);
        vector<int> level_nodes;
        int result = 0;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            for(int node: level_nodes)
            {
                for(PIB son: g[node])
                {
                    if(visited[son.first]) continue;
                    visited[son.first] = true;
                    q.push(son.first);
                    if(son.second)
                        ++result;
                }
            }
        }
        return result;
    }

private:
    using PIB = pair<int, bool>;
};
