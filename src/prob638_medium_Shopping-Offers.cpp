// prob638: Shopping Offers

/*
 * In LeetCode Store, there are some kinds of items to sell. Each item has a price.
 * However, there are some special offers, and a special offer consists of one or more different kinds of items with a sale price.
 * You are given the each item's price, a set of special offers, and the number we need to buy for each item. The job is to output the lowest price you have to pay for exactly certain items as given, where you could make optimal use of the special offers.
 * Each special offer is represented in the form of an array, the last number represents the price you need to pay for this special offer, other numbers represents how many specific items you could get if you buy this offer.
 * You could use any of special offers as many times as you want.
 */

/*
 * Example 1:
 * Input: [2,5], [[3,0,5],[1,2,10]], [3,2]
 * Output: 14
 * Explanation:
 * There are two kinds of items, A and B. Their prices are $2 and $5 respectively.
 * In special offer 1, you can pay $5 for 3A and 0B
 * In special offer 2, you can pay $10 for 1A and 2B.
 * You need to buy 3A and 2B, so you may pay $10 for 1A and 2B (special offer #2), and $4 for 2A.
 * Example 2:
 * Input: [2,3,4], [[1,1,0,4],[2,2,1,9]], [1,2,1]
 * Output: 11
 * Explanation:
 * The price of A is $2, and $3 for B, $4 for C.
 * You may pay $4 for 1A and 1B, and $9 for 2A ,2B and 1C.
 * You need to buy 1A ,2B and 1C, so you may pay $4 for 1A and 1B (special offer #1), and $3 for 1B, $4 for 1C.
 * You cannot add more items, though only $9 for 2A ,2B and 1C.
 */

/*
 * Note:
 * There are at most 6 kinds of items, 100 special offers.
 * For each item, you need to buy at most 6 of them.
 * You are not allowed to buy more items than you want, even if that would lower the overall price.
 */

#include <set>
#include <vector>
#include <climits>
#include <unordered_map>

using namespace std;

// 完全背包 + 状态压缩， 记忆化
// 900ms
class Solution {
public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        if(needs.empty()) return 0;
        int n = needs.size();
        // state 需要 3 * n 位
        // n == 2
        // 000111111 (1 << (n * 3))
        vector<int> dp((1 << (n * 3)), -1);
        dp[0] = 0;
        unordered_map<int, int> valid;
        for(int i = 0; i < n; ++i)
            valid[(1 << (i * 3))] = price[i];
        for(const vector<int>& bag: special)
        {
            int val = bag[n];
            int state = 0;
            for(int i = 0; i < n; ++i)
            {
                int item_state = bag[i]; // 0 ~ 6
                state |= (item_state << (i * 3));
            }
            if(valid.count(state) == 0)
                valid[state] = val;
            else
                valid[state] = min(valid[state], val);
        }
        int target_state = 0;
        for(int i = 0; i < n; ++i)
        {
            int item_state = needs[i];
            target_state |= (item_state << (i * 3));
        }
        return solve(target_state, valid, dp, n);
    }

private:
    int solve(int state, unordered_map<int, int>& valid, vector<int>& dp, int n)
    {
        if(dp[state] != -1)
            return dp[state];

        dp[state] = INT_MAX;
        for(pair<int, int> select: valid)
        {
            int s = select.first;
            int nxt = next_state(state, s, n);
            if(nxt == -1) continue;
            int val = select.second;
                dp[state] = min(dp[state], val + solve(nxt, valid, dp, n));
        }
        return dp[state];
    }

    int next_state(int state, int cur, int n)
    {
        for(int i = 0; i < n; ++i)
        {
            // 000...00111 向右整体移 i * 3 位
            int cnt1 = (7 << i * 3) & state;
            int cnt2 = (7 << (i * 3)) & cur;
            if(cnt1 < cnt2)
                return -1;
        }
        return state - cur;
    }
};

// 迭代
// TLE
class Solution_2 {
public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        if(needs.empty()) return 0;
        int n = needs.size();
        // state 需要 3 * n 位
        // n == 2
        // 000111111 (1 << (n * 3))
        vector<int> dp((1 << (n * 3)), INT_MAX);
        dp[0] = 0;
        // v 是背包容量
        int v = 0;
        for(int i = 0; i < n; ++i)
        {
            int item_state = needs[i];
            v |= (item_state << (i * 3));
        }
        for(int i = 0; i < n; ++i)
        {
            vector<int> t(n + 1);
            t[i] = 1;
            t[n] = price[i];
            special.push_back(t);
        }
        vector<vector<int>> &w = special; // 物品及对应的价值(负价值)
        int m = w.size(); // 物品个数
        for(int i = 0; i < m; ++i) // 枚举物品
        {
            for(int state = 0; state <= v; ++state) // 枚举此前已选物品(枚举背包容量)
            {
                bool flag = true;
                // 判断 state 下选 i 是否合法
                for(int k = 0; k < n; ++k)
                {
                    if((((state >> (k * 3)) & 0x07) + w[i][k]) > ((v >> (k * 3)) & 0x07))
                    {
                        flag = false;
                        break;
                    }
                }
                if(flag)
                {
                    int s = 0; // 所选 i 对应的状态
                    for(int k = 0; k < n; ++k)
                        s |= w[i][k] << (3 * k);
                    dp[s + state] = min(dp[s + state], dp[state] + w[i][n]);
                }
            }
        }
        return dp[v];
    }
};


