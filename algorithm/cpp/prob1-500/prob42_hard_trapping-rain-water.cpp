// prob42: trapping-rain-water

/*
 * Given n non-negative integers representing an elevation map where the width of each bar is 1,
 * compute how much water it is able to trap after raining.
 */

/*
 * Example:
 * Input: [0,1,0,2,1,0,1,3,2,1,2,1]
 * Output: 6
 */

#include <vector>
#include <stack>

using namespace std;

// 1. 暴力
class Solution_5 {
public:
    int trap(vector<int>& height) {
        if(height.empty()) return 0;
        int n = height.size();
        if(n <= 2) return 0;
        int result = 0;
        for(int i = 1; i <= n - 2; ++i)
        {
            // i 这个位置的水深
            // lh, rh
            int lh = 0, rh = 0;
            for(int j = i - 1; j >= 0; --j)
                lh = max(lh, height[j]);
            for(int j = i + 1; j <= n - 1; ++j)
                rh = max(rh, height[j]);
            int hw = min(lh, rh);
            if(hw > height[i])
                result += hw - height[i];
        }
        return result;
    }
};

// 2. DP
// 对每个 i 找
//  lh[i]: i 左边的最高值
//  rh[i]: i 右边的最高值
//  lh[i] = max(lh[i - 1], h[i - 1]), max 有结合律，可以从左往右扫
//  rh[i] = max(rh[i + 1], h[i + 1]), 类似地, rh 从右往左扫
class Solution_2 {
public:
    int trap(vector<int>& height) {
        if(height.empty()) return 0;
        int n = height.size();
        if(n <= 2) return 0;
        vector<int> lh(n, 0); // 0,[1..n],n+1
        vector<int> rh(n, 0);
        for(int i = 1; i <= n - 1; ++i)
            lh[i] = max(lh[i - 1], height[i - 1]);
        for(int i = n - 2; i >= 0; --i)
            rh[i] = max(rh[i + 1], height[i + 1]);
        int result = 0;
        for(int i = 1; i < n - 1; ++i)
        {
            int hw = min(lh[i], rh[i]);
            if(height[i] < hw)
                result += hw - height[i];
        }
        return result;
    }
};

// 3. DP 空间优化
class Solution_2_optim {
public:
    int trap(vector<int>& height) {
        if(height.empty()) return 0;
        int n = height.size();
        if(n <= 2) return 0;
        // vector<int> lh(n, 0); // 0,[1..n],n+1
        vector<int> rh(n, 0);
        // for(int i = 1; i <= n - 1; ++i)
            // lh[i] = max(lh[i - 1], height[i - 1]);
        for(int i = n - 2; i >= 0; --i)
            rh[i] = max(rh[i + 1], height[i + 1]);
        int result = 0;
        int lh = height[0];
        for(int i = 1; i < n - 1; ++i)
        {
            lh = max(lh, height[i - 1]);
            int hw = min(lh, rh[i]);
            if(height[i] < hw)
                result += hw - height[i];
        }
        return result;
    }
};

// 4. 双指针
class Solution_3 {
public:
    int trap(vector<int>& height) {
        if(height.empty()) return 0;
        int n = height.size();
        if(n <= 2) return 0;
        int lh = height[0], rh = height[n - 1];
        int left = 0, right = n - 1;
        int result = 0;
        while(left < right)
        {
            if(lh <= rh) // 向右移动 left
            {
                ++left;
                if(height[left] < lh)
                    result += lh - height[left];
                else if(height[left] > lh)
                    lh = height[left];
            }
            else // 向左移动 right
            {
                --right;
                if(height[right] < rh)
                    result += rh - height[right];
                else if(height[right] > rh)
                    rh = height[right];
            }
        }
        return result;
    }
};

// 5. 单调栈
class Solution_4 {
public:
    int trap(vector<int>& height) {
        if(height.empty()) return 0;
        int n = height.size();
        if(n <= 2) return 0;
        stack<int> st;
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            while(!st.empty() && height[st.top()] <= height[i])
            {
                int j = st.top();
                st.pop();
                if(st.empty())
                    break;
                int k = st.top();
                ans += (i - k - 1) * (min(height[k], height[i]) - height[j]);
            }
            st.push(i);
        }
        return ans;
    }
};

#include <climits>
#include <cmath>

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        return solve(height, 0, n - 1);
    }

private:
    int solve(const vector<int>& h, int l, int r)
    {
        if(r - l <= 1)
            return 0;
        int m1 = -1, m2 = -1;
        int max1 = INT_MIN, max2 = INT_MIN;
        for(int i = l; i <= r; ++i)
        {
            if(h[i] > max1)
            {
                max2 = max1;
                m2 = m1;
                max1 = h[i];
                m1 = i;
            }
            else if(h[i] > max2)
            {
                max2 = h[i];
                m2 = i;
            }
        }
        int ans = (abs(m1 - m2) - 1) * max2;
        for(int i = min(m1, m2) + 1; i <= max(m1, m2) - 1; ++i)
            ans -= h[i];
        ans += solve(h, l, min(m1, m2));
        ans += solve(h, max(m1, m2), r);
        return ans;
    }
};
