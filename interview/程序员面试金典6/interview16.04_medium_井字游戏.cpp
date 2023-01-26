// interview16.04: 井字游戏

/*
 * https://leetcode-cn.com/problems/tic-tac-toe-lcci/
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string tictactoe(vector<string>& board) {
        // N * N
        // 1 <= N <= 100
        int N = board.size();
        // O, X
        bool draw = true;
        for(int i = 0; i < N; ++i)
        {
            // 行
            char cur = board[i][0];
            if(cur == ' ')
            {
                draw = false;
                continue;
            }
            bool flag = true;
            for(int j = 1; j < N; ++j)
            {
                if(board[i][j] != cur)
                {
                    flag = false;
                    if(board[i][j] == ' ')
                        draw = false;
                    if(!draw)
                        break;
                }
            }
            if(flag)
                return string(1, cur);
        }
        for(int j = 0; j < N; ++j)
        {
            // 列
            char cur = board[0][j];
            if(cur == ' ')
                continue;
            bool flag = true;
            for(int i = 1; i < N; ++i)
            {
                if(board[i][j] != cur)
                {
                    flag = false;
                    break;
                }
            }
            if(flag)
                return string(1, cur);
        }
        char cur = board[0][0];
        bool flag = true;
        if(cur != ' ')
        {
            for(int i = 1; i < N; ++i)
                if(board[i][i] != cur)
                {
                    flag = false;
                    break;
                }
            if(flag)
                return string(1, cur);
        }
        cur = board[0][N - 1];
        flag = true;
        if(cur != ' ')
        {
            for(int i = 1; i < N; ++i)
                if(board[i][N - 1 - i] != cur)
                {
                    flag = false;
                    break;
                }
            if(flag)
                return string(1, cur);
        }
        if(draw)
            return "Draw";
        return "Pending";
    }
};

