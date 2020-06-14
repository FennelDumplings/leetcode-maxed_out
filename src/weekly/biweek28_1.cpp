// 20200613
// 1. 商品折扣后的最终价格

/*
 * 给你一个数组 prices ，其中 prices[i] 是商店里第 i 件商品的价格。
 * 商店里正在进行促销活动，如果你要买第 i 件商品，那么你可以得到与 prices[j] 相等的折扣，其中 j 是满足 j > i 且 prices[j] <= prices[i] 的 最小下标 ，如果没有满足条件的 j ，你将没有任何折扣。
 * 请你返回一个数组，数组中第 i 个元素是折扣后你购买商品 i 最终需要支付的价格。
 */

#include <vector>

using namespace std;

// 暴力
class Solution {
public:
    vector<int> finalPrices(vector<int>& prices) {
        int n = prices.size();
        vector<int> result(n, -1);
        result[n - 1] = prices[n - 1];
        for(int i = 0; i < n - 1; ++i)
        {
            int d = 0;
            for(int j = i + 1; j < n; ++j)
            {
                if(prices[j] <= prices[i])
                {
                    d = prices[j];
                    break;
                }
            }
            result[i] = prices[i] - d;
        }
        return result;
    }
};
