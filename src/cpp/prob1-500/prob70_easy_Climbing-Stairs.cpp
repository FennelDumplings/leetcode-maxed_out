// prob70: Climbing Stairs

/*
 * You are climbing a stair case. It takes n steps to reach to the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 * Note: Given n will be a positive integer.
 */

/*
 * Example 1:
 * Input: 2
 * Output: 2
 * Explanation: There are two ways to climb to the top.
 * 1. 1 step + 1 step
 * 2. 2 steps
 * Example 2:
 * Input: 3
 * Output: 3
 * Explanation: There are three ways to climb to the top.
 * 1. 1 step + 1 step + 1 step
 * 2. 1 step + 2 steps
 * 3. 2 steps + 1 step
 */

#include <vector>

using namespace std;

using ll = long long;

class Matrix {
public:
    Matrix(int m){
        M = m;
        mat = vector<vector<int> >(M, vector<int>(M, 0));
    }

    void assign(int i, int j, int val)
    {
        mat[i][j] = val;
    }

    int get(int i, int j)
    {
        return mat[i][j];
    }

    void init()
    {
        for(int i = 0; i < M; ++i)
            for(int j = 0; j < M; ++j)
                mat[i][j] = 0;
        for(int i = 0; i < M; ++i)
            mat[i][i] = 1;
    }

    Matrix operator*(const Matrix& matrix) const
    {
        Matrix ans(M);
        for(int i = 0; i < M; ++i)
            for(int j = 0; j < M; ++j)
                for(int k = 0; k < M; ++k)
                    ans.mat[i][j] += ((ll)mat[i][k] * matrix.mat[k][j]);
        return ans;
    }

    Matrix operator^(int n) const
    {
        Matrix ans(M);
        ans.init();
        Matrix A = *this; // 拷贝出来用于自乘
        while(n)
        {
            if(n & 1) ans = ans * A;
            A = A * A;
            n >>= 1;
        }
        return ans;
    }

    void operator=(const Matrix& matrix)
    {
        for(int i = 0; i < M; ++i)
            for(int j = 0; j < M; ++j)
                mat[i][j] = matrix.mat[i][j];
    }

private:
    vector<vector<int> > mat;
    int M;
};


class Solution {
public:
    int climbStairs(int n) {
        if(n == 1) return 1;
        if(n == 2) return 2;
        Matrix mat(2);
        mat.assign(0, 0, 1);
        mat.assign(0, 1, 1);
        mat.assign(1, 0, 1);
        Matrix mat_power = mat ^ (n - 2);
        int res = mat_power.get(0, 0) * 2 + mat_power.get(0, 1) * 1;
        return res;
    }
};
