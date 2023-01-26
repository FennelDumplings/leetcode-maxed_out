class Solution {
public:
    int subarrayGCD(vector<int>& nums, int k) {
        int n = nums.size();
        int left = 0;
        int ans = 0;
        while(left < n)
        {
            int right = left;
            int cur_gcd = nums[right++];
            while(right < n && cur_gcd > k)
            {
                cur_gcd = gcd<int>(cur_gcd, nums[right]);
                ++right;
            }
            int len = 0;
            while(right < n && cur_gcd == k)
            {
                ++len;
                cur_gcd = gcd<int>(cur_gcd, nums[right]);
                ++right;
            }
            ans += len;
            ++left;
        }
        return ans;
    }
};
