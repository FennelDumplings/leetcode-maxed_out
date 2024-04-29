#include <queue>
#include <vector>
#include <climits>


struct Item
{
    int dp, idx;
    Item(){}
    Item(int dp, int idx):dp(dp),idx(idx){}
    bool operator<(const Item& other) const
    {
        return dp < other.dp;
    }
};

struct HeapCmp
{
    bool operator()(const Item& i1, const Item& i2) const
    {
        return i1.dp > i2.dp;
    }
};

class Solution {
public:
    int minimumVisitedCells(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<priority_queue<Item, vector<Item>, HeapCmp>> row_heaps(m);
        vector<priority_queue<Item, vector<Item>, HeapCmp>> col_heaps(n);

        vector<vector<int>> dp(m, vector<int>(n, -1));
        dp[0][0] = 0;
        row_heaps[0].push(Item(dp[0][0], 0));
        col_heaps[0].push(Item(dp[0][0], 0));

        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
            {
                if(i == 0 && j == 0)
                    continue;
                int minx = INT_MAX / 2;
                while(!row_heaps[i].empty())
                {
                    Item top_item = row_heaps[i].top();
                    if(top_item.idx + grid[i][top_item.idx] < j)
                        row_heaps[i].pop();
                    else
                    {
                        minx = min(minx, top_item.dp);
                        break;
                    }
                }
                while(!col_heaps[j].empty())
                {
                    Item top_item = col_heaps[j].top();
                    if(top_item.idx + grid[top_item.idx][j] < i)
                        col_heaps[j].pop();
                    else
                    {
                        minx = min(minx, top_item.dp);
                        break;
                    }
                }
                if(minx != INT_MAX / 2)
                {
                    dp[i][j] = minx + 1;
                    row_heaps[i].push(Item(dp[i][j], j));
                    col_heaps[j].push(Item(dp[i][j], i));
                }
            }
        if(dp[m - 1][n - 1] == -1)
            return -1;
        return dp[m - 1][n - 1] + 1;
    }
};
