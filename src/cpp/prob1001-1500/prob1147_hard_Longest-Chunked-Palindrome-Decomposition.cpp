// prob1127: Longest Chunked Palindrome Decomposition

/*
 * Return the largest possible k such that there exists a_1, a_2, ..., a_k such that:
 * Each a_i is a non-empty string;
 * Their concatenation a_1 + a_2 + ... + a_k is equal to text;
 * For all 1 <= i <= k,  a_i = a_{k+1 - i}.
 */

/*
 * Example 1:
 * Input: text = "ghiabcdefhelloadamhelloabcdefghi"
 * Output: 7
 * Explanation: We can split the string on "(ghi)(abcdef)(hello)(adam)(hello)(abcdef)(ghi)".
 * Example 2:
 * Input: text = "merchant"
 * Output: 1
 * Explanation: We can split the string on "(merchant)".
 * Example 3:
 * Input: text = "antaprezatepzapreanta"
 * Output: 11
 * Explanation: We can split the string on "(a)(nt)(a)(pre)(za)(tpe)(za)(pre)(a)(nt)(a)".
 * Example 4:
 * Input: text = "aaa"
 * Output: 3
 * Explanation: We can split the string on "(a)(a)(a)".
 */

/*
 * Constraints:
 * text consists only of lowercase English characters.
 * 1 <= text.length <= 1000
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int longestDecomposition(string text) {
        int n = text.size();
        vector<vector<int> > dp(n, vector<int>(n, -1));
        solve(0, n - 1, text, dp);
        return dp[0][n - 1];
    }

private:
    // dp[i][j]:= [i..j] 上最大段数
    void solve(int i, int j, const string& text, vector<vector<int> >& dp)
    {
        if(dp[i][j] != -1) return;
        if(i > j)
        {
            dp[i][j] = 0;
            return;
        }
        if(i == j)
        {
            dp[i][j] = 1;
            return;
        }

        // i < j
        if(text[i] == text[j])
        {
            solve(i + 1, j - 1, text, dp);
            dp[i][j] = 2 + dp[i + 1][j - 1];
            return;
        }

        // text[i] != text[j]
        // 1 <= step && i + step < j - step
        // 若 text[i..i+step] = text[j-step..j] solve(i+step+1, j-step-1, text, dp)
        dp[i][j] = 1;
        for(int step = 1; i + step < j - step; ++step)
        {
            if(text.substr(i, step + 1) == text.substr(j - step, step + 1))
            {
                solve(i + step + 1, j - step - 1, text, dp);
                dp[i][j] = max(dp[i][j], dp[i + step + 1][j - step - 1] + 2);
                break;
            }
        }
    }
};
