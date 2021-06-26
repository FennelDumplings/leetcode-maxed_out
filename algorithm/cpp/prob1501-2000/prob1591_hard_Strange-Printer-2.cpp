// prob1591: Strange Printer II

/*
 * https://leetcode-cn.com/problems/strange-printer-ii/
 */

#include <vector>
#include <unordered_map>

using namespace std;

struct Rec
{
    int x1, y1, x2, y2;
    Rec(){}
    Rec(int x1, int y1, int x2, int y2):x1(x1),y1(y1),x2(x2),y2(y2){}
};

class Solution {
public:
    bool isPrintable(vector<vector<int>>& targetGrid) {
        vector<vector<int>> &grid = targetGrid;
        int n = grid.size(), m = grid[0].size();
        unordered_map<int, Rec> mapping;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                int color = grid[i][j];
                if(mapping.count(color) == 0)
                    mapping[color] = Rec(i, j, i, j);
                else
                {
                    mapping[color].x1 = min(mapping[color].x1, i);
                    mapping[color].y1 = min(mapping[color].y1, j);
                    mapping[color].x2 = max(mapping[color].x2, i);
                    mapping[color].y2 = max(mapping[color].y2, j);
                }
            }
        while(!getit(grid))
        {
            bool flag = false;
            for(auto color_info: mapping)
            {
                if(check(grid, color_info.first, color_info.second))
                {
                    flag = true;
                    update(grid, color_info.second);
                    mapping.erase(color_info.first);
                    break;
                }
            }
            if(!flag)
                return false;
        }
        return true;
    }

private:
    void update(vector<vector<int>>& grid, const Rec& rec)
    {
        for(int i = rec.x1; i <= rec.x2; ++i)
            for(int j = rec.y1; j <= rec.y2; ++j)
                grid[i][j] = 0;
    }

    bool check(const vector<vector<int>>& grid, const int color, const Rec& rec)
    {
        for(int i = rec.x1; i <= rec.x2; ++i)
            for(int j = rec.y1; j <= rec.y2; ++j)
            {
                if(grid[i][j] != color && grid[i][j] != 0)
                    return false;
            }
        return true;
    }

    bool getit(const vector<vector<int>>& grid)
    {
        int n = grid.size(), m = grid[0].size();
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] != 0)
                    return false;
            }
        return true;
    }
};
