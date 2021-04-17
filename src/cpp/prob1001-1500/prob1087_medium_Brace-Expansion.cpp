// prob1087: Brace Expansion

/*
 * A string S represents a list of words.
 * Each letter in the word has 1 or more options.  If there is one option, the letter is represented as is.  If there is more than one option, then curly braces delimit the options.  For example, "{a,b,c}" represents options ["a", "b", "c"].
 * For example, "{a,b,c}d{e,f}" represents the list ["ade", "adf", "bde", "bdf", "cde", "cdf"].
 * Return all words that can be formed in this manner, in lexicographical order.
 */

/*
 * Example 1:
 * Input: "{a,b}c{d,e}f"
 * Output: ["acdf","acef","bcdf","bcef"]
 * Example 2:
 * Input: "abcd"
 * Output: ["abcd"]
 */

/*
 * Note:
 * 1 <= S.length <= 50
 * There are no nested curly brackets.
 * All characters inside a pair of consecutive opening and ending curly brackets are different.
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> expand(string S) {
        vector<string> items;
        preprocess(S, items);
        vector<string> result;
        string record;
        int n = items.size();
        dfs(items, 0, record, result, n);
        return result;
    }

private:
    void dfs(const vector<string>& items, int pos, string& record, vector<string>& result, int n)
    {
        if(pos == n)
        {
            result.push_back(record);
            return;
        }
        for(const char &ch: items[pos])
        {
            record += ch;
            dfs(items, pos + 1, record, result, n);
            record.pop_back();
        }
    }

    void preprocess(const string& S, vector<string>& items)
    {
        int n = S.size();
        int left = 0;
        while(left < n)
        {
            if(S[left] != '{')
            {
                items.push_back(string(1, S[left]));
                ++left;
            }
            else
            {
                items.push_back("");
                while(S[left] != '}')
                {
                    ++left;
                    items.back() += S[left];
                    ++left;
                }
                ++left;
                sort(items.back().begin(), items.back().end());
            }
        }
    }
};
