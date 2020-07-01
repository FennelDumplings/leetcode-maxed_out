// prob258: Add Digits

/*
 * Given a non-negative integer num, repeatedly add all its digits until the result has only one digit.
 */

/*
 * Example:
 * Input: 38
 * Output: 2
 * Explanation: The process is like: 3 + 8 = 11, 1 + 1 = 2.
 */

class Solution {
public:
    int addDigits(int num) {
        while(num / 10 != 0)
        {
            num = sum_digits(num);
        }
        return num;
    }

private:
    int sum_digits(int num)
    {
        // 调用方保证 num >= 10
        int sum = 0;
        while(num)
        {
            sum += num % 10;
            num /= 10;
        }
        return sum;
    }
};

// 100x + 10y + z = 99x + 9y + x + y + z
class Solution
{
public:
    int addDigits(int num)
    {
        return (num - 1) % 9 + 1;
    }
};
