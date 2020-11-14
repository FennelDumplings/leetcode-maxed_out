// prob470: Implement Rand10() Using Rand7()

/*
 * https://leetcode-cn.com/problems/implement-rand10-using-rand7/
 */

// The rand7() API is already defined for you.
int rand7();
// @return a random integer in the range 1 to 7

class Solution {
public:
    int rand10() {
        while (true) {
            int x1 = rand7();
            int x2 = rand7();
            int x = x2 + (x1 - 1) * 7;
            if (x <= 40)
                return 1 + x % 10;
            int y = x - 40;
            int x3 = rand7();
            // get uniform dist from 1 - 63
            x = x3 + (y - 1) * 7;
            if (x <= 60)
                return 1 + x % 10;
            int z = x - 60;
            int x4 = rand7();
            // get uniform dist from 1 - 21
            x = x4 + (z - 1) * 7;
            if (x <= 20)
                return 1 + x % 10;
        }
    }
};
