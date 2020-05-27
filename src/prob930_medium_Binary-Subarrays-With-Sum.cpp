// prob930: Binary Subarrays With Sum

/*
 * In an array A of 0s and 1s, how many non-empty subarrays have sum S?
 */

/*
 * Example 1:
 * Input: A = [1,0,1,0,1], S = 2
 * Output: 4
 * Explanation:
 * The 4 subarrays are bolded below:
 * [1,0,1,0,1]
 * [1,0,1,0,1]
 * [1,0,1,0,1]
 * [1,0,1,0,1]
 */

/*
 * Note:
 * A.length <= 30000
 * 0 <= S <= A.length
 * A[i] is either 0 or 1.
 */

#include <vector>

using namespace std;

class Solution {
public:
    int numSubarraysWithSum(vector<int>& A, int S) {
        if(A.empty()) return 0;
        int n = A.size();
        vector<int> cnts(n + 1, 0);
        cnts[0] = 1;
        int sum = 0;
        int result = 0;
        for(int i = 0; i < n; ++i)
        {
            sum = sum + A[i];
            if(sum >= S)
            {
                int gap = sum - S;
                result += cnts[gap];
            }
            ++cnts[sum];
        }
        return result;
    }
};

/*
 * 我们在固定区间的右端点 j 时，用计数器求出满足要求的左端点 i 的数目。而由于此题的特殊性，
 * 前缀和数组 P 是单调不降的，因此左端点的位置一定是连续的，即可以用 [i_lo, i_hi] 表示，并且随着 j 的增加，i_lo 和 i_hi 也单调不降，因此可以用类似双指针的方法，使用三个指针维护左端点的区间。
 */
