#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {
        int N = original.size();
        if(m * n != N)
            return {};
        vector<vector<int>> result(m, vector<int>(n));
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                result[i][j] = original[i * n + j];
        return result;
    }
};
