
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    int maxSumMinProduct(vector<int>& nums) {
        // 对每个 nums[i]，求以 nums[i] 为最小值的区间
        // 即求 [j1, j2]，对 j1 <= j<= j2 有 nums[i] <= nums[j]
        int n = nums.size();
        stack<int> st;
        using ll = long long;
        const int MOD = 1e9 + 7;
        ll ans = 0;
        vector<ll> sums(n + 1);
        for(int i = 0; i < n; ++i)
            sums[i + 1] = sums[i] + nums[i];
        for(int i = 0; i < n; ++i)
        {
            while(!st.empty() && nums[st.top()] > nums[i])
            {
                ll min_x = nums[st.top()];
                st.pop();
                int right = i - 1;
                int left = 0;
                if(!st.empty())
                    left = st.top() + 1;
                ans = max(ans, min_x * (sums[right + 1] - sums[left]));
            }
            st.push(i);
        }
        while(!st.empty())
        {
            ll min_x = nums[st.top()];
            st.pop();
            int right = n - 1;
            int left = 0;
            if(!st.empty())
                left = st.top() + 1;
            ans = max(ans, min_x * (sums[right + 1] - sums[left]));
        }
        return ans % MOD;
    }
};
