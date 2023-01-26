// prob497: Random Point in Non-overlapping Rectangles

/*
 * https://leetcode-cn.com/problems/random-point-in-non-overlapping-rectangles/
 */

#include <vector>
#include <random>
#include <algorithm>

using namespace std;

class Solution {
public:
    Solution(vector<vector<int>>& rects) {
        int n = rects.size();
        int all = 0;
        for(const vector<int>& rect: rects)
            all += int_num(rect);
        ranges.assign(n, 0.0);
        int pre_sum = int_num(rects[0]);
        for(int i = 1; i < n; ++i)
        {
            ranges[i] = (double)pre_sum / (double)all;
            pre_sum += int_num(rects[i]);
        }
        dre = std::default_random_engine();
        dr = std::uniform_real_distribution<double>(0.0, 1.0);
        this -> rects = rects;
    }

    vector<int> pick() {
        double p = dr(dre);
        auto it = --upper_bound(ranges.begin(), ranges.end(), p);
        int rect_idx = it - ranges.begin();
        int x, y;
        pick_point(rects[rect_idx], x, y);
        return {x, y};
    }

private:
    vector<double> ranges;
    vector<vector<int>> rects;
    std::default_random_engine dre;
    std::uniform_real_distribution<double> dr;

    void pick_point(const vector<int>& rect, int& x, int& y)
    {
        int x1 = rect[0], y1 = rect[1];
        int x2 = rect[2], y2 = rect[3];
        std::uniform_int_distribution<int> di_x(x1, x2);
        x = di_x(dre);
        std::uniform_int_distribution<int> di_y(y1, y2);
        y = di_y(dre);
    }

    int int_num(const vector<int>& rect)
    {
        int w = rect[2] - rect[0] + 1;
        int h = rect[3] - rect[1] + 1;
        return w * h;
    }
};
