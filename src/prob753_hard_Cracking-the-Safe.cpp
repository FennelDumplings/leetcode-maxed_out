// prob753: Cracking the Safe

/*
 * https://leetcode-cn.com/problems/cracking-the-safe/
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <list>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
public:
    string crackSafe(int n, int k) {
        // k in [1..10]
        // n in [1..4]
        if(n == 1)
        {
            string result = "";
            for(int i = 0; i < k; ++i)
                result += '0' + i;
            return result;
        }
        items = vector<string>(pow(k, n - 1));
        mapping = unordered_map<string, int>();
        string item;
        int total = 0;
        dfs(n - 1, k, 0, item, total);
        vector<list<int>> g(total);
        build(g, k);
        vector<int> euler_path = find_euler_path(g, 0);
        string result = items[0];
        for(int i = 1; i < (int)euler_path.size(); ++i)
            result += items[euler_path[i]].back();
        return result;
    }

private:
    vector<string> items;
    unordered_map<string, int> mapping;

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

    void build(vector<list<int>>& g, const int k)
    {
        for(const auto &item: mapping)
        {
            const string &cur = item.first;
            for(int i = 0; i < k; ++i)
            {
                string son = cur.substr(1);
                son += '0' + i;
                g[mapping[cur]].push_back(mapping[son]);
            }
        }
    }

    void dfs(const int n, const int k, int pos, string& item, int& total)
    {
        if(pos == n)
        {
            mapping[item] = total;
            items[total] = item;
            ++total;
            return;
        }
        for(int i = 0; i < k; ++i)
        {
            item.push_back('0' + i);
            dfs(n, k, pos + 1, item, total);
            item.pop_back();
        }
    }
};
