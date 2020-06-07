// prob271: Largest Component Size by Common Factor

/*
 * Given a non-empty array of unique positive integers A, consider the following graph:
 * There are A.length nodes, labelled A[0] to A[A.length - 1];
 * There is an edge between A[i] and A[j] if and only if A[i] and A[j] share a common factor greater than 1.
 * Return the size of the largest connected component in the graph.
 */

/*
 * Example 1:
 * Input: [4,6,15,35]
 * Output: 4
 * Example 2:
 * Input: [20,50,9,63]
 * Output: 2
 * Example 3:
 * Input: [2,3,6,7,4,12,21,39]
 * Output: 8
 */

/*
 * Note:
 * 1 <= A.length <= 20000
 * 1 <= A[i] <= 100000
 */

#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// --------------------------------------------------
// TLE
// 素数筛 204
vector<int> countPrimes(int n) {
    if(n < 2) return {};
    bool* vec = new bool[n];
    for(int i = 0; i < n; ++i)
        vec[i] = true;
    vec[0] = false;
    vec[1] = false;
    for(int i = 2; i * i < n; ++i)
    {
        if(vec[i])
        {
            for(int j = i * i; j < n; j += i)
                vec[j] = false;
        }
    }
    vector<int> result;
    for(int i = 0; i < n; ++i)
    {
        bool flag = vec[i];
        if(flag)
            result.push_back(i);
    }
    return result;
}

// 分解质因数 263
vector<int> get_prime_factor(int num, const vector<int>& primes) {
    // 大于 1 的质因数
   if(num <= 0) return {};
   if(num == 1) return {};
   vector<int> result;
   for(int prime: primes)
   {
       if(prime > num) break;
       if(num % prime == 0)
           result.push_back(prime);
   }
   return result;
}

class UnionFindSet
{
public:
    UnionFindSet(int n):n(n),N(n)
    {
        _rank = vector<int>(n, 0);
        _father = vector<int>(n, 0);
        for(int i = 0; i < n; ++i)
            _father[i] = i;
        _primes = vector<int>();
        prime_idx = unordered_map<int, int>();
        _weight = vector<int>(n, 1);
    }

    bool same(int a, int b)
    {
        return _find(a) == _find(b);
    }

    void merge(int a, int b)
    {
        int x = _find(a);
        int y = _find(b);
        if(x == y) return;

        if(_rank[x] > _rank[y])
        {
            _father[y] = x;
            _weight[x] += _weight[y];
        }
        else
        {
            _father[x] = y;
            _weight[y] += _weight[x];
            if(_rank[x] == _rank[y])
                ++_rank[y];
        }
    }

    void update_prime(int maxn)
    {
        _primes = countPrimes(maxn);
        N += _primes.size();
        for(int i = n; i < N; ++i)
        {
            _rank.push_back(-1);
            _father.push_back(i);
            prime_idx[_primes[i - n]] = i;
            _weight.push_back(0);
        }
    }

    void process(const vector<int>& A)
    {
        for(int i = 0; i < n; ++i)
        {
            vector<int> prime_factors = get_prime_factor(A[i], _primes);
            for(int prime: prime_factors)
            {
                merge(prime_idx[prime], i);
            }
        }

    }

    int stat()
    {
        int result = 0;
        for(int i = 0; i < n; ++i)
        {
            if(_father[i] == i)
                result = max(result, _weight[i]);
        }
        return result;
    }

    void view()
    {
        for(int i = 0; i < N; ++i)
        {
            cout << i << " " << _father[i] << endl;
        }
    }

private:
    vector<int> _rank;
    vector<int> _father;
    unordered_map<int, int> prime_idx;
    vector<int> _primes;
    vector<int> _weight; // 连通分量大小
    int n, N;

    int _find(int x)
    {
        if(_father[x] == x)
            return x;
        return _father[x] = _find(_father[x]);
    }
};

class Solution {
public:
    int largestComponentSize(vector<int>& A) {
        const int N = 1e5 + 1;
        int n = A.size();
        UnionFindSet unionfindset(n);
        unionfindset.update_prime(N);
        unionfindset.process(A);
        return unionfindset.stat();
    }
};


// ---------------------------------------
// 优化：merge 在素数筛的时候做
// 1000ms
class UnionFindSet
{
public:
    UnionFindSet(int n):n(n)
    {
        _rank = vector<int>(n, 0);
        _father = vector<int>(n, 0);
        for(int i = 0; i < n; ++i)
            _father[i] = i;
        _weight = vector<int>(n, 0);
    }

    bool same(int a, int b)
    {
        return _find(a) == _find(b);
    }

    void merge(int a, int b)
    {
        // a 是目标数字，b 是质数
        int x = _find(a);
        int y = _find(b);
        if(x == y) return;

        if(_rank[x] > _rank[y])
        {
            _father[y] = x;
            _weight[x] += _weight[y];
        }
        else
        {
            _father[x] = y;
            _weight[y] += _weight[x];
            if(_rank[x] == _rank[y])
                ++_rank[y];
        }
    }

    void change_weight(int x)
    {
        _weight[x] = 1;
    }

    int stat()
    {
        int result = 0;
        for(int i = 0; i < n; ++i)
        {
            if(_father[i] == i)
                result = max(result, _weight[i]);
        }
        return result;
    }

private:
    vector<int> _rank;
    vector<int> _father;
    vector<int> _weight; // 连通分量大小
    int n;

    int _find(int x)
    {
        if(_father[x] == x)
            return x;
        _father[x] = _find(_father[x]);
        return _father[x];
    }
};

class Solution {
public:
    int largestComponentSize(vector<int>& A) {
        int N = *max_element(A.begin(), A.end());
        int n = A.size();
        nums = unordered_set<int>(A.begin(), A.end());
        UnionFindSet unionfindset(N + 1);
        primes_sieve(N + 1, &unionfindset);
        return unionfindset.stat();
    }

private:
    unordered_set<int> nums;

    void primes_sieve(int n, UnionFindSet* it) {
        if(n < 2) return;
        bool* vec = new bool[n];
        for(int i = 0; i < n; ++i)
            vec[i] = true;
        vec[0] = false;
        vec[1] = false;
        int cnt = 0;
        for(int i = 2; i < n; ++i)
        {
            if(vec[i])
            {
                if(nums.find(i) != nums.end())
                {
                    it -> change_weight(i);
                }
                for(int j = i * 2; j < n; j += i)
                {
                    ++cnt;
                    vec[j] = false;
                    if(nums.find(j) != nums.end())
                    {
                        it -> change_weight(j);
                        it -> merge(j, i);
                    }
                }
            }
        }
    }
};


// 另外写法1
// 1200ms
class Solution {
public:
    int largestComponentSize(vector<int>& A) {
        unordered_map<int, int> p;
        for (auto a : A)
            for (int k = 2; k <= sqrt(a); ++k)
                if (a % k == 0)
                    p[find(p, k)] = p[find(p, a/k)] = p[find(p, a)];
        unordered_map<int, int> cnt;
        int ans = 0;
        for (auto a : A)
            ans = max(ans, ++cnt[find(p, a)]);
        return ans;
    }
    int find(unordered_map<int, int> &p, int n) {
        if (!p.count(n)) return p[n] = n;
        return p[n] == n ? n : p[n] = find(p, p[n]);
    }
};

// 另外写法2
// 556ms
class Solution {
public:
    vector<int> F;
    int father(int x) {
        if (x != F[x]) F[x] = father(F[x]);
        return F[x];
    }
    int largestComponentSize(vector<int>& A) {
        int M = *max_element(A.begin(), A.end());
        F.resize(M + 1);
        for (int i = 2; i <= M; ++i) {
            F[i] = i;
        }
        vector<bool> isCandidate(M + 1, false);
        for (auto x : A) {
            isCandidate[x] = true;
        }
        vector<bool> isPrime(M + 1, true);
        for (int i = 2; i <= M; ++i) {
            if (isPrime[i]) {
                int t = isCandidate[i] ? i : -1;
                for (int j = i + i; j <= M; j += i) {
                    if (isCandidate[j]) {
                        if (t == -1) {
                            t = j;
                        } else {
                            F[father(j)] = father(t);
                        }
                    }
                    isPrime[j] = false;
                }
            }
        }
        map<int, int> counts;
        for (auto x : A) {
            ++counts[father(x)];
        }
        int res = 0;
        for (auto& p : counts) {
            res = max(res, p.second);
        }
        return res;
    }
};
