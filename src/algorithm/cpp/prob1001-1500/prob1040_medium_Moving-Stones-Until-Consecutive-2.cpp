// prob1040: Moving Stones Until Consecutive II

/*
 * https://leetcode-cn.com/problems/moving-stones-until-consecutive-ii/
 */

#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> numMovesStonesII(vector<int>& stones) {
        int n = stones.size();
        sort(stones.begin(), stones.end());
        int side_left = stones[1] - stones[0];
        int side_right = stones[n - 1] - stones[n - 2];
        vector<int> result(2, 0);
        result[1] = stones[n - 1] - stones[0] + 1 - n - (min(side_left, side_right) - 1);
        // 长度为 n 的滑窗最多覆盖 k 个石子
        // 最少 n - k 步
        queue<int> q;
        int k = 0;
        int left = -1;
        int right = -1;
        for(int i = 0; i < n; ++i)
        {
            int cur = stones[i];
            // q 中 <= cur - n 的出队
            while(!q.empty() && stones[q.front()] <= cur - n)
                q.pop();
            q.push(i);
            if((int)q.size() == n)
            {
                result[0] = 0;
                break;
            }
            if((int)q.size() == n - 1)
            {
                k = (int)q.size();
                left = q.front();
                right = q.back();
                if(stones[left] == stones[right] - n + 1)
                {
                    result[0] = 1;
                    break;
                }
                else
                    result[0] = 2;
            }
            else if((int)q.size() > k)
            {
                k = (int)q.size();
                left = q.front();
                right = q.back();
                result[0] = n - k;
            }
        }
        return result;
    }
};
