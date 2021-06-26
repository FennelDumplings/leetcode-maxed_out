// prob17: Letter Combinations of a Phone Number

/*
 * Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent.
 * A mapping of digit to letters is just like on the telephone buttons
 */

/*
 * Example:
 * Input: "23"
 * Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
 */

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if(digits.empty()) return vector<string>();
        int n = digits.size();
        vector<string> result;
        string result_item = "";
        dfs(digits, 0, result_item, result, n);
        return result;
    }

private:
    unordered_map<char, string> mapping = {
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"}
    };

    void dfs(const string& digits, int pos, string& result_item, vector<string>& result, int n)
    {
        if(pos == n)
        {
            result.push_back(result_item);
            return;
        }

        for(char c : mapping[digits[pos]])
        {
            result_item += c;
            dfs(digits, pos + 1, result_item, result, n);
            result_item.pop_back();
        }
    }
};


