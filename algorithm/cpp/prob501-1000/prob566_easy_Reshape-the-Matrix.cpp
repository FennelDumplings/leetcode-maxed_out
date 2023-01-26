// prob566: Reshape the Matrix

/*
 * https://leetcode-cn.com/problems/reshape-the-matrix/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {
        if(nums.empty()) return {};
        int n = nums.size(), m = nums[0].size();
        if(n * m != r * c) return nums;
        vector<vector<int>> result(r, vector<int>(c, -1));
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
            {
                int idx = i * c + j;
                int x = idx / m;
                int y = idx % m;
                result[i][j] = nums[x][y];
            }
        return result;
    }
};
