// prob791: Custom Sort String

/*
 * S and T are strings composed of lowercase letters. In S, no letter occurs more than once.
 * S was sorted in some custom order previously. We want to permute the characters of T so that they match the order that S was sorted.
 * More specifically, if x occurs before y in S, then x should occur before y in the returned string.
 * Return any permutation of T (as a string) that satisfies this property.
 */

/*
 * Example :
 * Input:
 * S = "cba"
 * T = "abcd"
 * Output: "cbad"
 * Explanation:
 * "a", "b", "c" appear in S, so the order of "a", "b", "c" should be "c", "b", and "a".
 * Since "d" does not appear in S, it can be at any position in T. "dcba", "cdba", "cbda" are also valid outputs.
 */

/*
 * Note:
 * S has length at most 26, and no character is repeated in S.
 * T has length at most 200.
 * S and T consist of lowercase letters only.
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string customSortString(string S, string T) {
        int n = S.size();
        if(n <= 1) return T;
        vector<int> char_idx(26, -1);
        for(int i = 0; i < n; ++i)
            char_idx[S[i] - 'a'] = i;
        Dictionary_less dictionary_less(char_idx);
        sort(T.begin(), T.end(), dictionary_less);
        return T;
    }

private:
    struct Dictionary_less
    {
        vector<int> char_idx;

        Dictionary_less(vector<int> mapping):char_idx(mapping) {}

        bool operator() (const char& c1, const char& c2)
        {
            return char_idx[c1 - 'a'] < char_idx[c2 - 'a'];
        }
    };
};
