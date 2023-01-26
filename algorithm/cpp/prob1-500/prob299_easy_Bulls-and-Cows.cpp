// prob299 Bulls and Cows

/* Examples:
 * Example 1:
 * Input: secret = "1807", guess = "7810"
 * Output: "1A3B"
 * Explanation: 1 bull and 3 cows. The bull is 8, the cows are 0, 1 and 7.
 * Example 2:
 * Input: secret = "1123", guess = "0111"
 * Output: "1A1B"
 * Explanation: The 1st 1 in friend's guess is a bull, the 2nd or 3rd 1 is a cow.
 */

/* Note:
 * Note: You may assume that the secret number and your friend's guess only contain digits,
 * and their lengths are always equal.
 */

#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    string getHint(string secret, string guess) {
        int n = secret.size();
        if(n == 0) return "0A0B";
        unordered_multiset<char> setting;
        for(char c : secret)
            setting.insert(c);
        int bulls = 0;
        int cows = 0;
        for(int i = 0; i < (int)guess.size(); ++i)
        {
            if(guess[i] == secret[i])
            {
                ++bulls;
                auto iter = setting.find(guess[i]);
                setting.erase(iter);
            }
        }
        for(int i = 0; i < (int)guess.size(); ++i)
        {
            if(guess[i] != secret[i])
            {
                auto iter = setting.find(guess[i]);
                if(iter != setting.end())
                {
                    ++cows;
                    setting.erase(iter);
                }
            }
        }
        string result = to_string(bulls) + "A" + to_string(cows) + "B";
        return result;
    }
};
