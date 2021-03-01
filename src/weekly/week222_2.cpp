
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int countPairs(vector<int>& deliciousness) {
        const int MOD = 1e9 + 7;
        using ll = long long;
        sort(deliciousness.begin(), deliciousness.end());
        int n = deliciousness.size();
        if(n <= 1)
            return 0;
        int minx = deliciousness[0] + deliciousness[1];
        int maxx = deliciousness[n - 2] + deliciousness[n - 1];
        vector<int> targets;
        int p = 0;
        int iter = 1;
        while(iter <= maxx)
        {
            if(iter >= minx)
                targets.push_back(iter);
            ++p;
            iter *= 2;
        }
        unordered_map<int, int> mapping;
        for(int d: deliciousness)
            ++mapping[d];
        ll ans = 0;
        for(auto item: mapping)
        {
            int d = item.first;
            for(int t: targets)
            {
                if(t - d == d)
                    ans = ans + mapping[t - d] * ((ll)mapping[t - d] - 1);
                else
                    ans = ans + mapping[t - d] * (ll)mapping[d];
            }
        }
        return (ans / 2) % MOD;
    }
};
