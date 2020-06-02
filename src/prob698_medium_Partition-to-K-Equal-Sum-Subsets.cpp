// prob698: Partition to K Equal Sum Subsets

/*
 * Given an array of integers nums and a positive integer k, find whether it's possible to divide this array into k non-empty subsets whose sums are all equal.
 */

/*
 * Example 1:
 * Input: nums = [4, 3, 2, 3, 5, 2, 1], k = 4
 * Output: True
 * Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
 */

/*
 * Note:
 * 1 <= k <= len(nums) <= 16.
 * 0 < nums[i] < 10000.
 */

#include <vector>
#include <climits>
#include <algorithm>
#include <functional>

using namespace std;

class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = 0;
        int maxx = 0;
        for(int num: nums)
        {
            sum += num;
            maxx = max(maxx, num);
        }
        if(sum % k != 0) return false;
        int block = sum / k;
        if(maxx > block) return false;
        vector<bool> visited((int)nums.size(), false);
        sort(nums.begin(), nums.end(), greater<int>());
        return dfs(nums, visited, 0, block, k);
    }

private:
    bool dfs(const vector<int>& nums, vector<bool>& visited, int cur, int block, int k)
    {
        if(k == 0)
            return true;

        int n = nums.size();
        for(int i = 0; i < n; ++i)
        {
            if(visited[i]) continue;
            int nxt = cur + nums[i];
            if(nxt > block)
                continue;
            visited[i] = true;
            if(nxt < block)
                if(dfs(nums, visited, nxt, block, k))
                    return true;
            if(nxt == block)
                if(dfs(nums, visited, 0, block, k - 1))
                    return true;
            visited[i] = false;
        }
        return false;
    }
};
