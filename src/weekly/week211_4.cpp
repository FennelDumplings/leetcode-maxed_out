
#include <vector>
#include <unordered_set>

using namespace std;

class UnionFindSet
{
    public:
        UnionFindSet(int n):n(n)
    {
        _rank = vector<int>(n, 0);
        _father = vector<int>(n, 0);
        for(int i = 0; i < n; ++i)
            _father[i] = i;
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
        }
        else
        {
            _father[x] = y;
            if(_rank[x] == _rank[y])
                ++_rank[y];
        }
    }

private:
    vector<int> _rank;
    vector<int> _father;
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
    vector<bool> areConnected(int n, int threshold, vector<vector<int>>& queries) {
        vector<int> A(n);
        H = threshold;
        for(int i = 1; i <= n; ++i)
            A[i] = i;
        nums = unordered_set<int>(A.begin(), A.end());
        UnionFindSet unionfindset(n + 1);
        primes_sieve(n + 1, &unionfindset);
        int m = queries.size();
        vector<bool> result(m);
        for(int i = 0; i < m; ++i)
        {
            vector<int>& q = queries[i];
            result[i] = unionfindset.same(q[0], q[1]);
        }
        return result;
    }

private:
    unordered_set<int> nums;
    int H;

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
                for(int j = min(i * 2, H + 1); j < n; j += i)
                {
                    ++cnt;
                    vec[j] = false;
                    if(nums.find(j) != nums.end())
                    {
                        it -> merge(j, i);
                    }
                }
            }
        }
    }
};
