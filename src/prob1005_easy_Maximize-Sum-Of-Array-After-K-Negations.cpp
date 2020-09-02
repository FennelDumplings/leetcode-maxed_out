// prob1005: Maximize Sum Of Array After K Negations

/*
 * https://leetcode-cn.com/problems/maximize-sum-of-array-after-k-negations/
 */

#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;

class Solution {
public:
    int largestSumAfterKNegations(vector<int>& A, int K) {
        sort(A.begin(), A.end());
        auto it_nonnega = lower_bound(A.begin(), A.end(), 0);
        auto it = A.begin();
        while(it != it_nonnega && K > 0)
        {
            *it = -(*it);
            ++it;
            --K;
        }
        if(K & 1)
        {
            auto min_it = min_element(A.begin(), A.end());
            *min_it = -(*min_it);
        }
        return accumulate(A.begin(), A.end(), 0);
    }
};
