

#include <unordered_set>
#include <queue>
#include <vector>

using namespace std;

class Solution_2 {
public:
    int minDays(int n) {
        if(n == 1) return 1;
        queue<int> q;
        q.push(1);
        vector<int> level;
        unordered_set<int> setting;
        setting.insert(1);
        int d = 1;
        while(true)
        {
            level.clear();
            while(!q.empty())
            {
                int cur = q.front();
                level.push_back(cur);
                q.pop();
            }
            ++d;
            for(int i: level)
            {
                int nxt;
                if(n / 3 + 1 > i)
                {
                    nxt = i * 3;
                    if(nxt <= n && setting.count(nxt) == 0)
                    {
                        if(nxt == n)
                            return d;
                        setting.insert(nxt);
                        q.push(nxt);
                    }
                }
                if(n / 2 + 1 > i)
                {
                    nxt = i * 2;
                    if(nxt <= n && setting.count(nxt) == 0)
                    {
                        if(nxt == n)
                            return d;
                        setting.insert(nxt);
                        q.push(nxt);
                    }
                }
                nxt = i + 1;
                if(nxt <= n && setting.count(nxt) == 0)
                {
                    if(nxt == n)
                        return d;
                    setting.insert(nxt);
                    q.push(nxt);
                }
            }
        }
    }
};

class Solution_3 {
public:
    int minDays(int n) {
        if(n == 1) return 1;
        int d = 0;
        while(n > 1)
        {
            if(n % 3 == 0)
            {
                n /= 3;
                ++d;
            }
            else
            {
                if(n % 3 == 1)
                {
                    --n;
                    ++d;
                }
                else if(n % 2 == 2)
                {
                    n /= 2;
                    ++d;
                }
                else
                {
                    n -= 2;
                    d += 2;
                }
            }
        }
        return d;
    }
};


class Solution {
public:
    int minDays(int n) {
        if(n == 1) return 1;
        queue<int> q;
        q.push(n);
        vector<int> level;
        int d = 0;
        while(true)
        {
            level.clear();
            while(!q.empty())
            {
                int cur = q.front();
                level.push_back(cur);
                q.pop();
            }
            ++d;
            for(int i: level)
            {
                int nxt;
                if(i % 3 == 0)
                {
                    nxt = i / 3;
                    if(nxt == 1)
                        return d + 1;
                    q.push(nxt);
                    continue;
                }
                if(i % 3 == 1)
                {
                    nxt = i - 1;
                    if(nxt == 1)
                        return d + 1;
                    q.push(nxt);
                    if(i % 2 == 0)
                    {
                        nxt = i / 2;
                        if(nxt == 1)
                            return d + 1;
                        q.push(nxt);
                    }
                }
                else
                {
                    if(i % 2 == 0)
                    {
                        nxt = i / 2;
                        if(nxt == 1)
                            return d + 1;
                        q.push(nxt);
                    }
                    nxt = i - 1;
                    if(nxt == 1)
                        return d + 1;
                    q.push(nxt);
                }
            }
        }
    }
};
