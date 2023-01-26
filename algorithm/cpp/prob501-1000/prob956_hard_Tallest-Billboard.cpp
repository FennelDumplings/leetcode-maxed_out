// prob956: Tallest Billboard

/*
 * https://leetcode-cn.com/problems/tallest-billboard/
 */

#include <vector>
#include <unordered_set>
#include <algorithm>
#include <functional>
#include <cmath>
#include <climits>

using namespace std;

// 自己的 DFS 加剪枝
// TLE
class Solution {
public:
    int tallestBillboard(vector<int>& rods) {
        int n = rods.size();
        if(n < 2) return 0;
        sort(rods.begin(), rods.end(), greater<int>());
        for(int i: rods) L += i;
        int ans = 0;
        dfs(0, 0, rods, 0, ans);
        return ans;
    }

private:
    int L;
    void dfs(int pos, int state, const vector<int>& rods, int len, int& ans)
    {
        if(len > L / 2) return;
        int n = rods.size();
        if(pos == n) return;
        int sum = 0;
        unordered_set<int> sums({0});
        for(int i = 0; i < n; ++i)
        {
            if((state >> i) & 1) continue;
            int cur = rods[i];
            sum += cur;
            int target = sum - len;
            if(sums.count(target) > 0)
                ans = max(ans, len);
            else
                sums.insert(sum);
        }
        dfs(pos + 1, state, rods, len, ans);
        dfs(pos + 1, (state | (1 << pos)), rods, len + rods[pos], ans);
    }
};


// 别人的 DFS + 剪枝
// 20ms
class Solution_2 {
private:
    int maxheight;
public:
    int tallestBillboard(vector<int>& rods) {
        if(rods.size() < 2){
            return 0;
        }
        int sum = 0;
        for(auto &i : rods){
            sum += i;
        }
        maxheight = 0;
        //从大到小排序,这样这样24行支剪就会尽快发生,否则超时
        sort(rods.begin(), rods.end(), greater<int>());
        //左右都一样，不妨就从左开始，省略向右的
        dfs(rods, 0, rods[0], 0, sum - rods[0]);
        dfs(rods, 0, 0, 0, sum - rods[0]);
        return maxheight;
    }

    void dfs(vector<int> &rods, int index, int left, int right, int remain){
        //剪去剩下的不足以使得左右对齐分支和对齐发生后不再增加左右高度38行的分支
        if(abs(left - right) > remain || left + right + remain <= maxheight * 2){
            return;
        }
        if(left == right){
            maxheight = max(maxheight, left);
        }
        //这里先增加index后判断边界,于是首次index参数为0
        index++;
        if(index == (int)rods.size()){
            return;
        }
        remain -= rods[index];
        dfs(rods, index, left + rods[index], right, remain);
        dfs(rods, index, left, right + rods[index], remain);
        dfs(rods, index, left, right, remain);
    }
};

// 改进后的 DFS + 剪枝
class Solution_3 {
public:
    int tallestBillboard(vector<int>& rods) {
        int n = rods.size();
        if(n < 2) return 0;
        sort(rods.begin(), rods.end(), greater<int>());
        int remain = 0;
        for(int i: rods) remain += i;
        int ans = 0;
        dfs(0, 0, 0, remain, ans, rods);
        return ans;
    }

private:
    void dfs(int lh, int rh, int pos, int remain, int& ans, const vector<int>& rods)
    {
        int n = rods.size();
        if(lh == rh)
            ans = max(ans, lh);
        if(pos == n)
            return;
        if(abs(lh - rh) > remain)
            return;
        if(lh + rh + remain <= ans * 2)
            return;
        dfs(lh + rods[pos], rh, pos + 1, remain - rods[pos], ans, rods);
        dfs(lh, rh + rods[pos], pos + 1, remain - rods[pos], ans, rods);
        dfs(lh, rh, pos + 1, remain - rods[pos], ans, rods);
    }
};

// 动态规划
class Solution_4 {
public:
    int tallestBillboard(vector<int>& rods) {
        int n = rods.size();
        if(n < 2) return 0;
        int max_sum = 0;
        for(int i: rods) max_sum += i;
        vector<vector<int>> dp(n + 1, vector<int>(max_sum + 1, INT_MIN));
        dp[0][0] = 0;
        int sum = 0;
        for(int i = 1; i <= n; ++i)
        {
            int h = rods[i - 1];
            sum += h;
            for(int j = 0; j <= max_sum; ++j)
            {
                // h 未选
                dp[i][j] = max(dp[i][j], dp[i - 1][j]);
                // h 放长
                if(j + h < max_sum)
                    dp[i][j + h] = max(dp[i][j + h], dp[i - 1][j]);
                // h 放短
                dp[i][abs(j - h)] = max(dp[i][abs(j - h)], dp[i - 1][j] + min(j, h));
            }
        }
        return dp[n][0];
    }
};
