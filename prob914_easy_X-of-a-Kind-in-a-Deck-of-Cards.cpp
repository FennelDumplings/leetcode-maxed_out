// prob914: X of a Kind in a Deck of Cards

/*
 * In a deck of cards, each card has an integer written on it.
 * Return true if and only if you can choose X >= 2 such that it is possible to split the entire deck into 1 or more groups of cards, where:
 * Each group has exactly X cards.
 * All the cards in each group have the same integer.
 */

/*
 * Constraints:
 * 1 <= deck.length <= 10^4
 * 0 <= deck[i] < 10^4
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    bool hasGroupsSizeX(vector<int>& deck) {
        int n = deck.size();
        if(n == 1) return false;
        vector<int> cnt(1e4, 0);
        for(int num: deck)
            ++cnt[num];
        vector<int> vec;
        for(int i: cnt)
        {
            if(i != 0)
                vec.push_back(i);
        }
        int m = vec.size();
        if(m == 1) return true;
        int min_gcd = gcd(vec[0], vec[1]);
        if(min_gcd < 2) return false;
        for(int i = 2; i < m; ++i)
        {
            min_gcd = gcd(min_gcd, vec[i]);
            if(min_gcd < 2)
                return false;
        }
        return true;
    }

private:
    int gcd(int x, int y)
    {
        return x == 0 ? y : gcd(y % x, x);
    }
};

// 素数筛
class Solution_2 {
public:
    bool hasGroupsSizeX(vector<int>& deck) {
        int n = deck.size();
        if(n == 1) return false;
        vector<int> cnt(1e4, 0);
        for(int num: deck)
            ++cnt[num];
        vector<int> vec;
        int minx = INT_MAX;
        for(int i: cnt)
        {
            if(i != 0)
                vec.push_back(i);
            if(i > 0)
                minx = min(minx, i);
        }
        vector<int> primes = _prime_sieve(minx);
        for(int prime: primes)
        {
            bool flag = true;
            for(int num: vec)
                if(num % prime != 0)
                {
                    flag = false;
                    break;
                }
            if(flag) return true;
        }
        return false;
    }

private:
    vector<int> _prime_sieve(int N)
    {
        // <= N 的素数
        //标记数组，如果mark[i] == false 且 i>=2，则认为 i 是素数。初始时假设都是素数
        vector<bool> mark(N + 1, 0);
        vector<int> primes; //用来存储素数的容器
        for(int i = 2; i <= N; i++)
        {
            if(mark[i]) continue; //i 已经被标记为不是素数了，continue
            primes.push_back(i); //i是一个素数，放进容器。
            for(int j = i + i; j <= N; j += i) //筛掉所有能被i整除的数字。
                mark[j] = true;
        }
        return primes;
    }
};
