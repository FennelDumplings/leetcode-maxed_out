// prob862: Shortest Subarray with Sum at Least K

/*
 * Return the length of the shortest, non-empty, contiguous subarray of A with sum at least K.
 * If there is no non-empty subarray with sum at least K, return -1.
 */

/*
 * Note:
 * 1 <= A.length <= 50000
 * -10 ^ 5 <= A[i] <= 10 ^ 5
 *  1 <= K <= 10 ^ 9
 */

/*
 * Example 1:
 * Input: A = [1], K = 1
 * Output: 1
 * Example 2:
 * Input: A = [1,2], K = 4
 * Output: -1
 * Example 3:
 * Input: A = [2,-1,2], K = 3
 * Output: 3
 */

#include <vector>

using namespace std;

// 照搬prob209双指针，答案错
// 因为A中可能有0或负数了
class Solution {
public:
    int shortestSubarray(vector<int>& A, int K) {
        if(A.empty()) return 0;
        int n = A.size();
        int result = 0;
        int sum = 0;
        int left = 0, right = 0;
        while(right < n)
        {
            if(left > right)
                left = right;
            if(sum + A[right] < K)
            {
                sum += A[right];
                ++right;
            }
            else
            {
                if(result > 0)
                    result = min(result, right - left + 1);
                else
                    result = right - left + 1;
                sum -= A[left];
                ++left;
            }
        }
        if(result == 0) return -1;
        return result;
    }
};


// 二分
class Solution_2 {
public:
    int shortestSubarray(vector<int>& A, int K) {
        if(A.empty()) return 0;
        int n = A.size();
        int left = 1, right = n;
        while(left <= right)
        {
            int mid = left + (right - left) / 2;
            if(_check(A, mid, K))
                right = mid - 1;
            else
                left = mid + 1;
        }
        if(left > n) return 0;
        return left;
    }

private:
    bool _check(const vector<int>& A, int mid, int K)
    {
        int n = A.size();
        int sum = 0;
        for(int i = 0; i < mid; ++i)
            sum += A[i];
        if(sum >= K) return true;
        for(int i = 1; i + mid - 1 <= n - 1; ++i)
        {
            sum -= A[i - 1];
            sum += A[i + mid - 1];
            if(sum >= K)
                return true;
        }
        return false;
    }
};
