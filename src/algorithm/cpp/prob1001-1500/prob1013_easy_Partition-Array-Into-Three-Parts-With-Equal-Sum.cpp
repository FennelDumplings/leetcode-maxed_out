// prob1013: Partition Array Into Three Parts With Equal Sum

/*
 * Given an array A of integers, return true if and only if we can partition the array into three non-empty parts with equal sums.
 * Formally, we can partition the array if we can find indexes i+1 < j with (A[0] + A[1] + ... + A[i] == A[i+1] + A[i+2] + ... + A[j-1] == A[j] + A[j-1] + ... + A[A.length - 1])
 */

/*
 * Example 1:
 *
 * Input: A = [0,2,1,-6,6,-7,9,1,2,0,1]
 * Output: true
 * Explanation: 0 + 2 + 1 = -6 + 6 - 7 + 9 + 1 = 2 + 0 + 1
 * Example 2:
 *
 * Input: A = [0,2,1,-6,6,7,9,-1,2,0,1]
 * Output: false
 * Example 3:
 *
 * Input: A = [3,3,6,5,-2,2,5,1,-9,4]
 * Output: true
 * Explanation: 3 + 3 = 6 = 5 - 2 + 2 + 5 + 1 - 9 + 4
 */

/*
 * Constraints:
 * 3 <= A.length <= 50000
 * -10^4 <= A[i] <= 10^4
 */

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool canThreePartsEqualSum(vector<int>& A) {
        int sum = 0;
        for(int a: A) sum += a;
        if(sum % 3 != 0)
            return false;
        bool flag1 = false, flag2 = false; // 出现前缀和为 1/3 sum, 2/3 sum
        int sum1, sum2;
        if(sum == 0)
        {
            sum1 = 0;
            sum2 = 0;
        }
        else
        {
            sum1 = sum / 3;
            sum2 = sum * 2 / 3;
        }
        int prefix_sum = 0;
        int n = A.size();
        for(int i = 0; i < n - 1; ++i)
        {
            int a = A[i];
            prefix_sum += a;
            if(!flag1 && prefix_sum == sum1)
                flag1 = true;
            else if(flag1 && !flag2 && prefix_sum == sum2)
                flag2 = true;
        }
        return flag2;
    }
};
