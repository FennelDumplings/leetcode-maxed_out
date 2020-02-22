// prob137: Single Number II

/*
 * Given a non-empty array of integers, every element appears three times except for one, which appears exactly once. Find that single one.
 */

/*
 * Note:
 * Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
 */

/*
 * Example 1:
 * Input: [2,2,3,2]
 * Output: 3
 * Example 2:
 * Input: [0,1,0,1,0,1,99]
 * Output: 99
 */

#include <vector>

using namespace std;

// 名门正派的算法
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int result = 0;
        for(int i = 0; i <= 31; ++i)
        {
            int count = 0;
            for(int num : nums)
                if(num >> i & 1)
                    ++count;
            if(count % 3 == 1) result += (1 << i);
        }
        return result;
    }
};

// 灵光一闪的算法，没有可扩展性, 虽然更快，但不推荐
// 状态机
//        ones   twos
// 初始： 0      0
// 1个1： 1      0
// 2个1： 0      1
// 3个1： 0      0
class Solution_2 {
public:
    int singleNumber(vector<int>& nums) {
        int ones = 0, twos = 0;
        for(auto x: nums)
        {
            ones = (ones ^ x) & ~twos;
            twos = (twos ^ x) & ~ones;
        }
        return ones;
    }
};

