#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
        int n = box.size(), m = box[0].size();
        for(int i = 0; i < n; ++i)
        {
            process_col(box[i]);
        }
        vector<vector<char>> rotated(m, vector<char>(n));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                rotated[j][n - 1 - i] = box[i][j];
        return rotated;
    }

private:
    void process_col(vector<char>& row)
    {
        int n = row.size();
        int l = 0;
        while(l < n && row[l] == '*')
            ++l;
        while(l < n)
        {
            // row[l] != '*'
            int r = l;
            int cnt = 0;
            while(r < n && row[r] != '*')
            {
                if(row[r] == '#')
                    ++cnt;
                ++r;
            }
            for(int i = 0; i < cnt; ++i)
                row[r - 1 - i] = '#';
            for(int i = r - 1 - cnt; i >= l; --i)
                row[i] = '.';
            l = r;
            while(l < n && row[l] == '*')
                ++l;
        }
    }
};
