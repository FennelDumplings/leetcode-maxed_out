// prob6: ZigZag Conversion

/*
 *
 * The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows
 * like this: (you may want to display this pattern in a fixed font for better legibility)
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if(s.empty()) return s;
        int n = s.size();
        if(numRows == 1) return s;
        int col1 = (numRows - 1) * (n / (2 * numRows - 2));
        int m = n % (2 * numRows - 2);
        int col2 = 0;
        if(0 < m && m <= numRows)
            col2 = 1;
        else if(m > numRows)
            col2 = 1 + (m - numRows);
        int col = col1 + col2;
        vector<vector<char> > z(numRows, vector<char>(col, ' '));
        int dx[2] = {1, -1}, dy[2] = {0, 1};
        int x = 0, y = 0, d = 0;
        for(int i = 0; i < n; ++i)
        {
            if(x + dx[d] > (numRows - 1) || x + dx[d] < 0)
            {
                d = (d + 1) % 2;
            }
            z[x][y] = s[i];
            x = x + dx[d];
            y = y + dy[d];
        }
        string result;
        for(int i = 0; i < numRows; ++i)
        {
            for(int j = 0; j < col; ++j)
            {
                if(z[i][j] != ' ')
                    result += z[i][j];
            }
        }
        return result;
    }
};
