#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

class BIT_RMQ
{
public:
    BIT_RMQ():vec(1,-2),a(1,-2){}
    BIT_RMQ(int n):vec(n + 1, -2),a(n,-2){}

    void update(int idx, int x)
    {
        // vec[idx] 管的是 [idx-lowbit[idx] + 1..idx] 这个区间
        // a[idx -  1] 改为 x
        // vec[idx]
        a[idx - 1] = x;
        vec[idx] = x;
        int n = a.size();
        for(int i = idx; i <= n; i += _lowbit(i))
        {
            for(int j = 1; j < _lowbit(i); j <<= 1)
            {
                // j < _lowbit(i) <= j - i < _lowbit(i) - i <= i - j > i - _lowbit(i)
                // i = 8，即改 vec[8]
                // 要看 vec[7] = i - 1
                //      vec[6] = i - 2
                //      vec[4] = i - 4
                vec[i] = max(vec[i], vec[i - j]);
            }
        }
    }

    int query(int l, int r)
    {
        // 直接看 vec[r] 不行
        // vec[r] 对应 [r - lowbit[r] + 1, r]
        int ans = a[r - 1];
        while(true)
        {
            ans = max(ans, a[r - 1]);
            if(l == r)
                break;
            --r;
            for(; r - _lowbit(r) >= l; r -= _lowbit(r))
                ans = max(ans, vec[r]);
        }
        return ans;
    }

    void view()
    {
        int n = a.size();
        for(int i = 0; i < n; ++i)
            cout << a[i] << " ";
        cout << endl;
        for(int i = 1; i <= n; ++i)
            cout << vec[i] << " ";
        cout << endl;
    }

private:
    vector<int> vec;
    vector<int> a;

    int _lowbit(int x)
    {
        return x & (-x);
    }
};


struct Point
{
    int x;
    int y;
    int q; // >= 0: 查询的下标; -1: 点集
    Point(){}
    Point(int x, int y, int q):x(x),y(y), q(q){}
    bool operator<(const Point& p) const
    {
        if(x == p.x)
            return q > p.q;
        return x < p.x;
    }
};

int _find(int v, const vector<int>& aa) // 从 nums 的值找到对应的离散化之后的值
{
    return lower_bound(aa.begin(), aa.end(), v) - aa.begin() + 1;
}

vector<int> discretization(const vector<int>& a)
{
    int n = a.size();
    vector<int> aa = a;
    sort(aa.begin(), aa.end());
    aa.erase(unique(aa.begin(), aa.end()), aa.end());
    return aa;
}

class Solution {
public:
    vector<int> maximumSumQueries(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        int n = nums1.size();
        int m = queries.size();
        vector<Point> events(n + m);
        for(int i = 0; i < n; ++i)
        {
            events[i].x = nums1[i];
            events[i].y = nums2[i];
            events[i].q = -1;
        }
        for(int i = 0; i < m; ++i)
        {
            events[n + i].x = queries[i][0];
            events[n + i].y = queries[i][1];
            events[n + i].q = i;
        }

        const int INF = 1e9;
        vector<int> ys(n + m + 1);
        for(int i = 0; i < n; ++i)
            ys[i] = nums2[i];
        for(int i = 0; i < m; ++i)
            ys[n + i] = queries[i][1];
        ys[n + m] = INF;
        vector<int> idx = discretization(ys);

        BIT_RMQ bit_rmq(idx.size());
        bit_rmq.update(_find(INF, idx), -1);

        sort(events.begin(), events.end());
        vector<int> result(m);
        for(int i = n + m - 1; i >= 0; --i)
        {
            Point e = events[i];
            if(e.q == -1)
            {
                if(bit_rmq.query(_find(e.y, idx), _find(e.y, idx)) < e.x + e.y)
                    bit_rmq.update(_find(e.y, idx), e.x + e.y);
            }
            else
            {
                result[e.q] = bit_rmq.query(_find(e.y, idx), _find(INF, idx));
            }
        }
        return result;
    }
};
