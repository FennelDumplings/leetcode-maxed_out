#include <vector>

using namespace std;

class Solution {
public:
    int totalMoney(int n) {
        // 完整的周数 p，最后一周的天数 q
        // n = 7p + q
        // 1 2 3 4 5 6 7
        // 2 3 4 5 6 7 8
        // 3 4
        int p = n / 7;
        int q = n % 7;
        int ans = 0;
        if(p > 0)
            ans += sum(p);
        // 最后一行第一个数 p + 1
        if(q > 0)
            ans += ((p + 1) + (p + 1 + (q - 1))) * q / 2;
        return ans;
    }

    int sum(int i)
    {
        // sum(i) = (f(1) + f(i)) * i / 2, 前 i 周总钱数
        return (f(1) + f(i)) * i / 2;
    }

    int f(int i)
    {
        // f(i) = 21 + 7 * i, 第 i 周总钱数
        return 21 + 7 * i;
    }
};
