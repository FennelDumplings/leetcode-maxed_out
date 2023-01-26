// prob1105: Filling Bookcase Shelves

/*
 * https://leetcode-cn.com/problems/filling-bookcase-shelves/
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minHeightShelves(vector<vector<int>>& books, int shelf_width) {
        int n = books.size();
        dp = vector<int>(n, -1);
        dp[0] = books[0][1];
        max_width = shelf_width;
        // dp[i] := [0..i] 的最小高度
        return solve(books, n - 1);
    }

private:
    vector<int> dp;
    int max_width;

    int solve(const vector<vector<int>>& books, int i)
    {
        if(i == -1)
            return 0;
        if(dp[i] != -1)
            return dp[i];
        int cur_w = books[i][0];
        int cur_h = books[i][1];
        int ans = cur_h + solve(books, i - 1);
        int j = i - 1;
        while(j >= 0 && cur_w < max_width)
        {
            cur_w += books[j][0];
            if(cur_w <= max_width)
            {
                cur_h = max(cur_h, books[j][1]);
                ans = min(ans, cur_h + solve(books, j - 1));
            }
            --j;
        }
        return dp[i] = ans;
    }
};
