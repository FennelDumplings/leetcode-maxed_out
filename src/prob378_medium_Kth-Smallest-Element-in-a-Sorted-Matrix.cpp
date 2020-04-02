// prob378: Kth Smallest Element in a Sorted Matrix

/*
 * Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.
 * Note that it is the kth smallest element in the sorted order, not the kth distinct element.
 */

/*
 * Example:
 * matrix = [
 *    [ 1,  5,  9],
 *    [10, 11, 13],
 *    [12, 13, 15]
 * ],
 * k = 8,
 *
 * return 13.
 */

#include <vector>

using namespace std;

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int left = matrix[0][0], right = matrix[n - 1][n - 1];
        while(left < right)
        {
            int mid = (left + right) / 2;
            if(_count_smaller(matrix, mid) < k)
                left = mid + 1;
            else
                right = mid;
        }
        return left;
    }

private:
    int _count_smaller(vector<vector<int> >& matrix, int mid)
    {
        int n = matrix.size();
        int i = n - 1, j = 0, cnt = 0;
        while(i >= 0 && j < n)
        {
            if(matrix[i][j] <= mid)
            {
                cnt += i + 1;
                ++j;
            }
            else
                --i;
        }
        return cnt;
    }
};
