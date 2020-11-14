// prob360: Sort Transformed Array

/*
 * https://leetcode-cn.com/problems/sort-transformed-array/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
        int n = nums.size();
        vector<int> result(n);
        int left = 0, right = n - 1;
        if(a >= 0)
        {
            int iter = n - 1;
            while(left <= right)
            {
                if(f(nums[left], a, b, c) > f(nums[right], a, b, c))
                {
                    result[iter--] = f(nums[left], a, b, c);
                    ++left;
                }
                else
                {
                    result[iter--] = f(nums[right], a, b, c);
                    --right;
                }
            }
        }
        else
        {
            int iter = 0;
            while(left <= right)
            {
                if(f(nums[left], a, b, c) < f(nums[right], a, b, c))
                {
                    result[iter++] = f(nums[left], a, b, c);
                    ++left;
                }
                else
                {
                    result[iter++] = f(nums[right], a, b, c);
                    --right;
                }
            }
        }
        return result;
    }

private:
    int f(int x, int a, int b, int c)
    {
        return a * x * x + b * x + c;
    }
};
