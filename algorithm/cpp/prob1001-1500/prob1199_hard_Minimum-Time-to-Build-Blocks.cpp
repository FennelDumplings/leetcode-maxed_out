// prob1199: Minimum Time to Build Blocks

/*
 * https://leetcode-cn.com/problems/minimum-time-to-build-blocks/
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;


class Solution1 {
public:
    int minBuildTime(vector<int>& blocks, int split) {
        int n = blocks.size();
        blocks.push_back(-1);
        sort(blocks.begin(), blocks.end());
        dp = vector<vector<int>>(n + 1, vector<int>(n + 1, -1));
        return solve(blocks, split, n, 1);
    }

private:
    vector<vector<int>> dp;

    int solve(const vector<int>& blocks, const int split, int i, int k)
    {
        // blocks[1..i] 共 i 个街区，k 个人 k <= i
        if(dp[i][k] != -1)
            return dp[i][k];

        dp[i][k] = blocks[i];
        if(i == k) return dp[i][k];

        // k < i
        // 取 j 个人分裂，k - j 个人干活，同时需要满足 j * 2 + k - j < i
        int minx = INT_MAX / 2;
        for(int j = 1; j <= k && (j * 2 <= i - (k - j)); ++j)
        {
            minx = min(minx, split + solve(blocks, split, i - (k - j), j * 2));
        }
        dp[i][k] = max(dp[i][k], minx);
        return dp[i][k];
    }
};


// 剪枝
class Solution_2 {
public:
    int minBuildTime(vector<int>& blocks, int split) {
        int n = blocks.size();
        blocks.push_back(-1);
        sort(blocks.begin(), blocks.end());
        dp = vector<vector<int>>(n + 1, vector<int>(n + 1, -1));
        return solve(blocks, split, n, 1);
    }

private:
    vector<vector<int>> dp;

    int solve(const vector<int>& blocks, const int split, int i, int k)
    {
        // blocks[1..i] 共 i 个街区，k 个人 k <= i
        if(dp[i][k] != -1)
            return dp[i][k];

        if(i == k) return dp[i][k] = blocks[i];

        // k < i
        // 取 j 个人分裂，k - j 个人干活，同时需要满足 j * 2 + k - j < i
        dp[i][k] = INT_MAX / 2;
        // for(int j = 1; j <= k && (j * 2 <= i - (k - j)); ++j)
        for(int j = min(k, i - k); j >= 1; j >>= 1)
        {
            int tmp = max(split + solve(blocks, split, i - (k - j), j * 2), blocks[i]);
            // j 的枚举方式已经以下剪枝
            if(tmp < dp[i][k])
                dp[i][k] = tmp;
            else
                break;
        }
        return dp[i][k];
    }
};


#include <queue>
#include <functional>

class Solution {
public:
    int minBuildTime(vector<int>& blocks, int split) {
        priority_queue<int, vector<int>, greater<int>> pq;
        for(int i: blocks)
            pq.push(i);
        while((int)pq.size() > 1)
        {
            int ai = pq.top();
            pq.pop();
            int aj = pq.top();
            pq.pop();
            int fa = split + max(ai, aj);
            pq.push(fa);
        }
        return pq.top();
    }
};
