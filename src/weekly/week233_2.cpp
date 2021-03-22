
#include <vector>
#include <functional>
#include <map>

using namespace std;

class Solution {
public:
    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        using ll = long long;
        const int MOD = 1e9 + 7;
        map<int, ll> sell_map;
        map<int, ll, greater<int>> buy_map;
        for(const vector<int> &order: orders)
        {
            int type = order[2];
            ll amount = order[1];
            int price = order[0];
            if(type == 0)
            {
                // 采购订单
                auto it = sell_map.begin();
                while(it != sell_map.end() && amount > 0 && (it -> first) <= price)
                {
                    if(amount < it -> second)
                    {
                        // amount 清空，且 sell_map 中当前价格的订单有剩余
                        it -> second -= amount;
                        amount = 0;
                    }
                    else
                    {
                        // sell_map 中当前价格的订单清空
                        amount -= it -> second;
                        it = sell_map.erase(it);
                    }
                }
                if(amount > 0)
                {
                    buy_map[price] += amount;
                }
            }
            else
            {
                // 销售订单
                auto it = buy_map.begin();
                while(it != buy_map.end() && amount > 0 && (it -> first) >= price)
                {
                    if(amount < it -> second)
                    {
                        // amount 清空，且 buy_map 中当前价格的订单有剩余
                        it -> second -= amount;
                        amount = 0;
                    }
                    else
                    {
                        // buy_map 中当前价格的订单清空
                        amount -= it -> second;
                        it = buy_map.erase(it);
                    }
                }
                if(amount > 0)
                {
                    sell_map[price] += amount;
                }
            }
        }
        ll ans = 0;
        for(auto order: sell_map)
            ans += order.second;
        for(auto order: buy_map)
            ans += order.second;
        return ans % MOD;
    }
};
