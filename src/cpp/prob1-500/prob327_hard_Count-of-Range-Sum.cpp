// prob327: Count of Range Sum

/*
 * Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
 * Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i ≤ j), inclusive.
 */

/*
 * Example:
 * Input: nums = [-2,5,-1], lower = -2, upper = 2,
 * Output: 3
 * Explanation: The three ranges are : [0,0], [2,2], [0,2] and their respective sums are: -2, -1, 2.
 */

#include <vector>
#include <algorithm>

using namespace std;

class BIT
{
public:
    BIT(int m)
    {
        vec = vector<int>(m + 1, 0);
    }

    void add(int x)
    {
        while(x < (int)vec.size())
        {
            ++vec[x];
            x += _lowbit(x);
        }
    }

    int query(int x)
    {
        if(x < 0 || x >= (int)vec.size()) return 0;
        int result = 0;
        while(x > 0)
        {
            result += vec[x];
            x -= _lowbit(x);
        }
        return result;
    }

private:
    vector<int> vec;

    int _lowbit(int x)
    {
        return x & (-x);
    }
};

class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        if(nums.empty()) return 0;
        int n = nums.size();
        vector<ll> sums(n + 1, 0);
        for(int i = 1; i <= n; ++i)
            sums[i] = sums[i - 1] + nums[i - 1];
        vector<ll> x(sums.begin(), sums.end());
        for(ll sum: sums)
        {
            x.push_back(sum - (ll)lower);
            x.push_back(sum - (ll)upper);
        }
        sort(x.begin(), x.end());
        x.erase(unique(x.begin(), x.end()), x.end());
        int m = x.size();
        BIT bit(m);
        int result = 0;
        bit.add(_find(0, x));
        for(int i = 0; i < n; ++i)
        {
            ll cur = sums[i + 1];
            result += bit.query(_find(cur - (ll)lower, x)) - bit.query(_find(cur - (ll)upper, x) - 1);
            bit.add(_find(cur, x));
        }
        return result;
    }

private:
    using ll = long long;
    int _find(ll v, const vector<ll>& x)
    {
        return lower_bound(x.begin(), x.end(), v) - x.begin() + 1;
    }
};

//
