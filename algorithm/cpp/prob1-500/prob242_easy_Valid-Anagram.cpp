// prob242: Valid Anagram

/*
 * Given two strings s and t , write a function to determine if t is an anagram of s.
 */

/*
 * Example 1:
 * Input: s = "anagram", t = "nagaram"
 * Output: true
 * Example 2:
 * Input: s = "rat", t = "car"
 * Output: false
 */

/*
 * Note:
 * You may assume the string contains only lowercase alphabets.
 */

/*
 * Follow up:
 * What if the inputs contain unicode characters? How would you adapt your solution to such case?
 */

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 排序
class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.empty() && t.empty()) return true;
        if(s.empty() || t.empty()) return false;
        int n = s.size(), m = t.size();
        if(n != m) return false;
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        // for(int i = 0; i < m; ++i)
        // {
        //     if(s[i] != t[i])
        //         return false;
        // }
        // return true;
        return s == t;
    }
};

// 字符计数
class Solution_2 {
public:
    bool isAnagram(string s, string t) {
        if(s.empty() && t.empty()) return true;
        if(s.empty() || t.empty()) return false;
        int n = s.size(), m = t.size();
        if(n != m) return false;
        // return _counting(s) == _counting(t);
        vector<int> count1 = _counting2(s);
        vector<int> count2 = _counting2(t);
        for(int i = 0; i < 26; ++i)
            if(count1[i] != count2[i])
                return false;
        return true;
    }

private:
    string _counting(const string& s)
    {
        vector<int> count(26, 0);
        int n = s.size();
        for(int i = 0; i < n; ++i)
            ++count[s[i] - 'a'];
        string result = "#";
        for(int i = 0; i < 26; ++i)
            result += to_string(count[i]) + "#";
        return result;
    }

    vector<int> _counting2(const string& s)
    {
        int n = s.size();
        vector<int> count(26, 0);
        for(int i = 0; i < n; ++i)
            ++count[s[i] - 'a'];
        return count;
    }
};

