// prob616: Add Bold Tag in String

/*
 * Given a string s and a list of strings dict, you need to add a closed pair of bold tag <b> and </b> to wrap the substrings in s that exist in dict. If two such substrings overlap, you need to wrap them together by only one pair of closed bold tag. Also, if two substrings wrapped by bold tags are consecutive, you need to combine them.
 */

/*
 * Example 1:
 *
 * Input:
 * s = "abcxyz123"
 * dict = ["abc","123"]
 * Output:
 * "<b>abc</b>xyz<b>123</b>"
 *  
 *
 * Example 2:
 *
 * Input:
 * s = "aaabbcc"
 * dict = ["aaa","aab","bc"]
 * Output:
 * "<b>aaabbc</b>c"
 */

/*
 * Constraints:
 *
 * The given dict won't contain duplicates, and its length won't exceed 100.
 * All the strings in input have length in range [1, 1000].
 */


#include <string>
#include <vector>
#include <unordered_set>
#include <list>
#include <algorithm>

using namespace std;


// 枚举单词
// 用 mask
// 改成 KMP 后，变为 60ms
// 332ms
class Solution {
public:
    string addBoldTag(string S, vector<string>& words) {
        int n = S.size();
        vector<bool> mask(n, false);
        for(const string& word: words)
        {
            int len = word.size();
            vector<int> kmpnext = get_kmp_next(word);
            vector<int> matches = kmp_match(S, word, kmpnext);
            for(int i : matches)
            {
                for(int l = i; l <= i + len - 1; ++l)
                    mask[l] = true;
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

private:
    vector<int> kmp_match(const string& s, const string& p, const vector<int>& kmpnext)
    {
        int n = s.size(), m = p.size();
        vector<int> result;
        for(int i = 0, j = 0; i < n; ++i)
        {
            while(j > -1 && s[i] != p[j])
                j = kmpnext[j];
            ++j;
            if(j == m)
            {
                result.push_back(i - m + 1);
                j = kmpnext[j];
            }
        }
        return result;
    }

    vector<int> get_kmp_next(const string& p)
    {
        int m = p.size();
        vector<int> kmpnext(m + 1, -1);
        for(int i = 0, j = -1; i < m; ++i)
        {
            while(j > -1 && p[i] != p[j])
                j = kmpnext[j];
            // j == -1 或 p[i] == p[j]
            ++j;
            if(p[i + 1] == p[j])
                kmpnext[i + 1] = kmpnext[j];
            else
                kmpnext[i + 1] = j;
        }
        return kmpnext;
    }
};


// 枚举单词
// 此时区间不是天然有序了，就需要排序
// 改成 kmp
// 308ms -> 90ms
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
    string addBoldTag(string S, vector<string>& words) {
        int n = S.size();
        vector<Interval> ranges_vec;
        for(const string& word: words)
        {
            int len = word.size();
            vector<int> kmpnext = get_kmp_next(word);
            vector<int> matches = kmp_match(S, word, kmpnext);
            for(int i : matches)
                ranges_vec.push_back(Interval(i, i + len - 1));
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

private:
    vector<int> kmp_match(const string& s, const string& p, const vector<int>& kmpnext)
    {
        int n = s.size(), m = p.size();
        vector<int> result;
        for(int i = 0, j = 0; i < n; ++i)
        {
            while(j > -1 && s[i] != p[j])
                j = kmpnext[j];
            ++j;
            if(j == m)
            {
                result.push_back(i - m + 1);
                j = kmpnext[j];
            }
        }
        return result;
    }

    vector<int> get_kmp_next(const string& p)
    {
        int m = p.size();
        vector<int> kmpnext(m + 1, -1);
        for(int i = 0, j = -1; i < m; ++i)
        {
            while(j > -1 && p[i] != p[j])
                j = kmpnext[j];
            // j == -1 或 p[i] == p[j]
            ++j;
            if(p[i + 1] == p[j])
                kmpnext[i + 1] = kmpnext[j];
            else
                kmpnext[i + 1] = j;
        }
        return kmpnext;
    }
};


// 枚举单词
// 此时区间不是天然有序了，就需要排序
// 308ms
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
    string addBoldTag(string S, vector<string>& words) {
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

// ----------------------------------------------------------------------------------------------------
struct Interval
{
    int l, r;
    Interval(int l, int r):l(l),r(r){}
};

class Solution {
public:
    string addBoldTag(string S, vector<string>& words) {
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


