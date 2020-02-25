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
class Solution {
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

// 4. 双指针class Solution {
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
        stack<pair<int, int>> st;
        int max_h = 0; // 栈底特判
        int result = 0;
        for(int i = 0; i < n; ++i)
        {
            int cur_h = height[i];
            if(cur_h >= max_h)
            {
                while(!st.empty())
                {
                    int h = st.top().first;
                    int j = st.top().second;
                    st.pop();
                    if(st.empty()) break;
                    result += (j - st.top().second) * (max_h - h);
                }
                max_h = cur_h;
                st.push(pair<int, int>(cur_h, i));
            }
            else
            {
                while(st.top().first <= cur_h)
                {
                    int h = st.top().first;
                    int j = st.top().second;
                    st.pop();
                    result += (j - st.top().second) * (cur_h - h);
                }
                st.push(pair<int, int>(cur_h, i));
            }
        }
        return result;
    }
};
