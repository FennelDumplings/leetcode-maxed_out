// interview17: 打印从1到最大的n位数

/*
 * https://leetcode-cn.com/problems/da-yin-cong-1dao-zui-da-de-nwei-shu-lcof/
 */

#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> printNumbers(int n) {
        int N = get(n);
        vector<int> result(N, 0);
        for(int i = 0; i < N; ++i)
            result[i] = i + 1;
        return result;
    }
private:
    int get(int n)
    {
        // 1 -> 9
        // 2 -> 99;
        return pow(10, n) - 1;
    }
};
