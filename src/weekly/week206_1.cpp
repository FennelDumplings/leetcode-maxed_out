
#include <vector>

using namespace std;

class Solution {
public:
    int numSpecial(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            int y = -1;
            for(int j = 0; j < m; ++j)
            {
                if(mat[i][j] == 0)
                    continue;
                if(y != -1)
                    y = -2;
                if(y == -1)
                    y = j;
            }
            if(y >= 0)
            {
                int x = -1;
                for(int k = 0; k < n; ++k)
                {
                    if(mat[k][y] == 0)
                        continue;
                    if(x != -1)
                        x = -2;
                    if(x == -1)
                        x = k;
                }
                if(x >= 0)
                    ++ans;
            }
        }
        return ans;
    }
};
