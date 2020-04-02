// prob416: Partition Equal Subset Sum

/*
 * Given a non-empty array containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.
 */

/*
 * Note:
 * Each of the array element will not exceed 100.
 * The array size will not exceed 200.
 */

/*
 * Example 1:
 * Input: [1, 5, 11, 5]
 * Output: true
 * Explanation: The array can be partitioned as [1, 5, 5] and [11].
 * Example 2:
 * Input: [1, 2, 3, 5]
 * Output: false
 * Explanation: The array cannot be partitioned into equal sum subsets.
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int N = nums.size(); // 背包问题物品数
        if(N < 2) return false;
        int V = 0;
        for(int num: nums) V += num;
        if(V & 1) return false;
        V /= 2; // 背包问题的容量
        vector<int> &v = nums; // 每个物品的体积
        vector<int> dp(V + 1, INT_MIN); // 需要体积恰好取到容量，所以要初始化为负无穷
        dp[0] = 0;
        for(int i = 0; i < N; ++i)
            for(int j = V; j >= v[i]; --j)
                dp[j] = max(dp[j], dp[j - v[i]] + 1);
        return dp[V] > 0;
    }
};
