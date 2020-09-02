// 排布二进制网格的最少交换次数

#include <vector>
#include <algorithm>
#include <deque>
#include <map>

using namespace std;

class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = grid.size();
        if(n == 1) return 0;
        vector<int> rows(n, 0);
        for(int i = 0; i < n; ++i)
        {
            for(int j = n - 1; j >= 0; --j)
            {
                if(grid[i][j] == 1)
                {
                    rows[i] = j + 1;
                    break;
                }
            }
        }
        vector<int> rows_sorted(rows.begin(), rows.end());
        sort(rows_sorted.begin(), rows_sorted.end());
        for(int i = 0; i < n; ++i)
            if(rows_sorted[i] > i + 1)
                return -1;
        multimap<int, int> mapping;
        for(int i = 0; i < n; ++i)
            mapping[]
        deque<int> board(rows.begin(), rows.end());
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            // board[i] > i + 1
            // 最左也要放到 board[i] - 1
            bool flag = true;
            while(flag)
            {
                flag = false;
                if(board[i] <= i + 1)
                    break;
                int cur = board[i];
                ans += cur - 1 - i;
                flag = true;
                board.erase(board.begin() + i);
                auto it = board.begin() + cur - 1;
                board.insert(it, cur);
                for(int i: board) cout << i << " ";
                cout << endl;
            }
        }
        return ans;
    }
};
