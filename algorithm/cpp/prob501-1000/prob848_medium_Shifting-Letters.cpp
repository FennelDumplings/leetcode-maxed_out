// prob848: Shifting Letters

/*
 * https://leetcode-cn.com/problems/shifting-letters/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string shiftingLetters(string S, vector<int>& shifts) {
        using ll = long long;
        int n = S.size();
        string result = S;
        ll sum = 0;
        for(int i = n - 1; i >= 0; --i)
        {
            sum += shifts[i];
            result[i] = 'a' + (((result[i] - 'a') + (sum % 26))) % 26;
        }
        return result;
    }
};
