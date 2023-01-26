// prob918: Maximum Sum Circular Subarray

/*
 * Given a circular array C of integers represented by A, find the maximum possible sum of a non-empty subarray of C.
 * Here, a circular array means the end of the array connects to the beginning of the array.  (Formally, C[i] = A[i]
 * when 0 <= i < A.length, and C[i+A.length] = C[i] when i >= 0.)
 * Also, a subarray may only include each element of the fixed buffer A at most once. 
 * (Formally, for a subarray C[i], C[i+1], ..., C[j], there does not exist i <= k1, k2 <= j with k1 % A.length = k2 % A.length.)
 */

/*
 * Example 1:
 * Input: [1,-2,3,-2]
 * Output: 3
 * Explanation: Subarray [3] has maximum sum 3
 * Example 2:
 * Input: [5,-3,5]
 * Output: 10
 * Explanation: Subarray [5,5] has maximum sum 5 + 5 = 10
 * Example 3:
 * Input: [3,-1,2,-1]
 * Output: 4
 * Explanation: Subarray [2,-1,3] has maximum sum 2 + (-1) + 3 = 4
 * Example 4:
 * Input: [3,-2,2,-3]
 * Output: 3
 * Explanation: Subarray [3] and [3,-2,2] both have maximum sum 3
 * Example 5:
 * Input: [-2,-3,-1]
 * Output: -1
 * Explanation: Subarray [-1] has maximum sum -1
 */

/*
 * Note:
 * -30000 <= A[i] <= 30000
 *  1 <= A.length <= 30000
 */

#include <vector>
#include <deque>
#include <climits>

using namespace std;

// 单调队列
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& A) {
        int n = A.size();
        if(n == 1) return A[0];
        A.insert(A.end(), A.begin(), A.end());
        deque<int> deq;
        vector<int> sums(n * 2 + 1, 0);
        for(int i = 0; i < n * 2; ++i)
            sums[i + 1] = A[i] + sums[i];
        int ans = INT_MIN;
        deq.push_back(0);
        for(int j = 1; j <= n * 2; ++j)
        {
            int pj = sums[j];
            int pi = sums[deq.front()];
            ans = max(ans, pj - pi);
            while(!deq.empty() && sums[deq.back()] >= pj)
                deq.pop_back();
            deq.push_back(j);
            if(j - deq.front() == n)
                deq.pop_front();
        }
        return ans;
    }
};

// Kadane
class Solution_2 {
public:
    int maxSubarraySumCircular(vector<int>& A) {
        int n = A.size();
        if(n == 1) return A[0];
        int sum = A[0], sum1 = A[0], ans1 = A[0];
        for(int i = 1; i < n; ++i)
        {
            sum += A[i];
            sum1 = A[i] + max(sum1, 0);
            ans1 = max(ans1, sum1);
        }
        if(n == 2) return ans1;
        int sum2 = A[1], ans2 = A[1];
        for(int i = 1; i < n - 1; ++i)
        {
            sum2 = A[i] + min(sum2, 0);
            ans2 = min(ans2, sum2);
        }
        ans2 = sum - ans2;
        return max(ans1, ans2);
    }
};
