// prob1007: Minimum Domino Rotations For Equal Row

/*
 * https://leetcode-cn.com/problems/minimum-domino-rotations-for-equal-row/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int minDominoRotations(vector<int>& A, vector<int>& B) {
        int n = A.size();
        vector<int> up(7), down(7);
        vector<vector<int>> idxs(7);
        for(int i = 0; i < n; ++i)
        {
            ++up[A[i]];
            ++down[B[i]];
            idxs[A[i]].push_back(i);
            if(A[i] != B[i])
                idxs[B[i]].push_back(i);
        }
        for(int t = 1; t <= 6; ++t)
            if((int)idxs[t].size() == n)
                return min(up[t], down[t]) - (up[t] + down[t] - n);
        return -1;
    }
};
