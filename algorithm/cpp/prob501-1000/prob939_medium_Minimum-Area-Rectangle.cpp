// prob939: Minimum Area Rectangle

/*
 * https://leetcode-cn.com/problems/minimum-area-rectangle/
 */

#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <climits>

using namespace std;

// 按列排序
class Solution_2 {
public:
    int minAreaRect(vector<vector<int>>& points) {
        int n = points.size();
        map<int, unordered_set<int>> mapping;
        for(int i = 0; i < n; ++i)
        {
            int x = points[i][0], y = points[i][1];
            mapping[y].insert(x);
        }
        int ans = INT_MAX / 2;
        auto it = mapping.begin();
        while(it != mapping.end())
        {
            int y0 = it -> first;
            vector<int> xs((it -> second).begin(), (it -> second).end());
            ++it;
            int m = xs.size();
            if(m == 1)
                continue;
            for(int i = 0; i < m - 1; ++i)
                for(int j = i + 1; j < m; ++j)
                {
                    int x1 = xs[i];
                    int x2 = xs[j];
                    auto ity = it;
                    while(ity != mapping.end())
                    {
                        if((ity -> second).count(x1) > 0 && (ity -> second).count(x2) > 0)
                        {
                            ans = min(ans, abs(x1 - x2) * abs(ity -> first - y0));
                            break;
                        }
                        ++ity;
                    }
                }
        }
        if(ans == INT_MAX / 2)
            return 0;
        return ans;
    }
};

// 枚举对角线
class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        unordered_set<int> setting;
        int base = 4e4 + 7;
        for(vector<int>& p: points)
            setting.insert(p[0] * base + p[1]);
        int n = points.size();
        int ans = INT_MAX / 2;
        for(int i = 0; i < n - 1; ++i)
            for(int j = i + 1; j < n; ++j)
            {
                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];
                if(x1 == x2 || y1 == y2)
                    continue;
                if(setting.count(x1 * base + y2) > 0 && setting.count(x2 * base + y1) > 0)
                    ans = min(ans, abs(x1 - x2) * abs(y1 - y2));
            }
        if(ans == INT_MAX / 2)
            return 0;
        return ans;
    }
};
