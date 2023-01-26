// prob1175: Prime Arrangements

/*
 * https://leetcode-cn.com/problems/prime-arrangements/
 */

#include <vector>

using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;

int fac(int n, int p)
{
    ll ans = 1;
    for(ll i = 1; i <= n; ++i)
        ans = (ans * i) % p;
    return ans;
}

class Solution {
public:
    int numPrimeArrangements(int n) {
        int N_prime = prime(n);
        int ans = (fac(N_prime, MOD) * (ll)fac(n - N_prime, MOD)) % MOD;
        return ans;
    }

private:
    int prime(int n)
    {
        int cnt = 0;
        vector<bool> vec(n + 1, false);
        for(int i = 2; i <= n; ++i)
        {
            if(vec[i]) continue;
            ++cnt;
            for(int j = i * 2; j <= n; j += i)
                vec[j] = true;
        }
        return cnt;
    }
};
