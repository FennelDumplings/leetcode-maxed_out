// prob991: Broken Calculator

/*
 * https://leetcode-cn.com/problems/broken-calculator/
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int brokenCalc(int X, int Y) {
        return solve(X, Y);
    }

private:
    int solve(int X, int Y)
    {
        if(X == Y) return 0;
        if(X > Y) return X - Y;
        // 若 Y 奇数
        // Y 无法除以 2
        if(Y & 1)
            return 1 + solve(X, Y + 1);
        return 1 + solve(X, Y / 2);
    }

};

