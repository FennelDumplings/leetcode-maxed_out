// prob419: Battleships in a Board

/*
 * https://leetcode-cn.com/problems/battleships-in-a-board/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        if(board.empty()) return 0;
        int n = board.size(), m = board[0].size();
        int ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(board[i][j] == '.')
                    continue;
                int cnt = 0;
                if((i - 1) < 0 || board[i - 1][j] == '.')
                    ++cnt;
                if((i + 1) >= n || board[i + 1][j] == '.')
                    ++cnt;
                if((j - 1) < 0 || board[i][j - 1] == '.')
                    ++cnt;
                if((j + 1) >= m || board[i][j + 1] == '.')
                    ++cnt;
                if(cnt == 4)
                    ans += 2;
                else if(cnt == 3)
                    ans++;
            }
        return ans / 2;
    }
};
