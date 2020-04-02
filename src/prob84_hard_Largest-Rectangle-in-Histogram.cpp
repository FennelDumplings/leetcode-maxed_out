// prob84: Largest Rectangle in Histogram

/*
 * Given n non-negative integers representing the histogram's bar height
 * where the width of each bar is 1, find the area of largest rectangle in the histogram.
 */

#include <stack>
#include <vector>

using namespace std;

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
