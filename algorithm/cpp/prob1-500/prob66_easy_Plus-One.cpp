// prob67: Plus One

/*
 * Given a non-empty array of digits representing a non-negative integer, plus one to the integer.
 * The digits are stored such that the most significant digit is at the head of the list, and each element in the array contain a single digit.
 * You may assume the integer does not contain any leading zero, except the number 0 itself.
 */

/*
 * Example 1:
 * Input: [1,2,3]
 * Output: [1,2,4]
 * Explanation: The array represents the integer 123.
 * Example 2:
 * Input: [4,3,2,1]
 * Output: [4,3,2,2]
 * Explanation: The array represents the integer 4321.
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        vector<int> result = digits;
        reverse(result.begin(), result.end());
        int sum = 1 + result[0];
        result[0] = sum % 10;
        int carry = sum / 10;
        for(int i = 1; i < n; ++i)
        {
            sum = result[i] + carry;
            result[i] = sum % 10;
            carry = sum / 10;
        }
        if(carry) result.push_back(1);
        reverse(result.begin(), result.end());
        return result;
    }
};
