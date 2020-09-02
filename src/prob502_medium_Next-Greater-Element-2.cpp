// prob502: Next Greater Element II

/*
 * https://leetcode-cn.com/problems/next-greater-element-ii/
 */

#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        if(nums.empty()) return {};
        int n = nums.size();
        vector<int> result(n, -111);
        nums.insert(nums.end(), nums.begin(), nums.end());
        stack<int> st;
        for(int i = n * 2 - 1; i >= n; --i)
        {
            while(!st.empty() && nums[st.top()] <= nums[i])
                st.pop();
            st.push(i);
        }
        for(int i = n - 1; i >= 0; --i)
        {
            while(!st.empty() && nums[st.top()] <= nums[i])
                st.pop();
            if(st.empty())
                result[i] = -1;
            else
                result[i] = nums[st.top()];
            st.push(i);
        }
        return result;
    }
};
