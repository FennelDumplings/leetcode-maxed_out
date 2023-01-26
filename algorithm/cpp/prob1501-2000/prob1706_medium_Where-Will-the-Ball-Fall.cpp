#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findBall(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<int> result(m, -1);
        for(int k = 0; k < m; ++k)
        {
            int i = 0;
            int j = k;
            while(i < n)
            {
                if(grid[i][j] == 1)
                {
                    if(j + 1 >= m)
                        break;
                    if(grid[i][j + 1] == -1)
                        break;
                    j += 1;
                }
                else
                {
                    if(j - 1 < 0)
                        break;
                    if(grid[i][j - 1] == 1)
                        break;
                    j -= 1;
                }
                i += 1;
            }
            if(i == n)
                result[k] = j;
        }
        return result;
    }
};
