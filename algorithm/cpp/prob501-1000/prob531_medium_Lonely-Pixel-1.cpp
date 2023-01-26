// prob531: Lonely Pixel I

/*
 * Given a picture consisting of black and white pixels, find the number of black lonely pixels.
 * The picture is represented by a 2D char array consisting of 'B' and 'W', which means black and white pixels respectively.
 * A black lonely pixel is character 'B' that located at a specific position where the same row and same column don't have any other black pixels.
 */

/*
 * Example:
 * Input:
 * [['W', 'W', 'B'],
 *  ['W', 'B', 'W'],
 *  ['B', 'W', 'W']]
 * Output: 3
 * Explanation: All the three 'B's are black lonely pixels.
 */

/*
 * Note:
 * The range of width and height of the input 2D array is [1,500].
 */

#include <vector>

using namespace std;

class Solution {
public:
    int findLonelyPixel(vector<vector<char>>& picture) {
        int n = picture.size(), m = picture[0].size();
        vector<int> row(n, -2);
        vector<int> col(m, -2);
        for(int i = 0; i < n; ++i)
        {
            int cnt = 0;
            for(int j = 0; j < m; ++j)
            {
                if(picture[i][j] == 'B')
                {
                    ++cnt;
                    row[i] = j;
                    if(cnt > 1)
                    {
                        row[i] = -1;
                        break;
                    }
                }
            }
            if(cnt == 0)
                row[i] = -1;
        }
        for(int j = 0; j < m; ++j)
        {
            int cnt = 0;
            for(int i = 0; i < n; ++i)
            {
                if(picture[i][j] == 'B')
                {
                    ++cnt;
                    col[j] = i;
                    if(cnt > 1)
                    {
                        col[j] = -1;
                        break;
                    }
                }
            }
            if(cnt == 0)
                col[j] = -1;
        }
        int result = 0;
        for(int j: row)
            if(col[j] != -1 && col[j] != -2)
                ++result;
        return result;
    }
};
