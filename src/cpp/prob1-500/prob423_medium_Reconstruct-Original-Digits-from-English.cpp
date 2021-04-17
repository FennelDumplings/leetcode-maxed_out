// prob423: Reconstruct Original Digits from English

/*
 * https://leetcode-cn.com/problems/reconstruct-original-digits-from-english/
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string originalDigits(string s) {
        vector<int> cnts(26);
        for(char ch: s)
            ++cnts[ch - 'a'];
        vector<int> ns(10);
        ns[0] = cnts['z' - 'a'];
        ns[2] = cnts['w' - 'a'];
        ns[8] = cnts['g' - 'a'];
        ns[6] = cnts['x' - 'a'];
        ns[3] = cnts['t' - 'a'] - ns[2] - ns[8];
        ns[4] = cnts['r' - 'a'] - ns[3] - ns[0];
        ns[7] = cnts['s' - 'a'] - ns[6];
        ns[1] = cnts['o' - 'a'] - ns[4] - ns[2] - ns[0];
        ns[5] = cnts['v' - 'a'] - ns[7];
        ns[9] = cnts['i' - 'a'] - ns[8] - ns[6] - ns[5];
        string result;
        for(int i = 0; i <= 9; ++i)
            result += string(ns[i], '0' + i);
        return result;
    }
};
