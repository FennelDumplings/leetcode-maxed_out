// prob373: 373. Find K Pairs with Smallest Sums

/*
 * https://leetcode-cn.com/problems/find-k-pairs-with-smallest-sums/
 */

#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

struct State
{
    int i, j;
    int v;
    State(int i, int j, int v):i(i),j(j),v(v){}
};

struct HeapCmp
{
    bool operator()(const State& s1, const State& s2) const
    {
        return s1.v > s2.v;
    }
};

using ll = long long;
const int MOD = 1e9 + 7;
const int p = 12739;

struct MyHash
{
    int operator()(const State& s) const
    {
        int ans = 0;
        ans = (ans + s.i) % MOD;
        ans = ans * (ll)p % MOD;
        ans = (ans + s.j) % MOD;
        ans = ans * (ll)p % MOD;
        ans = (ans + s.v) % MOD;
        return ans;
    }
};

struct MyCmp
{
    bool operator()(const State& s1, const State& s2) const
    {
        return s1.v == s2.v && s1.i == s2.i && s1.j == s2.j;
    }
};

class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        if(n1 == 0 || n2 == 0)
            return {};
        priority_queue<State, vector<State>, HeapCmp> pq;
        State start(0, 0, nums1[1] + nums2[0]);
        pq.push(start);
        vector<vector<int>> result;
        unordered_set<State, MyHash, MyCmp> setting;
        setting.insert(start);
        int iter = 0;
        while(!pq.empty())
        {
            State s = pq.top();
            pq.pop();
            result.push_back({nums1[s.i], nums2[s.j]});
            ++iter;
            if(iter == k)
                break;
            if(s.i + 1 < n1)
            {
                State nxt1(s.i + 1, s.j, nums1[s.i + 1] + nums2[s.j]);
                if(setting.count(nxt1) == 0)
                {
                    pq.push(nxt1);
                    setting.insert(nxt1);
                }
            }
            if(s.j + 1 < n2)
            {
                State nxt2(s.i, s.j + 1, nums1[s.i] + nums2[s.j + 1]);
                if(setting.count(nxt2) == 0)
                {
                    pq.push(nxt2);
                    setting.insert(nxt2);
                }
            }
        }
        return result;
    }
};
