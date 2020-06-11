// prob320: Generalized Abbreviation

/*
 * Write a function to generate the generalized abbreviations of a word. 
 * Note: The order of the output does not matter.
 */

/*
 * Example:
 * Input: "word"
 * Output:
 * ["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> generateAbbreviations(string word) {
        vector<string> result;
        dfs(word, 0, "", result);
        return result;
    }

private:
    void dfs(const string& word, int left, string item, vector<string>& result)
    {
        int n = word.size();
        if(left >= n)
        {
            result.push_back(item);
            return;
        }
        for(int i = left; i < n; ++i)
        {
            // [left, i) 是数字，i 是分格字符 [i + 1, n) 是下一个
            int len = i - left;
            string num = "";
            if(len > 0) num = to_string(len);
            dfs(word, i + 1, item + num + word[i], result);
        }
        dfs(word, n + 1, item + to_string(n - left), result);
    }
};
