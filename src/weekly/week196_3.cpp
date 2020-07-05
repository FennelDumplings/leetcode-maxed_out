// 20200705
// 3.

#include <vector>

using namespace std;

class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        vector<vector<int>> sums(n + 1, vector<int>(m + 1));
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
                sums[i][j] = sums[i][j - 1] + sums[i - 1][j]
                    - sums[i - 1][j - 1] + mat[i - 1][j - 1];
        int ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                for(int h = 1; h <= i + 1; ++h)
                    for(int w = 1; w < j + 1; ++w)
                    {
                        int x2 = i, y2 = j, x1 = i - h + 1, y1 = j - h + 1;
                        if(sum_region(x1, y1, x2, y2, sums) == w * h)
                            ++ans;
                    }
            }
        return ans;
    }

private:
    int sum_region(int x1, int y1, int x2, int y2, vector<vector<int>>& sums)
    {
        return sums[x2 + 1][y2 + 1] - sums[x2 + 1][y1]
            - sums[x1][y2 + 1] + sums[x1][y1];
    }
};

class Solution_2 {
public:
    int numSubmat(vector<vector<int>>& matrix) {
        if(matrix.empty()) return 0;
        int n = matrix.size(), m = matrix[0].size();
        vector<int> heights(m, 0);
        int result = 0;
        for(int i = 0; i < n; ++i)
        {
            _get_geights(matrix, heights, i);
            int result_i = _max_rec_hist(heights);
            result += result_i;
        }
        return result;
    }

private:
    void _get_geights(vector<vector<int> >& matrix, vector<int>& heights, int i)
    {
        int m = matrix[0].size();
        for(int j = 0; j < m; ++j)
        {
            int cnt = 0;
            int h = i;
            while(h >= 0 && matrix[h][j] == 1)
            {
                ++cnt;
                --h;
            }
            heights[j] = cnt;
        }
    }

    int _max_rec_hist(vector<int>& heights)
    {
        int m = heights.size();
        int result = 0;
        for(int i = 0; i < m; ++i)
        {
            if(heights[i] == 0)
                continue;
            result += heights[i];
            int min_h = heights[i];
            for(int j = i + 1; j < m && heights[j] > 0; ++j)
            {
                min_h = min(min_h, heights[j]);
                result += min_h;
            }
        }
        return result;
    }
};
