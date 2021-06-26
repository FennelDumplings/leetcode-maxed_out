// prob1423: Maximum Points You Can Obtain from Cards

/*
 * https://leetcode-cn.com/problems/maximum-points-you-can-obtain-from-cards/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        int L = n - k;
        int sum = 0;
        for(int i = 0; i < L; ++i)
            sum += cardPoints[i];
        int ans = sum;
        int S = sum;
        for(int i = L; i < n; ++i)
        {
            sum -= cardPoints[i - L];
            sum += cardPoints[i];
            S += cardPoints[i];
            ans = min(ans, sum);
        }
        return S - ans;
    }
};
