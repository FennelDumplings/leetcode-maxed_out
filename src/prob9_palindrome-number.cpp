// Prob9 Palindrome Number

/*
 * Determine whether an integer is a palindrome.
 * An integer is a palindrome when it reads the same backward as forward.
 */

/*
 * Example 1:
 * Input: 121
 * Output: true
 *
 * Example 2:
 * Input: -121
 * Output: false
 * Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
 *
 * Example 3:
 * Input: 10
 * Output: false
 * Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
 */

#include <iostream>
#include <vector>
#include <climits>
using namespace std;


class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0) return false;
        if(x == 0) return true;
        if(x % 10 == 0) return false;

        vector<int> digits;
        for(; x; x /= 10)
        {
            int r = x % 10;
            digits.push_back(r);
        }
        int left = 0;
        int right = digits.size() - 1;
        while(right > left)
        {
            if(digits[left] != digits[right])
                return false;
            --right;
            ++left;
        }
        return true;
    }
};

// 优化：不用 vector
// 注意判断溢出
class Solution_2 {
public:
    bool isPalindrome(int x) {
        if(x < 0) return false;
        if(x == 0) return true;
        if(x % 10 == 0) return false;

        int reversed = 0;
        for(int i = x; i > 0; i /= 10)
        {
            int r = i % 10;
            if(reversed > (INT_MAX - r) / 10)
                return false;
            reversed = reversed * 10 + r;
        }
        return reversed == x;
    }
};

// 优化
// 问题: 我们如何知道反转数字的位数已经达到原始数字位数的一半？
// 我们将原始数字除以 10，然后给反转后的数字乘上 10，当原始数字小于反转后的数字时，就意味着我们已经处理了一半位数的数字。
class Solution_3 {
public:
    bool isPalindrome(int x) {
        if(x < 0) return false;
        if(x == 0) return true;
        if(x % 10 == 0) return false;
        int revertedNumber = 0;
        while(x > revertedNumber) {
            revertedNumber = revertedNumber * 10 + x % 10;
            x /= 10;
        }

        // 当数字长度为奇数时，我们可以通过 revertedNumber/10 去除处于中位的数字。
        // 例如，当输入为 12321 时，在 while 循环的末尾我们可以得到 x = 12，revertedNumber = 123，
        // 由于处于中位的数字不影响回文（它总是与自己相等），所以我们可以简单地将其去除。
        return x == revertedNumber || x == revertedNumber/10;
    }
};


int main()
{
    int x;
    cout << "input x: " << endl;
    cin >> x;

    Solution solution;
    bool result = solution.isPalindrome(x);
    cout << result << endl;
}
