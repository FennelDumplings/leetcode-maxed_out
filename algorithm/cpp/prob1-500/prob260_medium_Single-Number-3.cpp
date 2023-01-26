// prob260: Single Number |||

/*
 * Given an array of numbers nums, in which exactly two elements appear only once
 * and all the other elements appear exactly twice. Find the two elements that appear only once.
 */

/*
 * Example:
 * Input:  [1,2,1,3,2,5]
 * Output: [3,5]
 */

/*
 * Note:
 * The order of the result is not important. So in the above example, [5, 3] is also correct.
 * Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int s = 0; // a ^ b
        for(int num: nums) s ^= num;

        int i = 0; // a ^ b 中最右的 1 的位数
        while(!(s >> i & 1)) ++i;

        int a = 0;
        for(int num: nums)
            if(num >> i & 1)
                a ^= num;

        return vector<int>({a, a ^ s});
    }
};
