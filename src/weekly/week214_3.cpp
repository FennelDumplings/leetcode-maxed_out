
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

using ll = long long;
const int MOD = 1e9 + 7;

struct Item
{
    ll cnt; // 个数
    ll kind; // 种类数
    Item(ll c, ll k):cnt(c),kind(k){}
};

struct HeapCmp
{
    bool operator()(const Item& i1, const Item& i2) const
    {
        return i1.cnt < i2.cnt;
    }
};

class Solution {
public:
    int maxProfit(vector<int>& inventory, int orders) {
        unordered_map<int, int> mapping; // cnt -> kinds
        for(int i: inventory)
            ++mapping[i];
        priority_queue<Item, vector<Item>, HeapCmp> pq;
        for(auto i: mapping)
            pq.push(Item(i.first, i.second));
        ll ans = 0;
        ll K = orders;
        while(K > 0)
        {
            Item cur = pq.top();
            pq.pop();
            if(pq.empty())
            {
                // 剩余选择均由 cur 提供
                ll x = K / cur.kind; // 完整的层
                // cur.kind * cur.cnt, cur.kind * (cur.cnt - 1) ... cur.kind * (cur.cnt - x + 1)
                ll y = K % cur.kind; // 最后一层的个数
                // y * (cur.cnt - x)
                ans = (ans + ((cur.kind * cur.cnt) + (cur.kind * ((ll)cur.cnt - x + 1))) * x / 2) % MOD;
                ans = (ans + y * (cur.cnt - x)) % MOD;
                K = 0;
            }
            else
            {
                Item nxt = pq.top();
                ll all = (cur.cnt - nxt.cnt) * cur.kind;
                if(all >= K)
                {
                    // 剩余选择均由 cur 提供
                    ll x = K / cur.kind; // 完整的层
                    // cur.kind * cur.cnt, cur.kind * (cur.cnt - 1) ... cur.kind * (cur.cnt - x + 1)
                    ll y = K % cur.kind; // 最后一层的个数
                    // y * (cur.cnt - x)
                    ans = (ans + ((cur.kind * cur.cnt) + (cur.kind * ((ll)cur.cnt - x + 1))) * x / 2) % MOD;
                    ans = (ans + y * (cur.cnt - x)) % MOD;
                    K = 0;
                }
                else
                {
                    ll all = (cur.cnt - nxt.cnt) * cur.kind;
                    ll x = cur.cnt - nxt.cnt;
                    ans = (ans + ((cur.kind * cur.cnt) + (cur.kind * ((ll)cur.cnt - x + 1))) * x / 2) % MOD;
                    K -= all;
                    pq.pop();
                    nxt.kind += cur.kind;
                    pq.push(nxt);
                }
            }
        }
        return ans;
    }
};
