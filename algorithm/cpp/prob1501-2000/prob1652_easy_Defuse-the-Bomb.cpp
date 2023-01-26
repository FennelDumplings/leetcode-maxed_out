#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> decrypt(vector<int>& code, int k) {
        int n = code.size();
        if(k == 0)
            return vector<int>(n, 0);
        vector<int> sums(n);
        int K = abs(k);
        for(int i = 0; i < K; ++i)
            sums[0] += code[(i + 1) % n];
        for(int i = 1; i < n; ++i)
            sums[i] = sums[(i + n - 1) % n] - code[i] + code[(i + K) % n];
        if(k > 0)
            return sums;
        else
        {
            int right_shift = -(k - 1);
            rotate(sums.begin(), sums.begin() + (n - right_shift), sums.end());
            return sums;
        }
    }
};
