// prob1589: Maximum Sum Obtained of Any Permutation

/*
 * https://leetcode-cn.com/problems/maximum-sum-obtained-of-any-permutation/
 */

#include <vector>
#include <algorithm>

using namespace std;

struct Idx
{
    int idx;
    int cnt;
    Idx(int idx, int cnt=0):idx(idx),cnt(cnt){}
};

struct IdxCmp
{
    bool operator()(const Idx& i1, const Idx& i2) const
    {
        return i1.cnt < i2.cnt;
    }
};

class Solution {
public:
    int maxSumRangeQuery(vector<int>& nums, vector<vector<int>>& requests) {
        int n = nums.size();
        vector<int> left_end(n), right_end(n);
        for(const vector<int> &e: requests)
        {
            ++left_end[e[0]];
            ++right_end[e[1]];
        }
        vector<Idx> idxs;
        int cnt = 0;
        for(int i = 0; i < n; ++i)
        {
            cnt += left_end[i];
            idxs.emplace_back(i, cnt);
            cnt -= right_end[i];
        }
        sort(idxs.begin(), idxs.end(), IdxCmp());
        sort(nums.begin(), nums.end());
        vector<int> rearranged(n);
        for(int i = 0; i < n; ++i)
            rearranged[idxs[i].idx] = nums[i];
        vector<int> sums(n + 1);
        for(int i = 1; i <= n; ++i)
            sums[i] = sums[i - 1] + rearranged[i - 1];
        int ans = 0;
        for(const vector<int> &e: requests)
        {
            ans = (ans + (ll)sums[e[1] + 1] - sums[e[0]]) % MOD;
        }
        return ans;
    }

private:
    using ll = long long;
    const int MOD = 1e9 + 7;
};
