// prob945: Minimum Increment to Make Array Unique

/*
 * Given an array of integers A, a move consists of choosing any A[i], and incrementing it by 1.
 * Return the least number of moves to make every value in A unique.
 */

/*
 * Note:
 * 0 <= A.length <= 40000
 * 0 <= A[i] < 40000
 */

/*
 * Example 1:
 * Input: [1,2,2]
 * Output: 1
 * Explanation:  After 1 move, the array could be [1, 2, 3].
 * Example 2:
 * Input: [3,2,1,2,1,7]
 * Output: 6
 * Explanation:  After 6 moves, the array could be [3, 4, 1, 2, 5, 7].
 * It can be shown with 5 or less moves that it is impossible for the array to have all unique values.
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minIncrementForUnique(vector<int>& A) {
        int n = A.size();
        if(n < 2) return 0;
        int M = 40000;
        _countingsort(A, M);
        int cur = A[0];
        int res = 0;
        for(int i = 1; i < n; ++i)
        {
            if(A[i] > cur)
                cur = A[i];
            else
            {
                res += cur - A[i] + 1;
                ++cur;
            }
        }
        return res;
    }

private:
    void _countingsort(vector<int>& A, int M)
    {
        vector<int> cnt(M, 0);
        for(int num: A) ++cnt[num];
        int n = A.size();
        int j = 0;
        for(int i = 0; i < (int)cnt.size(); ++i)
        {
            int k = cnt[i];
            while(k > 0)
            {
                A[j] = i;
                ++j;
                --k;
            }
            if(j == n) break;
        }
    }
};

// 解决哈希冲突的线性探测
class Solution_3 {
public:
    int minIncrementForUnique(vector<int>& A) {
        if (A.empty()) return 0;
        int res = 0;
        // -1表示空位
        vector<int> pos(80000, -1);
        // 遍历每个数字a对其寻地址得到位置b, b比a的增量就是操作数。
        for (int a: A)
        {
            int b = _findPos(a, pos);
            res += b - a;
        }
        return res;
    }

    // 线性探测寻址(状态压缩)
    int _findPos(int a, vector<int>& pos)
    {
        int b = pos[a];
        // a对应的位置pos[a]是空位，直接放入
        if (b == -1)
        {
            pos[a] = a;
            return a;
        }
        // 向后寻址
        b = _findPos(b + 1, pos);
        pos[a] = b;
        return b;
    }
};
