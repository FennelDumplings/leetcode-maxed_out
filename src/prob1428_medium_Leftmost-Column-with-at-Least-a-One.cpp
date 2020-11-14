// prob1428: Leftmost Column with at Least a One

/*
 * https://leetcode-cn.com/problems/leftmost-column-with-at-least-a-one/
 */

/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 */

#include <vector>

using namespace std;

 class BinaryMatrix {
   public:
     int get(int row, int col);
     vector<int> dimensions();
 };

class Solution {
public:
    int leftMostColumnWithOne(BinaryMatrix &binaryMatrix) {
        vector<int> info = binaryMatrix.dimensions();
        int n = info[0], m = info[1];
        int left = 0, right = m - 1;
        while(left < right)
        {
            int mid = (left + right) / 2;
            if(check(binaryMatrix, mid, n))
                right = mid;
            else
                left = mid + 1;
        }
        if(left < n - 1 || check(binaryMatrix, left, n))
            return left;
        return -1;
    }

private:
    bool check(BinaryMatrix& binaryMatrix, int mid, int n)
    {
        for(int i = 0; i < n; ++i)
            if(binaryMatrix.get(i, mid) == 1)
                return true;
        return false;
    }
};
