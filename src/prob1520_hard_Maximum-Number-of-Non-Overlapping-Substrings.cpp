// prob1520: Maximum Number of Non-Overlapping Substrings

/*
 * https://leetcode-cn.com/problems/maximum-number-of-non-overlapping-substrings/
 */


#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

struct Range
{
    int l, r;
    Range()
    {
        l = -1;
        r = -1;
    }
    Range(int l, int r):l(l),r(r){}
};

class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();
        // 预处理
        vector<Range> ranges(26);
        vector<vector<int>> idxs(26);
        for(int i = 0; i < n; ++i)
        {
            if(ranges[s[i] - 'a'].l == -1)
                ranges[s[i] - 'a'].l = i;
            ranges[s[i] - 'a'].r = i;
            idxs[s[i] - 'a'].push_back(i);
        }
        // 扩展区间
        expand(ranges, idxs);
        expand(ranges, idxs);
        // 后处理
        map<int, int> mapping; // 自带去重
        for(Range &range: ranges)
        {
            if(range.l == -1)
                continue;
            mapping[range.l] = range.r;
        }
        auto it = mapping.begin();
        int right = -1;
        while(it != mapping.end())
        {
            if(it -> first > right)
            {
                right = it -> second;
            }
            else
            {
                right = it -> second;
                --it;
                it = mapping.erase(it);
            }
            ++it;
        }
        // 整理答案
        vector<string> result;
        it = mapping.begin();
        while(it != mapping.end())
        {
            result.push_back(s.substr(it->first, it -> second - it -> first + 1));
            ++it;
        }
        return result;
    }

private:
    void expand(vector<Range>& ranges, const vector<vector<int>>& idxs)
    {
        for(int i = 0; i < 26; ++i)
        {
            if(ranges[i].l == -1) continue;
            for(int j = 0; j < 26; ++j)
            {
                if(i == j || ranges[j].l == -1) continue;
                // ranges[i].l, ranges[i].r 内有无 j
                auto it = upper_bound(idxs[j].begin(), idxs[j].end(), ranges[i].l);
                if(it != idxs[j].end() && *it < ranges[i].r) // 有
                {
                    if(ranges[i].l >= ranges[j].l || ranges[j].r >= ranges[i].r)
                    {
                        ranges[i].l = min(ranges[i].l, ranges[j].l);
                        ranges[i].r = max(ranges[i].r, ranges[j].r);
                        ranges[j].l = ranges[i].l;
                        ranges[j].r = ranges[i].r;
                    }
                }
            }
        }
    }
};
