// prob306: Additive Number

/*
 * Additive number is a string whose digits can form additive sequence.
 * A valid additive sequence should contain at least three numbers. Except for the first two numbers, each subsequent number in the sequence must be the sum of the preceding two.
 * Given a string containing only digits '0'-'9', write a function to determine if it's an additive number.
 * Note: Numbers in the additive sequence cannot have leading zeros, so sequence 1, 2, 03 or 1, 02, 3 is invalid.
 */

/*
 * Example 1:
 * Input: "112358"
 * Output: true
 * Explanation: The digits can form an additive sequence: 1, 1, 2, 3, 5, 8.
 *              1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
 * Example 2:
 * Input: "199100199"
 * Output: true
 * Explanation: The additive sequence is: 1, 99, 100, 199. 
 *              1 + 99 = 100, 99 + 100 = 199
 */

/*
 * Constraints:
 * num consists only of digits '0'-'9'.
 * 1 <= num.length <= 35
 */

/*
 * Follow up:
 * How would you handle overflow for very large input integers?
 */

#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
    bool isAdditiveNumber(string num) {
        int n = num.size();
        if(n < 3)
            return false;
        for(int i = 0; i < n - 2; ++i)
        {
            for(int j = i + 1; j < n - 1; ++j)
            {
                string n1 = num.substr(0, i + 1);
                string n2 = num.substr(i + 1, j - i);
                if(dfs(n1, n2, num, j + 1))
                    return true;
                if(num[i + 1] == '0')
                    break;
                if(num[j] == '0')
                    continue;
            }
            if(num[0] == '0')
                break;
            if(num[i] == '0')
                continue;
        }
        return false;
    }

private:
    bool dfs(string& n1, string& n2, const string& num, int left)
    {
        int n = num.size();
        if(left == n)
            return true;

        string target = addStrings(n1, n2);
        int len = target.size();
        if(n - left < len)
            return false;
        if(num.substr(left, len) == target)
        {
            n1 = n2, n2 = target;
            return dfs(n1, n2, num, left + len);
        }
        return false;
    }

    // lc415
    string addStrings(const string& num1, const string& num2) {
        string result;
        int carry = 0, i = num1.size() - 1, j = num2.length() - 1;
        while(i >= 0 || j >= 0 || carry != 0){
            if(i >= 0) carry += num1[i--] - '0';
            if(j >= 0) carry += num2[j--] - '0';
            result = char(carry % 10 + '0') + result;
            carry /= 10;
        }
        return result;
    }
};
