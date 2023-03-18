class Solution {
public:
    vector<int> answerQueries(vector<int>& nums, vector<int>& queries) {
        // 排序 + 贪心 + 前缀和 + 二分
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<int> sums(n + 1);
        for(int i = 1; i <= n; ++i)
            sums[i] = sums[i - 1] + nums[i - 1];
        int m = queries.size();
        vector<int> result(m);
        for(int i = 0; i < m; ++i)
        {
            // sums 中小于等于 queries[i] 的最大值
            auto iter = upper_bound(sums.begin(), sums.end(), queries[i]);
            result[i] = iter - sums.begin() - 1;
        }
        return result;
    }
};
