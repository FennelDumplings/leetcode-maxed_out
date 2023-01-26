// prob 723: Candy Crush

/*
 * https://leetcode-cn.com/problems/candy-crush/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> candyCrush(vector<vector<int>>& board) {
        int n = board.size(), m = board[0].size();
        vector<vector<bool>> label(n, vector<bool>(m, false));
        bool flag = true;
        while(flag)
        {
            flag = false;
            label.assign(n, vector<bool>(m, false));
            for(int i = 0; i < n; ++i)
            {
                int j = 0;
                while(j < m)
                {
                    int right = j + 1;
                    while(right < m && board[i][right] == board[i][j] && board[i][j] != 0)
                        ++right;
                    if(right - j >= 3)
                    {
                        flag = true;
                        for(int k = j; k < right; ++k)
                            label[i][k] = true;
                    }
                    j = right;
                }
            }
            for(int j = 0; j < m; ++j)
            {
                int i = 0;
                while(i < n)
                {
                    int right = i + 1;
                    while(right < n && board[right][j] == board[i][j] && board[i][j] != 0)
                        ++right;
                    if(right - i >= 3)
                    {
                        flag = true;
                        for(int k = i; k < right; ++k)
                            label[k][j] = true;
                    }
                    i = right;
                }
            }
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < m; ++j)
                {
                    if(label[i][j])
                        board[i][j] = 0;
                }
            for(int j = 0; j < m; ++j)
            {
                int iter = n - 1, i = n - 1;
                while(iter >= 0)
                {
                    if(board[i][j] == 0)
                    {
                        int right = iter - 1;
                        while(right >= 0 && label[right][j])
                            --right;
                        if(right >= 0)
                        {
                            board[i][j] = board[right][j];
                            board[right][j] = 0;
                        }
                        iter = right;
                    }
                    else
                        --iter;
                    --i;
                }
            }
        }
        return board;
    }
};
