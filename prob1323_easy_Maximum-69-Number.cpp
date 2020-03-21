// prob1323: Maximum 69 Number

/*
 * Given a positive integer num consisting only of digits 6 and 9.
 * Return the maximum number you can get by changing at most one digit (6 becomes 9, and 9 becomes 6).
 */

#include <cmath>

class Solution {
public:
    int maximum69Number (int num) {
        int toggle = 0; // 翻转的数位(最高位的6),0代表没有6
        int result = num;
        int i = 1;
        while(num)
        {
            if(num % 10 == 6)
                toggle = i;
            num /= 10;
            ++i;
        }
        if(toggle == 0) return result;
        result += 3 * pow(10, toggle - 1);
        return result;
    }
};
