// prob1049: Last Stone Weight II

/*
 * https://leetcode-cn.com/problems/last-stone-weight-ii/
 */

#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int W = 0;
        for(int i: stones) W += i;
        int target = W / 2;
        // 选，使得和 小于等于 target 同时尽可能接近 target
        set<int> setting({0}); // [0..i] 中所有小于等于 target 的和
        for(int cur: stones)
        {
            vector<int> addition;
            for(int sum: setting)
            {
                if(sum + cur <= target)
                    addition.push_back(sum + cur);
            }
            for(int a: addition)
                setting.insert(a);
        }
        int sum = *setting.rbegin();
        return W - 2 * sum;
    }
};


// 01背包
class Solution_2 {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int W = 0;
        for(int i: stones) W += i;
        int target = W / 2;
        // 使得和 小于等于 target 同时尽可能接近 target
        vector<int> &v = stones; // 物品体积
        int &V = target; // 背包容量
        int n = v.size();
        // dp[i][j] := 考虑前 i 件中，容量为 j，能取到的最大体积
        vector<vector<int>> dp(n + 1, vector<int>(V + 1, 0));
        for(int i = 1; i <= n; ++i)
            for(int j = V; j >= 0; --j)
            {
                dp[i][j] = dp[i - 1][j]; // 不选 i
                if(j - v[i - 1] >= 0) // 选 i
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - v[i - 1]] + v[i - 1]);
            }
        return W - 2 * dp[n][V];
    }
};
