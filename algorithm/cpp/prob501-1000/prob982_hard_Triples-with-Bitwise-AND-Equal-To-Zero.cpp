// prob982: Triples with Bitwise AND Equal To Zero

/*
 * https://leetcode-cn.com/problems/triples-with-bitwise-and-equal-to-zero/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int countTriplets(vector<int>& A) {
        int n = A.size();
        vector<int> dp((1<<16));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                ++dp[A[i] & A[j]];
        int ans = 0;
        for(int a: A)
            for(int state = 0; state < (1 << 16); ++state)
                if((a & state) == 0)
                    ans += dp[state];
        return ans;
    }
};

// FWT(别人的)
class Solution_2 {
public:
    int w;
    int B[1 << 16];
    void FWTand(int *a, int opt)
    {
        int N = 1 << w;
        for (int mid = 1; mid < N; mid <<= 1)
            for (int R = mid << 1, j = 0; j < N; j += R)
                for (int k = 0; k < mid; k++)
                    if (opt == 1) a[j + k] += a[j + k + mid];
                    else a[j + k] -= a[j + k + mid];
    }
    int countTriplets(vector<int>& A) {
        for (auto a : A)
        {
            B[a]++;
            while ((1 << w) <= a)w++;
        }
        FWTand(B, 1);
        for (int i = 0; i<(1 << w); i++) B[i] *= B[i] * B[i];
        FWTand(B, -1);
        return B[0];
    }
};
