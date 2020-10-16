
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

using ll = long long;
const int MOD = 1e9 + 7;

struct State
{
    int s;
    int n;
    State(const int& s, int n):s(s),n(n){}
};

int get_state(const vector<int>& cnt)
{
    int base = 27;
    int ans = 0;
    for(int i: cnt)
    {
        ans *= base;
        ans += i;
    }
    return ans;
}

struct MyCmp
{
    bool operator()(const State& s1, const State& s2) const
    {
        return s1.s == s2.s && s1.n == s2.n;
    }
};

struct MyHash
{
    int operator()(const State& s) const
    {
        return s.n * (ll)s.s % MOD;
    }
};

int get_digit(int s, int i, int K)
{
    i = K - i;
    int base = 27;
    while(i)
    {
        s /= base;
        --i;
    }
    return s % base;
}

int change_digit(int s, int i, int delta, int K)
{
    int base = 27;
    s += delta * (int)pow(base, K - i);
    return s;
}

class Solution {
public:
    int keyboard(int k, int n) {
        dp = unordered_map<State, int, MyHash, MyCmp>();
        vector<int> cnt(k + 1, 0);
        cnt[k] = 26;
        K = k;
        State start(get_state(cnt), n);
        return solve(start);
    }

private:
    int K;
    unordered_map<State, int, MyHash, MyCmp> dp;

    int solve(State& s)
    {
        if(dp.count(s))
        {
            return dp[s];
        }
        if(s.n == 0)
            return 1;
        int ans = 0;
        for(int k = 1; k <= K; ++k)
        {
            // s.cnt[k] := 当前剩余 k 次的键的个数
            int choose = get_digit(s.s, k, K);
            if(choose == 0)
                continue;
            State nxt = s;
            nxt.s = change_digit(nxt.s, k, -1, K);
            nxt.s = change_digit(nxt.s, k - 1, 1, K);
            --nxt.n;
            int tmp = solve(nxt);
            ans = (ans + (ll)choose * tmp) % MOD;
        }
        return dp[s] = ans;
    }
};
