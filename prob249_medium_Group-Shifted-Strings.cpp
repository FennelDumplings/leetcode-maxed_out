// prob249: Group Shifted Strings

/*
 * Given a string, we can "shift" each of its letter to its successive letter,
 * for example: "abc" -> "bcd". We can keep "shifting" which forms the sequence:
 * "abc" -> "bcd" -> ... -> "xyz"
 * Given a list of strings which contains only lowercase alphabets, group all strings that belong to the same shifting sequence.
 */

/*
 * Example:
 *
 * Input: ["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"],
 * Output:
 * [
 *   ["abc","bcd","xyz"],
 *   ["az","ba"],
 *   ["acef"],
 *   ["a","z"]
 * ]
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        if(strings.empty()) return vector<vector<string> >();
        unordered_map<string, int> mapping;
        vector<vector<string> > result;
        int idx = -1;
        for(string s: strings)
        {
            string key = _shift(s);
            auto it = mapping.find(key);
            if(it != mapping.end())
                result[mapping[key]].push_back(s);
            else
            {
                ++idx;
                mapping[key] = idx;
                result.push_back(vector<string>());
                result[idx].push_back(s);
            }
        }
        return result;
    }

private:
    string _shift(const string& s)
    {
        if(s.empty()) return "";
        int n = s.size();
        int delta = s[0] - 'a';
        string result(n, ' ');
        result[0] = 'a'; // s[0] - delta;
        for(int i = 1; i < n; ++i)
        {
            if(s[i] >= s[0])
                result[i] = s[i] - delta;
            else
                result[i] = s[i] - delta + 26;
        }
        return result;
    }
};
