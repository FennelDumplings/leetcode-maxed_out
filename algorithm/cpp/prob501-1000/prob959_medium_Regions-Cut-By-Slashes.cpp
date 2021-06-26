// prob959: Regions Cut By Slashes

/*
 * In a N x N grid composed of 1 x 1 squares, each 1 x 1 square consists of a /, \, or blank space.  These characters divide the square into contiguous regions.
 * (Note that backslash characters are escaped, so a \ is represented as "\\".)
 * Return the number of regions.
 */

/*
 * Example 1:
 * Input:
 * [
 *   " /",
 *   "/ "
 * ]
 * Output: 2
 * Explanation: The 2x2 grid is as follows:
 * Example 2:
 * Input:
 * [
 *   " /",
 *   "  "
 * ]
 * Output: 1
 * Explanation: The 2x2 grid is as follows:
 * Example 3:
 * Input:
 * [
 *   "\\/",
 *   "/\\"
 * ]
 * Output: 4
 * Explanation: (Recall that because \ characters are escaped, "\\/" refers to \/, and "/\\" refers to /\.)
 * The 2x2 grid is as follows:
 * Example 4:
 * Input:
 * [
 *   "/\\",
 *   "\\/"
 * ]
 * Output: 5
 * Explanation: (Recall that because \ characters are escaped, "/\\" refers to /\, and "\\/" refers to \/.)
 * The 2x2 grid is as follows:
 * Example 5:
 * Input:
 * [
 *   "//",
 *   "/ "
 * ]
 * Output: 3
 * Explanation: The 2x2 grid is as follows:
 */

/*
 * Note:
 * 1 <= grid.length == grid[0].length <= 30
 * grid[i][j] is either '/', '\', or ' '.
 */

#include <vector>
#include <string>

using namespace std;

class UnionFindSet
{
public:
    UnionFindSet(int N):N(N)
    {
        int n = N * N * 4;
        _rank = vector<int>(n, 0);
        _father = vector<int>(n, 0);
        for(int i = 0; i < n; ++i)
            _father[i] = i;
    }

    void merge(int a, int b)
    {
        int x = _find(a);
        int y = _find(b);
        if(x == y)
            return;
        if(_rank[x] < _rank[y])
            _father[x] = y;
        else
        {
            _father[y] = x;
            if(_rank[x] == _rank[y])
                ++_rank[x];
        }
    }

    int stat()
    {
        int result = 0;
        int n = _father.size();
        for(int i = 0; i < n; ++i)
        {
            if(_father[i] == i)
            {
                ++result;
            }
        }
        return result;
    }

private:
    vector<int> _father;
    vector<int> _rank;
    int N;

    int _find(int x)
    {
        if(_father[x] == x)
            return x;
        return _father[x] = _find(_father[x]);
    }
};

class Solution {
public:
    int regionsBySlashes(vector<string>& grid) {
        int n = grid.size();
        for(int i = 0; i < n; ++i)
        {
            string &row = grid[i];
            int iter = 0;
            int pos = 0;
            while(iter < n)
            {
                row[pos] = row[iter];
                ++pos;
                ++iter;
            }
        }
        UnionFindSet unionfindset(n);
        // 0, 左
        // 1, 上
        // 2, 右
        // 3, 下
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
            {
                if(grid[i][j] == ' ')
                {
                    // (i, j) 0, (i, j-1) 2
                    // (i, j) 1, (i-1, j) 3
                    // (i, j) 2, (i, j+1) 0
                    // (i, j) 3, (i+1, j) 1
                    unionfindset.merge(to_idx(i, j, 0, n), to_idx(i, j, 1, n));
                    unionfindset.merge(to_idx(i, j, 1, n), to_idx(i, j, 2, n));
                    unionfindset.merge(to_idx(i, j, 2, n), to_idx(i, j, 3, n));
                    if(i - 1 >= 0)
                        unionfindset.merge(to_idx(i, j, 1, n), to_idx(i - 1, j, 3, n));
                    if(i + 1 < n)
                        unionfindset.merge(to_idx(i, j, 3, n), to_idx(i + 1, j, 1, n));
                    if(j - 1 >= 0)
                        unionfindset.merge(to_idx(i, j, 0, n), to_idx(i, j - 1, 2, n));
                    if(j + 1 < n)
                        unionfindset.merge(to_idx(i, j, 2, n), to_idx(i, j + 1, 0, n));
                }
                else if(grid[i][j] == '\\')
                {
                    // (i, j) 1, (i-1, j) 3
                    // (i, j) 2, (i, j+1) 0
                    unionfindset.merge(to_idx(i, j, 1, n), to_idx(i, j, 2, n));
                    if(i - 1 >= 0)
                        unionfindset.merge(to_idx(i, j, 1, n), to_idx(i - 1, j, 3, n));
                    if(j + 1 < n)
                        unionfindset.merge(to_idx(i, j, 2, n), to_idx(i, j + 1, 0, n));
                    // (i, j) 0, (i, j-1) 2
                    // (i, j) 3, (i+1, j) 1
                    unionfindset.merge(to_idx(i, j, 0, n), to_idx(i, j, 3, n));
                    if(i + 1 < n)
                        unionfindset.merge(to_idx(i, j, 3, n), to_idx(i + 1, j, 1, n));
                    if(j - 1 >= 0)
                        unionfindset.merge(to_idx(i, j, 0, n), to_idx(i, j - 1, 2, n));
                }
                else
                {
                    // (i, j) 0, (i, j-1) 2
                    // (i, j) 1, (i-1, j) 3
                    unionfindset.merge(to_idx(i, j, 0, n), to_idx(i, j, 1, n));
                    if(i - 1 >= 0)
                        unionfindset.merge(to_idx(i, j, 1, n), to_idx(i - 1, j, 3, n));
                    if(j - 1 >= 0)
                        unionfindset.merge(to_idx(i, j, 0, n), to_idx(i, j - 1, 2, n));
                    // (i, j) 2, (i, j+1) 0
                    // (i, j) 3, (i+1, j) 1
                    unionfindset.merge(to_idx(i, j, 2, n), to_idx(i, j, 3, n));
                    if(j + 1 < n)
                        unionfindset.merge(to_idx(i, j, 2, n), to_idx(i, j + 1, 0, n));
                    if(i + 1 < n)
                        unionfindset.merge(to_idx(i, j, 3, n), to_idx(i + 1, j, 1, n));
                }
            }
        return unionfindset.stat();
    }

private:
    int to_idx(int i, int j, int d, int n)
    {
        return i * (4 * n) + j * 4 + d;
    }
};
