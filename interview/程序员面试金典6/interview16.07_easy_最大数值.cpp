// interview16.07: 最大数值

/*
 * https://leetcode-cn.com/problems/maximum-lcci/
 */

#include <cmath>

using namespace std;

class Solution {
public:
    int maximum(int a, int b) {
        using ll = long long;
        return (a + (ll)b + abs((ll)a - (ll)b)) / 2;
    }
};


class Solution_2 {
public:
    int maximum(int a, int b) {
        using ll = long long;
        // max(a, b) = (a + b + abs(a - b)) / 2
        ll diff = (ll)a - (ll)b;
        diff = (diff ^ (diff >> 63)) - (diff >> 63);
        return (a + (ll)b + diff) / 2;
    }
};
