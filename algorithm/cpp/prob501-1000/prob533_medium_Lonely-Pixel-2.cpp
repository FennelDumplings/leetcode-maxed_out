// prob533: Lonely Pixel II

/*
 * Given a picture consisting of black and white pixels, and a positive integer N, find the number of black pixels located at some specific row R and column C that align with all the following rules:
 *
 * Row R and column C both contain exactly N black pixels.
 * For all rows that have a black pixel at column C, they should be exactly the same as row R
 * The picture is represented by a 2D char array consisting of 'B' and 'W', which means black and white pixels respectively.
 */

/*
 * Example:
 * Input:
 * [['W', 'B', 'W', 'B', 'B', 'W'],
 *  ['W', 'B', 'W', 'B', 'B', 'W'],
 *  ['W', 'B', 'W', 'B', 'B', 'W'],
 *  ['W', 'W', 'B', 'W', 'B', 'W']]
 *
 * N = 3
 * Output: 6
 * Explanation: All the bold 'B' are the black pixels we need (all 'B's at column 1 and 3).
 *         0    1    2    3    4    5         column index
 * 0    [['W', 'B', 'W', 'B', 'B', 'W'],
 * 1     ['W', 'B', 'W', 'B', 'B', 'W'],
 * 2     ['W', 'B', 'W', 'B', 'B', 'W'],
 * 3     ['W', 'W', 'B', 'W', 'B', 'W']]
 * row index
 *
 * Take 'B' at row R = 0 and column C = 1 as an example:
 * Rule 1, row R = 0 and column C = 1 both have exactly N = 3 black pixels.
 * Rule 2, the rows have black pixel at column C = 1 are row 0, row 1 and row 2. They are exactly the same as row R = 0.
 */

/*
 * Note:
 * The range of width and height of the input 2D array is [1,200].
 */

#include <map>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int findBlackPixel(vector<vector<char>>& picture, int N) {
        int n = picture.size(), m = picture[0].size();
        vector<string> row_str(n);
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < m; ++j)
                row_str[i] += picture[i][j];
        }
        vector<int> cnt_row; // cnt==N -> i1, i2,...
        vector<int> cnt_col; // cnt==N -> j1, j2,...
        for(int i = 0; i < n; ++i)
        {
            int cnt = 0;
            for(int j = 0; j < m; ++j)
            {
                if(picture[i][j] == 'B')
                    ++cnt;
            }
            if(cnt == N)
                cnt_row.push_back(i);
        }
        for(int j = 0; j < m; ++j)
        {
            int cnt = 0;
            for(int i = 0; i < n; ++i)
            {
                if(picture[i][j] == 'B')
                    ++cnt;
            }
            if(cnt == N)
            cnt_col.push_back(j);
        }
        vector<vector<int>> blacks(m);
        for(int j = 0; j < m; ++j)
            for(int i = 0; i < n; ++i)
            {
                if(picture[i][j] == 'B')
                    blacks[j].push_back(i);
            }
        // 枚举 (i, j) 其中 cnt 相同
        int result = 0;
        if(!cnt_col.empty() && !cnt_row.empty())
        {
            for(int j: cnt_col)
            {
                for(int i : cnt_row)
                {
                    bool flag = true;
                    for(int ii: blacks[j])
                    {
                        if(i == ii) continue;
                        if(row_str[i] != row_str[ii])
                        {
                            flag = false;
                            break;
                        }
                    }
                    if(flag)
                    {
                        result += blacks[j].size();
                        break;
                    }
                }
            }
        }
        return result;
    }
};
