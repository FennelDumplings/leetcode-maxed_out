// prob1063: Number of Valid Subarrays

/*
 * https://leetcode-cn.com/problems/special-binary-string/submissions/
 */

#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    int validSubarrays(vector<int>& nums) {
        int n = nums.size();
        stack<int> st;
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            while(!st.empty() && nums[i] < nums[st.top()])
            {
                ans += i - st.top();
                st.pop();
            }
            st.push(i);
        }
        while(!st.empty())
        {
            ans += n - st.top();
            st.pop();
        }
        return ans;
    }
};
