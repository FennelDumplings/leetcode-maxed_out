// prob1153: String Transforms Into Another String

/*
 * Given two strings str1 and str2 of the same length, determine whether you can transform str1 into str2 by doing zero or more conversions.
 * In one conversion you can convert all occurrences of one character in str1 to any other lowercase English character.
 * Return true if and only if you can transform str1 into str2.
 */

/*
 * Example 1:
 *
 * Input: str1 = "aabcc", str2 = "ccdee"
 * Output: true
 * Explanation: Convert 'c' to 'e' then 'b' to 'd' then 'a' to 'c'. Note that the order of conversions matter.
 * Example 2:
 *
 * Input: str1 = "leetcode", str2 = "codeleet"
 * Output: false
 * Explanation: There is no way to transform str1 to str2.
 */

/*
 * Note:
 *
 * 1 <= str1.length == str2.length <= 10^4
 * Both str1 and str2 contain only lowercase English letters.
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool canConvert(string str1, string str2) {
        vector<vector<int> > char_positions = process(str1);
        for(const vector<int>& pos: char_positions)
            if(!check(pos, str2))
                return false;
        bool all_used1 = true, all_used2 = true;
        vector<vector<int> > char_positions2 = process(str2);
        for(auto position: char_positions)
            if(position.empty())
                all_used1 = false;
        for(auto position: char_positions2)
            if(position.empty())
                all_used2 = false;
        if(all_used1 && all_used2)
            return str1 == str2;
        return true;
    }

private:
    vector<vector<int> > process(const string& str1)
    {
        // 相同字母的位置列表
        vector<vector<int>> result(26);
        int n = str1.size();
        for(int i = 0; i < n; ++i)
        {
            char ch = str1[i];
            result[ch - 'a'].push_back(i);
        }
        return result;
    }

    bool check(const vector<int>& pos, const string& str2)
    {
        char ch = ' ';
        for(int i: pos)
        {
            if(ch == ' ')
            {
                ch = str2[i];
                continue;
            }
            if(str2[i] != ch)
                return false;
        }
        return true;
    }
};
