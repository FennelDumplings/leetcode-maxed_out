// prob1409: Queries on a Permutation With Key

/*
 * https://leetcode-cn.com/problems/queries-on-a-permutation-with-key/
 */

#include <vector>
#include <list>

using namespace std;

class Solution_2 {
public:
    vector<int> processQueries(vector<int>& queries, int m) {
        int Q = queries.size();
        list<int> l(m);
        int x = 1;
        for(auto it = l.begin(); it != l.end(); ++it)
            *it = x++;
        vector<int> result(Q);
        for(int i = 0; i < Q; ++i)
        {
            auto it = l.begin();
            int idx = 0;
            while(it != l.end())
            {
                if(*it == queries[i])
                {
                    result[i] = idx;
                    l.erase(it);
                    l.push_front(queries[i]);
                    break;
                }
                ++idx;
                ++it;
            }
        }
        return result;
    }
};

// BIT
class BIT
{
public:
    BIT(int n)
    {
        vec.assign(n + 1, 0);
        this -> n = n;
    }

    void add(int idx, int delta)
    {
        // vec[idx + 1] 增加 delta
        for(int i = idx + 1; i <= n; i += lowbit(i))
            vec[i] += delta;
    }

    int query(int idx)
    {
        // vec[1..idx+1] 的和
        int ans = 0;
        for(int i = idx + 1; i >= 1; i -= lowbit(i))
            ans += vec[i];
        return ans;
    }

private:
    vector<int> vec;
    int n;

    int lowbit(int x)
    {
        return x & (-x);
    }
};

class Solution {
public:
    vector<int> processQueries(vector<int>& queries, int m) {
        int Q = queries.size();
        // 维护操作
        // 初始时 [0,...,0,1,2,...,m]
        vector<int> vec(Q + m);
        // mapping[j] := j 在 vec 中的下标
        vector<int> mapping(m + 1);
        BIT bit(Q + m);
        for(int i = 0; i < m; ++i)
        {
            vec[Q + i] = i + 1;
            mapping[i + 1] = Q + i;
            bit.add(Q + i, 1);
        }
        vector<int> result(Q);
        for(int i = 0; i < Q; ++i)
        {
            int j = queries[i];
            int idx = mapping[j];
            result[i] = bit.query(idx - 1);
            vec[idx] = 0;
            vec[Q - 1 - i] = j;
            mapping[j] = Q - 1 - i;
            bit.add(idx, -1);
            bit.add(Q - 1 - i, 1);
        }
        return result;
    }
};
