// prob764: Largest Plus Sign

/*
 * https://leetcode-cn.com/problems/largest-plus-sign/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int orderOfLargestPlusSign(int N, vector<vector<int>>& mines) {
        vector<vector<int>> grid(N, vector<int>(N, 1));
        for(const vector<int>& z: mines)
            grid[z[0]][z[1]] = 0;
        vector<vector<int>> L(N, vector<int>(N, 0)), R(N, vector<int>(N, 0)),
            T(N, vector<int>(N, 0)), B(N, vector<int>(N, 0));
        for(int i = 0; i < N; ++i)
        {
            // L
            if(grid[i][0] == 1)
                L[i][0] = 1;
            for(int j = 1; j < N; ++j)
                if(grid[i][j] == 1)
                    L[i][j] = L[i][j - 1] + 1;
            // R
            if(grid[i][N - 1] == 1)
                R[i][N - 1] = 1;
            for(int j = N - 2; j >= 0; --j)
                if(grid[i][j] == 1)
                    R[i][j] = R[i][j + 1] + 1;
        }
        for(int j = 0; j < N; ++j)
        {
            // T
            if(grid[0][j] == 1)
                T[0][j] = 1;
            for(int i = 1; i < N; ++i)
                if(grid[i][j] == 1)
                    T[i][j] = T[i - 1][j] + 1;
            // B
            if(grid[N - 1][j] == 1)
                B[N - 1][j] = 1;
            for(int i = N - 2; i >= 0; --i)
                if(grid[i][j] == 1)
                    B[i][j] = B[i + 1][j] + 1;
        }
        int ans = 0;
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j)
            {
                if(grid[i][j] == 1)
                {
                    int len = L[i][j];
                    len = min(len, R[i][j]);
                    len = min(len, T[i][j]);
                    len = min(len, B[i][j]);
                    ans = max(ans, len);
                }
            }
        return ans;
    }
};
