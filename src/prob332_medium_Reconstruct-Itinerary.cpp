// prob332: Reconstruct Itinerary

/*
 * https://leetcode-cn.com/problems/reconstruct-itinerary
 */

#include <vector>
#include <stack>
#include <string>
#include <list>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Cmp
{
    vector<string> names;
    Cmp(const vector<string>& names):names(names){}
    bool operator()(const int& node1, const int& node2) const
    {
        return names[node1] < names[node2];
    }
};

class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        int id = 0;
        unordered_map<string, int> mapping; // str -> idx
        for(const vector<string>& edge: tickets)
        {
            if(mapping.count(edge[0]) == 0)
                mapping[edge[0]] = id++;
            if(mapping.count(edge[1]) == 0)
                mapping[edge[1]] = id++;
        }
        int n = mapping.size();
        vector<string> names(n);
        for(const auto &item: mapping)
            names[item.second] = item.first;
        vector<list<int>> g(n);
        for(const vector<string>& edge: tickets)
            g[mapping[edge[0]]].push_back(mapping[edge[1]]);
        Cmp cmp(names);
        for(list<int> &edges: g)
            edges.sort(cmp);
        int root = mapping["JFK"];
        vector<int> euler_path = find_euler_path(g, root);
        vector<string> result;
        for(int i: euler_path)
            result.push_back(names[i]);
        return result;
    }

private:
    vector<int> find_euler_path(vector<list<int>>& g, const int root)
    {
        // 调用方保证从 root 出发存在欧拉路径，否则返回结果错误
        int n = g.size();
        vector<int> euler_path;
        stack<int> cur_path;
        cur_path.push(root);
        vector<bool> visited(n, false);
        while(!cur_path.empty())
        {
            int cur = cur_path.top();
            bool flag = false;
            list<int> &edges = g[cur];
            auto it = edges.begin();
            while(it != edges.end())
            {
                int son = *it;
                if(!visited[son])
                {
                    cur_path.push(son);
                    it = edges.erase(it); // 删边
                    flag = true;
                    break;
                }
            }
            if(!flag)
            {
                visited[cur] = true;
                euler_path.push_back(cur_path.top());
                cur_path.pop();
            }
        }
        reverse(euler_path.begin(), euler_path.end());
        return euler_path;
    }
};
