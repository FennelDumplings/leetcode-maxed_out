// prob389: Find the Difference

/*
 * https://leetcode-cn.com/problems/find-the-difference/
 */

#include <string>

using namespace std;

class Solution {
public:
    char findTheDifference(string s, string t) {
        int xor_sum = 0;
        for(const char &ch: s)
            xor_sum ^= (int)ch;
        for(const char &ch: t)
            xor_sum ^= (int)ch;
        return char(xor_sum);
    }
};
