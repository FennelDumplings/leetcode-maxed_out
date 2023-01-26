// prob433: Minimum Genetic Mutation

/*
 * https://leetcode-cn.com/problems/minimum-genetic-mutation/
 */

#include <string>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        if(start == end)
            return 0;
        int n = bank.size();
        int m = start.size();
        if((int)end.size() != m)
            return -1;
        int s = -1, t = -1;
        vector<int> d(n); // 0 未访问, 正： 起点侧, 负：终点侧
        for(int i = 0; i < n; ++i)
        {
            if(bank[i] == start)
            {
                s = i;
                d[i] = 1;
            }
            if(bank[i] == end)
            {
                t = i;
                d[i] = -1;
            }
        }
        if(t == -1)
            return -1;
        if(s == -1)
        {
            bank.push_back(start);
            d.push_back(1);
            s = n;
        }
        queue<int> q;
        q.push(s);
        q.push(t);
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            for(int v = 0; v < n; ++v)
            {
                if(check(bank[u], bank[v]))
                {
                    if(d[v] == 0)
                    {
                        d[v] = d[u] > 0 ? d[u] + 1 : d[u] - 1;
                        q.push(v);
                    }
                    else
                    {
                        if((d[u] ^ d[v]) < 0)
                            return abs(d[u]) + abs(d[v]) - 1;
                    }
                }
            }
        }
        return -1;
    }

private:
    bool check(const string& s1, const string& s2)
    {
        int n1 = s1.size(), n2 = s2.size();
        if(n1 != n2)
            return false;
        int diff = 0;
        for(int i = 0; i < n1; ++i)
        {
            if(s1[i] != s2[i])
            {
                ++diff;
                if(diff > 1)
                    return false;
            }
        }
        return diff == 1;
    }
};
