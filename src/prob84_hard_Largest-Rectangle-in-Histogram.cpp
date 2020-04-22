// prob84: Largest Rectangle in Histogram

/*
 * Given n non-negative integers representing the histogram's bar height
 * where the width of each bar is 1, find the area of largest rectangle in the histogram.
 */

#include <stack>
#include <vector>

using namespace std;

// heights.push_back(-1) 的做法，保证出循环栈已经空了，减少代码量
class Solution_1 {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size(), ans = 0;
        heights.push_back(-1);
        // 为了算法书写方便，在数组末尾添加高度 -1
        // 这会使得栈中所有数字在最后出栈。
        stack<int> st;
        for (int i = 0; i <= n; i++) {
            while (!st.empty() && heights[i] < heights[st.top()]) {
                int cur = st.top();
                st.pop();
                if (st.empty())
                    ans = max(ans, heights[cur] * i);
                else
                    ans = max(ans, heights[cur]
                            * (i - st.top() - 1));
            }
            st.push(i);
        }
        return ans;
    }
};

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        if(heights.empty()) return 0;
        int n = heights.size();
        stack<int> st({-1});
        int result = 0;
        for(int i = 0; i < n; ++i)
        {
            if(st.top() == -1 || heights[st.top()] < heights[i])
                st.push(i);
            else
            {
                while(st.top() != -1 && heights[st.top()] > heights[i])
                {
                    int index = st.top();
                    st.pop();
                    int w = i - st.top() - 1;
                    int area = w * heights[index];
                    result = max(result, area);
                }
                st.push(i);
            }
        }
        while(st.top() != -1)
        {
            int index = st.top();
            st.pop();
            int w = n - st.top() - 1;
            int area = w * heights[index];
            result = max(result, area);
        }
        return result;
    }
};

class Solution_2 {
public:
    int largestRectangleArea(vector<int>& heights) {
        if(heights.empty()) return 0;
        int n = heights.size();
        stack<int> st;
        st.push(-1);
        int result = 0;
        for(int i = 0; i < n; ++i)
        {
            while(st.top() != -1 && heights[i] < heights[st.top()])
            {
                int h = heights[st.top()];
                st.pop();
                int l = st.top();
                int r = i;
                int w = r - l  - 1;
                result = max(result, h * w);
            }
            st.push(i);
        }
        while(st.top() != -1)
        {
            int h = heights[st.top()];
            st.pop();
            int l = st.top();
            int r = n;
            int w = r - l - 1;
            result = max(result, h * w);
        }
        return result;
    }
};
