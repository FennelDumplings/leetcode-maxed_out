// prob879: Profitable Schemes

/*
 * https://leetcode-cn.com/problems/profitable-schemes/
 */

#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>

using namespace std;

// 优化过程
// 1. 加 remain (k 的剪枝)
// 2. 改传结构体数组
// 3. 加 sort (上一步用结构体也是为了方便这一步) (提升明显，约一倍)
// 4. 加 j == 0 的判断
// 5. 改成 int[][][] 加 memset (提升明显，约一倍)
struct Item
{
    int p, g;
    Item(int p, int g):p(p),g(g){}
};

struct Cmp
{
    bool operator()(const Item& i1, const Item& i2) const
    {
        return i1.p > i2.p;
    }
};

class Solution {
public:
    int profitableSchemes(int G, int P, vector<int>& group, vector<int>& profit) {
        int n = profit.size();
        // dp[i][j][k] := 剩余[i..n - 1], G = j, P = k 方案数
        vector<Item> items;
        for(int i = 0; i < n; ++i)
            items.push_back(Item(profit[i], group[i]));
        sort(items.begin(), items.end(), Cmp());
        vector<int> remain(n, 0); // [i..n-1] 剩余的总利润
        remain[n - 1] = items[n - 1].p;
        for(int i = n - 2; i >= 0; --i)
            remain[i] = remain[i + 1] + items[i].p;
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(G + 1, vector<int>(P + 1, -1)));
        return solve(0, G, P, items, dp, remain);
    }

private:
    const int MOD = 1e9 + 7;
    using ll = long long;

    int solve(int i, int j, int k, const vector<Item>& items,
            vector<vector<vector<int>>>& dp, const vector<int>& remain)
    {
        if(dp[i][j][k] != -1)
            return dp[i][j][k];

        int n = items.size();
        if(i == n - 1)
        {
            dp[i][j][k] = 0;
            if(k == 0) ++dp[i][j][k];
            if(items[i].p < k || items[i].g > j)
                return dp[i][j][k];
            else
                return ++dp[i][j][k];
        }

        if(remain[i] < k)
            return dp[i][j][k] = 0;

        if(j == 0)
        {
            if(k == 0)
                return dp[i][j][k] = 1;
            else
                return dp[i][j][k] = 0;
        }

        dp[i][j][k] = solve(i + 1, j, k, items, dp, remain);
        if(j >= items[i].g)
            dp[i][j][k] = ((ll)dp[i][j][k] + solve(i + 1, max(0, j - items[i].g), max(0, k - items[i].p), items, dp, remain)) % MOD;
        return dp[i][j][k];
    }
};
