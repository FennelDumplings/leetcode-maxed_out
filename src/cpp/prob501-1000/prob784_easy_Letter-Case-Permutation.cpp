// prob784: Letter Case Permutation

/*
 * Given a string S, we can transform every letter individually to be lowercase or uppercase to create another string.
 * Return a list of all possible strings we could create.
 */

/*
 * Note:
 * S will be a string with length between 1 and 12.
 * S will consist only of letters or digits.
 */

/*
 * Examples:
 * Input: S = "a1b2"
 * Output: ["a1b2", "a1B2", "A1b2", "A1B2"]
 * Input: S = "3z4"
 * Output: ["3z4", "3Z4"]
 * Input: S = "12345"
 * Output: ["12345"]
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> letterCasePermutation(string S) {
        if(S.empty()) return vector<string>();
        vector<string> result;
        dfs(S, 0, result);
        return result;
    }

private:
    void dfs(string& S, int pos, vector<string>& result)
    {
        int n = S.size();
        if(pos == n)
        {
            result.push_back(S);
            return;
        }
        dfs(S, pos + 1, result);
        if(S[pos] >= '0' && S[pos] <= '9')
            return;
        _flip(S, pos);
        dfs(S, pos + 1, result);
        _flip(S, pos);
    }

    void _flip(string& S, int pos)
    {
        if(S[pos] >= 'a' && S[pos] <= 'z')
            S[pos] -= 32;
        else if(S[pos] >= 'A' && S[pos] <= 'Z')
            S[pos] += 32;
    }
};
