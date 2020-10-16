
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;

struct State
{
    vector<int> cnt;
    int n;
    State(const vector<int>& cnt, int n):cnt(cnt),n(n){}
};

struct MyCmp
{
    bool operator()(const State& s1, const State& s2) const
    {
        if(s1.n != s2.n)
            return false;
        int k = s1.cnt.size();
        for(int i = 0; i < k; ++i)
            if(s1.cnt[i] != s2.cnt[i])
                return false;
        return true;
    }
};

struct MyHash
{
    int operator()(const State& s) const
    {
        int base = 27;
        int ans = 1;
        for(int i: s.cnt)
        {
            ans *= base;
            ans += i;
        }
        ans = (ll)ans * s.n;
        return ans;
    }
};

class Solution {
public:
    int keyboard(int k, int n) {
        dp = unordered_map<State, int, MyHash, MyCmp>();
        vector<int> cnt(k + 1, 0);
        cnt[k] = 26;
        State start(cnt, n);
        return solve(start);
    }

private:
    unordered_map<State, int, MyHash, MyCmp> dp;

    int solve(State& s)
    {
        if(dp.count(s))
        {
            return dp[s];
        }
        if(s.n == 0)
            return 1;
        int K = s.cnt.size();
        int ans = 0;
        for(int k = 1; k < K; ++k)
        {
            // s.cnt[k] := 当前剩余 k 次的键的个数
            if(s.cnt[k] == 0) continue;
            int choose = s.cnt[k];
            --s.cnt[k];
            ++s.cnt[k - 1];
            --s.n;
            int tmp = solve(s);
            ++s.n;
            --s.cnt[k - 1];
            ++s.cnt[k];
            ans = (ans + (ll)choose * tmp) % MOD;
        }
        return dp[s] = ans;
    }
};
