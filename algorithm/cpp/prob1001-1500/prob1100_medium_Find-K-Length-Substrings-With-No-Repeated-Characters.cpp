// prob1100: Find K-Length Substrings With No Repeated Characters

/*
 * https://leetcode-cn.com/problems/find-k-length-substrings-with-no-repeated-characters/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int numKLenSubstrNoRepeats(string S, int K) {
        int n = S.size();
        int left = 0, right = 0;
        int state = 0;
        int ans = 0;
        while(right < n)
        {
            while(right < n && !(state >> (S[right] - 'a') & 1))
            {
                state |= 1 << (S[right] - 'a');
                if(right - left + 1 >= K)
                    ++ans;
                ++right;
            }
            if(right == n)
                break;
            while(S[left] != S[right])
            {
                state &= ~(1 << (S[left] - 'a'));
                ++left;
            }
            state &= ~(1 << (S[left] - 'a'));
            ++left;
        }
        return ans;
    }
};
