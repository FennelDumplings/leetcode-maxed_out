// interview16.14: 最佳直线

/*
 * https://leetcode-cn.com/problems/best-line-lcci/s://leetcode-cn.com/problems/best-line-lcci/
 */

#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <climits>

using namespace std;

class Solution {
public:
    vector<int> bestLine(vector<vector<int>>& points) {
        int n = points.size();
        int max_cnt = 0;
        int p1 = -1, p2 = -1;
        for(int i = 0; i < n - 1; ++i)
        {
            // 经过 points[i] 的直线
            // mapping[i][j] := 方向向量除以最大公约数后为 (i, j) 的点数, i >= 0
            map<int, map<int, set<int>>> mapping;
            vector<int> duplicate(1, i);
            for(int j = i + 1; j < n; ++j)
            {
                int a = points[i][0] - points[j][0];
                int b = points[i][1] - points[j][1];
                if(a == 0 && b == 0)
                {
                    duplicate.push_back(j);
                    continue;
                }
                if(a < 0)
                {
                    a = -a;
                    b = -b;
                }
                if(a != 0 && b != 0)
                {
                    int gcd_ = gcd<int>(abs(a), abs(b));
                    a /= gcd_;
                    b /= gcd_;
                }
                else if(b != 0)
                    b = INT_MAX / 2;
                else if(a != 0)
                    a = INT_MAX / 2;
                mapping[a][b].insert(j);
            }
            for(auto a: mapping)
                for(auto b: a.second)
                {
                    set<int> &setting = b.second;
                    for(int i: duplicate)
                        setting.insert(i);
                    if((int)setting.size() > max_cnt)
                    {
                        max_cnt = b.second.size();
                        p1 = *setting.begin();
                        p2 = *++(setting.begin());
                    }
                    else if((int)setting.size() == max_cnt)
                    {
                        if(*setting.begin() < p1)
                        {
                            p1 = *setting.begin();
                            p2 = *++(setting.begin());
                        }
                        else if(*setting.begin() == p1 && *++setting.begin() < p2)
                        {
                            p2 = *++(setting.begin());
                        }
                    }
                }
        }
        return {p1, p2};
    }
};

