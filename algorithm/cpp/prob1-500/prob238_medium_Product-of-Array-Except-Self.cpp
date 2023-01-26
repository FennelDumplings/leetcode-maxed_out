// prob238: Product of Array Except Self

/*
 * Given an array nums of n integers where n > 1,  return an array output such that output[i] is equal to the
 * product of all the elements of nums except nums[i].
 */

/*
 * Example:
 * Input:  [1,2,3,4]
 * Output: [24,12,8,6]
 */

/*
 * Constraint: It's guaranteed that the product of the elements of any prefix or suffix of the array (including the whole array) fits in a 32 bit integer.
 * Note: Please solve it without division and in O(n).
 */

/*
 * Follow up:
 * Could you solve it with constant space complexity? (The output array does not count as extra space for the purpose of space complexity analysis.)
 */

#include <vector>

using namespace std;

// 前缀积 + 后缀积
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        if(nums.empty()) return vector<int>();
        int n = nums.size();
        vector<int> pre_product(n + 1, 1);
        vector<int> post_product(n + 1, 1);
        for(int i = 0; i < n; ++i)
            pre_product[i + 1] = pre_product[i] * nums[i];
        for(int i = n - 1; i >= 0; -- i)
            post_product[i] = post_product[i + 1] * nums[i];
        vector<int> result(n, 1);
        for(int i = 0; i < n; ++i)
            result[i] = pre_product[i] * post_product[i + 1];
        return result;
    }
};

// O(1) 额外空间
class Solution_2 {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        if(nums.empty()) return vector<int>();
        int n = nums.size();
        vector<int> post_product(n + 1, 1);
        for(int i = n - 1; i >= 0; -- i)
            post_product[i] = post_product[i + 1] * nums[i];
        vector<int> &result = post_product;
        int pre_product = 1;
        for(int i = 0; i < n; ++i)
        {
            result[i] = post_product[i + 1] * pre_product;
            pre_product *= nums[i];
        }
        result.pop_back();
        return result;
    }
};
