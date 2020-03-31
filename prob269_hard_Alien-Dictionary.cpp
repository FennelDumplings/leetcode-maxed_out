// prob269: Alien Dictionary

/*
 * There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you.
 * You receive a list of non-empty words from the dictionary, where words are sorted lexicographically by the rules of this new language.
 * Derive the order of letters in this language.
 */

/*
 * Example 1:
 * Input:
 * [
 *   "wrt",
 *   "wrf",
 *   "er",
 *   "ett",
 *   "rftt"
 * ]
 * Output: "wertf"
 * Example 2:
 * Input:
 * [
 *   "z",
 *   "x"
 * ]
 * Output: "zx"
 * Example 3:
 * Input:
 * [
 *   "z",
 *   "x",
 *   "z"
 * ]
 * Output: "" 
 * Explanation: The order is invalid, so return "".
 */

/*
 * Note:
 * You may assume all letters are in lowercase.
 * If the order is invalid, return an empty string.
 * There may be multiple valid order of letters, return any one of them is fine.
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string alienOrder(vector<string>& words) {
        int n = words.size();
        if(n <= 1) return "";
        vector<vector<int> > partial_order(26, vector<int>(26, -2));
        string result;
        for(int i = 1; i < n; ++i)
        {
        }

    }
};
