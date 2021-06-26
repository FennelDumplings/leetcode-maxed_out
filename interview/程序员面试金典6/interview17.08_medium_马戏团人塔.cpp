// interview17.08: 马戏团人塔

/*
 * https://leetcode-cn.com/problems/circus-tower-lcci/
 */

#include <vector>
#include <algorithm>

using namespace std;

struct Person
{
    int h, w;
    Person(int h, int w):h(h),w(w){}
};

struct Cmp
{
    bool operator()(const Person& p1, const Person& p2) const
    {
        if(p1.h == p2.h)
            return p1.w > p2.w;
        return p1.h < p2.h;
    }
};

class Solution {
public:
    int bestSeqAtIndex(vector<int>& height, vector<int>& weight) {
        if(height.empty()) return 0;
        int n = height.size();
        if(n == 1) return 1;
        vector<Person> persons;
        for(int i = 0; i < n; ++i)
            persons.push_back(Person(height[i], weight[i]));
        sort(persons.begin(), persons.end(), Cmp());
        vector<int> a(n);
        for(int i = 0; i < n; ++i)
            a[i] = persons[i].w;
        x = vector<int>();
        for(int i: a)
            x.push_back(i);
        sort(x.begin(), x.end());
        x.erase(unique(x.begin(), x.end()), x.end());
        m = x.size();
        dp.assign(m + 1, 0);
        bit.assign(m + 1, 0);
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            int w_idx = find(a[i]);
            int len = 1;
            if(w_idx > 0)
                len += query(1, w_idx);
            ans = max(ans, len);
            update(w_idx + 1, len);
        }
        return ans;
    }

private:
    vector<int> x; // 所有能值排序后去重
    vector<int> dp; // 权值数组
    int m; // 权值数组的长度

    vector<int> bit; // 权值数组的树状数组

    void update(int idx, int val)
    {
        dp[idx - 1] = val;
        bit[idx] = val;
        for(int i = idx; i <= m; i += lowbit(i))
        {
            for(int j = 1; j < lowbit(i); j <<= 1)
            {
                bit[i] = max(bit[i], bit[i - j]);
            }
        }
    }

    int query(int l, int r)
    {
        int ans = dp[r - 1];
        while(true)
        {
            for(; r - lowbit(r) + 1 > l; r -= lowbit(r))
                ans = max(ans, bit[r]);
            if(r - lowbit(r) + 1 == l)
            {
                ans = max(ans, bit[r]);
                return ans;
            }
            ans = max(ans, dp[r - 1]);
            --r;
        }
    }

    int lowbit(int v)
    {
        return v & (-v);
    }

    int find(int v)
    {
        return lower_bound(x.begin(), x.end(), v) - x.begin();
    }
};
