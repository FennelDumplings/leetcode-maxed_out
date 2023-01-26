// prob932: Beautiful Array

/*
 * https://leetcode-cn.com/problems/beautiful-array/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> beautifulArray(int N) {
        vector<int> A(N);
        for(int i = 1; i <= N; ++i)
            A[i - 1] = i;
        solve(A, 0, N - 1);
        return A;
    }

private:
    void solve(vector<int>& A, int l, int r)
    {
        if(l == r)
            return;
        int len = r - l + 1;
        int len_left = (len + 1) / 2;
        int len_right = len - len_left;
        vector<int> tmp(len, -1);
        for(int step = 0; step < len_left; ++step)
        {
            int i = l + step * 2;
            tmp[step] = A[i];
        }
        for(int step = 0; step < len_right; ++step)
        {
            int i = l + 1 + step * 2;
            tmp[step + len_left] = A[i];
        }
        for(int i = 0; i < len; ++i)
            A[l + i] = tmp[i];
        solve(A, l, l + len_left - 1);
        solve(A, l + len_left, r);
    }
};
