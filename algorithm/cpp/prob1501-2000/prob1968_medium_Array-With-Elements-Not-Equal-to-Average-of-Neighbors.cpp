class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = nums.size();
        nth_element(nums.begin(), nums.begin() + n / 2, nums.end());
        vector<int> result(n);
        for(int i = 0; i < (n + 1) / 2; ++i)
            result[i * 2] = nums[i];
        for(int i = (n + 1) / 2, j = 0; i < n; ++i, ++j)
            result[j * 2 + 1] = nums[i];
        return result;
    }
};
