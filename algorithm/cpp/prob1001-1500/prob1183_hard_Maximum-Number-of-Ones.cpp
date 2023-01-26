// prob1183: Maximum Number of Ones

/*
 * https://leetcode-cn.com/problems/maximum-number-of-ones/
 */

#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class Solution {
public:
    int maximumNumberOfOnes(int width, int height, int sideLength, int maxOnes) {
        vector<int> up_left(sideLength * sideLength);
        for(int i = 0; i < sideLength; ++i)
            for(int j = 0; j < sideLength; ++j)
            {
                int ki = (width - 1 - i) / sideLength;
                int kj = (height - 1 - j) / sideLength;
                up_left[i * sideLength + j] = (ki + 1) * (kj + 1);
            }
        nth_element(up_left.begin(), up_left.begin() + maxOnes, up_left.end(), greater<int>());
        int ans = 0;
        for(int i = 0; i < maxOnes; ++i)
            ans += up_left[i];
        return ans;
    }
};
