// prob798: Smallest Rotation with Highest Score

/*
 * https://leetcode-cn.com/problems/smallest-rotation-with-highest-score/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int bestRotation(vector<int>& A) {
        int n = A.size();
        vector<int> left(n); // left[i] := 左端点在 i 的区间个数
        vector<int> right(n); // right[i] := 右端点在 i 的区间个数
        for(int i = 0; i < n; ++i)
        {
            if(i - A[i] >= 0 && i - A[i] < i)
            {
                ++left[0];
                ++right[i - A[i]];
                if(i < n - 1)
                {
                    ++left[i + 1];
                    ++right[n - 1];
                }
            }
            else if(i - A[i] < 0 && i + 1 <= i - A[i] + n)
            {
                ++left[i + 1];
                ++right[i - A[i] + n];
            }
        }
        int max_cnt = 0;
        int idx = 0;
        int cnt = 0;
        for(int i = 0; i < n; ++i)
        {
            cnt += left[i];
            if(cnt > max_cnt)
            {
                idx = i;
                max_cnt = cnt;
            }
            cnt -= right[i];
        }
        return idx;
    }
};
