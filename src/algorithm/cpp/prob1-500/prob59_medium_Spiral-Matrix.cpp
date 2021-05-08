// prob59: Spiral Matrix

/*
 * Given a positive integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.
 */

/*
 * Example:
 * Input: 3
 * Output:
 * [
 *  [ 1, 2, 3 ],
 *  [ 8, 9, 4 ],
 *  [ 7, 6, 5 ]
 * ]
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        if(n <= 0) return vector<vector<int>>();
        vector<vector<int> > result(n, vector<int>(n, 0));
        int cnt = 1; // 插入的数字
        for(int i = 0; i <= (n - 1) / 2; ++i)
        {
            int start = i;
            int len = n - 2 * i;
            _generate_boundary(result, cnt, start, len);
        }
        return result;
    }

private:
    void _generate_boundary(vector<vector<int> >& result, int& cnt, int start, int len)
    {
        if(len == 1)
        {
            result[start][start] = cnt;
            ++cnt;
            return;
        }
        for(int j = 0; j < len; ++j)
        {
            result[start][start + j] = cnt;
            ++cnt;
        }
        for(int i = 1; i < len - 1; ++i)
        {
            result[start + i][start + len - 1] = cnt;
            ++cnt;
        }
        for(int j = len - 1; j >= 0; --j)
        {
            result[start + len - 1][start + j] = cnt;
            ++cnt;
        }
        for(int i = len - 2; i >= 1; --i)
        {
            result[start + i][start] = cnt;
            ++cnt;
        }
    }
};
