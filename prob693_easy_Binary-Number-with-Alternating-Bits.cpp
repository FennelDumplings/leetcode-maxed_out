// prob693: Binary Number with Alternating Bits

/*
 * Given a positive integer, check whether it has alternating bits: namely, if two adjacent bits will always have different values.
 */

/*
 * Example 1:
 * Input: 5
 * Output: True
 * Explanation:
 * The binary representation of 5 is: 101
 * Example 2:
 * Input: 7
 * Output: False
 * Explanation:
 * The binary representation of 7 is: 111.
 * Example 3:
 * Input: 11
 * Output: False
 * Explanation:
 * The binary representation of 11 is: 1011.
 * Example 4:
 * Input: 10
 * Output: True
 * Explanation:
 * The binary representation of 10 is: 1010.
 */

class Solution {
public:
    bool hasAlternatingBits(int n) {
        int h = high_bit(n);
        for(int i = 0; i <= 31 && (1 << i) < h; ++i)
        {
            if((bool)(n & (1 << i)) == (bool)(n & (1 << (i + 1))))
                return false;
        }
        return true;
    }

private:
    int low_bit(int x)
    {
        return x & (-x);
    }

    int high_bit(int x)
    {
        int p = low_bit(x);
        while(p != x)
        {
            x -= p;
            p = low_bit(x);
        }
        return p;
    }
};
