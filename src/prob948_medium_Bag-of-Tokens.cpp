// prob948: Bag of Tokens

/*
 * https://leetcode-cn.com/problems/bag-of-tokens/
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int P) {
        int n = tokens.size();
        sort(tokens.begin(), tokens.end());
        int left = 0, right = n - 1;
        int ans = 0;
        while(left <= right)
        {
            while(left <= right && tokens[left] <= P)
            {
                P -= tokens[left++];
                ++ans;
            }
            if(left >= right || ans < 1)
                break;
            // left < right
            // P += token[right] 之后一定能 cover token[left]
            if(ans >= 1)
            {
                P += tokens[right--];
                --ans;
            }
        }
        return ans;
    }
};
