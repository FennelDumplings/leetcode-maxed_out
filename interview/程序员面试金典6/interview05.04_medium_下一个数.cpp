// interview05.04: 下一个数

/*
 * https://leetcode-cn.com/problems/closed-number-lcci/
 */

#include <vector>
#include <climits>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> findClosedNumbers(int num) {
        if(num == INT_MAX)
            return {-1, -1};
        vector<int> result({-1, -1});
        int n = (~num);
        int p = n & (-n);
        int i = log2(p);
        // 后缀有 i 个 1
        n = num & (~((1 << i) - 1));
        if(n != 0)
        {
            p = n & (-n);
            int x = n - p;
            int ii = log2(p);
            // 后缀共 ii 位, 其中 i + 1 位是 1
            // 10001   ii = 5, i = 1 右移 (ii - i)
            x |= ((1 << (i + 1)) - 1) << (ii - i - 1);
            result[1] = x;
        }
        n = num;
        int q = n & (-n);
        int j = log2(q);
        int l = 1;
        while(j < 30 && ((num >> (j + 1)) & 1))
        {
            ++j;
            ++l;
        }
        if(j != 30)
        {
            int y = (((1 << (29 - j)) - 1) << (j + 2)) & num;
            y += (1 << (j + 1));
            y += (1 << (l - 1)) - 1;
            result[0] = y;
        }
        return result;
    }
};


// 另解
class Solution_2 {
public:
    vector<int> findClosedNumbers(int num) {
        int n = __builtin_popcount(num);
        int a,b;
        for(a=num+1;a>0;++a){
            if(__builtin_popcount(a)==n) break;
        }
        for(b=num-1;b>0;--b){
            if(__builtin_popcount(b)==n) break;
        }
        return {a>0?a:-1,b>0?b:-1};
    }
};
