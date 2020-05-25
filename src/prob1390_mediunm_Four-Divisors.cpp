// prob1390: Four Divisors

/*
 * Given an integer array nums, return the sum of divisors of the integers in that array that have exactly four divisors.
 * If there is no such integer in the array, return 0.
 */

/*
 * Example 1:
 * Input: nums = [21,4,7]
 * Output: 32
 * Explanation:
 * 21 has 4 divisors: 1, 3, 7, 21
 * 4 has 3 divisors: 1, 2, 4
 * 7 has 2 divisors: 1, 7
 * The answer is the sum of divisors of 21 only.
 */

/*
 * Constraints:
 * 1 <= nums.length <= 10^4
 * 1 <= nums[i] <= 10^5
 */

#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
        int result = 0;
        for(int num: nums)
        {
            vector<int> divisors = _solve(num);
            if((int)divisors.size() == 4)
                result += accumulate(divisors.begin(), divisors.end(), 0);
        }
        return result;
    }

private:
    vector<int> _solve(int num)
    {
        vector<int> result;
        for(int i = 1; i * i <= num; ++i)
        {
            int j = num / i;
            if(i * j == num)
            {
                result.push_back(i);
                if(i != j)
                    result.push_back(j);
            }
        }
        return result;
    }
};
