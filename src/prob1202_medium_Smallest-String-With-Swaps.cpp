// prob1202: Smallest String With Swaps

/*
 * https://leetcode-cn.com/problems/smallest-string-with-swaps/
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.size();
        vector<vector<int>> components;
        vector<vector<int>> g(n);
        for(const vector<int> &p: pairs)
        {
            g[p[0]].push_back(p[1]);
            g[p[1]].push_back(p[0]);
        }
        vector<bool> visited(n, false);
        vector<int> item;
        for(int i = 0; i < n; ++i)
        {
            if(visited[i])
                continue;
            item.clear();
            visited[i] = true;
            item.push_back(i);
            dfs(g, i, item, visited);
            components.push_back(item);
        }
        for(vector<int> &p: components)
        {
            sort(p.begin(), p.end());
            string part;
            for(int i: p)
                part += s[i];
            sort(part.begin(), part.end());
            int m = p.size();
            for(int i = 0; i < m; ++i)
                s[p[i]] = part[i];
        }
        return s;
    }

private:
    void dfs(const vector<vector<int>>& g, int cur, vector<int>& item, vector<bool>& visited)
    {
        for(int son: g[cur])
        {
            if(visited[son])
                continue;
            visited[son] = true;
            item.push_back(son);
            dfs(g, son, item, visited);
        }
    }
};
