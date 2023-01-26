// prob524: Longest Word in Dictionary through Deleting

/*
 * Given a string and a string dictionary, find the longest string in the dictionary that can be
 * formed by deleting some characters of the given string. If there are more than one possible results,
 * return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.
 */

/*
 * Example 1:
 * Input:
 * s = "abpcplea", d = ["ale","apple","monkey","plea"]
 * Output:
 * "apple"
 * Example 2:
 * Input:
 * s = "abpcplea", d = ["a","b","c"]
 * Output:
 * "a"
 */

/*
 * Note:
 * All the strings in the input will only contain lower-case letters.
 * The size of the dictionary won't exceed 1,000.
 * The length of all the strings in the input won't exceed 1,000.
 */

#include <string>
#include <vector>
#include <algorithm>

using namespace std;


struct Cmp
{
    Cmp(){}
    bool operator()(const string& word1, const string& word2) const
    {
        if(word1.size() == word2.size())
            return word1 < word2;
        return word1.size() > word2.size();
    }
};

class Solution {
public:
    string findLongestWord(string s, vector<string>& d) {
        if(s.empty() || d.empty()) return "";
        Cmp cmp;
        sort(d.begin(), d.end(), cmp);
        for(const string& word: d)
            if(check(s, word))
                return word;
        return "";
    }

private:
    bool check(const string& s, const string& word) const
    {
        // word 是否可以通过 origin 删除某些字符得到
        int n = s.size();
        int m = word.size();
        if(m > n) return false;
        int i = 0, j = 0;
        while(i < n && j < m)
        {
            if(s[i] == word[j])
                ++j;
            ++i;
            if(m - j > n - i)
                return false;
        }
        return j == m;
    }
};
