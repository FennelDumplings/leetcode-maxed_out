// prob668: Kth Smallest Number in Multiplication Table

/*
 * Nearly every one have used the Multiplication Table.
 * But could you find out the k-th smallest number quickly from the multiplication table?
 * Given the height m and the length n of a m * n Multiplication Table, and a positive integer k,
 * you need to return the k-th smallest number in this table.
 */

/*
 * Note:
 * The m and n will be in the range [1, 30000].
 * The k will be in the range [1, m * n]
 */

/*
 * Example 1:
 * Input: m = 3, n = 3, k = 5
 * Output:
 * Explanation:
 * The Multiplication Table:
 * 1    2   3
 * 2    4   6
 * 3    6   9
 * The 5-th smallest number is 3 (1, 2, 2, 3, 3).
 * Example 2:
 * Input: m = 2, n = 3, k = 6
 * Output:
 * Explanation:
 * The Multiplication Table:
 * 1    2   3
 * 2    4   6
 * The 6-th smallest number is 6 (1, 2, 2, 3, 4, 6).
 */

#include <climits>
#include <algorithm>

using namespace std;

// 若 k 变大 (k < k') 则值 v 会相同或更大(v <= v')
// 由 v 反推 k, 得到的应该是区间
// 若二分 v(二分答案)，反推 kmax(使得值是 v 的最大的k)
// 记所求答案为 v0(对所求的k0), 若 v = v0 ，则反推的 kmax >= k0, 即求 k0<=kmax 且最小的kmax对应的v
// 如何从 v 反推 kmax:
//     1 2 3 4 5      min(n, v/1)
//     2 4 6 8 10     min(n, v/2)
//     3 6 9 12 15    min(n, v/3)
//     所有这些 min 的结果加起来就是 kmax
class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        // 1 <= m, n <= 30000
        // 1 < m*n <= 9e8
        int left = 1, right = m * n;
        while(left <= right)
        {
            int mid = left + (right - left) / 2;
            int maxk = get_maxk(m, n, mid);
            if(maxk < k)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return left;
    }

private:
    int get_maxk(int m, int n, int v)
    {
        int result = 0;
        for(int i = 1; i <= m; ++i)
            result += min(n, v / i);
        return result;
    }
};
