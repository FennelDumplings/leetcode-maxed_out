// prob758: Bold Words in String

/*
 * Given a set of keywords words and a string S, make all appearances of all keywords in S bold. Any letters between <b> and </b> tags become bold.
 *
 * The returned string should use the least number of tags possible, and of course the tags should form a valid combination.
 *
 * For example, given that words = ["ab", "bc"] and S = "aabcd", we should return "a<b>abc</b>d". Note that returning "a<b>a<b>b</b>c</b>d" would use more tags, so it is incorrect.
 */

/*
 * Constraints:
 *
 * words has length in range [0, 50].
 * words[i] has length in range [1, 10].
 * S has length in range [0, 500].
 * All characters in words[i] and S are lowercase letters.
 */

#include <string>
#include <vector>
#include <unordered_set>
#include <list>
#include <algorithm>

using namespace std;

// 枚举单词
// 112ms
struct Interval
{
    int l, r;
    Interval(int l, int r):l(l),r(r){}
};

struct Cmp
{
    bool operator()(const Interval& i1, const Interval& i2) const
    {
        if(i1.l == i2.l)
            return i1.r < i2.r;
        return i1.l < i2.l;
    }
};

class Solution {
public:
    string boldWords(vector<string>& words, string S) {
        int n = S.size();
        vector<Interval> ranges_vec;
        for(const string& word: words)
        {
            int len = word.size();
            for(int i = 0; i + len - 1  < n; ++i)
            {
                if(S.substr(i, len) == word)
                    ranges_vec.push_back(Interval(i, i + len - 1));
            }
        }
        sort(ranges_vec.begin(), ranges_vec.end(), Cmp());
        list<Interval> ranges(ranges_vec.begin(), ranges_vec.end());
        auto it = ranges.begin();
        int pre_right = -2;
        while(it != ranges.end())
        {
            int left = it -> l, right = it -> r;
            if(left > pre_right + 1)
            {
                pre_right = right;
                ++it;
            }
            else
            {
                it = ranges.erase(it);
                if(right > pre_right)
                {
                    --it;
                    pre_right = right;
                    it -> r = pre_right;
                    ++it;
                }
            }
        }
        string result = "";
        int i = 0;
        it = ranges.begin();
        while(i < n)
        {
            if(it != ranges.end())
            {
                Interval range = *it;
                ++it;
                result += S.substr(i, range.l - i);
                result += "<b>";
                result += S.substr(range.l, range.r - range.l + 1);
                result += "</b>";
                i = range.r + 1;
            }
            else
            {
                result += S.substr(i);
                i = n;
            }
        }
        return result;
    }
};

// 枚举单词
// 用 mask
// 104ms
class Solution {
public:
    string boldWords(vector<string>& words, string S) {
        int n = S.size();
        vector<bool> mask(n, false);
        for(const string& word: words)
        {
            int len = word.size();
            for(int i = 0; i + len - 1  < n; ++i)
            {
                if(S.substr(i, len) == word)
                {
                    for(int l = i; l <= i + len - 1; ++l)
                        mask[l] = true;
                }
            }
        }
        string result = "";
        for(int i = 0; i < n; ++i)
        {
            if(i == 0)
            {
                if(mask[i])
                    result += "<b>";
            }
            else
            {
                if(mask[i] && !mask[i - 1])
                    result += "<b>";
                if(!mask[i] && mask[i - 1])
                    result += "</b>";
            }
            result += S[i];
            if(i == n - 1 && mask[i])
                result += "</b>";
        }
        return result;
    }
};

//---------------------------------------------------------------------------

// TLE
struct Interval
{
    int l, r;
    Interval(int l, int r):l(l),r(r){}
};

class Solution {
public:
    string boldWords(vector<string>& words, string S) {
        unordered_set<string> setting(words.begin(), words.end());
        int n = S.size();
        list<Interval> ranges;
        for(int i = 0; i < n; ++i)
        {
            for(int len = 1; i + len <= n; ++len)
            {
                if(setting.find(S.substr(i, len)) != setting.end())
                    ranges.push_back(Interval(i, i + len - 1));
            }
        }
        auto it = ranges.begin();
        int pre_right = -2;
        while(it != ranges.end())
        {
            int left = it -> l, right = it -> r;
            if(left > pre_right + 1)
            {
                pre_right = right;
                ++it;
            }
            else
            {
                it = ranges.erase(it);
                if(right > pre_right)
                {
                    --it;
                    pre_right = right;
                    it -> r = pre_right;
                    ++it;
                }
            }
        }
        string result = "";
        int i = 0;
        it = ranges.begin();
        while(i < n)
        {
            if(it != ranges.end())
            {
                Interval range = *it;
                ++it;
                result += S.substr(i, range.l - i);
                result += "<b>";
                result += S.substr(range.l, range.r - range.l + 1);
                result += "</b>";
                i = range.r + 1;
            }
            else
            {
                result += S.substr(i);
                i = n;
            }
        }
        return result;
    }
};


// 用区间合并组件
// TLE
class Solution_56 {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.empty()) return vector<vector<int> >();
        int n = intervals.size();
        if(n == 1) return intervals;
        sort(intervals.begin(), intervals.end(), compare);
        vector<vector<int> > results;
        for(const auto& interval: intervals)
        {
            if(results.empty() || interval[0] > results.back()[1] + 1) // +1 是唯一改动
                results.push_back(interval);
            else
                results.back()[1] = max(results.back()[1], interval[1]);
        }
        return results;
    }

private:
    static bool compare(const vector<int>& interval1, const vector<int>& interval2)
    {
        return interval1[0] < interval2[0];
    }
};


class Solution_2 {
public:
    string boldWords(vector<string>& words, string S) {
        unordered_set<string> setting(words.begin(), words.end());
        int n = S.size();
        vector<vector<int>> ranges;
        for(int i = 0; i < n; ++i)
        {
            for(int len = 1; i + len <= n; ++len)
            {
                if(setting.find(S.substr(i, len)) != setting.end())
                    ranges.push_back(vector<int>({i, i + len - 1}));
            }
        }
        Solution_56 solution_56;
        ranges = solution_56.merge(ranges);
        string result = "";
        int i = 0;
        auto it = ranges.begin();
        while(i < n)
        {
            if(it != ranges.end())
            {
                vector<int> range = *it;
                ++it;
                result += S.substr(i, range[0] - i);
                result += "<b>";
                result += S.substr(range[0], range[1] - range[0] + 1);
                result += "</b>";
                i = range[1] + 1;
            }
            else
            {
                result += S.substr(i);
                i = n;
            }
        }
        return result;
    }
};
