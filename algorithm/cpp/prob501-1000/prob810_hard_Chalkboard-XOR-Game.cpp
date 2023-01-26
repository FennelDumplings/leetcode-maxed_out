// prob810: Chalkboard XOR Game

/*
 * https://leetcode-cn.com/problems/chalkboard-xor-game/
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool xorGame(vector<int>& nums) {
        int S = 0;
        for(int i: nums) S ^= i;
        if(S == 0)
            return true;
        return !((nums.size()) & 1);
    }
};
