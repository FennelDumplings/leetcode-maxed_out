class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int s = accumulate(nums.begin(), nums.end(), 0);
        int t = s - x;
        int n = nums.size();
        int cur_sum = 0;
        // 对每个 left，找最大可能得 right
        int right = 0;
        int max_w = -1;
        for(int left = 0; left < n; ++left)
        {
            while(right < n && cur_sum < t)
                cur_sum += nums[right++];
            if(cur_sum == t)
                max_w = max(max_w, right - left);
            cur_sum -= nums[left];
        }
        if(max_w == -1)
            return -1;
        return n - max_w;
    }
};
