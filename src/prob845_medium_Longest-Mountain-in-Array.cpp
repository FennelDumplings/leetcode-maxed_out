// prob845: Longest Mountain in Array

/*
 * Let's call any (contiguous) subarray B (of A) a mountain if the following properties hold:
 * B.length >= 3
 * There exists some 0 < i < B.length - 1 such that B[0] < B[1] < ... B[i-1] < B[i] > B[i+1] > ... > B[B.length - 1]
 * (Note that B could be any subarray of A, including the entire array A.)
 * Given an array A of integers, return the length of the longest mountain. 
 * Return 0 if there is no mountain.
 */

/*
 * Example 1:
 * Input: [2,1,4,7,3,2,5]
 * Output: 5
 * Explanation: The largest mountain is [1,4,7,3,2] which has length 5.
 * Example 2:
 * Input: [2,2,2]
 * Output: 0
 * Explanation: There is no mountain.
 */

/*
 * Note:
 * 0 <= A.length <= 10000
 * 0 <= A[i] <= 10000
 * Follow up:
 * Can you solve it using only one pass?
 * Can you solve it in O(1) space?
 */

#include <vector>

using namespace std;

class Solution {
public:
    int longestMountain(vector<int>& A) {
        int n = A.size();
        int result = 0;
        int left = 0;
        while(left < n)
        {
            while(left + 1 < n && A[left] >= A[left + 1])
                ++left;
            int mid = left + 1;
            if(mid == n)
                break;
            while(mid + 1 < n && A[mid] < A[mid + 1])
                ++mid;
            int right = mid + 1;
            if(right == n)
                break;
            if(A[mid] == A[right])
            {
                left = right;
                continue;
            }
            while(right + 1 < n && A[right] > A[right + 1])
                ++right;
            result = max(result, right - left + 1);
            left = right;
        }
        return result;
    }
};
