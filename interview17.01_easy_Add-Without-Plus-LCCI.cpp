// interview17.01: Add Without Plus LCCI

/*
 * Write a function that adds two numbers. You should not use + or any arithmetic operators.
 */

/*
 * Note:
 * a and b may be 0 or negative.
 * The result fits in 32-bit integer.
 */

// 非递归
class Solution {
public:
    int add(int a, int b) {
        while (b != 0)
        {
            int sum = (a ^ b);
            int carry = ((a & b) << 1);
            a = sum;
            b = carry;
        }
        return a;
    }
};

// 递归
class Solution_2 {
public:
    int add(int a, int b) {
        if(b == 0) return a;
        return add(a ^ b, (unsigned int)(a & b) << 1);
    }
};
