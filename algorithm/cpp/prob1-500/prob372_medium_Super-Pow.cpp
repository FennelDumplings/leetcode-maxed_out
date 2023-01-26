// prob372: Super Pow

/*
 * Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
 * You may assume that the intervals were initially sorted according to their start times.
 */

/*
 * Example 1:
 * Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
 * Output: [[1,5],[6,9]]
 * Example 2:
 * Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
 * Output: [[1,2],[3,10],[12,16]]
 * Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
 */

/*
 * NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.
 */

#include <vector>

using namespace std;

class Solution_2 {
public:
    int superPow(int a, vector<int>& b) {
        // a > 0, b > 0
        int len = b.size();
        int ans = 1;
        a %= M;
        for(int i = len - 1; i >= 0; --i)
        {
            if(b[i] != 0)
                ans = (ans * _power(a, b[i])) % M;
            a = _power10(a);
        }
        return ans;
    }

private:
    const int M = 1337;

    int _power10(int a)
    {
        int n = 10;
        int ans = 1;
        while(n)
        {
            if(n & 1)
                ans = (ans * a) % M;
            a = (a * a) % M;
            n >>= 1;
        }
        return ans;
    }

    int _power(int a, int n)
    {
        int ans = 1;
        while(n)
        {
            if(n & 1)
                ans = (ans * a) % M;
            a = (a * a) % M;
            n >>= 1;
        }
        return ans;
    }
};


//---------------------------------------------------



vector<int> get_phi(int n)
{
    if(n < 2) return {};
    vector<bool> vec(n, true);
    vec[0] = false;
    vec[1] = false;
    int cnt = 0;
    vector<int> primes;
    vector<int> phi(n, -1);
    phi[1] = 1;
    for(int i = 2; i < n; ++i)
    {
        if(vec[i])
        {
            ++cnt;
            phi[i] = i - 1; // 性质2
            primes.push_back(i);
        }
        for(int j = 0; j < cnt && i * primes[j] < n; ++j)
        {
            vec[i * primes[j]] = false;
            if(i % primes[j] == 0)
            {
                phi[i * primes[j]] = phi[i] * primes[j]; // 性质4
                break;
            }
            else
                phi[i * primes[j]] = phi[i] * (primes[j] - 1); // 性质1: 积性函数
        }
    }
    return phi;
}

class Solution {
public:
    int superPow(int a, vector<int>& b) {
        const int M = 1337;
        int phi = get_phi(M + 1)[M];
        int numB = b[0]; // 从高位开始
        a = a % M;
        if(a == 0) return 0;
        for(int i = 1; i < (int)b.size(); ++i)
            numB = (numB * 10 + b[i]) % phi;
        numB += phi;
        int x = a;
        for(int j = 0; j < numB; ++j)
        {
            x = x % M;
            x *= a;
        }
        x /= a;
        return x;
    }
};
