
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        if(nums.empty()) return 0;
        int n = nums.size();
        stack<int> st({-1});
        int result = nums[k];
        for(int i = 0; i < n; ++i)
        {
            if(st.top() == -1 || nums[st.top()] <= nums[i])
                st.push(i);
            else
            {
                while(st.top() != -1 && nums[st.top()] > nums[i])
                {
                    int index = st.top();
                    st.pop();
                    if((i - 1) >= k && (st.top() + 1) <= k)
                    {
                        int w = i - st.top() - 1;
                        int area = w * nums[index];
                        result = max(result, area);
                    }
                }
                st.push(i);
            }
        }
        while(st.top() != -1)
        {
            int index = st.top();
            st.pop();
            if((st.top() + 1) <= k)
            {
                int w = n - st.top() - 1;
                int area = w * nums[index];
                result = max(result, area);
            }
        }
        return result;
    }
};
