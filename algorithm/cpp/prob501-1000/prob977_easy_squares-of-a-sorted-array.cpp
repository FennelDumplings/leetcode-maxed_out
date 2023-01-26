// Prob777 Squares of a Sorted Array

/* Description:
 * Given an array of integers A sorted in non-decreasing order,
 * return an array of the squares of each number,
 * also in sorted non-decreasing order.
 */

/* Examples:
 * Example 1:
 * Input: [-4,-1,0,3,10]
 * Output: [0,1,9,16,100]
 * Example 2:
 * Input: [-7,-3,2,3,11]
 * Output: [4,9,9,49,121]
 */

/* Note:
 * 1 <= A.length <= 10000
 * -10000 <= A[i] <= 10000
 * A is sorted in non-decreasing order.
 */


#include <iostream>
#include <vector>
using namespace std;

// 从外向内
class Solution {
public:
    vector<int> sortedSquares(vector<int>& A)
    {
        if(A.empty()) return vector<int>();
        int n = A.size();
        vector<int> result(n, 0);
        int left = 0, right = n - 1;
        for(int i = n - 1; i >= 0; --i)
        {
            if(A[right] < 0)
            {
                result[i] = A[left] * A[left];
                ++left;
            }
            else if(A[left] > 0)
            {
                result[i] = A[right] * A[right];
                --right;
            }
            else
            {
                if(abs(A[left]) <= A[right])
                {
                    result[i] = A[right] * A[right];
                    --right;
                }
                else
                {
                    result[i] = A[left] * A[left];
                    ++left;
                }
            }
        }
        return result;
    }
};

// 从内向外
class Solution_2 {
public:
    vector<int> sortedSquares(vector<int>& A) {
        int n = A.size();
        vector<int> result(n, 0);
        int near_zero_pos = positionNearZero(A);
        int i = 0;
        result[i] = A[near_zero_pos] * A[near_zero_pos];
        ++i;
        int ir = near_zero_pos + 1;
        int il = near_zero_pos - 1;
        while((ir <= n - 1) && (il >= 0))
        {
            if(-A[il] <= A[ir])
            {
                result[i] = A[il] * A[il];
                ++i;
                --il;
            }
            else
            {
                result[i] = A[ir] * A[ir];
                ++i;
                ++ir;
            }
        }
        if(ir > n - 1)
        {
            while(il >= 0)
            {
                result[i] = A[il] * A[il];
                ++i;
                --il;
            }
        }
        else
        {
            while(ir <= n - 1)
            {
                result[i] = A[ir] * A[ir];
                ++i;
                ++ir;
            }
        }
        return result;
    }

private:
    int positionNearZero(vector<int>& vec)
    {
        // return the position where the element is nearest to zero
        // vec is a sorted array
        int n = vec.size();
        if(n == 1) return 0;
        int left = 0;
        int right = n - 1;
        if(vec[left] > 0) return left;
        if(vec[right] < 0) return right;
        while(left + 1 < right)
        {
            int mid = (left + right) / 2;
            if(vec[mid] == 0)
                return mid;
            else if(vec[mid] > 0)
                right = mid;
            else
                left = mid;
        }
        if(-vec[left] <= vec[right])
            return left;
        else
            return right;
    }
};
