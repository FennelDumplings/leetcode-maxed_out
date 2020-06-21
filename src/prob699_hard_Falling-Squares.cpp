// prob999: Falling Squares

/*
 * https://leetcode-cn.com/problems/falling-squares/
 */

/*
 * Note:
 * 1 <= positions.length <= 1000.
 * 1 <= positions[i][0] <= 10^8.
 * 1 <= positions[i][1] <= 10^6.
 */

#include <vector>
#include <map>

using namespace std;

class Ranges
{
public:
    Ranges()
    {
        ranges = map<int, PII>();
        max_h = 0;
    }

    int update(int start, int end, int len)
    {
        // [start, end) 范围的 h 最大值, 返回 h
        IT l, r;
        get_overlap(start, end, l, r);
        // [l, r) 为有重叠的区间
        if(l == r) // [start, end) 范围无已有区间
        {
            ranges.insert(PIP(start, PII(end, len)));
            max_h = max(max_h, len);
            return max_h;
        }
        auto last = r;
        --last;

        bool has_left = false, has_right = false;
        int left_l = l -> first;
        int left_r = start;
        int left_h = (l -> second).second;
        int right_l = end;
        int right_r = (last -> second).first;
        int right_h = (last -> second).second;
        if(left_l < left_r)
            has_left = true;
        if(right_l < right_r)
            has_right = true;

        auto iter = l;
        int h = (iter -> second).second;
        ++iter;
        while(iter != r)
        {
            h = max(h, (iter -> second).second);
            ++iter;
        }

        ranges.erase(l, r);
        if(has_left)
            ranges.insert(PIP(left_l, PII(left_r, left_h)));
        if(has_right)
            ranges.insert(PIP(right_l, PII(right_r, right_h)));
        int new_h = h + len;
        ranges.insert(PIP(start, PII(end, new_h)));
        max_h = max(max_h, new_h);
        return max_h;
    }

private:
    using PII = pair<int, int>;
    using PIP = pair<int, PII>;
    using IT = map<int, PII>::iterator;
    map<int, PII> ranges; // left -> (right, h)
    int max_h;

    void get_overlap(int left, int right, IT& l, IT& r)
    {
        l = ranges.upper_bound(left);
        r = ranges.lower_bound(right);
        if(l != ranges.begin())
        {
            --l;
            if((l -> second).first <= left)
                ++l;
        }
    }
};

class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        int n = positions.size();
        vector<int> result(n, -1);
        Ranges ranges;
        for(int i = 0; i < n; ++i)
        {

            int left = positions[i][0];
            int len = positions[i][1];
            int right = left + len; // right 是开区间
            result[i] = ranges.update(left, right, len);
        }
        return result;
    }
};
