#include <vector>
#include <>

using namespace std;

class Solution {
public:
    long long subArrayRanges(vector<int>& nums) {
        int n = nums.size();
        stack<int> st_max; // 单调递减栈
        stack<int> st_min; // 单调递增栈
        long long ans = 0;
        for(int r = 0; r < n; ++r)
        {
            while(!st_max.empty() && nums[st_max.top()] < nums[r])
            {
                int i = st_max.top();
                st_max.pop();
                int l = -1;
                if(!st_max.empty())
                    l = st_max.top();
                ans += (long long)nums[i] * (i - l) * (r - i);
            }
            st_max.push(r);
            while(!st_min.empty() && nums[st_min.top()] > nums[r])
            {
                int i = st_min.top();
                st_min.pop();
                int l = -1;
                if(!st_min.empty())
                    l = st_min.top();
                ans -= (long long)nums[i] * (i - l) * (r - i);
            }
            st_min.push(r);
        }
        int r = n;
        while(!st_max.empty())
        {
            int i = st_max.top();
            st_max.pop();
            int l = -1;
            if(!st_max.empty())
                l = st_max.top();
            ans += (long long)nums[i] * (i - l) * (r - i);
        }
        while(!st_min.empty())
        {
            int i = st_min.top();
            st_min.pop();
            int l = -1;
            if(!st_min.empty())
                l = st_min.top();
            ans -= (long long)nums[i] * (i - l) * (r - i);
        }
        return ans;
    }
};

/*
class Solution {
public:
    long long subArrayRanges(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp1(n, vector<int>(n)), dp2(n, vector<int>(n));
        for(int i = 0; i < n; ++i)
        {
            dp1[i][i] = nums[i];
            dp2[i][i] = nums[i];
        }
        for(int i = 0; i < n - 1; ++i)
        {
            for(int j = i + 1; j < n; ++j)
            {
                dp1[i][j] = max(dp1[i][j - 1], nums[j]);
                dp2[i][j] = min(dp2[i][j - 1], nums[j]);
            }
        }
        long long ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = i; j < n; ++j)
            {
                ans += ((long long)dp1[i][j] - dp2[i][j]);
            }
        return ans;
    }
};
*/
