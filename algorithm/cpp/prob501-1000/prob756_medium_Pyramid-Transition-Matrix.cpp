// prob756: Pyramid Transition Matrix

/*
 * We are stacking blocks to form a pyramid. Each block has a color which is a one letter string.
 * We are allowed to place any color block C on top of two adjacent blocks of colors A and B, if and only if ABC is an allowed triple.
 * We start with a bottom row of bottom, represented as a single string. We also start with a list of allowed triples allowed.
 * Each allowed triple is represented as a string of length 3.
 * Return true if we can build the pyramid all the way to the top, otherwise false.
 */

/*
 * Example 1:
 * Input: bottom = "BCD", allowed = ["BCG", "CDE", "GEA", "FFF"]
 * Output: true
 * Explanation:
 * We can stack the pyramid like this:
 *     A
 *    / \
 *   G   E
 *  / \ / \
 * B   C   D
 * We are allowed to place G on top of B and C because BCG is an allowed triple.  Similarly, we can place E on top of C and D, then A on top of G and E.
 * Example 2:
 * Input: bottom = "AABA", allowed = ["AAA", "AAB", "ABA", "ABB", "BAC"]
 * Output: false
 * Explanation:
 * We can't stack the pyramid to the top.
 * Note that there could be allowed triples (A, B, C) and (A, B, D) with C != D.
 */

/*
 * Note:
 * bottom will be a string with length in range [2, 8].
 * allowed will have length in range [0, 200].
 * Letters in all strings will be chosen from the set {'A', 'B', 'C', 'D', 'E', 'F', 'G'}.
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        if(allowed.empty()) return false;
        int n = bottom.size();
        int iter = 0;
        unordered_map<string, string> mapping;
        for(const string &s: allowed)
            mapping[s.substr(0, 2)].push_back(s[2]);
        return dfs(bottom, iter, n, mapping);
    }

private:
    bool dfs(string& bottom, int iter, int len, const unordered_map<string, string>& mapping)
    {
        if(iter + 1 == len)
        {
            if(len == 2) return true;
            iter = 0;
            --len;
        }
        string cur = bottom.substr(iter, 2);
        auto it = mapping.find(cur);
        if(it == mapping.end()) return false;
        int tmp = bottom[iter];
        for(const char &c: it -> second)
        {
            bottom[iter] = c;
            if(dfs(bottom, iter + 1, len, mapping))
                return true;
            bottom[iter] = tmp;
        }
        return false;
    }
};
