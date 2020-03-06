// prob1004: Max Consecutive Ones

/*
 * Given an array A of 0s and 1s, we may change up to K values from 0 to 1.
 * Return the length of the longest (contiguous) subarray that contains only 1s.
 */

/*
 * Example 1:
 * Input: A = [1,1,1,0,0,0,1,1,1,1,0], K = 2
 * Output: 6
 * Explanation:
 * [1,1,1,0,0,1,1,1,1,1,1]
 * Bolded numbers were flipped from 0 to 1.  The longest subarray is underlined.
 * Example 2:
 * Input: A = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], K = 3
 * Output: 10
 * Explanation:
 * [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
 * Bolded numbers were flipped from 0 to 1.  The longest subarray is underlined.
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestOnes(vector<int>& A, int K) {
        if(K == 0) return _longestOnes(A);
        int n = A.size();
        int count = K;
        int left = 0, right = 0;
        int result = 0;
        while(right < n)
        {
            while(right < n && (A[right] == 1 || count > 0))
            {
                if(A[right] == 0)
                    --count;
                ++right;
            }
            result = max(result, right - left);
            if(A[left] == 0) ++count;
            ++left;
        }
        return result;
    }

private:
    int _longestOnes(vector<int>& A) {
        int n = A.size();
        int left = 0, right = 0;
        int result = 0;
        while(right < n)
        {
            while(left < n && A[left] == 0)
                ++left;
            right = left;
            while(right < n && A[right] == 1)
                ++right;
            result = max(result, right - left);
            left = right;
        }
        return result;
    }
};
