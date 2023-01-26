// prob927: Three Equal Parts

/*
 * https://leetcode-cn.com/problems/three-equal-parts/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> threeEqualParts(vector<int>& A) {
        int n = A.size();
        vector<int> idxs;
        for(int i = 0; i < n; ++i)
            if(A[i] == 1)
                idxs.push_back(i);
        if(idxs.empty())
            return {0, (int)A.size() - 1};
        if((int)idxs.size() % 3 != 0)
            return {-1, -1};
        int t = (int)idxs.size() / 3;
        int tail_zero = n - 1 - idxs[t * 3 - 1];
        int len = n - idxs[2 * t];
        int i = idxs[t - 1] + tail_zero;
        if(i >= idxs[t] || i - idxs[0] + 1 != len)
            return {-1, -1};
        int j = idxs[t * 2 - 1] + tail_zero + 1;
        if(j > idxs[t * 2] || j - idxs[t] != len)
            return {-1, -1};
        if(check(A, n - 1, i, len) && check(A, n - 1, j - 1, len))
            return {i, j};
        else
            return {-1, -1};
    }

private:
    bool check(const vector<int>& A, int r1, int r2, int len)
    {
        for(int d = 0; d < len; ++d)
        {
            int i1 = r1 - d, i2 = r2 - d;
            if(A[i1] != A[i2])
                return false;
        }
        return true;
    }
};
