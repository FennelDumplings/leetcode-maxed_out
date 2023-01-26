// prob1222: Queens That Can Attack the King

/*
 * https://leetcode-cn.com/problems/queens-that-can-attack-the-king/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> queensAttacktheKing(vector<vector<int>>& queens, vector<int>& king) {
        int n = queens.size();
        int x0 = king[0], y0 = king[1];
        // 维护八个方向离 (x, y) 最近的点
        // (x + k, y) , (x - k, y)
        // (x, y + k) , (x, y - k)
        // (x + k, y + k), (x - k, y - k)
        // (x + k, y - k), (x - k, y + k)
        vector<int> state(8, 8); // 8 个方向的 k(k > 0)
        for(int i = 0; i < n; ++i)
        {
            int x = queens[i][0], y = queens[i][1];
            int k1 = x - x0;
            int k2 = y - y0;
            if(k2 == 0)
            {
                if(k1 > 0)
                    state[0] = min(state[0], k1);
                else
                    state[1] = min(state[1], -k1);
            }
            if(k1 == 0)
            {
                if(k2 > 0)
                    state[2] = min(state[2], k2);
                else
                    state[3] = min(state[3], -k2);
            }
            if(k1 == k2)
            {
                if(k1 > 0)
                    state[4] = min(state[4], k1);
                else
                    state[5] = min(state[5], -k1);
            }
            if(k1 == -k2)
            {
                if(k1 > 0)
                    state[6] = min(state[6], k1);
                else
                    state[7] = min(state[7], -k1);
            }
        }
        vector<vector<int>> result;
        if(state[0] < 8)
            result.push_back({x0 + state[0], y0});
        if(state[1] < 8)
            result.push_back({x0 - state[1], y0});
        if(state[2] < 8)
            result.push_back({x0, y0 + state[2]});
        if(state[3] < 8)
            result.push_back({x0, y0 - state[3]});
        if(state[4] < 8)
            result.push_back({x0 + state[4], y0 + state[4]});
        if(state[5] < 8)
            result.push_back({x0 - state[5], y0 - state[5]});
        if(state[6] < 8)
            result.push_back({x0 + state[6], y0 - state[6]});
        if(state[7] < 8)
            result.push_back({x0 - state[7], y0 + state[7]});
        return result;
    }
};
