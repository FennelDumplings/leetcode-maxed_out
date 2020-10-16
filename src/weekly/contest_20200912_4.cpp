
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int busRapidTransit(int target, int inc, int dec, vector<int>& jump, vector<int>& cost) {
        mapping = unordered_map<int, ll>();
        ll min_cost = -1;
        ll deep = 0;
        solve(1, target, inc, dec, jump, cost, min_cost, inc, deep);
        return min_cost % MOD;
    }

private:
    using ll = long long;
    const int MOD = 1e9 + 7;
    unordered_map<int, ll> mapping;
    const int max_deep = 10000;

    void solve(ll j, const int target, const int inc, const int dec, const vector<int>& jump, const vector<int>& cost, ll& min_cost, ll pre_cost, ll deep)
    {
        if(deep > max_deep)
            return;
        if(j == target)
        {
            if(mapping.count(j) == 0)
                mapping[j] = 0;
            if(min_cost == -1)
                min_cost = pre_cost;
            else
                min_cost = min(min_cost, pre_cost);
            return;
        }
        if(j > target)
        {
            if(mapping.count(j) == 0)
                mapping[j] = dec * (j - target);
            if(min_cost == -1)
                min_cost = pre_cost + mapping[j];
            else
                min_cost = min(min_cost, pre_cost + mapping[j]);
            return;
        }
        // 1 <= j < target
        // if(mapping.count(j) > 0 && mapping[j] != -1)
        if(mapping.count(j) > 0 && mapping[j] != -1)
        {
            min_cost = min(min_cost, pre_cost + mapping[j]);
            return;
        }
        int m = jump.size();
        mapping[j] = -1;
        ll &ans = mapping[j];
        for(int i = 0; i < m; ++i)
        {
            ll nxt = j * jump[i];
            if(min_cost != -1 && pre_cost + cost[i] >= min_cost)
                continue;
            solve(nxt, target, inc, dec, jump, cost, min_cost, pre_cost + cost[i], deep + 1);
            if(mapping[nxt] != -1)
            {
                if(ans == -1)
                    ans = cost[i] + mapping[nxt];
                else
                    ans = min(ans, cost[i] + mapping[nxt]);
            }
        }
        if(min_cost == -1 || pre_cost + inc < min_cost)
        {
            int nxt = j + 1;
            solve(nxt, target, inc, dec, jump, cost, min_cost, pre_cost + inc, deep + 1);
            if(mapping[nxt] != -1)
            {
                if(ans == -1)
                    ans = inc + mapping[nxt];
                else
                    ans = min(ans, inc + mapping[nxt]);
            }
        }
        if(j > 1 && (min_cost == -1 || pre_cost + dec < min_cost))
        {
            int nxt = j - 1;
            solve(nxt, target, inc, dec, jump, cost, min_cost, pre_cost + dec, deep + 1);
            if(mapping[nxt] != -1)
            {
                if(ans == -1)
                    ans = dec + mapping[nxt];
                else
                    ans = min(ans, dec + mapping[nxt]);
            }
        }
    }
};
