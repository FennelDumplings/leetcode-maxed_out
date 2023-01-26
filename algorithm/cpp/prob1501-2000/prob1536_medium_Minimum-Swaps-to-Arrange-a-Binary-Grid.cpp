// prob1536: Minimum Swaps to Arrange a Binary Grid

/*
 * https://leetcode-cn.com/problems/minimum-swaps-to-arrange-a-binary-grid/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> idxs(n);
        // idxs[i] := [i,..,n-1] 均为 0 的行下标
        for(int i = 0; i < n; ++i) // O(N)
        {
            int j = left_1(grid[i]); // O(N)
            if(j < n)
            {
                for(int k = j; k < n; ++k)
                    idxs[k].push_back(i); // O(N^2)
            }
        }
        for(int i = 1; i < n; ++i)
            if((int)idxs[i].size() < i)
                return -1;
        vector<bool> moved(n, false); // move[i] := 第 i 行是否往前移动过了
        int ans = 0;
        for(int i = 0; i < n - 1; ++i)
        {
            // [i+1..n-1] 都是 0 的最小行号
            int j;
            for(int jj: idxs[i + 1]) // O(N^2)
            {
                if(moved[jj])
                    continue;
                j = jj;
                break;
            }
            int moved_cnt = 0; // [j+1,..n-1] 有多少移动过
            for(int jj = j + 1; jj < n; ++jj) // O(N^2)
                moved_cnt += moved[jj];
            ans += j - i + moved_cnt;
            moved[j] = true;
        }
        return ans;
    }

private:
    int left_1(const vector<int>& row)
    {
        int n = row.size();
        for(int i = n - 1; i >= 0; --i)
            if(row[i] == 1)
                return i + 1;
        return 0;
    }
};
