// prob1056: Confusing Number

/*
 * Given a number N, return true if and only if it is a confusing number, which satisfies the following condition:
 * We can rotate digits by 180 degrees to form new digits. When 0, 1, 6, 8, 9 are rotated 180 degrees, they become 0, 1, 9, 8, 6 respectively. When 2, 3, 4, 5 and 7 are rotated 180 degrees, they become invalid. A confusing number is a number that when rotated 180 degrees becomes a different number with each digit valid.
 */

/*
 * Example 1:
 * Input: 6
 * Output: true
 * Explanation:
 * We get 9 after rotating 6, 9 is a valid number and 9!=6.
 * Example 2:
 * Input: 89
 * Output: true
 * Explanation:
 * We get 68 after rotating 89, 86 is a valid number and 86!=89.
 * Example 3:
 * Input: 11
 * Output: false
 * Explanation:
 * We get 11 after rotating 11, 11 is a valid number but the value remains the same, thus 11 is not a confusing number.
 * Example 4:
 * Input: 25
 * Output: false
 * Explanation:
 * We get an invalid number after rotating 25.
 */

/*
 * Note:
 * 0 <= N <= 10^9
 * After the rotation we can ignore leading zeros, for example if after rotation we have 0008 then this number is considered as just 8
 */

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    // N: [0, 1e9]
    bool confusingNumber(int N) {
        if(N == 0) return false;
        vector<int> digits;
        while(N)
        {
            int cur = N % 10;
            digits.push_back(cur);
            N /= 10;
        }
        unordered_set<int> setting({0, 1, 6, 8, 9});
        bool flag = false; // 一个 69，且对称位置不是 96, 或者在中间
        // 0, 1, 6, 8, 9
        // 所有数字均为 01689
        // 至少有1个为69, 且对称位置不是 96, 或者在中间
        int m = digits.size();
        int left = 0, right = m - 1;
        while(left < right)
        {
            if(setting.count(digits[left]) == 0)
                return false;
            if(setting.count(digits[right]) == 0)
                return false;
            if(digits[left] != digits[right])
            {
                if(!(digits[left] == 6 && digits[right] == 9) &&
                   !(digits[left] == 9 && digits[right] == 6))
                    flag = true;
            }
            else
            {
                if(digits[left] == 6 || digits[left] == 9)
                    flag = true;
            }
            ++left;
            --right;
        }
        if(right == left)
        {
            if(setting.count(digits[left]) == 0)
                return false;
            if(digits[left] == 6 || digits[right] == 9)
                flag = true;
        }
        return flag;
    }
};
