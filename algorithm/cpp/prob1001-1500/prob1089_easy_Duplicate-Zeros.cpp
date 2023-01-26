// prob1089: Duplicate Zeros

/*
 * https://leetcode-cn.com/problems/duplicate-zeros/
 */

#include <vector>

using namespace std;

class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        int n = arr.size();
        int left = 0, right = 0;
        while(right < n)
        {
            if(arr[left] == 0)
                ++right;
            ++left;
            ++right;
        }
        // [0..left] -> [0..right]
        --left;
        --right;
        if(right == n) // 最后一个数是 0 且不成对
        {
            arr[n - 1] = 0;
            right -= 2;
            --left;
        }
        while(left >= 0)
        {
            if(arr[left] == 0)
            {
                arr[right--] = 0;
            }
            arr[right--] = arr[left--];
        }
    }
};
