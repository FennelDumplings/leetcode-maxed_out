// prob869: Reordered Power of 2

/*
 * https://leetcode-cn.com/problems/reordered-power-of-2/
 */

#include <vector>
#include <cmath>
#include <unordered_set>
#include <climits>

using namespace std;

const int MOD = 1e9 + 7;
const int p = 12739;
using ll = long long;

struct Item
{
    vector<int> cnts;
    Item(ll n)
    {
        cnts = vector<int>(10);
        while(n)
        {
            ++cnts[n % 10];
            n /= 10;
        }
    }
};

struct MyHash
{
    int operator()(const Item& i) const
    {
        int ans = 0;
        for(int j: i.cnts)
        {
            ans = (ans * (ll)p) % MOD;
            ans = (ans + (ll)j) % MOD;
        }
        return ans;
    }
};

struct MyCmp
{
    bool operator()(const Item& i1, const Item& i2) const
    {
        for(int i = 0; i < 10; ++i)
            if(i1.cnts[i] != i2.cnts[i])
                return false;
        return true;
    }
};

class Solution {
public:
    bool reorderedPowerOf2(int N) {
        unordered_set<Item, MyHash, MyCmp> mapping;
        ll MAX_P2 = 1e10;
        for(ll k = 0; pow((ll)2, (ll)k) <= MAX_P2; ++k)
        {
            Item item(pow(2, k));
            mapping.insert(item);
        }
        Item itemN(N);
        return mapping.count(itemN) > 0;
    }
};
