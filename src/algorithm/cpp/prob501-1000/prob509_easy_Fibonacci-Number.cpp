// prob509: Fibonacci Number

/*
 * The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence,
 * such that each number is the sum of the two preceding ones, starting from 0 and 1. That is,
 * F(0) = 0,   F(1) = 1
 * F(N) = F(N - 1) + F(N - 2), for N > 1.
 * Given N, calculate F(N).
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

    void init()
    {
        for(int i = 0; i < M; ++i)
            for(int j = 0; j < M; ++j)
                mat[i][j] = 0;
        for(int i = 0; i < M; ++i)
            mat[i][i] = 1;
    }

    void assign(int i, int j, int val)
    {
        mat[i][j] = val;
    }

    int get(int i, int j) const
    {
        return mat[i][j];
    }

    Matrix operator*(const Matrix& matrix) const
    {
        Matrix ans(M);
        for(int i = 0; i < M; ++i)
            for(int j = 0; j < M; ++j)
                for(int k = 0; k < M; ++k)
                    ans.mat[i][j] += (ll)mat[i][k] * matrix.mat[k][j];
        return ans;
    }

    Matrix operator^(int n) const
    {
        Matrix ans(M);
        ans.init();
        Matrix a = *this;
        while(n)
        {
            if(n & 1)
                ans = ans * a;
            a = a * a;
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
    const int MOD = 1e9 + 7;
    int M;
    vector<vector<int> > mat;
};

class Solution {
public:
    int fib(int N) {
        if(N == 0) return 0;
        if(N == 1) return 1;
        Matrix mat(2);
        mat.assign(0, 0, 1);
        mat.assign(0, 1, 1);
        mat.assign(1, 0, 1);
        Matrix mat_power = mat ^ (N - 1);
        int ans = mat_power.get(0, 0);
        return ans;
    }
};
