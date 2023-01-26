// prob520: Detect Capital

/*
 * Given a word, you need to judge whether the usage of capitals in it is right or not.
 * We define the usage of capitals in a word to be right when one of the following cases holds:
 * All letters in this word are capitals, like "USA".
 * All letters in this word are not capitals, like "leetcode".
 * Only the first letter in this word is capital, like "Google".
 * Otherwise, we define that this word doesn't use capitals in a right way.
 */

/*
 * Example 1:
 * Input: "USA"
 * Output: True
 * Example 2:
 * Input: "FlaG"
 * Output: False
 */

/*
 * Note: The input will be a non-empty word consisting of uppercase and lowercase latin letters.
 */

#include <string>

using namespace std;

class Solution {
public:
    bool detectCapitalUse(string word) {
        int n = word.size();
        if(n == 1) return true;
        if(word[0] < 'a')
        {
            bool has_capital = false;
            bool has_lowercase = false;
            for(int i = 1; i < n; ++i)
            {
                if(word[i] >= 'a')
                {
                    if(has_capital)
                        return false;
                    else
                        has_lowercase = true;
                }
                else
                {
                    if(has_lowercase)
                        return false;
                    else
                        has_capital = true;
                }
            }
        }
        else
        {
            for(int i = 1; i < n; ++i)
            {
                if(word[i] < 'a')
                    return false;
            }
        }
        return true;
    }
};
