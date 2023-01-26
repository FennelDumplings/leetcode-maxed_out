// prob1477: Find Two Non-overlapping Sub-arrays Each With Target Sum

/*
 * Given an array of integers arr and an integer target.
 *
 * You have to find two non-overlapping sub-arrays of arr each with sum equal target. There can be multiple answers so you have to find an answer where the sum of the lengths of the two sub-arrays is minimum.
 *
 * Return the minimum sum of the lengths of the two required sub-arrays, or return -1 if you cannot find such two sub-arrays.
 */

/*
 * Example 1:
 *
 * Input: arr = [3,2,2,4,3], target = 3
 * Output: 2
 * Explanation: Only two sub-arrays have sum = 3 ([3] and [3]). The sum of their lengths is 2.
 * Example 2:
 *
 * Input: arr = [7,3,4,7], target = 7
 * Output: 2
 * Explanation: Although we have three non-overlapping sub-arrays of sum = 7 ([7], [3,4] and [7]), but we will choose the first and third sub-arrays as the sum of their lengths is 2.
 * Example 3:
 *
 * Input: arr = [4,3,2,6,2,3,4], target = 6
 * Output: -1
 * Explanation: We have only one sub-array of sum = 6.
 * Example 4:
 *
 * Input: arr = [5,5,4,4,5], target = 3
 * Output: -1
 * Explanation: We cannot find a sub-array of sum = 3.
 * Example 5:
 *
 * Input: arr = [3,1,1,1,5,1,2,1], target = 3
 * Output: 3
 * Explanation: Note that sub-arrays [1,2] and [2,1] cannot be an answer because they overlap.
 */

/*
 * Constraints:
 *
 * 1 <= arr.length <= 10^5
 * 1 <= arr[i] <= 1000
 * 1 <= target <= 10^8
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        // l[i] = [0..i]
        // r[i] = [i..n-1]
        vector<int> l(n, n + 1), r(n, n + 1);
        unordered_map<int, int> mapping; // sum -> idx
        mapping[0] = -1;
        int sum = 0;
        for(int i = 0; i < n; ++i)
        {
            if(i > 0)
                l[i] = l[i - 1];
            sum += arr[i];
            int gap = sum - target;
            if(mapping.count(gap))
                l[i] = min(l[i], i - mapping[gap]);
            mapping[sum] = i;
        }
        // 推后缀和的过程
        // mapping.clear();
        // mapping[0] = n;
        unordered_map<int, int> mapping2; // sum -> idx
        mapping2[0] = n;
        sum = 0;
        for(int i = n - 1; i >= 0; --i)
        {
            if(i < n - 1)
                r[i] = r[i + 1];
            sum += arr[i];
            int gap = sum - target;
            if(mapping2.count(gap))
                r[i] = min(r[i], mapping2[gap] - i);
            mapping2[sum] = i;
        }
        int result = -1;
        for(int p = 0; p < n - 1; ++p)
        {
            // [0..p], [p+1..n-1]
            if(l[p] == n + 1 || r[p + 1] == n + 1)
                continue;
            if(result == -1 || result > l[p] + r[p + 1])
                result = l[p] + r[p + 1];
        }
        return result;
    }
};
