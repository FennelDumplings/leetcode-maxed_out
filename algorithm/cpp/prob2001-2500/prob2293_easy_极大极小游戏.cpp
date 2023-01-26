class Solution {
public:
    int minMaxGame(vector<int>& nums) {
        int n = nums.size();
        vector<int> tmp(n);
        while(n > 1)
        {
            for(int i = 0; i < n / 2; ++i)
            {
                if(i & 1)
                {
                    tmp[i] = max(nums[2 * i], nums[2 * i + 1]);
                }
                else
                {
                    tmp[i] = min(nums[2 * i], nums[2 * i + 1]);
                }
            }
            swap(nums, tmp);
            n /= 2;
        }
        return nums[0];
    }
};
