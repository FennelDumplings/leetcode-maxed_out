// interview08.13: 堆箱子

/*
 * https://leetcode-cn.com/problems/pile-box-lcci/
 */

#include <vector>
#include <algorithm>

using namespace std;

struct Box
{
    int w, d, h;
    Box(int w, int d, int h):w(w),d(d),h(h){}
    bool operator<(const Box& box) const
    {
        return w < box.w && d < box.d && h < box.h;
    }
};

struct Cmp
{
    bool operator()(const Box& box1, const Box& box2) const
    {
        if(box1.h == box2.h)
        {
            return box1.d > box2.d && box1.w > box2.w;
        }
        return box1.h < box2.h;

    }
};

class Solution {
public:
    int pileBox(vector<vector<int>>& box) {
        vector<Box> a;
        for(const vector<int>& i: box)
        {
            a.push_back(Box(i[0], i[1], i[2]));
        }
        sort(a.begin(), a.end(), Cmp());
        int n = a.size();
        vector<int> dp(n, 0);
        dp[0] = a[0].h;
        for(int i = 1; i < n; ++i)
        {
            dp[i] = a[i].h;
            for(int j = 0; j < i; ++j)
            {
                if(a[j] < a[i])
                {
                    dp[i] = max(dp[i], dp[j] + a[i].h);
                }
            }
        }
        int ans = 0;
        for(int i: dp) ans = max(ans, i);
        return ans;
    }
};
