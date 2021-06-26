// prob686:Repeated String Match

/*
 * https://leetcode-cn.com/problems/repeated-string-match/
 */

#include <cmath>
#include <string>

using namespace std;

class Solution {
public:
    int repeatedStringMatch(string a, string b) {
        int n = a.size(), m = b.size();
        ull hash_b = 0;
        for(const char ch: b)
        {
            hash_b = hash_b * p;
            hash_b = hash_b + ch;
        }
        int k = ceil((double)m / n);
        ull hash_a = 0;
        int iter = 0;
        for(int i = 0; i < m; ++i)
        {
            hash_a = hash_a * p;
            hash_a = hash_a + a[iter];
            iter = (iter + 1) % n;
        }
        if(hash_a == hash_b && check(a, 0, b))
            return k;
        int partition = n - m % n;
        if(partition == n)
            partition = 0;
        ull power = quick_pow(p, m - 1);
        for(int shift = 0; shift < partition; ++shift)
        {
            hash_a = hash_a - a[shift] * power;
            hash_a = hash_a * p;
            hash_a = hash_a + a[iter];
            iter = (iter + 1) % n;
            if(hash_a == hash_b && check(a, shift + 1, b))
                return k;
        }
        for(int shift = partition; shift < n; ++shift)
        {
            hash_a = hash_a - a[shift] * power;
            hash_a = hash_a * p;
            hash_a = hash_a + a[iter];
            iter = (iter + 1) % n;
            if(hash_a == hash_b && check(a, shift + 1, b))
                return k + 1;
        }
        return -1;
    }

private:
    using ull = unsigned long long;
    const ull p = 201326611;

    bool check(const string& a, int i, const string& b)
    {
        int n = a.size(), m = b.size();
        for(int j = 0; j < m; ++j)
        {
            if(a[i] != b[j])
                return false;
            i = (i + 1) % n;
        }
        return true;
    }

    ull quick_pow(ull x, ull n)
    {
        ull ans = 1;
        while(n)
        {
            if(n & 1)
                ans = ans * x;
            x = x * x;
            n >>= 1;
        }
        return ans;
    }
};
