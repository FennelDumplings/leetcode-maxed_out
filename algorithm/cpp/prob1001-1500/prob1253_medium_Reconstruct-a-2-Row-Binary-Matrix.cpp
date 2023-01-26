// prob1253: Reconstruct a 2-Row Binary Matrix

/*
 * https://leetcode-cn.com/problems/reconstruct-a-2-row-binary-matrix/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> reconstructMatrix(int upper, int lower, vector<int>& colsum) {
        int m = colsum.size();
        vector<vector<int>> result(2, vector<int>(m, -1));
        for(int j = 0; j < m; ++j)
        {
            if(colsum[j] == 0)
            {
                result[0][j] = 0;
                result[1][j] = 0;
            }
            else if(colsum[j] == 2)
            {
                if(upper == 0 || lower == 0)
                    return {};
                result[0][j] = 1;
                result[1][j] = 1;
                --upper;
                --lower;
            }
            else
            {
                if(lower == 0 && upper == 0)
                    return {};
                if(lower > upper)
                {
                    --lower;
                    result[0][j] = 0;
                    result[1][j] = 1;
                }
                else
                {
                    --upper;
                    result[0][j] = 1;
                    result[1][j] = 0;
                }
            }
        }
        if(upper > 0 || lower > 0)
            return {};
        return result;
    }
};
