// prob975: Odd Even Jump

/*
 * You are given an integer array A.  From some starting index, you can make a series of jumps.  The (1st, 3rd, 5th, ...) jumps in the series are called odd numbered jumps, and the (2nd, 4th, 6th, ...) jumps in the series are called even numbered jumps.
 * You may from index i jump forward to index j (with i < j) in the following way:
 * During odd numbered jumps (ie. jumps 1, 3, 5, ...), you jump to the index j such that A[i] <= A[j] and A[j] is the smallest possible value.  If there are multiple such indexes j, you can only jump to the smallest such index j.
 * During even numbered jumps (ie. jumps 2, 4, 6, ...), you jump to the index j such that A[i] >= A[j] and A[j] is the largest possible value.  If there are multiple such indexes j, you can only jump to the smallest such index j.
 * (It may be the case that for some index i, there are no legal jumps.)
 * A starting index is good if, starting from that index, you can reach the end of the array (index A.length - 1) by jumping some number of times (possibly 0 or more than once.)
 * Return the number of good starting indexes.
 */

/*
 * Example 1:
 * Input: [10,13,12,14,15]
 * Output: 2
 * Explanation:
 * From starting index i = 0, we can jump to i = 2 (since A[2] is the smallest among A[1], A[2], A[3], A[4] that is greater or equal to A[0]), then we can't jump any more.
 * From starting index i = 1 and i = 2, we can jump to i = 3, then we can't jump any more.
 * From starting index i = 3, we can jump to i = 4, so we've reached the end.
 * From starting index i = 4, we've reached the end already.
 * In total, there are 2 different starting indexes (i = 3, i = 4) where we can reach the end with some number of jumps.
 * Example 2:
 * Input: [2,3,1,1,4]
 * Output: 3
 * Explanation:
 * From starting index i = 0, we make jumps to i = 1, i = 2, i = 3:
 * During our 1st jump (odd numbered), we first jump to i = 1 because A[1] is the smallest value in (A[1], A[2], A[3], A[4]) that is greater than or equal to A[0].
 * During our 2nd jump (even numbered), we jump from i = 1 to i = 2 because A[2] is the largest value in (A[2], A[3], A[4]) that is less than or equal to A[1].  A[3] is also the largest value, but 2 is a smaller index, so we can only jump to i = 2 and not i = 3.
 * During our 3rd jump (odd numbered), we jump from i = 2 to i = 3 because A[3] is the smallest value in (A[3], A[4]) that is greater than or equal to A[2].
 * We can't jump from i = 3 to i = 4, so the starting index i = 0 is not good.
 * In a similar manner, we can deduce that:
 * From starting index i = 1, we jump to i = 4, so we reach the end.
 * From starting index i = 2, we jump to i = 3, and then we can't jump anymore.
 * From starting index i = 3, we jump to i = 4, so we reach the end.
 * From starting index i = 4, we are already at the end.
 * In total, there are 3 different starting indexes (i = 1, i = 3, i = 4) where we can reach the end with some number of jumps.
 * Example 3:
 * Input: [5,1,3,4,2]
 * Output: 3
 * Explanation:
 * We can reach the end from starting indexes 1, 2, and 4.
 */

#include <vector>
#include <set>

using namespace std;

struct Item
{
    int idx, val;
    Item(int idx, int val):idx(idx),val(val){}
};

struct Cmp
{
    bool operator()(const Item& i1, const Item& i2) const
    {
        if(i1.val == i2.val)
            return i1.idx < i2.idx;
        return i1.val < i2.val;
    }
};

class Solution {
public:
    int oddEvenJumps(vector<int>& A) {
        int n = A.size();
        vector<vector<bool>> dp(n, vector<bool>(2, false));
        // dp[i][state]
        // dp[i][0] := 在 i 偶跳能否到 n - 1
        // dp[i][1] := 在 i 奇跳能否到 n - 1
        // dp[i][0] := dp[j][1], j 为使得 A[i] >= A[j] 的最大 A[j] 的最小 j
        // dp[i][1] := dp[j][0], j 为使得 A[i] <= A[j] 的最小 A[j] 的最小 j
        // dp[n - 1][0] = true
        // dp[n - 1][1] = true
        dp[n - 1][0] = true;
        dp[n - 1][1] = true;
        set<Item, Cmp> setting;
        setting.insert(Item(n - 1, A[n - 1]));
        for(int i = n - 2; i >= 0; --i)
        {
            // dp[i][0], dp[i][1]
            int cur = A[i];
            // 要么 it -> val 比 cur 大, 要么 it -> idx 比 i 大
            auto it = setting.upper_bound(Item(i, cur));
            // 比 cur 大的最小值
            if(it != setting.end())
            {
                int j = it -> idx;
                dp[i][1] = dp[j][0];
            }
            // 比 cur 小的最大值
            if(it -> val == cur)
            {
                // it -> val == cur
                int j = it -> idx;
                dp[i][0] = dp[j][1];
            }
            else
            {
                // it -> val < cur
                if(it != setting.begin())
                {
                    // --it 后, 要么 it -> val 比 cur 小, 要么 it -> idx 比 i 小(不可能)
                    --it;
                    int val = it -> val;
                    while(it != setting.begin())
                    {
                        --it;
                        if(it -> val != val)
                        {
                            ++it;
                            break;
                        }
                    }
                    int j = it -> idx;
                    dp[i][0] = dp[j][1];
                }
            }
            setting.insert(Item(i, cur));
        }
        int result = 0;
        for(int i = 0; i < n; ++i)
            if(dp[i][1])
            {
                ++result;
            }
        return result;
    }
};
